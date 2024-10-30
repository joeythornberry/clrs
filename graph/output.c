#include <stdio.h>
#include "graph.h"

void outputEdge(FILE * f, int x1, int y1, int x2, int y2) {
	fprintf(f, "e(%d, %d, %d, %d);\n", x1, y1, x2, y2);
}

void outputNode(FILE * f, int i, int x, int y) {
	fprintf(f, "n(%d, %d, %d);\n", i, x, y);
}

void outputGraph(const char * filename, int node_count, GraphNode * graph[]) {
	FILE * f = fopen(filename, "w");

	for (int i = 0; i < node_count; i++) {
		if (!graph[i]->edges) continue;
		GraphEdge * head = graph[i]->edges;
		while (head) {
			outputEdge(f, graph[i]->p.x, graph[i]->p.y, graph[head->end]->p.x, graph[head->end]->p.y);
			head = head->next;
		}
	}

	for (int i = 0; i < node_count; i++) {
		outputNode(f, i, graph[i]->p.x, graph[i]->p.y);
	}
}
