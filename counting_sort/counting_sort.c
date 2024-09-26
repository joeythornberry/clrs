#include "../clilonglist.h" // my command-line input utility functions
#include <stdlib.h>

long * counting_sort(int inputc, long * inputv, int k) {
	long * c = malloc(k * sizeof(long));
	long * outputv = malloc(inputc * sizeof(long));

	for (int i = 0; i < inputc; i++) {
		if (inputv[i] > k) continue;
		c[inputv[i]] += 1;
	}

	for (int i = 1; i < k; i++) c[i] += c[i - 1];

	for (int j = inputc - 1; j >= 0; j--) {
		if (inputv[j] > k) continue;
		outputv[c[inputv[j]] - 1] = inputv[j];
		c[inputv[j]]--;
	}

	free(inputv);
	free(c);
	return outputv;
}

int main(int argc, char * argv[]) {

	int inputc = argc - 1;
	long * inputv = extract_long_list(inputc, argv);
	// use my utility functions to grab the 
	// command line arguments as an array of longs
	
	inputv = counting_sort(inputc, inputv, 100);
	print_long_list(inputc, inputv);

	free(inputv);
}
