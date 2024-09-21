#include "../clilonglist.h" // my command-line input utility functions
#include <stdlib.h>

int partition(long * inputv, int p, int r) {
	/** This function arranges the input 
	 *  list into two sections, where elements
	 *  smaller than x (the first element) go
	 *  in the left section, and bigger and 
	 *  equal elements go in the right 
	 *  section **/

	int i = p - 1; 
	// this index will move left to right
	// looking for big elements
	
	int j = r + 1;
	// this index will move right to left
	// looking for small elements
	
	long x = inputv[p];
	// this is the element we compare things
	// to (it's arbitrarily chosen to be the
	// element that is in the first position)

	while (1) { // loop until loop is broken

		// move i to the right until it
		// finds an element not smaller
		// than x
		do i ++; while (inputv[i] < x);

		// move j to the left until it
		// finds an element not bigger 
		// than x
		do j --; while (inputv[j] > x);

		if ( i < j ) { 
		// if i and j have not met, swap
		// the elements they stopped at
			long tmp = inputv[i];
			inputv[i] = inputv[j];
			inputv[j] = tmp;
		} else return j;
		// if i and j have met, we're done
		// return j so further code knows 
		// where the partitions are
	}
}

void quick_sort_internal(long * inputv, int p, int r) {
	
	if (p >= r) return;
	// no need to sort a subarray of length 1

	int q = partition(inputv, p, r);
	// partition the array into big and small sections

	quick_sort_internal(inputv, p, q);
	// sort the small (left) section
	quick_sort_internal(inputv, q + 1, r);
	// sort the big (right) section
}

void quick_sort(int inputc, long * inputv) {
	/** this function just provides a nice
	 *  user interface for quick_sort_internal **/
	quick_sort_internal(inputv, 0, inputc - 1);
}

int main(int argc, char * argv[]) {

	int inputc = argc - 1;
	long * inputv = extract_long_list(inputc, argv);
	// use my utility functions to grab the 
	// command line arguments as an array of longs

	quick_sort(inputc, inputv);
	print_long_list(inputc, inputv);

	free(inputv);
}
