#include<iostream>
#include<vector>
#include<iomanip>
#include<cmath>
#include<chrono>
#include<random>
#include<vector>
#include<algorithm>
#include<inttypes.h>

using namespace std;
using namespace std::chrono;
random_device rd;

// int random(int low, int high)
// {
// 	// create random number with seed
// 	std::uniform_int_distribution<> dist(low, high);
//     return dist(mt1);
// }

int main(){
cout << setprecision(10) << fixed;
std::uniform_real_distribution<> dist(0, 1);

double mean=0;
#pragma omp parallel for reduction(+:mean)
for(int i=0; i<10; i++){
    mt19937 mt(rd());
    cout << "i=" << i << endl;
    for(int j=0; j<10; j++){
        cout << dist(mt) << " " << dist(mt) << endl;
    }
    cout << "------ \n";
}
cout << (double) mean/100 << endl;

}