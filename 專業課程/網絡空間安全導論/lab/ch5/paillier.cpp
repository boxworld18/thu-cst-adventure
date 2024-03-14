#include <iostream>
#include <iomanip>
#include <random>
#include <gmpxx.h>

using namespace std;
const int Prime_Bits = 1024;

struct PublicKey {
    mpz_class n, g;
};

struct PrivateKey {
    mpz_class lambda, mu;
};

class MyMpz {
public:
    mpz_class gen_random_number(int bits = Prime_Bits) {
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

    mpz_class gen_prime(int bits = Prime_Bits) {
        bits--;
        mpz_class res, low;

        // scale the random number to the range [low, high]
        res = gen_random_number(bits);
        mpz_ui_pow_ui(low.get_mpz_t(), 2, bits);
        res += low;

        // make sure the number is odd
        mpz_nextprime(res.get_mpz_t(), res.get_mpz_t());

        return res;
    }
};

class Paillier {
private:
    PublicKey puk;
    PrivateKey prk;
    MyMpz mpz;
    mpz_class max_voter;
    int max_candidate;

public:
    Paillier(int mtv, int mca): max_voter(mtv), max_candidate(mca) {
        mpz_class p, q, n, lambda, g, mu;
        p = mpz.gen_prime();
        q = mpz.gen_prime();
        n = p * q;

        mpz_class p_ = p - 1, q_ = q - 1;
        mpz_lcm(lambda.get_mpz_t(), p_.get_mpz_t(), q_.get_mpz_t());
        
        mpz_class n2 = n * n, x;
        g = mpz.gen_random_number(Prime_Bits * 2);
        mpz_powm(x.get_mpz_t(), g.get_mpz_t(), lambda.get_mpz_t(), n2.get_mpz_t());
        
        x = (x - 1) / n;
        mpz_invert(mu.get_mpz_t(), x.get_mpz_t(), n.get_mpz_t());

        puk.n = n;
        puk.g = g;
        prk.lambda = lambda;
        prk.mu = mu;
    }

    PublicKey get_key() {
        return puk;
    }

    mpz_class decrypt(mpz_class cipher) {
        mpz_class n = puk.n, lambda = prk.lambda, mu = prk.mu;
        mpz_class n2 = n * n;
        mpz_class tmp1;
        mpz_powm(tmp1.get_mpz_t(), cipher.get_mpz_t(), lambda.get_mpz_t(), n2.get_mpz_t());

        mpz_class m;
        m = ((tmp1 - 1) / n * mu) % n;

        // cerr << "Cipher:  " << cipher.get_str() << endl;
        // cerr << "Message: " << m.get_str() << endl;
        return m;
    }

    void get_result(mpz_class cipher) {
        mpz_class m = decrypt(cipher);
        cout << "====== RESULT ======\n";
        for (int i = 1; i <= max_candidate; i++) {
            cout << "Cand# " << std::setw(3) << i << ": " << std::setw(8) << m % max_voter << endl;
            m = m / max_voter;
        }
        cout << "====================\n";
    }
};

class VoteSystem {
private:
    mpz_class max_voter;
    int max_candidate, mode;
    PublicKey puk;
    MyMpz mpz;

    mpz_class _encrypt(mpz_class m, PublicKey k) {
        mpz_class n = k.n, g = k.g;
        mpz_class n2 = n * n;
        mpz_class r = mpz.gen_random_number(Prime_Bits * 2 - 2);

        mpz_class tmp1, tmp2;
        mpz_powm(tmp1.get_mpz_t(), g.get_mpz_t(), m.get_mpz_t(), n2.get_mpz_t());
        mpz_powm(tmp2.get_mpz_t(), r.get_mpz_t(), n.get_mpz_t(), n2.get_mpz_t());

        mpz_class c;
        c = tmp1 * tmp2 % n2;
        return c;
    }

public:
    VoteSystem(PublicKey k, int mvt, int mca, int md): puk(k), max_voter(mvt), max_candidate(mca) {
        mode = (md == 1) ? 0 : 1;
    }

    string vote() {
        int cid;
        if (mode) cerr << "Your vote is: ";
        cin >> cid;
        if (cid <= 0 || cid > max_candidate) {
            if (mode) cerr << "Invalid vote!" << endl;
            cerr << "Start Counting!!!" << endl;
            return "Exit";
        }
        mpz_class offset;
        mpz_pow_ui(offset.get_mpz_t(), max_voter.get_mpz_t(), cid - 1);
        return _encrypt(offset, puk).get_str();
    }

    mpz_class start_vote() {
        mpz_class result = 1;

        while (true) {
            string vo = vote();
            if (vo == "Exit") break;
            // if (mode) cerr << "Cipher: " << vo << endl;
            result *= mpz_class(vo);
        }

        return result;
    }
};

int main(int argc, char *argv[]) {
    int max_voter = 1e6;
    int max_candidate = 10;
    Paillier paillier(max_voter, max_candidate);
    PublicKey puk = paillier.get_key();
    VoteSystem system(puk, max_voter, max_candidate, argc);

    clock_t start, end;
    start = clock();

    mpz_class res = system.start_vote();
    
    end = clock();

    paillier.get_result(res);

    double time_cost = (double)(end - start) / CLOCKS_PER_SEC;
    cerr << "Time cost: " << setw(8) << time_cost << " s\n";

    return 0;
}