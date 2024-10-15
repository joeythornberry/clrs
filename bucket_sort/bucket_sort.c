#include "../clilonglist.h" // my command-line input utility functions
#include <stdio.h>
#include <stdlib.h>

// typical linked list node
typedef struct Node {
	long value;
	struct Node * next;
} Node;

void print_buckets(int num_buckets, Node ** buckets) {

	for (int i = 0; i < num_buckets; i ++) {
		printf("%d->", i);
		if (buckets[i] == NULL) {
			printf("empty\n");
			continue;
		}

		Node * current = buckets[i];
		printf("%ld->", current->value);
		while (current->next != NULL) {
			current = current->next;
			printf("%ld->", current->value);
		}
		printf("\n");
	}

}

int sort_list_into_subarray(long * array, int p, Node * list) {
	/* This function takes a linked list
	 *  places it, in sorted order,
	 *  at position p in the given
	 *  array. This implementation
	 *  uses a modified insertion sort. */

	if (list == NULL) return 0;
	// obviously, we don't want to touch an empty linked list
	
	// move the first element over
	array[p] = list->value;
	// this will keep track of how long the subarray
	// we're creating is
	int num_inserts = 1;

	// loop through the linked list until we run out of elements
	while ((list = list->next) != NULL) {

		// locate the last index in the subarray we're creating
		int i = num_inserts - 1;

		// move to the left, shifting each element over
		// until we find one that the current element
		// can fit in front of
		while (array[p + i] > list->value && i >= 0) {
			array[p + i + 1] = array[p + i];
			i--;
		}

		// put the current element into that spot
		array[p + i + 1] = list->value;

		// we inserted an element, so our subarray is longer
		num_inserts++;
	}

	// this tells the caller how many elements we added to the array
	return num_inserts;
}

void bucket_sort(
		int inputc,
		long * inputv,
		int num_buckets,
		int range_per_bucket
		) {

	// allocate an array of pointers to Nodes
	Node ** buckets = malloc(sizeof(Node*) * num_buckets);

	// loop through the input
	for (int i = 0; i < inputc; i++) {

		// quit if the current input is too big
		if (inputv[i] > num_buckets * range_per_bucket) {
			printf("\nERROR: %ld is too big.\n",
				inputv[i]);
			printf("Maximum allowed value is %d\n",
				num_buckets * range_per_bucket);
			return;
		}

		// find the "bucket" that this value belongs in
		int j = 0;
		while (inputv[i] > (j + 1) * range_per_bucket) {
			j++;
		}
		
		// create a linked list if there is none for 
		// this bucket, and put the current value in it
		if (buckets[j] == NULL) {
			buckets[j] = (Node *) malloc(sizeof(Node *));
			buckets[j]->value = inputv[i];
		} else {
			// if there already is a linked list
			// for this bucket,
			Node * current = buckets[j];
			// find the end of it
			while (current->next != NULL) {
				current = current->next;
			}

			// append a node with the current value to 
			// the end
			current->next = (Node *) malloc(sizeof(Node *));
			current->next->value = inputv[i];
		}
	}

	// at this point the entire input is placed 
	// into the correct buckets
	

	// now we need to sort each bucket, and combine them
	// all into the original array...

	print_buckets(num_buckets, buckets);

	// p marks the start of the unsorted portion of the array
	int p = 0;
	// for each bucket
	for (int i = 0; i < num_buckets; i++) {
		// sort the contents of the bucket into
		// the array, starting at index p
		p += sort_list_into_subarray(inputv, p, buckets[i]);
		// correct p for the next round
	}
}

int main(int argc, char * argv[]) {

	int inputc = argc - 1;
	long * inputv = extract_long_list(inputc, argv);
	// use my utility functions to grab the 
	// command line arguments as an array of longs
	
	bucket_sort(inputc, inputv, 10, 10);
	print_long_list(inputc, inputv);

	free(inputv);

	return 0;
}
