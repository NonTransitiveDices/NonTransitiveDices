    #include <iostream>
    #include <iomanip>
    #include <algorithm>

    using namespace std;
    
    char letters[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    string generateGame(int *numAtF)
    {
        stringstream result;

        for (int i = 0; i < 6; i++)
            for (int j = 0; j < numAtF[i]; j++)
                result << letters[i];

        return result.str();
    }

    bool specialp (string permutation)
    {
        int numX[6];
        int numXY[6][6];
        for (int i = 0; i < 6; i++) {
            numX[i] = 0;
            for (int j = 0; j < 6; j++) {
                numXY[i][j] = 0;
            }
        }

        for (uint64_t i = 0; i < 36; i++){
            switch(permutation[i]){
                case 'A':
                    numX[0]++;
                    for (int j = 0+1; j < 6; j++)
                        numXY[0][j] += numX[j];
                    break;
                case 'B':
                    numX[1]++;
                    for (int j = 1+1; j < 6; j++)
                        numXY[1][j] += numX[j];
                    break;
                case 'C':
                    numX[2]++;
                    for (int j = 2+1; j < 6; j++)
                        numXY[2][j] += numX[j];
                    break;
                case 'D':
                    numX[3]++;
                    for (int j = 3+1; j < 6; j++)
                        numXY[3][j] += numX[j];
                    break;
                case 'E':
                    numX[4]++;
                    for (int j = 4+1; j < 6; j++)
                        numXY[4][j] += numX[j];
                    break;
                case 'F':
                    numX[5]++;
                    for (int j = 5+1; j < 6; j++)
                        numXY[5][j] += numX[j];
                    break;
            }
        }
        for (int i = 0; i < 6; i++) {
            for (int j = i+1; j < 6; j++) {
                numXY[j][i] = 36 - numXY[i][j];
            }
        }

        // print matrx
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                cout << setw(3) << numXY[i][j];
            }
            cout << endl;
        }

        int index[][7] = {
            {0, 1, 2, 3, 4, 5, 0}, {0, 1, 2, 3, 5, 4, 0}, {0, 1, 2, 4, 3, 5, 0}, {0, 1, 2, 4, 5, 3, 0},
            {0, 1, 2, 5, 3, 4, 0}, {0, 1, 2, 5, 4, 3, 0}, {0, 1, 3, 2, 4, 5, 0}, {0, 1, 3, 2, 5, 4, 0},
            {0, 1, 3, 4, 2, 5, 0}, {0, 1, 3, 4, 5, 2, 0}, {0, 1, 3, 5, 2, 4, 0}, {0, 1, 3, 5, 4, 2, 0},
            {0, 1, 4, 2, 3, 5, 0}, {0, 1, 4, 2, 5, 3, 0}, {0, 1, 4, 3, 2, 5, 0}, {0, 1, 4, 3, 5, 2, 0},
            {0, 1, 4, 5, 2, 3, 0}, {0, 1, 4, 5, 3, 2, 0}, {0, 1, 5, 2, 3, 4, 0}, {0, 1, 5, 2, 4, 3, 0},
            {0, 1, 5, 3, 2, 4, 0}, {0, 1, 5, 3, 4, 2, 0}, {0, 1, 5, 4, 2, 3, 0}, {0, 1, 5, 4, 3, 2, 0},
            {0, 2, 1, 3, 4, 5, 0}, {0, 2, 1, 3, 5, 4, 0}, {0, 2, 1, 4, 3, 5, 0}, {0, 2, 1, 4, 5, 3, 0},
            {0, 2, 1, 5, 3, 4, 0}, {0, 2, 1, 5, 4, 3, 0}, {0, 2, 3, 1, 4, 5, 0}, {0, 2, 3, 1, 5, 4, 0},
            {0, 2, 3, 4, 1, 5, 0}, {0, 2, 3, 4, 5, 1, 0}, {0, 2, 3, 5, 1, 4, 0}, {0, 2, 3, 5, 4, 1, 0},
            {0, 2, 4, 1, 3, 5, 0}, {0, 2, 4, 1, 5, 3, 0}, {0, 2, 4, 3, 1, 5, 0}, {0, 2, 4, 3, 5, 1, 0},
            {0, 2, 4, 5, 1, 3, 0}, {0, 2, 4, 5, 3, 1, 0}, {0, 2, 5, 1, 3, 4, 0}, {0, 2, 5, 1, 4, 3, 0},
            {0, 2, 5, 3, 1, 4, 0}, {0, 2, 5, 3, 4, 1, 0}, {0, 2, 5, 4, 1, 3, 0}, {0, 2, 5, 4, 3, 1, 0},
            {0, 3, 1, 2, 4, 5, 0}, {0, 3, 1, 2, 5, 4, 0}, {0, 3, 1, 4, 2, 5, 0}, {0, 3, 1, 4, 5, 2, 0},
            {0, 3, 1, 5, 2, 4, 0}, {0, 3, 1, 5, 4, 2, 0}, {0, 3, 2, 1, 4, 5, 0}, {0, 3, 2, 1, 5, 4, 0},
            {0, 3, 2, 4, 1, 5, 0}, {0, 3, 2, 4, 5, 1, 0}, {0, 3, 2, 5, 1, 4, 0}, {0, 3, 2, 5, 4, 1, 0},
            {0, 3, 4, 1, 2, 5, 0}, {0, 3, 4, 1, 5, 2, 0}, {0, 3, 4, 2, 1, 5, 0}, {0, 3, 4, 2, 5, 1, 0},
            {0, 3, 4, 5, 1, 2, 0}, {0, 3, 4, 5, 2, 1, 0}, {0, 3, 5, 1, 2, 4, 0}, {0, 3, 5, 1, 4, 2, 0},
            {0, 3, 5, 2, 1, 4, 0}, {0, 3, 5, 2, 4, 1, 0}, {0, 3, 5, 4, 1, 2, 0}, {0, 3, 5, 4, 2, 1, 0},
            {0, 4, 1, 2, 3, 5, 0}, {0, 4, 1, 2, 5, 3, 0}, {0, 4, 1, 3, 2, 5, 0}, {0, 4, 1, 3, 5, 2, 0},
            {0, 4, 1, 5, 2, 3, 0}, {0, 4, 1, 5, 3, 2, 0}, {0, 4, 2, 1, 3, 5, 0}, {0, 4, 2, 1, 5, 3, 0},
            {0, 4, 2, 3, 1, 5, 0}, {0, 4, 2, 3, 5, 1, 0}, {0, 4, 2, 5, 1, 3, 0}, {0, 4, 2, 5, 3, 1, 0},
            {0, 4, 3, 1, 2, 5, 0}, {0, 4, 3, 1, 5, 2, 0}, {0, 4, 3, 2, 1, 5, 0}, {0, 4, 3, 2, 5, 1, 0},
            {0, 4, 3, 5, 1, 2, 0}, {0, 4, 3, 5, 2, 1, 0}, {0, 4, 5, 1, 2, 3, 0}, {0, 4, 5, 1, 3, 2, 0},
            {0, 4, 5, 2, 1, 3, 0}, {0, 4, 5, 2, 3, 1, 0}, {0, 4, 5, 3, 1, 2, 0}, {0, 4, 5, 3, 2, 1, 0},
            {0, 5, 1, 2, 3, 4, 0}, {0, 5, 1, 2, 4, 3, 0}, {0, 5, 1, 3, 2, 4, 0}, {0, 5, 1, 3, 4, 2, 0},
            {0, 5, 1, 4, 2, 3, 0}, {0, 5, 1, 4, 3, 2, 0}, {0, 5, 2, 1, 3, 4, 0}, {0, 5, 2, 1, 4, 3, 0},
            {0, 5, 2, 3, 1, 4, 0}, {0, 5, 2, 3, 4, 1, 0}, {0, 5, 2, 4, 1, 3, 0}, {0, 5, 2, 4, 3, 1, 0},
            {0, 5, 3, 1, 2, 4, 0}, {0, 5, 3, 1, 4, 2, 0}, {0, 5, 3, 2, 1, 4, 0}, {0, 5, 3, 2, 4, 1, 0},
            {0, 5, 3, 4, 1, 2, 0}, {0, 5, 3, 4, 2, 1, 0}, {0, 5, 4, 1, 2, 3, 0}, {0, 5, 4, 1, 3, 2, 0},
            {0, 5, 4, 2, 1, 3, 0}, {0, 5, 4, 2, 3, 1, 0}, {0, 5, 4, 3, 1, 2, 0}, {0, 5, 4, 3, 2, 1, 0}};
        
        bool acc = true;
        bool result = false;

        for (int numindex = 0; numindex < 1; numindex++) {

            for (int i = 0; i < 6; i++) {
                if (numXY[index[numindex][i]][index[numindex][i+1]] <= 18) {
                    acc = false;
                    break;
                }
            }

            cout << "acc: " << acc << endl;
            
            if (acc) {
                int comparisons[][2] = {{0, 3}, {1,4}, {2,5}};
                // This checks the draws
                for (int j = 0; j < 3; j++) {
                    if (!(numXY[index[numindex][comparisons[j][1]]][index[numindex][comparisons[j][2]]] == 18)) {
                        acc = false;
                        break;
                    }
                }
            }
            
            
            if (acc) {
                for (int i = 0; i < 6; i++) {
                    int sum = 0;
                    for (int j = 0; j < 6; j++) {
                        sum += (numXY[index[numindex][i]][index[numindex][j]] > 18);
                        if (sum > 2) {
                            cout << "sum > 2, que pena" << endl;
                            acc = false;
                            break;
                        }
                    }
                    if (sum != 2) {
                        cout << "sum < 2, que pena" << endl;
                        acc = false;
                        break;
                    }
                }
            }

            result = (result or acc);
            if (result) return result;
        }

        return result;
    }

    void scan_games (string str)
    {
        while (true)
        {
            if(specialp(str)) cout << str << endl;
            random_shuffle(str.begin(), str.end());
        }
    }

    int main()
    {
        int a[6] = {6,6,6,6,6,6};
        string test = "AAAAAABBBBBBCCCCCCDDDDDDEEEEEEFFFFFF";
        scan_games(test);

    }