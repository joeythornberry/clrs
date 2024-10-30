#include <assert.h>
#include <stdio.h>
#include "operations.h"
#include "graph.h"

void moveTowards(GraphNode * n, Point end) {
	float m = slope(n->p, end);

	int direction = -1 + (end.x > n->p.x)*2;
	n->p.x += direction;
	n->p.y += m * direction;
}

void detangleTwoNodes(GraphNode * graph[], int i1, int i2) {
	GraphNode * n1 = graph[i1];
	GraphNode * n2 = graph[i2];
	if (!n1->edges || !n2->edges) return;

	GraphEdge * h1 = n1->edges;
	while (h1) {
		if (h1->end == i1 || h1->end == i2) {
			h1 = h1->next;
			continue;
		}
		Point e1 = graph[h1->end]->p;
		GraphEdge * h2 = n2->edges;
		while (h2) {
			if (h2->end == i2 || h2->end == i1 || h1-> end == h2->end) {
				h2 = h2->next;
				continue;
			}
			Point e2 = graph[h2->end]->p;
			while (segmentsIntersect(n1->p, e1, n2->p, e2)) {
				moveTowards(n1, e1);
			}
			h2 = h2->next;
		}

		h1 = h1->next;
	}
}

void detangleGraph(int node_count, GraphNode * graph[]) {
	for (int i = 0; i < node_count; i++) {
		for (int j = 0; j < node_count; j++) {
			if (i != j) detangleTwoNodes(graph, i, j);
		}
	}
}

