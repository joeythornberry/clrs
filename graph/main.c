#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "output.h"
#include "detangle.h"

#define MAX_X 20
#define MAX_Y 20

int main(int argc, const char * argv[]) {

//	srand(time(NULL));
	srand(1);

	const int node_count = argc - 1;
	GraphNode * graph[node_count];
	for (int i = 0; i < node_count; i++) {
		graph[i] = parseGraphNode(argv[i + 1], node_count);
	}

	for (int i = 0; i < node_count; i++) {
		graph[i]->p.x = rand() % MAX_X;
		graph[i]->p.y = rand() % MAX_Y;
		printGraphNode(i, graph[i]);
	}

	outputGraph("graphbefore.js", node_count, graph);

	printf("DETANGLING...\n");
	detangleGraph(node_count, graph, MAX_X, MAX_Y);

	for (int i = 0; i < node_count; i++) {
		printGraphNode(i, graph[i]);
	}

	outputGraph("graph.js", node_count, graph);

	return 0;

}
