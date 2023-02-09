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
std::random_device rd;

uint64_t D(int n){
	long double result = 1/std::pow(10,30);
	
	for(long double i=1; i<=n; i++){
		result *= ((2*n+i)*(n+i))/(i*i);
	}
	
	return (uint64_t)(result);
}

long double esperanca(long double* a, int n){
	long double result = 0;
	
	for(int i=0; i<n; i++){
		result += a[i];
	}
	
	return result/n;
}

long double variancia(long double* a, int n){
	long double result = 0;
	long double esp = esperanca(a, n);

	for(int i=0; i<n; i++){
		result += std::pow(a[i]-esp, 2);
	}

	return result/(n-1);
}

int main(){
	
	cout << setprecision(10) << fixed;
	
	std::uniform_real_distribution<> dist(0, 1);

	int total=10000000;
	const int experiments=8;

	for (int nL=10000; nL<=10000; nL++){

		// cout << "Experimento para n = " << nL << endl;
		// cout << "Total de amostras = " << total << endl;
		// cout << "Numero de experimentos = " << experiments << endl;

		auto start = high_resolution_clock::now();
	
		double nt=0;

		const int n=nL;
		const int max=2;
		const int nn=n*n;
		long double *exp_med = new long double[experiments];

		#pragma omp parallel for reduction(+:nt)
		for(int j=0; j<experiments; j++){
			mt19937 gen(rd());

			for (int i=0; i<total; i++){

				double a[n+1], b[n+1], c[n+1];
				
				for(int j=0; j<n; j++){
					a[j]=dist(gen);
					b[j]=dist(gen);
					c[j]=dist(gen);
				}

				sort(a, a+n);
				sort(b, b+n);
				sort(c, c+n);
				
				int Nab=0, Nbc=0, Nca=0;
				int Pa=0, Pb=0, Pc=0;
				int rounds = 3*n;

				a[n] = b[n] = c[n] = max+1;
				
				while(rounds--){
					
					if(a[Pa]<b[Pb] and a[Pa]<c[Pc]){
						Pa++;
						Nab += Pb;
					}
					else if(b[Pb]<a[Pa] and b[Pb]<c[Pc]){
						Pb++;
						Nbc += Pc;
					}
					else {
						Pc++;
						Nca += Pa;
					}
					
				}

				if((2*Nab > nn and 2*Nbc > nn and 2*Nca > nn)
					or (2*Nab < nn and 2*Nbc < nn and 2*Nca < nn)) nt++;
			}
		
			exp_med[j] = nt/(total);
			cout << "Experimento " << j << " concluido" << endl;
			cout << "E(n) = " << exp_med[j] << endl;

		}

		long double esp = esperanca(exp_med, experiments);
		long double var = variancia(exp_med, experiments);
		long double sd = std::sqrt(var);

		if (sd > 0.001) {
			cout << "~ Corrigindo amostras, variancia = " << var << ", desvio padrao = " << sd << endl;
			total *= 2;
			nL--;
			continue;
		}

		auto stop = high_resolution_clock::now();

		double t = esp;

		// cout << "......" << endl;
		cout << "Tempo de execucao: " << duration_cast<milliseconds>(stop-start).count() << " ms" << endl;
		// cout << "D(n) = " << D(n) << endl;
		// cout << "E(n) = " << esp << endl;
		// cout << "Var(n) = " << var << endl;
		// cout << "SD(n) = " << sd << endl;
		// cout << "t(n) = " << t << endl;
		// cout << "------------------------" << endl;
		cout << "(" << n << "," << t << ")" << endl;

	}

}