#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <math.h>
#include <cmath>

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
             2*numCA > threshold));
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

    ofstream  MyFile;
     MyFile.open("extrapolation.dat");

     MyFile << setprecision(10) << fixed;
    
    int maxInt = 500000;

    for (int n = 3; n <= 1000; n++)
    {
        string text = "";
        for (int i = 0; i < n; i++){
            text += "ABC";
        }
        int numI = 0;
        double samples[100];
        for(int m = 1; m <= 100; m++)
        {
            srand(m*n);
            int numIaux = 0;
            scan_games(text, numIaux, n, maxInt);
            samples[m-1]=(double) numIaux/maxInt;
            numI += numIaux;
//            cout << m << " " << numIaux << ' ' << maxInt << endl;
        }

        double p = (double)numI/(100*maxInt);

        double sigma=0;
        for(int m=0; m<100; m++){
            sigma+=(p-samples[m])*(p-samples[m]);
        }
        sigma = sqrt(sigma/99);
        double logsigma = sigma/p;

        cout 
        << n << " " << p << " " << sigma << " " << log(p)/n << " " << logsigma/n << endl;
        
         MyFile 
        << n << " " << p << " " << sigma << " " << log(p)/n << " " << logsigma/n << endl;

    }

     MyFile.close();
    return 0;
}