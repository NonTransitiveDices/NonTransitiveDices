#include <iostream>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <array>
#include <vector>
#include <inttypes.h>

enum X {A, B, C};
enum XY {AB, BC, CA};

#define GENERATE_GAME(numX) \
    (std::string(numX[A], 'A')+std::string(numX[B], 'B')+std::string(numX[C], 'C'))

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
   containing the valid extensions for a certain char* prefix
   str. */
inline std::vector<char>
extensions(std::string str) {
    std::vector<char> extensionVector = { 'A', 'B' };
    if (has('B', str)) extensionVector.emplace_back('C');
    return extensionVector;
}

/* Returns a std::vector<char*> with all prefixes of size uint */
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

/* Returns a std::vector<unsigned> of three entries, which correspond
   to the amount of occurences of the chars 'A', 'B' and 'C' on the
   char* str */
inline std::vector<unsigned>
countX(std::string str) {
    std::vector<unsigned> X = {0, 0, 0};
    for (char c : str)
        switch (c) {
            case 'A':
                X[A]++;
                break;
            case 'B':
                X[B]++;
                break;
            case 'C':
                X[C]++;
                break;
        }
    return X;
}

/* Predicate function: Tests if the char* permutation is intransitive */
inline bool
intransitive (std::string permutation,
              unsigned n,
              uint16_t *numX,
              uint16_t *numXY) {
    int n2 = n*n;
    // L: we dont need this anymore
    //COUNT_VICTORIES(permutation, numX, numXY);
    unsigned permutationSize = permutation.length();
    
    // L: count the number of vitories and stop immediately if the str is too bad, performing an early exit.
    unsigned numY[3]={n-numX[A], n-numX[B], n-numX[C]};
        for (unsigned i = 0; i < permutationSize; i++){
            switch(permutation[i]){
                case 'A':
                    numX[A]++;
                    numY[A]--;
                    numXY[AB] += numX[B];
                    break;
                case 'B':
                    numX[B]++;
                    numY[B]--;
                    numXY[BC] += numX[C];
                    break;
                case 'C':
                    numX[C]++;
                    numY[C]--;
                    numXY[CA] += numX[A];
                    break;
            }
            // L: checking if the string is too bad. Im not sure if checking only every other char of the string did anything for the optimization
            if((2*(numXY[A]+numY[A]*n)<=n2 and 2*(numXY[C]+numY[C]*numX[A])>=n2
             or(2*(numXY[B]+numY[B]*n)<=n2 and 2*(numXY[A]+numY[A]*numX[B])>=n2)
             or(2*(numXY[C]+numY[C]*n)<=n2 and 2*(numXY[B]+numY[B]*numX[C])>=n2))) return 0;
        }
    return ((2*numXY[AB] > n2 and
             2*numXY[BC] > n2 and
             2*numXY[CA] > n2)
          or(2*numXY[AB] < n2 and
             2*numXY[BC] < n2 and
             2*numXY[CA] < n2));
}

// L: Instead of computing COUNT_VICTORIES(prefix, numX, numXY) for every str, we can precompute it and pass numX, numXY as an argument of the function. This saves a lot of time.
// L: the problem is that intransitive(str, n, numX, numXY) receives the pointers to numX and numXY, so I chose to instanciate a copy
inline void
scan_games (std::string prefix,
            std::string str,
            uint64_t &numT,
            unsigned n,
            uint16_t numX[3],
            uint16_t numXY[3]) {

    while (true) {
        // L: instanciating a copy of numX and numXY
        uint16_t numA[3] = { numX[A], numX[B], numX[C] };
        uint16_t numAB[3] = { numXY[AB], numXY[BC], numXY[CA] };
        numT += intransitive(str, n, numA, numAB);


        /* find the next lexicographically ordered permutation
           if no such permutation exists, we are done in this prefix */
        if (!std::next_permutation(str.begin(), str.end())) break;
    }
}

// Driver code
int main(void) {
    std::cout << std::setprecision(10) << std::fixed;

    for (unsigned n = 3; n < 9; n++) {
        auto start = std::chrono::high_resolution_clock::now();
        uint64_t numT = 0;

        std::vector<std::string> ps = prefixes(n);

        #pragma omp parallel for reduction(+:numT)
        for(std::string prefix : prefixes(n)){
            uint64_t numTacc = 0;
            uint16_t numX[3] = {0, 0, 0};
            uint16_t numXY[3] = {0, 0, 0};

            COUNT_VICTORIES(prefix, numX, numXY);
            std::vector<unsigned> numY = {n - numX[A], n - numX[B], n - numX[C]};

            unsigned n2 = n*n;
            if((2*(numXY[AB]+numY[AB]*n) <= n2 and 2*(numXY[CA]+numY[CA]*numX[AB]) >= n2)
             or(2*(numXY[BC]+numY[BC]*n) <= n2 and 2*(numXY[AB]+numY[AB]*numX[BC]) >= n2)
             or(2*(numXY[CA]+numY[CA]*n) <= n2 and 2*(numXY[BC]+numY[BC]*numX[CA]) >= n2)
             or(numX[A] == numX[B] and numX[A] == numY[A]))
             {
                continue;
             }
            scan_games(prefix, GENERATE_GAME(numY), numTacc, n, numX, numXY);
            numT += 3*numTacc;
        }

        std::cout << "    T(" << n << ") = " << numT << std::endl;

        auto stop = std::chrono::high_resolution_clock::now();

        std::cout << "    Elapsed time: "
                  << (double) std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count()/1000
                  << "s" << std::endl;
    }

    return 0;
}

