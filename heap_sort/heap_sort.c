#include "../clilonglist.h" // my command-line input utility functions
#include <stdlib.h>

// traditionally, these simple functions are
// inlined for greater efficiency
static inline int RIGHT(int i) {
	// return the index of the right child of a node
	return (i << 1) + 1;
}

static inline int LEFT(int i) {
	// return the index of the left child of a node
	return i << 1;
}

static inline int PARENT(int i) {
	// return the index of the parent of a node
	
	// note that / is floor division in C,
	// so PARENT(5) == PARENT(4) == 2, which
	// is what we want, because 5 and 4 have the 
	// same parent
	return i / 2;
}

void heapify(int heap_size, long * inputv, int i) {
	/** This function moves the element at i to 
	 *  a position where it is not greater than
	 *  either of its children, making sure to fix
	 *  the heap property whenever it breaks it **/


	int l = LEFT(i);
	int r = RIGHT(i);

	int largest;
	if ( l < heap_size && inputv[l] > inputv[i]) largest = l;
	else largest = i;
	// set the greater of the current and the left index as largest

	if ( r < heap_size && inputv[r] > inputv[largest] ) largest = r;
	// if the right index is larger, set it as the largest

	if (largest != i) {
		// if current index is not largest
		// swap largest and current
		long tmp = inputv[i];
		inputv[i] = inputv[largest];
		inputv[largest] = tmp;

		// repeat the whole process note that heapify is called with
		// the index that the original element ended up at
		heapify(heap_size, inputv, largest);
	}
}

void build_heap(int inputc, long * inputv) {
	/** This function turns a simple array into 
	 *  a heap by calling heapify() a bunch. **/

	for ( int i = (inputc + 1) / 2; i >= 0; i--) {
		// elements past inputc / 2 are guaranteed to be leaves
		heapify(inputc, inputv, i);
	}
}

void heap_sort(int inputc, long * inputv) {
	/** This function sorts inputv
	 *  by first turning it into a
	 *  heap, and then removing the
	 *  largest elements from the 
	 *  heap one by one **/

	build_heap(inputc, inputv);

	for ( int i = inputc - 1; i >= 1; i--) {
		// starting from the end of the list

		// switch the ith element with the first
		long tmp = inputv[i];
		inputv[i] = inputv[0];
		inputv[0] = tmp;
		// this puts the largest element (the one
		// at index 0) at the end of the array

		// re-heapify the part of the array UP TO
		// THE LARGEST VALUE THAT WE JUST MOVED,
		// so that the first section of the array
		// is a heap, but the second section is a 
		// sorted list.
		heapify(i, inputv, 0);
	}

}

int main(int argc, char * argv[]) {

	int inputc = argc - 1;
	long * inputv = extract_long_list(inputc, argv);
	// use my utility functions to grab the 
	// command line arguments as an array of longs
	
	heap_sort(inputc, inputv);
	print_long_list(inputc, inputv);

	free(inputv);
}
