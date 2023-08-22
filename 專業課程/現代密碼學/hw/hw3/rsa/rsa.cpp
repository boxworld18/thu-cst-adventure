#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <gmpxx.h>

const int Prime_Bits = 1024;
const int Rsa_bits = 2048;

class RSA {
private:
    int Pr[1500], Prcnt;
    int bits, elen, dlen;
    mpz_class n, d, e;

    // gen all prime numbers less than 10000
    void _gen_10k_prime() {
        Prcnt = 0;
        for (int i = 2; i < 10000; i++) {
            bool is_prime = true;
            for (int j = 2; j * j <= i; j++)
                if (i % j == 0) {
                    is_prime = false;
                    break;
                }
            if (is_prime)
                Pr[Prcnt++] = i;
        }
    }

    mpz_class _gen_random_number(int bits = Prime_Bits) {
        mpz_class res;
        // initialize random number generator
        gmp_randstate_t rstate;
        std::random_device rd;
        gmp_randinit_mt(rstate);
        gmp_randseed_ui(rstate, rd());
        mpz_urandomb(res.get_mpz_t(), rstate, bits);
        gmp_randclear(rstate);
        return res;
    }

    bool _miller_rabin(mpz_class tar, int bits = Prime_Bits, int rnd = 50) {
        // 1. factorization tar-1
        mpz_class r = tar - 1;
        int s = 0;
        while (r % 2 == 0) {
            r /= 2;
            s++;
        }

        // 2. test rnd rounds
        for (int t = 0; t < rnd; t++) {
            mpz_class a = _gen_random_number(bits - 1) + 2;
            mpz_class y;
            mpz_powm(y.get_mpz_t(), a.get_mpz_t(), r.get_mpz_t(), tar.get_mpz_t());
            if (y == 1 || y == tar - 1) continue;
            for (int j = 0; j < s; j++) {
                y = y * y % tar;
                if (y == 1) return false;
                if (y == tar - 1) break;
            }
            if (y != tar - 1) return false;
        }

        return true;
    }

    bool _check_prime(mpz_class tar, int bits = Prime_Bits) {
        // 1. use small primes to check
        for (int i = 0; i < Prcnt; i++) {
            if (Pr[i] * Pr[i] > tar)
                return true;
            if (tar % Pr[i] == 0)
                return false;
        }
        
        // 2. use miller-rabin to check
        return _miller_rabin(tar, bits);
    }

    mpz_class _gen_prime(int bits = Prime_Bits) {
        bits--;
        mpz_class res, low;

        // scale the random number to the range [low, high]
        res = _gen_random_number(bits);
        mpz_ui_pow_ui(low.get_mpz_t(), 2, bits);
        res += low;

        // make sure the number is odd
        if (res % 2 == 0) res += 1;
        while (!_check_prime(res, bits)) res += 2;

        return res;
    }

    // Ref: https://oi-wiki.org/math/number-theory/inverse/
    void _exgcd(mpz_class a, mpz_class b, mpz_class &x, mpz_class &y) {
        if (b == 0) {
            x = 1; y = 0;
            return;
        }
        _exgcd(b, a % b, y, x);
        y -= (a / b) * x;
    }

    mpz_class _convert2mpz(const std::string &str) {
        mpz_class res;
        int len = str.length();
        std::stringstream ss;
        for (int i = 0; i < len; i++)
            ss << std::hex << (int)str[i];
        
        mpz_set_str(res.get_mpz_t(), ss.str().c_str(), 16);
        return res;
    }

    int _hex2dec(const char chr) {
        if (chr >= '0' && chr <= '9') return chr - '0';
        if (chr >= 'a' && chr <= 'f') return chr - 'a' + 10;
        if (chr >= 'A' && chr <= 'F') return chr - 'A' + 10;
        return 0;
    }

