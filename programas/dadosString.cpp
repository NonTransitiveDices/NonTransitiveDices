#include <iostream>
#include <vector>
using namespace std;
 
// Returns true if str[curr] does not matches with any of the
// characters after str[start]
bool shouldSwap(string str, int start, int curr)
{
    for (int i = start; i < curr; i++)
        if (str[i] == str[curr])
            return 0;
    return 1;
}
 
// Prints all distinct permutations in str[0..n-1]
void findPermutations(vector<string> permutationsa, string str, int index, int n)
{
    if (index >= n) {
        cout << str << " " << endl;
        permutationsa.push_back(str);
        return;
    }
 
    for (int i = index; i < n; i++) {
 
        // Proceed further for str[i] only if it
        // doesn't match with any of the characters
        // after str[index]
        bool check = shouldSwap(str, index, i);
        if (check) {
            char aux=str[index];
            str[index]=str[i];
            str[i]=aux;
            findPermutations(permutationsa, str, index + 1, n);
            aux = str[index];
            str[index] = str[i];
            str[i] = aux;
        }
    }
}
 
int main(){
    int n = 3;
    char str[] = "AAABBBCCC";
    vector<string> permutationsa;
    findPermutations(permutationsa, str, 0, n);

    for(int i=0; i<permutationsa.size(); i++){
        cout << permutationsa[i] << endl;
    }
}