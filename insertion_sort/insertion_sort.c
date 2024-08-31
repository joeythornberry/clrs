#include "../clilonglist.h" // my command-line input utility functions
#include <stdlib.h>

long * insertion_sort(int inputc, long * inputv) {
	// inputc: the length of the input array
	// inputv: the input array itself
	
	for (int i = 0; i < inputc; i++) {
		// for every value in the input
		long key = inputv[i];
		// grab the value and call it "key"
		int j = i - 1;
		// the index we are going to check first
		// it starts at i - 1 because that will
		// always be the last element in the 
		// sorted list
		
		// begin insertion step
		while (j >= 0 && inputv[j] > key) {
			inputv[j + 1] = inputv[j];
			j--;
		}
		inputv[j + 1] = key;
		// insertion step done!
	}

	return inputv;
}

int main(int argc, char * argv[]) {

	int inputc = argc - 1;
	long * inputv = extract_long_list(inputc, argv);
	// use my utility functions to grab the 
	// command line arguments as an array of longs

	inputv = insertion_sort(inputc, inputv);

	print_long_list(inputc, inputv);

	free(inputv);
}