    std::string _convert2str(const mpz_class &dec) {
        std::string src = dec.get_str(16);
        int len = src.length();
        if (len % 2 != 0) src = '0' + src, len += 1;

        std::string res;
        for (int i = 0; i < len; i += 2) {
            int id = _hex2dec(src[i]) * 16 + _hex2dec(src[i + 1]);
            res += (char)id;
        }

        return res;
    }

public:
    mpz_class _encrypt(const mpz_class &m) {
        mpz_class res;
        mpz_powm(res.get_mpz_t(), m.get_mpz_t(), e.get_mpz_t(), n.get_mpz_t());
        return res;
    }

    mpz_class _decrypt(const mpz_class &m) {
        mpz_class res;
        mpz_powm(res.get_mpz_t(), m.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t());
        return res;
    }

public:
    RSA(int bits_ = Rsa_bits): bits(bits_), elen(bits / 8 - 11), dlen(bits / 4) {
        _gen_10k_prime();
        mpz_class p = _gen_prime(bits / 2);
        mpz_class q = _gen_prime(bits / 2);
        n = p * q;
        e = 65537;

        mpz_class phi = (p - 1) * (q - 1);
        mpz_class tmp;
        _exgcd(e, phi, d, tmp);
        if (d < 0) d += phi;

        std::cerr << "N = " << n.get_str().c_str() << std::endl;
        std::cerr << "e = " << e.get_str().c_str() << std::endl;
        std::cerr << "d = " << d.get_str().c_str() << std::endl;
    }

    std::string encrypt(std::string &msg) {
        std::string res;
        int len = msg.length();
        
        std::string src = msg;
        // RSA - No padding
        while (len % elen != 0) {
            src = char(0) + src;
            len++;
        }

        for (int i = 0; i < len; i += elen) {
            std::string tmp = src.substr(i, elen);
            std::string enc = _encrypt(_convert2mpz(tmp)).get_str(16);
            while (enc.length() < dlen) enc = '0' + enc;
            res += enc;
        }

        return res;
    }

    std::string decrypt(std::string &msg) {
        std::string res;
        int len = msg.length();
        for (int i = 0; i < len; i += dlen) {
            std::string tmp = msg.substr(i, dlen);
            mpz_class num;
            mpz_set_str(num.get_mpz_t(), tmp.c_str(), 16);
            res += _convert2str(_decrypt(num));
        }
        return res;
    }
};

int main() {
    RSA rsa;

    std::string src;
    std::ios::sync_with_stdio(false);
    std::cin.tie(0); 
    std::cout.tie(0);

    std::cerr << "Input plaintext: ";
    std::getline(std::cin, src);

    // timer
    clock_t start, end;
    start = clock();

    int len = src.length();
    std::string res = rsa.encrypt(src);
    // std::cerr << "Ciphertext: " << res << std::endl;

    end = clock();
    double encrypt_time = (double)(end - start) / CLOCKS_PER_SEC;

    std::cerr << "\n";
    std::cerr << "======== Encrypt ========\n";
    std::cerr << "Length:    " << std::setw(8) << len << " bytes\n";
    std::cerr << "Time cost: " << std::setw(8) << encrypt_time * 1000 << " ms\n";
    std::cerr << "Bit rate:  " << std::setw(8) << (double)len * 8 / encrypt_time / 1024 / 1024 << " Mbps\n";
    std::cerr << "=========================\n";

    int len2 = res.length();
    start = clock();

    std::string dec = rsa.decrypt(res);
    std::cout << "Plaintext:  " << dec << std::endl;

    end = clock();
    double decrypt_time = (double)(end - start) / CLOCKS_PER_SEC;

    std::cerr << "======== Decrypt ========\n";
    std::cerr << "Length:    " << std::setw(8) << len2 << " bytes\n";
    std::cerr << "Time cost: " << std::setw(8) << decrypt_time << " s\n";
    std::cerr << "Bit rate:  " << std::setw(8) << (double)len2 * 8 / decrypt_time / 1024 / 1024 << " Mbps\n";
    std::cerr << "=========================\n";

    if (src == dec) std::cerr << "Correct!\n";
    else std::cerr << "Wrong!\n";

    return 0;
}
