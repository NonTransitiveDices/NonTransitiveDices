#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;
 
int
intransitivep (string &permutation, int n)
{
    int threshold = n*n;
    int numA = 0,  numB = 0,  numC = 0;
    int numAB = 0, numBC = 0, numCA = 0;

    int permutationSize = permutation.size();
    for (int i = 0; i < permutationSize; i++){
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
scan_games (string text,
            int &numI,
            int n,
            int maxInt)
{

    while (maxInt--)
    {

        // find a random shuffle of the string
        random_shuffle(text.begin(), text.end());

        numI += intransitivep(text, n);
    }
}


// Driver code
int
main()
{
    cout << setprecision(10) << fixed;

    ofstream myfile;
    myfile.open("extrapolation.dat");
    
    int maxInt = 500000;
    for (int n = 1000; n <= 1000; n++)
    {
        string text = "";
        for (int i = 0; i < n; i++){
            text += "ABC";
        }
        int numI = 0;

        for(int m = 1; m <= 100; m++)
        {
            srand(m*n);
            int numIaux = 0;
            scan_games(text, numIaux, n, maxInt);
            numI += numIaux;
            myfile << m << " " << numIaux << ' ' << maxInt << endl;
        }

        double p = (double)numI/(100*maxInt);
        cout << n << " " << p << endl;

    }
    myfile.close();
    return 0;
}
