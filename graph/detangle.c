#include <assert.h>
#include "operations.h"
#include "graph.h"
#include <math.h>
#include <stdio.h>

void moveTowards(GraphNode * n, Point end, float distance) {
	float m = slope(n->p, end);
	float norm = sqrtf(1+m*m);
	float direction = -1 + (end.x > n->p.x)*2;
	n->p.x += direction * distance / norm;
	n->p.y += m * direction * distance/ norm;
}

void detangleTwoNodes(GraphNode * graph[], int i1, int i2) {
	GraphNode * n1 = graph[i1];
	GraphNode * n2 = graph[i2];
	if (!n1->edges || !n2->edges) return;

	GraphEdge * h1 = n1->edges;
	while (h1) {
		if (h1->end == i1 || h1->end == i2) goto next1;
		Point e1 = graph[h1->end]->p;
		GraphEdge * h2 = n2->edges;
		while (h2) {
			if (h2->end == i2 || h2->end == i1 || h1-> end == h2->end) goto next2;
			Point e2 = graph[h2->end]->p;
			if (segmentsIntersect(n1->p, e1, n2->p, e2)) {
				Point c = intersectionPoint(n1->p, e1, n2->p, e2);
				float d = dist(n1->p, c) + (dist(c, e1) / 2);
				moveTowards(n1, e1, d);
			}

next2:
			h2 = h2->next;
		}

next1:
		h1 = h1->next;
	}
}

void decrossGraph(int node_count, GraphNode * graph[]) {
	for (int i = 0; i < node_count; i++) {
		for (int j = 0; j < node_count; j++) {
			if (i != j) detangleTwoNodes(graph, i, j);
		}
	}
}

void inflateGraph(int node_count, GraphNode * graph[]) {

	const int INFLATION_FACTOR = 3;

	float minx = 2000;
	float miny = 2000;
	for (int i = 0; i < node_count; i++) {	
		if (graph[i]->p.x < minx) minx = graph[i]->p.x;
		if (graph[i]->p.y < miny) miny = graph[i]->p.y;
	}

	for (int i = 0; i < node_count; i++) {	
		graph[i]->p.x -= minx - 1;
		graph[i]->p.x *= INFLATION_FACTOR;
		graph[i]->p.y -= miny - 1;
		graph[i]->p.y *= INFLATION_FACTOR;
	}
}

void loosenGraph(int node_count, GraphNode * graph[]) {
}

void detangleGraph(int node_count, GraphNode * graph[]) {
	for (int i = 0; i < 3; i++) {
		printf("Detangling round %d...\n", i);
		decrossGraph(node_count, graph);
	}

	inflateGraph(node_count, graph);
}

