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
	float dx = direction * distance / norm;
	float dy = m * direction * distance / norm;
	//if (dy / dx > 1 || dy / dx < -1) printf("GT %2.2f\n", dy / dx);
	//else printf("LE %2.2f\n", dy / dx);
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

Point findCentroid(int node_count, GraphNode * graph[]) {
	int total_x = 0;
	int total_y = 0;

	for (int i = 0; i < node_count; i++) {
		total_x += graph[i]->p.x;
		total_y += graph[i]->p.y;
	}

	Point centroid = { total_x / node_count, total_y / node_count };
	return centroid;
}


void normalizeGraphPosition(int node_count, GraphNode * graph[], int max_x, int max_y) {

	Point centroid = findCentroid(node_count, graph);
	Point adjustment;
 	adjustment.x = max_x / 2 - centroid.x;
	adjustment.y = max_y / 2 - centroid.y;

	for (int i = 0; i < node_count; i++) {	
		graph[i]->p.x += adjustment.x;
		graph[i]->p.y += adjustment.y;
	}
}

Point calculateInflationFactors(int node_count, GraphNode * graph[], int max_x, int max_y) {
	float highx = 1;
	float highy = 1;

	for (int i = 0; i < node_count; i++) {	
		if (graph[i]->p.x > highx) highx = graph[i]->p.x;
		if (graph[i]->p.y > highy) highy = graph[i]->p.y;
	}

	Point inflation_factors = { max_x / highx, max_y / highy };
	return inflation_factors;
}

void inflateGraph(int node_count, GraphNode * graph[], Point inflation_factors) {
	for (int i = 0; i < node_count; i++) {	
		graph[i]->p.x *= inflation_factors.x;
		graph[i]->p.y *= inflation_factors.y;
	}
}

int hasCloseNeighbor(int i, int node_count, GraphNode * graph[], float cutoff) {
	for (int j = 0; j < node_count; j++) {
		if (j == i) continue;
	}
	return 1;
}

void loosenGraph(int node_count, GraphNode * graph[], float cutoff) {
	for (int i = 0; i < node_count; i++) {
		for (int j = 0; j < node_count; j++) {
			if (i == j) continue;
			float d = dist(graph[i]->p, graph[j]->p);
			if (d <= cutoff) {
				printf("backing up %2.2f\n", -(cutoff-d));
				moveTowards(graph[i], graph[j]->p, -(cutoff-d));
			}
		}
	}
}

void tightenGraph(int node_count, GraphNode * graph[], float cutoff, int direction) {
	printf("tightening...\n");
	for (int i = 0; i < node_count; i++) {
		if (!graph[i]->edges) return;
		GraphEdge * h = graph[i]->edges;
		while (h) {
			if (h->end == i) goto next;
			float d = dist(graph[i]->p, graph[h->end]->p);
			if (d > cutoff && direction > 0) {
				moveTowards(graph[i], graph[h->end]->p,  d-cutoff);
			} else if (d < cutoff && direction < 0) {
				moveTowards(graph[i], graph[h->end]->p, -cutoff);
			}
next:
			h = h->next;
		}
	}
}

void detangleGraph(int node_count, GraphNode * graph[], int max_x, int max_y) {
	for (int i = 0; i < 25; i++) {
		printf("Detangling round %d...\n", i);
		decrossGraph(node_count, graph);
		tightenGraph(node_count, graph, 5, 1);
		loosenGraph(node_count, graph, 3);
	}
	normalizeGraphPosition(node_count, graph, max_x, max_y);
}

