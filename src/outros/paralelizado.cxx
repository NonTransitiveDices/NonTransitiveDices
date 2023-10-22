#include <iostream>
#include <iomanip>
#include <algorithm>
#include <chrono>

using namespace std::chrono;

using namespace std;
 
// Returns true if str[curr] does not matches with any of the
// characters after str[start]
string generateGame (int nA, int nB, int nC)
{
    string a = "", b = "", c = "";
    for(int i = 0; i < nA; i++) a+= "A";
    for(int i = 0; i < nB; i++) b+= "B";
    for(int i = 0; i < nC; i++) c+= "C";
    return a+b+c;
}

bool simetric(string permutation)
{
    int n = permutation.size();
    for (int i = 0; i < n/2; i++){
        if (permutation[i] == 'A' and permutation[n-i-1] != 'A') return false;
        if (permutation[i] == 'B' and permutation[n-i-1] != 'B') return false;
        if (permutation[i] == 'C' and permutation[n-i-1] != 'C') return false;
    }
    return true;
}

bool abcNtransitive(string permutation, int n)
{
    int threshold = n*n;
    int countA = 0, countB = 0, countC = 0;
    int vicAB = 0, vicBC = 0, vicCA = 0;

    long long int permutationSize = permutation.size();
    for (long long int i = 0; i < permutationSize; i++){
        switch(permutation[i]){
            case 'A':
                countA++;
                vicAB += countB;
                break;
            case 'B':
                countB++;
                vicBC += countC;
                break;
            case 'C':
                countC++;
                vicCA += countA;
                break;
        }
    }
    if (2*vicAB == threshold and 2*vicBC == threshold and 2*vicCA == threshold) {
        if (!simetric(permutation)) {
            cout << permutation << endl;
        }
        return true;
    }
    return false;
}

void findPermutations(string prefix,
                 string str,
                 long long int &nTransitivo,
                 int n, long long int &total)
{
    while (true)
    {
        // print the current permutation
        total++;
        if(abcNtransitive(prefix+str, n)) nTransitivo++;

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

    for(int n=6; n<=6; n++){
        long long int total=0;
        long long int nTransitivo = 0;

        string Prefixo[] = {
            "AAAA", "AAAB", "AABA", "AABB", 
            "AABC", "ABAA", "ABAB", "ABAC", 
            "ABBA", "ABBB", "ABBC", "ABCA", 
            "ABCB", "ABCC"};

        int pesosPrefixo[] = {
            3, 6, 6, 6,
            6, 6, 6, 6,
            6, 6, 6, 6,
            6, 6};

        int nLetrasPrefixo[][3] = {
            {n-4, n, n},
            {n-3, n-1, n},
            {n-3, n-1, n},
            {n-2, n-2, n},
            {n-2, n-1, n-1},
            {n-3, n-1, n},
            {n-2, n-2, n},
            {n-2, n-1, n-1},
            {n-2, n-2, n},
            {n-1, n-3, n},
            {n-1, n-2, n-1},
            {n-2, n-1, n-1},
            {n-1, n-2, n-1},
            {n-1, n-1, n-2}};
        
        #pragma omp parallel for reduction(+:nTransitivo, total)
        for(int i = 0; i < 14; i++){
            long long int nTransitivoAux = 0, totalAux = 0;
            findPermutations(Prefixo[i], generateGame(nLetrasPrefixo[i][0], nLetrasPrefixo[i][1], nLetrasPrefixo[i][2]), nTransitivoAux, n, totalAux);
            nTransitivo += pesosPrefixo[i]*nTransitivoAux;
            total += pesosPrefixo[i]*totalAux;
        }

        cout << "        D(" << n << ") = " << total << endl
             << "        T(" << n << ") = " << nTransitivo << endl
             << "   T(" << n << ")/D(" << n << ") = " << (double) nTransitivo/total << endl
             << "" << endl;
             
    auto stop = high_resolution_clock::now();
    
    cout << (double) duration_cast<milliseconds>(stop-start).count()/1000 << endl;
    }
    return 0;

}
