#include <iostream>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <inttypes.h>

using namespace std::chrono;

using namespace std;
 
// Returns true if str[curr] does not matches with any of the
// characters after str[start]
string
generateGame (int *numABC)
{
    string a = "", b = "", c = "";
    for(int i = 0; i < numABC[0]; i++) a+= "A";
    for(int i = 0; i < numABC[1]; i++) b+= "B";
    for(int i = 0; i < numABC[2]; i++) c+= "C";
    return a+b+c;
}

bool
intransitivep (string permutation, int n)
{
    int threshold = n*n;
    int numA = 0,  numB = 0,  numC = 0;
    int numAB = 0, numBC = 0, numCA = 0;

    uint64_t permutationSize = permutation.size();
    for (uint64_t i = 0; i < permutationSize; i++){
        switch(permutation[i]){
            case 'A':
                numA++;
                numAB += numB;
                break;
            case 'B':
                numB++;
                numBC += numC;
                break;
            case 'C':
                numC++;
                numCA += numA;
                break;
        }
    }
    return ((2*numAB > threshold and
             2*numBC > threshold and
             2*numCA > threshold)
          or(2*numAB < threshold and
             2*numBC < threshold and
             2*numCA < threshold));
}

void
scan_games (string prefix,
            string str,
            uint64_t &numT,
            uint64_t &numD,
            int n)
{
    while (true)
    {
        // print the current permutation
        numD++;
        if(intransitivep(prefix+str, n)) numT++;

        // find the next lexicographically ordered permutation
        if (!next_permutation(str.begin(), str.end())) {
            break;
        }
    }
}

