#include <iostream>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <array>
#include <vector>
#include <inttypes.h>

enum X {A, B, C};
enum XY {AB, BC, CA};

#define COUNT_VICTORIES(str, numX, numXY) \
    do { \
        unsigned permutationSize = str.length(); \
        for (unsigned i = 0; i < permutationSize; i++){ \
            switch(str[i]){ \
                case 'A': \
                    numX[A]++; \
                    numXY[AB] += numX[B]; \
                    break; \
                case 'B': \
                    numX[B]++; \
                    numXY[BC] += numX[C]; \
                    break; \
                case 'C': \
                    numX[C]++; \
                    numXY[CA] += numX[A]; \
                    break; \
            } \
        } \
    } while(0)

/* Predicate function: Tests if a char* str has the char d */
inline bool
has(char c, std::string str) {
    for (char d : str) if (d == c) return true;
    return false;
}

/* Auxiliary function for prefixes(unsigned): Returns a std::vector<char>
   containing the valid extensions for a certain char* prefix str. */
inline std::vector<char>
extensions(std::string str) {
    std::vector<char> extensionVector = { 'A', 'B' };
    if (has('B', str)) extensionVector.emplace_back('C');
    return extensionVector;
}

/* Returns a std::vector<char*> with all prefixes of size uint n */
inline std::vector<std::string>
prefixes(unsigned n) {
    std::vector<std::string> prefixVector = { "A" };
    for (unsigned i = 1; i < n; i++) {
        std::vector<std::string> temp = {};
        for (std::string str : prefixVector)
            for (char extension : extensions(str))
                temp.emplace_back(str + extension);
        prefixVector = temp;
    }
    return prefixVector;
}

/* Predicate function: Tests if the std::string permutation is intransitive */
inline bool
intransitive (std::string permutation,
              unsigned n,
              std::array<uint16_t, 3> numX,
              std::array<uint16_t, 3> numXY) {
    unsigned n2 = n*n;
    unsigned permutationSize = permutation.length();

    /* count the number of vitories and perform an early exit if it's too bad */
    for (unsigned i = 0; i < permutationSize; i++){
        switch(permutation[i]){
            case 'A':
                numX[A]++;
                numXY[AB] += numX[B];
                break;
            case 'B':
                numX[B]++;
                numXY[BC] += numX[C];
                break;
            case 'C':
                numX[C]++;
                numXY[CA] += numX[A];
                break;
        }
        if((2*(numX[A] * n - numXY[AB]) >= n2 and
            2*(numXY[CA] + (n - numX[C]) * numX[A]) >= n2 or
           (2*(numX[B] * n - numXY[BC]) >= n2 and
            2*(numXY[AB] + (n - numX[A]) * numX[B]) >= n2) or
           (2*(numX[C] * n - numXY[CA]) >= n2 and
            2*(numXY[BC] + (n - numX[B]) * numX[C]) >= n2))) return 0;
    }
    return ((2*numXY[AB] > n2 and 2*numXY[BC] > n2 and 2*numXY[CA] > n2) or
            (2*numXY[AB] < n2 and 2*numXY[BC] < n2 and 2*numXY[CA] < n2));
}

int main(void) {
    std::cout << std::setprecision(10) << std::fixed;

    for (unsigned n = 3; n < 9; n++) {
        auto start = std::chrono::high_resolution_clock::now();
        uint64_t numT = 0;

        std::vector<std::string> ps = prefixes(n);

        #pragma omp parallel for reduction(+:numT)
        for(std::string prefix : prefixes(n)){
            uint64_t numTacc = 0;
            std::array<uint16_t, 3> numX = {0, 0, 0};
            std::array<uint16_t, 3> numXY = {0, 0, 0};

            COUNT_VICTORIES(prefix, numX, numXY);

            unsigned n2 = n*n;
            if((2*(numX[A] * n - numXY[AB]) >= n2 and
                2*(numXY[CA] + (n - numX[C]) * numX[A]) >= n2) or
               (2*(numX[B] * n - numXY[BC]) >= n2 and
                2*(numXY[AB] + (n - numX[A]) * numX[B]) >= n2) or
               (2*(numX[C] * n - numXY[CA]) >= n2 and
                2*(numXY[BC] + (n - numX[B]) * numX[C]) >= n2)
             or(numX[A] == numX[B] and 2 * numX[A] == n)) continue;

             std::string str = std::string(n - numX[A], 'A')
                             + std::string(n - numX[B], 'B')
                             + std::string(n - numX[C], 'C');
            /* Increment the numTacc if str is intransitive */
            do numTacc += intransitive(str, n, numX, numXY);
            while (std::next_permutation(str.begin(), str.end()));
            /* Stop if there's no next lexicographically ordered permutation */
            numT += 3*numTacc;
        }

        auto stop = std::chrono::high_resolution_clock::now();
        typedef std::chrono::milliseconds ms;
        double duration = std::chrono::duration_cast<ms>(stop - start).count();
        std::cout << std::endl
                  << "    T(" << n << ") = " << numT
                  << std::endl
                  << "    Elapsed time: " << duration/1000 << "s"
                  << std::endl;
    }

    return 0;
}

