#include "../clilonglist.h" // my command-line input utility functions
#include <stdlib.h>
#include <stdio.h>

void merge(long * inputv,
	   const int first_index,
	   const int last_of_first_subarray,
	   const int last_index) {

	int i1 = first_index; 
	int i2 = last_of_first_subarray + 1;

	int outputc = last_index -
		first_index + 1;
	long outputv[outputc];

	for (int i = 0; i < outputc; i++) {
		if ( 
		      (i1 <= last_of_first_subarray &&
		      inputv[i1] < inputv[i2]) ||
		      !(i2 <= last_index)
		      ) {
			outputv[i] = inputv[i1];
			i1++;
		} else {
			outputv[i] = inputv[i2];
			i2++;
		}
	}

	for (int i = 0; i < outputc; i++) {
		inputv[first_index + i] = outputv[i];
	}

}

void merge_sort_internal(long * inputv, int p, int r) {
	if (p >= r) {
		printf("skipped %d %d, it was %ld\n", p, r, inputv[p]);
		return;
	}

	int q = (p + r) / 2;
	merge_sort_internal(inputv, p, q);
	merge_sort_internal(inputv, q + 1, r);
	merge(inputv, p, q, r);
}

long * merge_sort(int inputc, long * inputv) {
	merge_sort_internal(inputv, 0, inputc - 1);
	return inputv;
}

int main(int argc, char * argv[]) {

	long test[4] = { 1, 3, 2, 4 };
	merge(test, 0, 1, 3);
	print_long_list(4, test);

	int inputc = argc - 1;
	long * inputv = extract_long_list(inputc, argv);
	// use my utility functions to grab the 
	// command line arguments as an array of longs

	inputv = merge_sort(inputc, inputv);

	print_long_list(inputc, inputv);

	free(inputv);
}
