#include <stdio.h>
#include <stdlib.h>

long * extract_long_list(int num_inputs, char * argv[]) {

	long * out = malloc(sizeof(long) * num_inputs); 

	for (int i = 0; i < num_inputs; i++) {
		char * end;
		out[i] = strtol(argv[i + 1], &end, 10);
	}

	return out;

}

void print_long_list(int len, const long * input) {
	for (int i = 0; i < len; i++) {
		printf("%ld ", input[i]);
	}
	putchar('\n');
}