// Driver code
int
main()
{
    cout << setprecision(10) << fixed;

    auto start = high_resolution_clock::now();
    for(int n = 10; n <= 10; n++)
    {
        uint64_t numD=0;
        uint64_t numT = 0;

        string prefix[] = {
            "AAAAAA", "AAAAAB", "AAAABA", "AAAABB",
            "AAAABC", "AAABAA", "AAABAB", "AAABAC",
            "AAABBA", "AAABBB", "AAABBC", "AAABCA",
            "AAABCB", "AAABCC", "AABAAA", "AABAAB",
            "AABAAC", "AABABA", "AABABB", "AABABC",
            "AABACA", "AABACB", "AABACC", "AABBAA",
            "AABBAB", "AABBAC", "AABBBA", "AABBBB",
            "AABBBC", "AABBCA", "AABBCB", "AABBCC",
            "AABCAA", "AABCAB", "AABCAC", "AABCBA",
            "AABCBB", "AABCBC", "AABCCA", "AABCCB",
            "AABCCC", "ABAAAA", "ABAAAB", "ABAAAC",
            "ABAABA", "ABAABB", "ABAABC", "ABAACA",
            "ABAACB", "ABAACC", "ABABAA", "ABABAB",
            "ABABAC", "ABABBA", "ABABBB", "ABABBC",
            "ABABCA", "ABABCB", "ABABCC", "ABACAA",
            "ABACAB", "ABACAC", "ABACBA", "ABACBB",
            "ABACBC", "ABACCA", "ABACCB", "ABACCC",
            "ABBAAA", "ABBAAB", "ABBAAC", "ABBABA",
            "ABBABB", "ABBABC", "ABBACA", "ABBACB",
            "ABBACC", "ABBBAA", "ABBBAB", "ABBBAC",
            "ABBBBA", "ABBBBB", "ABBBBC", "ABBBCA",
            "ABBBCB", "ABBBCC", "ABBCAA", "ABBCAB",
            "ABBCAC", "ABBCBA", "ABBCBB", "ABBCBC",
            "ABBCCA", "ABBCCB", "ABBCCC", "ABCAAA",
            "ABCAAB", "ABCAAC", "ABCABA", "ABCABB",
            "ABCABC", "ABCACA", "ABCACB", "ABCACC",
            "ABCBAA", "ABCBAB", "ABCBAC", "ABCBBA",
            "ABCBBB", "ABCBBC", "ABCBCA", "ABCBCB",
            "ABCBCC", "ABCCAA", "ABCCAB", "ABCCAC",
            "ABCCBA", "ABCCBB", "ABCCBC", "ABCCCA",
            "ABCCCB", "ABCCCC"};

        int prefixWeight[] = {
             3,6,6,6,6,6,6,6,6,6,
             6,6,6,6,6,6,6,6,6,6,
             6,6,6,6,6,6,6,6,6,6,
             6,6,6,6,6,6,6,6,6,6,
             6,6,6,6,6,6,6,6,6,6,
             6,6,6,6,6,6,6,6,6,6,
             6,6,6,6,6,6,6,6,6,6,
             6,6,6,6,6,6,6,6,6,6,
             6,6,6,6,6,6,6,6,6,6,
             6,6,6,6,6,6,6,6,6,6,
             6,6,6,6,6,6,6,6,6,6,
             6,6,6,6,6,6,6,6,6,6,6,6};

        int numABC[][3] = {
            {n-6, n, n    }, {n-5, n-1, n  }, {n-5, n-1, n  }, {n-4, n-2, n  },
            {n-4, n-1, n-1}, {n-5, n-1, n  }, {n-4, n-2, n  }, {n-4, n-1, n-1},
            {n-4, n-2, n  }, {n-3, n-3, n  }, {n-3, n-2, n-1}, {n-4, n-1, n-1},
            {n-3, n-2, n-1}, {n-3, n-1, n-2}, {n-5, n-1, n  }, {n-4, n-2, n  },
            {n-4, n-1, n-1}, {n-4, n-2, n  }, {n-3, n-3, n  }, {n-3, n-2, n-1},
            {n-4, n-1, n-1}, {n-3, n-2, n-1}, {n-3, n-1, n-2}, {n-4, n-2, n  },
            {n-3, n-3, n  }, {n-3, n-2, n-1}, {n-3, n-3, n  }, {n-2, n-4, n  },
            {n-2, n-3, n-1}, {n-3, n-2, n-1}, {n-2, n-3, n-1}, {n-2, n-2, n-2},
            {n-4, n-1, n-1}, {n-3, n-2, n-1}, {n-3, n-1, n-2}, {n-3, n-2, n-1},
            {n-2, n-3, n-1}, {n-2, n-2, n-2}, {n-3, n-1, n-2}, {n-2, n-2, n-2},
            {n-2, n-1, n-3}, {n-5, n-1, n  }, {n-4, n-2, n  }, {n-4, n-1, n-1},
            {n-4, n-2, n  }, {n-3, n-3, n  }, {n-3, n-2, n-1}, {n-4, n-1, n-1},
            {n-3, n-2, n-1}, {n-3, n-1, n-2}, {n-4, n-2, n  }, {n-3, n-3, n  },
            {n-3, n-2, n-1}, {n-3, n-3, n  }, {n-2, n-4, n  }, {n-2, n-3, n-1},
            {n-3, n-2, n-1}, {n-2, n-3, n-1}, {n-2, n-2, n-2}, {n-4, n-1, n-1},
            {n-3, n-2, n-1}, {n-3, n-1, n-2}, {n-3, n-2, n-1}, {n-2, n-3, n-1},
            {n-2, n-2, n-2}, {n-3, n-1, n-2}, {n-2, n-2, n-2}, {n-2, n-1, n-3},
            {n-4, n-2, n  }, {n-3, n-3, n  }, {n-3, n-2, n-1}, {n-3, n-3, n  },
            {n-2, n-4, n  }, {n-2, n-3, n-1}, {n-3, n-2, n-1}, {n-2, n-3, n-1},
            {n-2, n-2, n-2}, {n-3, n-3, n  }, {n-2, n-4, n  }, {n-2, n-3, n-1},
            {n-2, n-4, n  }, {n-1, n-5, n, }, {n-1, n-4, n-1}, {n-2, n-3, n-1},
            {n-1, n-4, n-1}, {n-1, n-3, n-2}, {n-3, n-2, n-1}, {n-2, n-3, n-1},
            {n-2, n-2, n-2}, {n-2, n-3, n-1}, {n-1, n-4, n-1}, {n-1, n-3, n-2},
            {n-2, n-2, n-2}, {n-1, n-3, n-2}, {n-1, n-2, n-3}, {n-4, n-1, n-1},
            {n-3, n-2, n-1}, {n-3, n-1, n-2}, {n-3, n-2, n-1}, {n-2, n-3, n-1},
            {n-2, n-2, n-2}, {n-3, n-1, n-2}, {n-2, n-2, n-2}, {n-2, n-1, n-3},
            {n-3, n-2, n-1}, {n-2, n-3, n-1}, {n-2, n-2, n-2}, {n-2, n-3, n-1},
            {n-1, n-4, n-1}, {n-1, n-3, n-2}, {n-2, n-2, n-2}, {n-1, n-3, n-2},
            {n-1, n-2, n-3}, {n-3, n-1, n-2}, {n-2, n-2, n-2}, {n-2, n-1, n-3},
            {n-2, n-2, n-2}, {n-1, n-3, n-2}, {n-1, n-2, n-3}, {n-2, n-1, n-3},
            {n-1, n-2, n-3}, {n-1, n-1, n-4}};

        #pragma omp parallel for reduction(+:numT, numD)
        for(int i = 0; i < 122; i++){
            uint64_t numTacc = 0, numDacc = 0;
            scan_games(prefix[i],
                       generateGame(numABC[i]),
                       numTacc, numDacc, n);
            numT += prefixWeight[i]*numTacc;
            numD += prefixWeight[i]*numDacc;
        }

        cout << "    D(" << n << ") = " << numD << endl
             << "    T(" << n << ") = " << numT << endl
             << "    T(" << n << ")/D(" << n << ") = " << (double) numT/numD << endl;

    auto stop = high_resolution_clock::now();

    cout << "    Elapsed time: "
         << (double) duration_cast<milliseconds>(stop-start).count()/1000
         << "s" << endl
         << endl;
    }
    return 0;
}
