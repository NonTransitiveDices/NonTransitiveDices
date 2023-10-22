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
    return ((
            2*vicAB > threshold and
            2*vicBC > threshold and
            2*vicCA > threshold
            )
        or(
            2*vicAB < threshold and
            2*vicBC < threshold and
            2*vicCA < threshold));
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
    int n = 5;
        long long int total=0;
        long long int nTransitivo = 0;
        findPermutations("AAA", generateGame(n-3, n  , n  ), nTransitivo, n, total);
        
        nTransitivo/=2;
        total/=2;
        
        findPermutations("AAB", generateGame(n-2, n-1, n  ), nTransitivo, n, total);
        findPermutations("ABA", generateGame(n-2, n-1, n  ), nTransitivo, n, total);
        findPermutations("ABB", generateGame(n-1, n-2, n  ), nTransitivo, n, total);
        findPermutations("ABC", generateGame(n-1, n-1, n-1), nTransitivo, n, total);

        cout << "        D(" << n << ") = " << 6*total << endl
             << "        T(" << n << ") = " << 6*nTransitivo << endl
             << "   T(" << n << ")/D(" << n << ") = " << (double) nTransitivo/total << endl
             << "" << endl;
             
    auto stop = high_resolution_clock::now();
    
    cout << (double) duration_cast<milliseconds>(stop-start).count()/1000 << endl;
    return 0;

}
