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
    for(int n = 7; n <= 8; n++)
    {
        uint64_t numD=0;
        uint64_t numT = 0;

        string prefix[] = {
            "AAAAAAA", "AAAAAAB", "AAAAABA", "AAAAABB", "AAAAABC", "AAAABAA",
            "AAAABAB", "AAAABAC", "AAAABBA", "AAAABBB", "AAAABBC", "AAAABCA",
            "AAAABCB", "AAAABCC", "AAABAAA", "AAABAAB", "AAABAAC", "AAABABA",
            "AAABABB", "AAABABC", "AAABACA", "AAABACB", "AAABACC", "AAABBAA",
            "AAABBAB", "AAABBAC", "AAABBBA", "AAABBBB", "AAABBBC", "AAABBCA",
            "AAABBCB", "AAABBCC", "AAABCAA", "AAABCAB", "AAABCAC", "AAABCBA",
            "AAABCBB", "AAABCBC", "AAABCCA", "AAABCCB", "AAABCCC", "AABAAAA",
            "AABAAAB", "AABAAAC", "AABAABA", "AABAABB", "AABAABC", "AABAACA",
            "AABAACB", "AABAACC", "AABABAA", "AABABAB", "AABABAC", "AABABBA",
            "AABABBB", "AABABBC", "AABABCA", "AABABCB", "AABABCC", "AABACAA",
            "AABACAB", "AABACAC", "AABACBA", "AABACBB", "AABACBC", "AABACCA",
            "AABACCB", "AABACCC", "AABBAAA", "AABBAAB", "AABBAAC", "AABBABA",
            "AABBABB", "AABBABC", "AABBACA", "AABBACB", "AABBACC", "AABBBAA",
            "AABBBAB", "AABBBAC", "AABBBBA", "AABBBBB", "AABBBBC", "AABBBCA",
            "AABBBCB", "AABBBCC", "AABBCAA", "AABBCAB", "AABBCAC", "AABBCBA",
            "AABBCBB", "AABBCBC", "AABBCCA", "AABBCCB", "AABBCCC", "AABCAAA",
            "AABCAAB", "AABCAAC", "AABCABA", "AABCABB", "AABCABC", "AABCACA",
            "AABCACB", "AABCACC", "AABCBAA", "AABCBAB", "AABCBAC", "AABCBBA",
            "AABCBBB", "AABCBBC", "AABCBCA", "AABCBCB", "AABCBCC", "AABCCAA",
            "AABCCAB", "AABCCAC", "AABCCBA", "AABCCBB", "AABCCBC", "AABCCCA",
            "AABCCCB", "AABCCCC", "ABAAAAA", "ABAAAAB", "ABAAAAC", "ABAAABA",
            "ABAAABB", "ABAAABC", "ABAAACA", "ABAAACB", "ABAAACC", "ABAABAA",
            "ABAABAB", "ABAABAC", "ABAABBA", "ABAABBB", "ABAABBC", "ABAABCA",
            "ABAABCB", "ABAABCC", "ABAACAA", "ABAACAB", "ABAACAC", "ABAACBA",
            "ABAACBB", "ABAACBC", "ABAACCA", "ABAACCB", "ABAACCC", "ABABAAA",
            "ABABAAB", "ABABAAC", "ABABABA", "ABABABB", "ABABABC", "ABABACA",
            "ABABACB", "ABABACC", "ABABBAA", "ABABBAB", "ABABBAC", "ABABBBA",
            "ABABBBB", "ABABBBC", "ABABBCA", "ABABBCB", "ABABBCC", "ABABCAA",
            "ABABCAB", "ABABCAC", "ABABCBA", "ABABCBB", "ABABCBC", "ABABCCA",
            "ABABCCB", "ABABCCC", "ABACAAA", "ABACAAB", "ABACAAC", "ABACABA",
            "ABACABB", "ABACABC", "ABACACA", "ABACACB", "ABACACC", "ABACBAA",
            "ABACBAB", "ABACBAC", "ABACBBA", "ABACBBB", "ABACBBC", "ABACBCA",
            "ABACBCB", "ABACBCC", "ABACCAA", "ABACCAB", "ABACCAC", "ABACCBA",
            "ABACCBB", "ABACCBC", "ABACCCA", "ABACCCB", "ABACCCC", "ABBAAAA",
            "ABBAAAB", "ABBAAAC", "ABBAABA", "ABBAABB", "ABBAABC", "ABBAACA",
            "ABBAACB", "ABBAACC", "ABBABAA", "ABBABAB", "ABBABAC", "ABBABBA",
            "ABBABBB", "ABBABBC", "ABBABCA", "ABBABCB", "ABBABCC", "ABBACAA",
            "ABBACAB", "ABBACAC", "ABBACBA", "ABBACBB", "ABBACBC", "ABBACCA",
            "ABBACCB", "ABBACCC", "ABBBAAA", "ABBBAAB", "ABBBAAC", "ABBBABA",
            "ABBBABB", "ABBBABC", "ABBBACA", "ABBBACB", "ABBBACC", "ABBBBAA",
            "ABBBBAB", "ABBBBAC", "ABBBBBA", "ABBBBBB", "ABBBBBC", "ABBBBCA",
            "ABBBBCB", "ABBBBCC", "ABBBCAA", "ABBBCAB", "ABBBCAC", "ABBBCBA",
            "ABBBCBB", "ABBBCBC", "ABBBCCA", "ABBBCCB", "ABBBCCC", "ABBCAAA",
            "ABBCAAB", "ABBCAAC", "ABBCABA", "ABBCABB", "ABBCABC", "ABBCACA",
            "ABBCACB", "ABBCACC", "ABBCBAA", "ABBCBAB", "ABBCBAC", "ABBCBBA",
            "ABBCBBB", "ABBCBBC", "ABBCBCA", "ABBCBCB", "ABBCBCC", "ABBCCAA",
            "ABBCCAB", "ABBCCAC", "ABBCCBA", "ABBCCBB", "ABBCCBC", "ABBCCCA",
            "ABBCCCB", "ABBCCCC", "ABCAAAA", "ABCAAAB", "ABCAAAC", "ABCAABA",
            "ABCAABB", "ABCAABC", "ABCAACA", "ABCAACB", "ABCAACC", "ABCABAA",
            "ABCABAB", "ABCABAC", "ABCABBA", "ABCABBB", "ABCABBC", "ABCABCA",
            "ABCABCB", "ABCABCC", "ABCACAA", "ABCACAB", "ABCACAC", "ABCACBA",
            "ABCACBB", "ABCACBC", "ABCACCA", "ABCACCB", "ABCACCC", "ABCBAAA",
            "ABCBAAB", "ABCBAAC", "ABCBABA", "ABCBABB", "ABCBABC", "ABCBACA",
            "ABCBACB", "ABCBACC", "ABCBBAA", "ABCBBAB", "ABCBBAC", "ABCBBBA",
            "ABCBBBB", "ABCBBBC", "ABCBBCA", "ABCBBCB", "ABCBBCC", "ABCBCAA",
            "ABCBCAB", "ABCBCAC", "ABCBCBA", "ABCBCBB", "ABCBCBC", "ABCBCCA",
            "ABCBCCB", "ABCBCCC", "ABCCAAA", "ABCCAAB", "ABCCAAC", "ABCCABA",
            "ABCCABB", "ABCCABC", "ABCCACA", "ABCCACB", "ABCCACC", "ABCCBAA",
            "ABCCBAB", "ABCCBAC", "ABCCBBA", "ABCCBBB", "ABCCBBC", "ABCCBCA",
            "ABCCBCB", "ABCCBCC", "ABCCCAA", "ABCCCAB", "ABCCCAC", "ABCCCBA",
            "ABCCCBB", "ABCCCBC", "ABCCCCA", "ABCCCCB", "ABCCCCC"};

        int prefixWeight[] = {
            3, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
            6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
            6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
            6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
            6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
            6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
            6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
            6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
            6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
            6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
            6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
            6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
            6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
            6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
            6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
            6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
            6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
            6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
            6, 6, 6, 6, 6};

        int numABC[][3] = {
            {n-7, n  , n  }, {n-6, n-1, n  }, {n-6, n-1, n  }, {n-5, n-2, n  },
            {n-5, n-1, n-1}, {n-6, n-1, n  }, {n-5, n-2, n  }, {n-5, n-1, n-1},
            {n-5, n-2, n  }, {n-4, n-3, n  }, {n-4, n-2, n-1}, {n-5, n-1, n-1},
            {n-4, n-2, n-1}, {n-4, n-1, n-2}, {n-6, n-1, n  }, {n-5, n-2, n  },
            {n-5, n-1, n-1}, {n-5, n-2, n  }, {n-4, n-3, n  }, {n-4, n-2, n-1},
            {n-5, n-1, n-1}, {n-4, n-2, n-1}, {n-4, n-1, n-2}, {n-5, n-2, n  },
            {n-4, n-3, n  }, {n-4, n-2, n-1}, {n-4, n-3, n  }, {n-3, n-4, n  },
            {n-3, n-3, n-1}, {n-4, n-2, n-1}, {n-3, n-3, n-1}, {n-3, n-2, n-2},
            {n-5, n-1, n-1}, {n-4, n-2, n-1}, {n-4, n-1, n-2}, {n-4, n-2, n-1},
            {n-3, n-3, n-1}, {n-3, n-2, n-2}, {n-4, n-1, n-2}, {n-3, n-2, n-2},
            {n-3, n-1, n-3}, {n-6, n-1, n  }, {n-5, n-2, n  }, {n-5, n-1, n-1},
            {n-5, n-2, n  }, {n-4, n-3, n  }, {n-4, n-2, n-1}, {n-5, n-1, n-1},
            {n-4, n-2, n-1}, {n-4, n-1, n-2}, {n-5, n-2, n  }, {n-4, n-3, n  },
            {n-4, n-2, n-1}, {n-4, n-3, n  }, {n-3, n-4, n  }, {n-3, n-3, n-1},
            {n-4, n-2, n-1}, {n-3, n-3, n-1}, {n-3, n-2, n-2}, {n-5, n-1, n-1},
            {n-4, n-2, n-1}, {n-4, n-1, n-2}, {n-4, n-2, n-1}, {n-3, n-3, n-1},
            {n-3, n-2, n-2}, {n-4, n-1, n-2}, {n-3, n-2, n-2}, {n-3, n-1, n-3},
            {n-5, n-2, n  }, {n-4, n-3, n  }, {n-4, n-2, n-1}, {n-4, n-3, n  },
            {n-3, n-4, n  }, {n-3, n-3, n-1}, {n-4, n-2, n-1}, {n-3, n-3, n-1},
            {n-3, n-2, n-2}, {n-4, n-3, n  }, {n-3, n-4, n  }, {n-3, n-3, n-1},
            {n-3, n-4, n  }, {n-2, n-5, n  }, {n-2, n-4, n-1}, {n-3, n-3, n-1},
            {n-2, n-4, n-1}, {n-2, n-3, n-2}, {n-4, n-2, n-1}, {n-3, n-3, n-1},
            {n-3, n-2, n-2}, {n-3, n-3, n-1}, {n-2, n-4, n-1}, {n-2, n-3, n-2},
            {n-3, n-2, n-2}, {n-2, n-3, n-2}, {n-2, n-2, n-3}, {n-5, n-1, n-1},
            {n-4, n-2, n-1}, {n-4, n-1, n-2}, {n-4, n-2, n-1}, {n-3, n-3, n-1},
            {n-3, n-2, n-2}, {n-4, n-1, n-2}, {n-3, n-2, n-2}, {n-3, n-1, n-3},
            {n-4, n-2, n-1}, {n-3, n-3, n-1}, {n-3, n-2, n-2}, {n-3, n-3, n-1},
            {n-2, n-4, n-1}, {n-2, n-3, n-2}, {n-3, n-2, n-2}, {n-2, n-3, n-2},
            {n-2, n-2, n-3}, {n-4, n-1, n-2}, {n-3, n-2, n-2}, {n-3, n-1, n-3},
            {n-3, n-2, n-2}, {n-2, n-3, n-2}, {n-2, n-2, n-3}, {n-3, n-1, n-3},
            {n-2, n-2, n-3}, {n-2, n-1, n-4}, {n-6, n-1, n  }, {n-5, n-2, n  },
            {n-5, n-1, n-1}, {n-5, n-2, n  }, {n-4, n-3, n  }, {n-4, n-2, n-1},
            {n-5, n-1, n-1}, {n-4, n-2, n-1}, {n-4, n-1, n-2}, {n-5, n-2, n  },
            {n-4, n-3, n  }, {n-4, n-2, n-1}, {n-4, n-3, n  }, {n-3, n-4, n  },
            {n-3, n-3, n-1}, {n-4, n-2, n-1}, {n-3, n-3, n-1}, {n-3, n-2, n-2},
            {n-5, n-1, n-1}, {n-4, n-2, n-1}, {n-4, n-1, n-2}, {n-4, n-2, n-1},
            {n-3, n-3, n-1}, {n-3, n-2, n-2}, {n-4, n-1, n-2}, {n-3, n-2, n-2},
            {n-3, n-1, n-3}, {n-5, n-2, n  }, {n-4, n-3, n  }, {n-4, n-2, n-1},
            {n-4, n-3, n  }, {n-3, n-4, n  }, {n-3, n-3, n-1}, {n-4, n-2, n-1},
            {n-3, n-3, n-1}, {n-3, n-2, n-2}, {n-4, n-3, n  }, {n-3, n-4, n  },
            {n-3, n-3, n-1}, {n-3, n-4, n  }, {n-2, n-5, n  }, {n-2, n-4, n-1},
            {n-3, n-3, n-1}, {n-2, n-4, n-1}, {n-2, n-3, n-2}, {n-4, n-2, n-1},
            {n-3, n-3, n-1}, {n-3, n-2, n-2}, {n-3, n-3, n-1}, {n-2, n-4, n-1},
            {n-2, n-3, n-2}, {n-3, n-2, n-2}, {n-2, n-3, n-2}, {n-2, n-2, n-3},
            {n-5, n-1, n-1}, {n-4, n-2, n-1}, {n-4, n-1, n-2}, {n-4, n-2, n-1},
            {n-3, n-3, n-1}, {n-3, n-2, n-2}, {n-4, n-1, n-2}, {n-3, n-2, n-2},
            {n-3, n-1, n-3}, {n-4, n-2, n-1}, {n-3, n-3, n-1}, {n-3, n-2, n-2},
            {n-3, n-3, n-1}, {n-2, n-4, n-1}, {n-2, n-3, n-2}, {n-3, n-2, n-2},
            {n-2, n-3, n-2}, {n-2, n-2, n-3}, {n-4, n-1, n-2}, {n-3, n-2, n-2},
            {n-3, n-1, n-3}, {n-3, n-2, n-2}, {n-2, n-3, n-2}, {n-2, n-2, n-3},
            {n-3, n-1, n-3}, {n-2, n-2, n-3}, {n-2, n-1, n-4}, {n-5, n-2, n  },
            {n-4, n-3, n  }, {n-4, n-2, n-1}, {n-4, n-3, n  }, {n-3, n-4, n  },
            {n-3, n-3, n-1}, {n-4, n-2, n-1}, {n-3, n-3, n-1}, {n-3, n-2, n-2},
            {n-4, n-3, n  }, {n-3, n-4, n  }, {n-3, n-3, n-1}, {n-3, n-4, n  },
            {n-2, n-5, n  }, {n-2, n-4, n-1}, {n-3, n-3, n-1}, {n-2, n-4, n-1},
            {n-2, n-3, n-2}, {n-4, n-2, n-1}, {n-3, n-3, n-1}, {n-3, n-2, n-2},
            {n-3, n-3, n-1}, {n-2, n-4, n-1}, {n-2, n-3, n-2}, {n-3, n-2, n-2},
            {n-2, n-3, n-2}, {n-2, n-2, n-3}, {n-4, n-3, n  }, {n-3, n-4, n  },
            {n-3, n-3, n-1}, {n-3, n-4, n  }, {n-2, n-5, n  }, {n-2, n-4, n-1},
            {n-3, n-3, n-1}, {n-2, n-4, n-1}, {n-2, n-3, n-2}, {n-3, n-4, n  },
            {n-2, n-5, n  }, {n-2, n-4, n-1}, {n-2, n-5, n  }, {n-1, n-6, n  },
            {n-1, n-5, n-1}, {n-2, n-4, n-1}, {n-1, n-5, n-1}, {n-1, n-4, n-2},
            {n-3, n-3, n-1}, {n-2, n-4, n-1}, {n-2, n-3, n-2}, {n-2, n-4, n-1},
            {n-1, n-5, n-1}, {n-1, n-4, n-2}, {n-2, n-3, n-2}, {n-1, n-4, n-2},
            {n-1, n-3, n-3}, {n-4, n-2, n-1}, {n-3, n-3, n-1}, {n-3, n-2, n-2},
            {n-3, n-3, n-1}, {n-2, n-4, n-1}, {n-2, n-3, n-2}, {n-3, n-2, n-2},
            {n-2, n-3, n-2}, {n-2, n-2, n-3}, {n-3, n-3, n-1}, {n-2, n-4, n-1},
            {n-2, n-3, n-2}, {n-2, n-4, n-1}, {n-1, n-5, n-1}, {n-1, n-4, n-2},
            {n-2, n-3, n-2}, {n-1, n-4, n-2}, {n-1, n-3, n-3}, {n-3, n-2, n-2},
            {n-2, n-3, n-2}, {n-2, n-2, n-3}, {n-2, n-3, n-2}, {n-1, n-4, n-2},
            {n-1, n-3, n-3}, {n-2, n-2, n-3}, {n-1, n-3, n-3}, {n-1, n-2, n-4},
            {n-5, n-1, n-1}, {n-4, n-2, n-1}, {n-4, n-1, n-2}, {n-4, n-2, n-1},
            {n-3, n-3, n-1}, {n-3, n-2, n-2}, {n-4, n-1, n-2}, {n-3, n-2, n-2},
            {n-3, n-1, n-3}, {n-4, n-2, n-1}, {n-3, n-3, n-1}, {n-3, n-2, n-2},
            {n-3, n-3, n-1}, {n-2, n-4, n-1}, {n-2, n-3, n-2}, {n-3, n-2, n-2},
            {n-2, n-3, n-2}, {n-2, n-2, n-3}, {n-4, n-1, n-2}, {n-3, n-2, n-2},
            {n-3, n-1, n-3}, {n-3, n-2, n-2}, {n-2, n-3, n-2}, {n-2, n-2, n-3},
            {n-3, n-1, n-3}, {n-2, n-2, n-3}, {n-2, n-1, n-4}, {n-4, n-2, n-1},
            {n-3, n-3, n-1}, {n-3, n-2, n-2}, {n-3, n-3, n-1}, {n-2, n-4, n-1},
            {n-2, n-3, n-2}, {n-3, n-2, n-2}, {n-2, n-3, n-2}, {n-2, n-2, n-3},
            {n-3, n-3, n-1}, {n-2, n-4, n-1}, {n-2, n-3, n-2}, {n-2, n-4, n-1},
            {n-1, n-5, n-1}, {n-1, n-4, n-2}, {n-2, n-3, n-2}, {n-1, n-4, n-2},
            {n-1, n-3, n-3}, {n-3, n-2, n-2}, {n-2, n-3, n-2}, {n-2, n-2, n-3},
            {n-2, n-3, n-2}, {n-1, n-4, n-2}, {n-1, n-3, n-3}, {n-2, n-2, n-3},
            {n-1, n-3, n-3}, {n-1, n-2, n-4}, {n-4, n-1, n-2}, {n-3, n-2, n-2},
            {n-3, n-1, n-3}, {n-3, n-2, n-2}, {n-2, n-3, n-2}, {n-2, n-2, n-3},
            {n-3, n-1, n-3}, {n-2, n-2, n-3}, {n-2, n-1, n-4}, {n-3, n-2, n-2},
            {n-2, n-3, n-2}, {n-2, n-2, n-3}, {n-2, n-3, n-2}, {n-1, n-4, n-2},
            {n-1, n-3, n-3}, {n-2, n-2, n-3}, {n-1, n-3, n-3}, {n-1, n-2, n-4},
            {n-3, n-1, n-3}, {n-2, n-2, n-3}, {n-2, n-1, n-4}, {n-2, n-2, n-3},
            {n-1, n-3, n-3}, {n-1, n-2, n-4}, {n-2, n-1, n-4}, {n-1, n-2, n-4},
            {n-1, n-1, n-5}};

        #pragma omp parallel for reduction(+:numT, numD)
        for(int i = 0; i < 365; i++){
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
