#include <iostream>
#include <iomanip>

const uint8_t S_Box[] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

const uint8_t Inv_S_Box[] = {
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

const int Rcon[] = {0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};

const int Bsize = 16;
const int Rcount = 10;
const int Bufsize = 3000000;
const int KeyBuf = 100;

int pad(uint8_t *src, int len) {
    int pad_len = 16 - len % 16;
    for (int i = len; i < len + pad_len; i++)
        src[i] = pad_len;
    return len + pad_len;
}

int unpad(uint8_t *src, int len) {
    int pad_len = src[len - 1] & 0xff;
    for (int i = len - pad_len; i < len; i++)
        src[i] = 0;
    return len - pad_len;
}

void sub_bytes(uint8_t *src) {
    for (int i = 0; i < Bsize; i++)
        src[i] = S_Box[int(src[i])];
}

void inv_sub_bytes(uint8_t *src) {
    for (int i = 0; i < Bsize; i++)
        src[i] = Inv_S_Box[src[i]];
}

void shift_rows(uint8_t *src) {
    uint8_t tmp;
    tmp = src[4];
    src[4] = src[5];
    src[5] = src[6];
    src[6] = src[7];
    src[7] = tmp;

    tmp = src[8];
    src[8] = src[10];
    src[10] = tmp;
    tmp = src[9];
    src[9] = src[11];
    src[11] = tmp;

    tmp = src[12];
    src[12] = src[15];
    src[15] = src[14];
    src[14] = src[13];
    src[13] = tmp;
}

void inv_shift_rows(uint8_t *src) {
    uint8_t tmp;
    tmp = src[7];
    src[7] = src[6];
    src[6] = src[5];
    src[5] = src[4];
    src[4] = tmp;

    tmp = src[10];
    src[10] = src[8];
    src[8] = tmp;
    tmp = src[11];
    src[11] = src[9];
    src[9] = tmp;

    tmp = src[12];
    src[12] = src[13];
    src[13] = src[14];
    src[14] = src[15];
    src[15] = tmp;
}

inline uint8_t mul(uint8_t x) { return (x << 1) ^ (((x >> 7) & 1) * 0x1b); }
inline uint8_t mul9(uint8_t x) { return mul(mul(mul(x))) ^ x; }
inline uint8_t mul11(uint8_t x) { return mul(mul(mul(x)) ^ x) ^ x; }
inline uint8_t mul13(uint8_t x) { return mul(mul(mul(x) ^ x)) ^ x; }
inline uint8_t mul14(uint8_t x) { return mul(mul(mul(x) ^ x) ^ x); }

void mix_columns(uint8_t *src) {
    for (int i = 0; i < 4; i++) {
        uint8_t res = src[i] ^ src[i + 4] ^ src[i + 8] ^ src[i + 12];
        uint8_t tmp = src[i];
        src[i] = mul(src[i]) ^ mul(src[i + 4]) ^ src[i] ^ res;
        src[i + 4] = mul(src[i + 4]) ^ mul(src[i + 8]) ^ src[i + 4] ^ res;
        src[i + 8] = mul(src[i + 8]) ^ mul(src[i + 12]) ^ src[i + 8] ^ res;
        src[i + 12] = mul(src[i + 12]) ^ mul(tmp) ^ src[i + 12] ^ res;
    }
}

void inv_mix_columns(uint8_t *src) {
    for (int i = 0; i < 4; i++) {
        uint8_t tmp1 = src[i];
        uint8_t tmp2 = src[i + 4];
        uint8_t tmp3 = src[i + 8];
        uint8_t tmp4 = src[i + 12];
        src[i] = mul14(tmp1) ^ mul11(tmp2) ^ mul13(tmp3) ^ mul9(tmp4);
        src[i + 4] = mul14(tmp2) ^ mul11(tmp3) ^ mul13(tmp4) ^ mul9(tmp1);
        src[i + 8] = mul14(tmp3) ^ mul11(tmp4) ^ mul13(tmp1) ^ mul9(tmp2);
        src[i + 12] = mul14(tmp4) ^ mul11(tmp1) ^ mul13(tmp2) ^ mul9(tmp3);
    }
}

void add_round_key(uint8_t *src, const uint8_t *key) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < Bsize / 4; j++)
            src[i * 4 + j] ^= key[i + j * 4];
}

void convert(uint8_t *state) {
    uint8_t tmp;
    tmp = state[1];
    state[1] = state[4];
    state[4] = tmp;

    tmp = state[2];
    state[2] = state[8];
    state[8] = tmp;

    tmp = state[3];
    state[3] = state[12];
    state[12] = tmp;

    tmp = state[6];
    state[6] = state[9];
    state[9] = tmp;

    tmp = state[7];
    state[7] = state[13];
    state[13] = tmp;

    tmp = state[11];
    state[11] = state[14];
    state[14] = tmp;
}

void encrypt_block(uint8_t *state, const uint8_t *rnd_key) {
    convert(state);
    add_round_key(state, rnd_key);
    for (int j = 1; j < Rcount; j++) {
        sub_bytes(state);
        shift_rows(state);
        mix_columns(state);
        add_round_key(state, rnd_key + j * Bsize);
    }
    sub_bytes(state);
    shift_rows(state);
    add_round_key(state, rnd_key + Rcount * Bsize);
    convert(state);
}

