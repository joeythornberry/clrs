#include "operations.h"
#pragma once

typedef struct GraphEdge {
	int end;
	struct GraphEdge * next;
} GraphEdge;

typedef struct GraphNode {
	struct GraphEdge * edges;
	Point p;
} GraphNode;


void printGraphNode(int i, GraphNode * g);

GraphNode * parseGraphNode(const char * input, const int node_count);
