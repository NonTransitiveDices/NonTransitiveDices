#include <iostream>
#include <iomanip>
#include <algorithm>

#include <chrono>

using namespace std::chrono;

using namespace std;
 

void geraDados (string &s, int n){
    string a="", b="", c="";
    for(int i=0; i<n-1; i++){
        a+="A";
        b+="B";
        c+="C";
    }
    s=a+b+"BC"+c;
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

void findPermutations(string &str, long long int &nTransitivo, long long int &total, int n)
{
    // base case
    if (str.length() == 0) {
        return;
    }
 
    while (1)
    {
        // print the current permutation
        total++;
        // print the permutation
        cout << "A"+str << endl;
        if(abcNtransitive("A"+str, n)) nTransitivo++;
 
        // find the next lexicographically ordered permutation
        if (!next_permutation(str.begin(), str.end())) {
            break;
        }
    }
}

// Driver code
int main(){
    cout << setprecision(10) << fixed;
    
    auto start = high_resolution_clock::now();
    
    int n=2;
    string str;
    geraDados(str, n);
    
    long long int total=0, nTransitivo=0;
    findPermutations(str, nTransitivo, total, n);
    
    cout << "       D(" << n << ") = " << 3*total << endl
    <<      "       T(" << n << ") = " << 3*nTransitivo << endl
    <<      "  T(" << n << ")/D(" << n << ") = " << (double) nTransitivo/total << endl;
    
    auto stop = high_resolution_clock::now();
    
    cout << (double) duration_cast<milliseconds>(stop-start).count()/1000 << endl;
    
    return 0;
    
}