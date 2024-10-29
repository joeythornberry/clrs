#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

typedef struct GraphEdge {
	int end;
	struct GraphEdge * next;
} GraphEdge;

typedef struct GraphNode {
	struct GraphEdge * edges;
	int x;
	int y;
} GraphNode;

void printGraphNode(GraphNode * g) {
	printf("%d %d NODE ", g->x, g->y);
	if (g->edges == NULL) return;
	GraphEdge * head = g->edges;
	while (head != NULL) {
		printf(" %d ", head->end);
		head = head->next;
	}
	printf("\n");
}

GraphNode * parseGraphNode(const char * input, const int node_count) {
	int i = 0;

	int edges_present[node_count] = {};

	GraphEdge start;
	start.end = -1;
	start.next = NULL;
	GraphEdge * head = &start;

	int start_of_edge = 0;
	while (1) {
		if (input[i] == '\0' || input[i] == ',') {
			int edge_digits = i - start_of_edge;

			char edge_string[edge_digits + 1]; // don't forget the null terminator
			edge_string[edge_digits] = '\0';
			for (int j = 0; j < edge_digits; j++) {
				edge_string[j] = input[start_of_edge + j];
			}

			char * endchar;
			int new_end = strtol(edge_string, &endchar, 10);
			if (new_end >= node_count) {
				printf("Edge cannot end at %d because there is no node %d. Ignoring.\n", new_end, new_end);
			} else if (edges_present[new_end]) {
				printf("Edge %d is present more than once. Ignoring duplicates.\n", new_end);
			} else {

				GraphEdge * new = malloc(sizeof(GraphEdge));
				new->end = new_end;
				new->next = NULL;

				head->next = new;
				head = new;

				edges_present[new_end] = 1;
			}

				start_of_edge = i + 1; // don't count the comma
		}

		if (input[i] == '\0') break;
		i++;
	}

	GraphNode * output = malloc(sizeof(GraphNode));
	output->x = -1;
	output->y = -1;
	output->edges = start.next;

	return output;
}

int main(int argc, const char * argv[]) {

	srand(time(NULL));

	const int node_count = argc - 1;
	GraphNode * graph[node_count];
	for (int i = 0; i < node_count; i++) {
		graph[i] = parseGraphNode(argv[i + 1], node_count);
	}

	for (int i = 0; i < node_count; i++) {
		graph[i]->x = rand() % 100;
		graph[i]->y = rand() % 50;
		printGraphNode(graph[i]);
	}
	return 0;
}
