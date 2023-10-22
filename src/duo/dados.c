#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int Nontransitive(int* die1, int* die2, int faces, int values);
int RecursiveTransitive(int **matrix, int **permutations, int dices, int faces, int values, int nPermutations, int die);

int main()
{

    for (int config = 3; config < 10; config ++)
    {

        FILE* arquivo;

        char filename[30] = "data/dados";
        char ext[30] = ".txt";
        char str[10];
        sprintf(str, "%d", config);
        strcat(filename, str);
        strcat(filename, ext);

        arquivo = fopen(filename, "r");

        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo");
            exit(1);
        }

        // read parameters
        int dices;
        fscanf(arquivo, "%d", &dices);
        int faces;
        fscanf(arquivo, "%d", &faces);
        int values;
        fscanf(arquivo, "%d", &values);
        int nPermutations;
        fscanf(arquivo, "%d", &nPermutations);

        int **permutation = malloc(sizeof(int *)*nPermutations);  
        for(int i = 0; i < nPermutations; i++)
        {
            permutation[i] = malloc(sizeof(int)*values);
        }

        int i = 0;
        do
        {
            for (int j = 0; j < values; j++)
            {
                fscanf(arquivo, "%d", &permutation[i][j]);
            }
            i++;
        }
        while (!feof(arquivo));

        fclose(arquivo);

        int **matrix = malloc(sizeof(int *)*dices);  
        for(int i = 0; i < dices; i++)
        {
            matrix[i] = malloc(sizeof(int)*values);
        }

        int count = RecursiveTransitive(matrix, permutation, dices, faces, values, nPermutations, 0);
        float total = pow(nPermutations, dices);
        float razao = count/total;

        printf("A probabilidade de dados não transitivos com %d dados, %d faces e %d valores é de %d/%.0f = %.20f\n", dices, faces, values, count, total, razao);
    }

}

int Nontransitive(int* die1, int* die2, int faces, int values)
{
    
    int total = faces * faces;
    int victory1 = 0;

    for (int i = 0; i < values; i++)
    {
        for (int j = i+1; j < values; j++)
        {
            victory1 += die1[i] * die2[j];
        }
    }

    if (victory1 > total / 2)
    {
        return 1;
    }
    else
    {
        int victory2 = 0;

        for (int i = 0; i < values; i++)
        {
            for (int j = i+1; j < values; j++)
            {
                victory2 += die2[i] * die1[j];
            }
        }

        if (victory1 > victory2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int RecursiveTransitive(int **matrix, int **permutations, int dices, int faces, int values, int nPermutations, int die)
{
    int count = 0;

    if (die == dices)
    {
        if (Nontransitive(matrix[die-1], matrix[0], faces, values))
        {
            printf("matriz: \n");
            for (int i = 0; i < dices; i++)
            {
                for (int j = 0; j < values; j++)
                {
                    printf("%d ", matrix[i][j]);
                }
                printf("\n");
            }
            return 1;
        } else
        {
            return 0;
        }
    } else 
    {
        for (int i = 0; i < nPermutations; i++)
        {
            if (die == 0)
            {
                matrix[die] = permutations[i];
                count += RecursiveTransitive(matrix, permutations, dices, faces, values, nPermutations, die+1);
            } else
            {
                if (Nontransitive(matrix[die-1], permutations[i], faces, values))
                {
                    matrix[die] = permutations[i];
                    count += RecursiveTransitive(matrix, permutations, dices, faces, values, nPermutations, die+1);
                }
            }
        }
    }

    return count;
}
