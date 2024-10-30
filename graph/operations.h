#pragma once 

typedef struct Point {
	float x;
	float y;
} Point;

Point closestPointOnLine(Point p, Point p1, Point p2);

int segmentsIntersect(Point p1, Point p2, Point p3, Point p4);

float slope(Point p1, Point p2);