void decrypt_block(uint8_t *state, const uint8_t *rnd_key) {
    convert(state);
    add_round_key(state, rnd_key + Rcount * Bsize);
    for (int j = Rcount - 1; j > 0; j--) {
        inv_shift_rows(state);
        inv_sub_bytes(state);
        add_round_key(state, rnd_key + j * Bsize);
        inv_mix_columns(state);
    }
    inv_shift_rows(state);
    inv_sub_bytes(state);
    add_round_key(state, rnd_key);
    convert(state);
}

void gen_key(const uint8_t *key, uint8_t *w) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            w[i * 4 + j] = key[i * 4 + j];
    
    for (int i = 4; i < 44; i++) {
        uint8_t tmp[4];
        for (int j = 0; j < 4; j++)
            tmp[j] = w[(i - 1) * 4 + j];
        
        if (i % 4 == 0) {
            uint8_t t = tmp[0];
            tmp[0] = S_Box[tmp[1]] ^ Rcon[i / 4];
            tmp[1] = S_Box[tmp[2]];
            tmp[2] = S_Box[tmp[3]];
            tmp[3] = S_Box[t];
        }

        for (int j = 0; j < 4; j++)
            w[i * 4 + j] = w[(i - 4) * 4 + j] ^ tmp[j];
    }
}

void xor_iv(uint8_t *src, const uint8_t *iv) {
    for (int i = 0; i < Bsize; i++)
        src[i] ^= iv[i];
}

int encrypt(uint8_t *state, uint8_t *key, uint8_t *iv, int len) {
    uint8_t rnd_key[44 * 4];
    gen_key(key, rnd_key);
    len = pad(state, len);
    int rnd = len / Bsize;

    uint8_t *rmd = iv;
    for (int i = 0; i < rnd; i++) {
        xor_iv(state + i * Bsize, rmd);
        encrypt_block(state + i * Bsize, rnd_key);
        rmd = state + i * Bsize;
    }

    return len;
}

int decrypt(uint8_t *state, uint8_t *key, uint8_t *iv, int len) {
    uint8_t rnd_key[44 * 4];
    gen_key(key, rnd_key);
    int rnd = len / Bsize;

    uint8_t *rmd = iv, *tmp = new uint8_t[Bsize];
    for (int i = 0; i < rnd; i++) {
        memcpy(tmp, state + i * Bsize, Bsize);
        decrypt_block(state + i * Bsize, rnd_key);
        xor_iv(state + i * Bsize, rmd);
        memcpy(rmd, tmp, Bsize);
    }

    return unpad(state, len);
}

/*
 * Generate random string
 * Ref: https://stackoverflow.com/a/440240
 * Author: Ates Goral
 */
std::string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i)
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    
    return tmp_s;
}

int main() {
    char src[Bufsize + 20], iv[KeyBuf], key[KeyBuf];
    std::ios::sync_with_stdio(false);
    std::cin.tie(0); 
    std::cout.tie(0);

    std::cerr << "Input plaintext: ";
    std::cin.getline(src, Bufsize);
    std::cerr << "Input key: ";
    std::cin.getline(key, KeyBuf);
    assert(strlen(key) == 16);
    std::cerr << "Input iv (can be empty): ";
    std::cin.getline(iv, KeyBuf);

    if (strlen(iv) != 16) {
        srand((unsigned)time(NULL));     
        memcpy(iv, gen_random(16).c_str(), 16);
        std::cerr << "==== Extra Info ====\n";
        std::cerr << "Auto Generated Iv: " << iv << "\n";
        std::cerr << "\n";
    }

    // timer
    clock_t start, end;
    start = clock();

    int olen = strlen(src);
    int len = encrypt((uint8_t *)src, (uint8_t *)key, (uint8_t *)iv, olen);

    end = clock();
    double encrypt_time = (double)(end - start) / CLOCKS_PER_SEC;

    std::cout << "Cipher: \n";
    for (int i = 0; i < len; i++) {
        std::cout << std::setw(2) << std::setfill('0') << std::hex
            << static_cast<int>(static_cast<unsigned char>(src[i]));
        if (i % 16 == 15)
            std::cout << "\n";
    }

    std::cerr << "\n";
    std::cerr << "======== Encrypt ========\n";
    std::cerr << "Length:    " << std::setw(8) << olen << " bytes\n";
    std::cerr << "Time cost: " << std::setw(8) << encrypt_time * 1000 << " ms\n";
    std::cerr << "Bit rate:  " << std::setw(8) << (double)len * 8 / encrypt_time / 1024 / 1024 << " Mbps\n";
    std::cerr << "=========================\n";

    start = clock();
    int nlen = decrypt((uint8_t *)src, (uint8_t *)key, (uint8_t *)iv, len);
    end = clock();

    double decrypt_time = (double)(end - start) / CLOCKS_PER_SEC;

    std::cout << "Decrypted: \n";
    for (int i = 0; i < nlen; i++) {
        std::cout << src[i];
        if (i % 16 == 15)
            std::cout << "\n";
    }

    std::cout << "\n";

    std::cerr << "======== Decrypt ========\n";
    std::cerr << "Length:    " << std::setw(8) << len << " bytes\n";
    std::cerr << "Time cost: " << std::setw(8) << decrypt_time * 1000 << " ms\n";
    std::cerr << "Bit rate:  " << std::setw(8) << (double)len * 8 / decrypt_time / 1024 / 1024 << " Mbps\n";
    std::cerr << "=========================\n";

    return 0;
}
