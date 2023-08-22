#include <iostream>
#include <iomanip>

const int Bufsize = 3000000;
const int Reslen = 32;

const uint64_t Lfsr[24] = {
    0x0000000000000001, 0x0000000000008082, 0x800000000000808A,
    0x8000000080008000, 0x000000000000808B, 0x0000000080000001,
    0x8000000080008081, 0x8000000000008009, 0x000000000000008A,
    0x0000000000000088, 0x0000000080008009, 0x000000008000000A,
    0x000000008000808B, 0x800000000000008B, 0x8000000000008089,
    0x8000000000008003, 0x8000000000008002, 0x8000000000000080,
    0x000000000000800A, 0x800000008000000A, 0x8000000080008081,
    0x8000000000008080, 0x0000000080000001, 0x8000000080008008,
};

// Ref: https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.202.pdf
const int Rho_ofs[5][5] = {
    {  0, 36,  3, 41, 18 },
    {  1, 44, 10, 45,  2 },
    { 62,  6, 43, 15, 61 },
    { 28, 55, 25, 21, 56 },
    { 27, 20, 39,  8, 14 },
};

uint64_t shift_left(uint64_t x, int ofs) { return (x << ofs) | (x >> (64 - ofs)); }

void theta(uint64_t A[5][5]) {
    uint64_t res[5], parity[5];

    for (int i = 0; i < 5; i++)
        parity[i] = A[i][0] ^ A[i][1] ^ A[i][2] ^ A[i][3] ^ A[i][4];
    
    for (int i = 0; i < 5; i++)
        res[i] = parity[(i + 4) % 5] ^ shift_left(parity[(i + 1) % 5], 1);
    
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++) 
            A[i][j] ^= res[i];
}


void rho(uint64_t A[5][5]) {
    uint64_t res[5][5];
    res[0][0] = A[0][0];
    int i = 1, j = 0;
    for (int t = 0; t < 24; t++) {
        res[i][j] = shift_left(A[i][j], Rho_ofs[i][j]);
        int tmp = j;
        j = (2 * i + 3 * j) % 5;
        i = tmp;
    }
    memcpy(A, res, sizeof(res));
}

void pi(uint64_t A[5][5]) {
    uint64_t res[5][5];
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            res[i][j] = A[(i + 3 * j) % 5][i];
    memcpy(A, res, sizeof(res));
}

void chi(uint64_t A[5][5]) {
    uint64_t res[5][5];
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            res[i][j] = A[i][j] ^ ((~A[(i + 1) % 5][j]) & A[(i + 2) % 5][j]);
    memcpy(A, res, sizeof(res));
}

void iota(uint64_t A[5][5], int ir) { A[0][0] ^= Lfsr[ir]; }

void keccak_p(uint8_t *src, int b = 1600, int nr = 24) {
    uint64_t A[5][5]; // 64 bits * 5 * 5 = 1600 bits
    int w = b / 25 / 8;
    for (int y = 0; y < 5; y++)
        for (int x = 0; x < 5; x++)
            memcpy(&A[x][y], src + (5 * y + x) * w, w);

    for (int ir = 24 - nr; ir < 24; ir++) { // l = log2(64 bits) = 6, 12 + 2 *l = 24
        theta(A);
        rho(A);
        pi(A);
        chi(A);
        iota(A, ir);
    }

    for (int y = 0; y < 5; y++)
        for (int x = 0; x < 5; x++)
            memcpy(src + (5 * y + x) * w, &A[x][y], w);
}

int pad10x1(uint8_t *src, int r, int len) { // bytes
    int padlen = r - len % r;

    memset(src + len, 0, padlen);
    src[len] |= 0x06;
    src[len + padlen - 1] |= 0x80;

    return len + padlen;
}

void sha3_256(uint8_t *src, int slen) {
    int b = 200, c = 64, r = 136, d = 32; /* 1600/8 = 200 bytes, 512/8 = 64 bytes */
    int len = pad10x1(src, r, slen);
    int rcnt = len / r;

    uint8_t *state = new uint8_t[b];
    memset(state, 0, b);
    for (int i = 0; i < rcnt; i++) {
        for (int j = 0; j < r; j++)
            state[j] ^= src[i * r + j];
        keccak_p(state);
    }
    // No need to squeeze, as r >> d.
    memcpy(src, state, d);
}

int main() {
    char src[Bufsize + 200]; /* buffer for padding */
    std::ios::sync_with_stdio(false);
    std::cin.tie(0); 
    std::cout.tie(0);

    std::cerr << "Input plaintext: ";
    std::cin.getline(src, Bufsize);

    // timer
    clock_t start, end;
    start = clock();

    int len = strlen(src);
    sha3_256((uint8_t *)src, len);

    end = clock();
    double encrypt_time = (double)(end - start) / CLOCKS_PER_SEC;

    std::cout << "SHA3-256 Hash: ";
    for (int i = 0; i < Reslen; i++) {
        std::cout << std::setw(2) << std::setfill('0') << std::hex
            << static_cast<int>(static_cast<unsigned char>(src[i]));
    }

    std::cerr << "\n";
    std::cerr << "========== Hash ==========\n";
    std::cerr << "Length:    " << std::setw(9) << len << " bytes\n";
    std::cerr << "Time cost: " << std::setw(9) << encrypt_time * 1000 << " ms\n";
    std::cerr << "Bit rate:  " << std::setw(9) << (double)len * 8 / encrypt_time / 1024 / 1024 << " Mbps\n";
    std::cerr << "==========================\n";

    return 0;
}
