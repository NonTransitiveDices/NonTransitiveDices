#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;
 
// Returns true if str[curr] does not matches with any of the
// characters after str[start]
void geraDados (string &s, int n){
    string a="", b="", c="";
    for(int i=0; i<n; i++){
        a+="A";
        b+="B";
        c+="C";
    }
    s=a+b+c;
}

void findPermutations(vector<string> &permutationsa, string str)
{
    // base case
    if (str.length() == 0) {
        return;
    }
 
    while (1)
    {
        // print the current permutation
        permutationsa.push_back(str);
 
        // find the next lexicographically ordered permutation
        if (!next_permutation(str.begin(), str.end())) {
            break;
        }
    }
}
 

bool abcNtransitive(string permutation, int n){

    int threshold = n*n;
    int countA=0, countB=0, countC=0;
    int vicAB=0, vicBC=0, vicCA=0;

    long long int permutationSize = permutation.size();
    for (long long int i=0; i<permutationSize; i++){
        if (permutation[i] == 'A'){
            countA++;
            vicAB += countB;
        }
        else if (permutation[i] == 'B'){
            countB++;
            vicBC += countC;
        }
        else if (permutation[i] == 'C'){
            countC++;
            vicCA += countA;
        }
    }
    if((2*vicAB > threshold 
    and 2*vicBC > threshold 
    and 2*vicCA > threshold)
    or
    (2*vicAB < threshold
    and 2*vicBC < threshold
    and 2*vicCA < threshold)){
        return true;
    }
    else{
        return false;
    }
}

// Driver code
int main(){
    cout << setprecision(5) << fixed;
    
    int n=7;
    string str;
    geraDados(str, n);
    
    vector<string> permutationsa;
    findPermutations(permutationsa, str);
    
    long long int permutationsaize=permutationsa.size();
    
    long long int countIntransitivos=0;
    for(long long int i=0; i<permutationsaize; i++){
        if (abcNtransitive(permutationsa[i], n)) countIntransitivos++;
    }
    
    cout << "       D(" << n << ") = " << permutationsaize << endl
    <<      "       T(" << n << ") = " << countIntransitivos << endl
    <<      "  T(" << n << ")/D(" << n << ") = " << (double) countIntransitivos/permutationsaize << endl;
    
    return 0;
    
};