#include <bits/stdc++.h>
using namespace std;

vector<int> Rice_Prime;
const long long MAX = 1000000000LL;
const int WHEEL = 3 * 5 * 7 * 11 * 13;
const int N_SMALL_PRIMES = 6536;
const int SIEVE_SPAN = WHEEL * 64;
const int SIEVE_SIZE = SIEVE_SPAN / 128 + 1;

uint64_t ONES[64];
int small_primes[N_SMALL_PRIMES];
uint64_t si[SIEVE_SIZE];
uint64_t pattern[WHEEL];

inline void mark(uint64_t *s, int o) { s[o >> 6] |= ONES[o & 63]; }
inline int test(uint64_t *s, int o) { return (s[o >> 6] & ONES[o & 63]) == 0; }

void update_sieve(int offset)
{
    for (int i = 0, k; i < SIEVE_SIZE; i += k)
    {
        k = std::min(WHEEL, SIEVE_SIZE - i);
        memcpy(si + i, pattern, sizeof(*pattern) * k);
    }

    if (offset == 0)
    {
        si[0] |= ONES[0];
        si[0] &= ~(ONES[1] | ONES[2] | ONES[3] | ONES[5] | ONES[6]);
    }

    for (int i = 0; i < N_SMALL_PRIMES; ++i)
    {
        int j = small_primes[i] * small_primes[i];
        if (j > offset + SIEVE_SPAN - 1)
            break;
        if (j > offset)
            j = (j - offset) >> 1;
        else
        {
            j = small_primes[i] - offset % small_primes[i];
            if ((j & 1) == 0)
                j += small_primes[i];
            j >>= 1;
        }
        while (j < SIEVE_SPAN / 2)
        {
            mark(si, j);
            j += small_primes[i];
        }
    }
}

void sieve()
{
    for (int i = 0; i < 64; ++i)
        ONES[i] = 1ULL << i;

    for (int i = 3; i < 256; i += 2)
    {
        if (test(si, i >> 1))
        {
            for (int j = i * i / 2; j < 32768; j += i)
                mark(si, j);
        }
    }
    {
        int m = 0;
        for (int i = 8; i < 32768; ++i)
        {
            if (test(si, i))
                small_primes[m++] = i * 2 + 1;
        }
        assert(m == N_SMALL_PRIMES);
    }

    for (int i = 1; i < WHEEL * 64; i += 3)
        mark(pattern, i);
    for (int i = 2; i < WHEEL * 64; i += 5)
        mark(pattern, i);
    for (int i = 3; i < WHEEL * 64; i += 7)
        mark(pattern, i);
    for (int i = 5; i < WHEEL * 64; i += 11)
        mark(pattern, i);
    for (int i = 6; i < WHEEL * 64; i += 13)
        mark(pattern, i);

    for (int offset = 0; offset < MAX; offset += SIEVE_SPAN)
    {
        update_sieve(offset);

        for (uint32_t j = 0; j < SIEVE_SIZE; j++)
        {
            uint64_t x = ~si[j];
            while (x)
            {
                uint32_t p = offset + (j << 7) + (__builtin_ctzll(x) << 1) + 1;
                if (p > offset + SIEVE_SPAN - 1)
                    break;
                if (p <= MAX)
                {
                    Rice_Prime.push_back(p);
                }
                x ^= (-x & x);
            }
        }
    }
}

const int N = 1e9 + 1;
bitset<N> sang;
vector<int> primes;

void sieve2()
{
    primes.reserve(5.1e8);
    primes.emplace_back(2);
    int SQRT = sqrt(N);
    for (int i = 3; i <= SQRT; i += 2)
    {
        if (!sang[i])
            continue;
        for (int j = i * i; j < N; j += (i << 1))
            sang[j] = 1;
    }

    for (int i = 3; i < N; i += 2)
    {
        if (!sang[i])
            primes.emplace_back(i);
    }
}

void sieve3()
{
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    sieve2();
    auto stop = std::chrono::high_resolution_clock::now();

    // Tính toán thời gian chạy (ở đây đang dùng milliseconds - mili giây)
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "Thoi gian chay: " << duration.count() << " ms" << std::endl;
    cout << primes.size() << '\n';
    std::cout << "hehe";
}