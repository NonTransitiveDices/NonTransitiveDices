// C program to distinct permutations of the string
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Returns true if str[curr] does not matches with any of
// the characters after str[start]
bool shouldSwap(char str[], int start, int curr)
{
	for (int i = start; i < curr; i++)
		if (str[i] == str[curr])
			return 0;
	return 1;
}

// Prints all distinct permutations in str[0..n-1]
char findPermutations(char str[], int index, int n, char **permutations)
{
	if (index >= n) {
        char result[n];
		strcpy(result, str);
		permutations[index] = result;
		return *result;
	}

	for (int i = index; i < n; i++) {

		// Proceed further for str[i] only if it
		// doesn't match with any of the characters
		// after str[index]
		bool check = shouldSwap(str, index, i);
		if (check) {
			// Swapping the str[index] with str[i]
			char temp = str[index];
			str[index] = str[i];
			str[i] = temp;
            // Recursively calling function findPermutations()
			char result = findPermutations(str, index + 1, n, permutations);
			// Swapping the str[index] with str[i]
			temp = str[index];
			str[index] = str[i];
			str[i] = temp;
		}
	}
}

// Driver code
int main()
{
	char str[] = "ABCA";
	int n = strlen(str);
    // create array of strings to store permutations
    char **permutations = malloc(sizeof(char *)*n);
    for(int i = 0; i < n; i++)
    {
        permutations[i] = malloc(sizeof(char)*n);
    }

    findPermutations(str, 0, n, permutations);

    for(int i = 0; i < n; i++)
    {
        printf("%s\n", permutations[i]);
    }

}

// This code is contributed by Aditya Kumar (adityakumar129)
