#include <assert.h>
#include <math.h>
#include <stdio.h>

typedef struct Point {
	float x;
	float y;
} Point;

int eq(float a, float b) {
	return (a - b < 0.1) && (b - a < 0.1);
}

float slope(Point p1, Point p2) {
	if ( eq(p1.x, p2.x) ) {
		return (p1.y - p2.y) / 0.01;
	}
	return (p1.y - p2.y) / (p1.x - p2.x);
}

float dist(Point p1, Point p2) {
	return sqrtf((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}

int isOnLine(Point p, Point p1, Point p2) {
	float m = slope(p1, p2);
	float b = p1.y - m * p1.x;
	return eq(p.y, m * p.x + b);
}


Point closestPointOnLine(Point p, Point p1, Point p2) {
	float m = slope(p1, p2);
	float b = p1.y - (m * p1.x);

	float x = (m / (m*m + 1)) * (p.y + p.x/m - b);
	float y = m*x + b;

	Point closest = {x, y};
	return closest;
}

Point intersectionPoint(Point p1, Point p2, Point p3, Point p4) {
	float m1 = slope(p1, p2);
	float m2 = slope(p3, p4);

	float b1 = p1.y - m1 * p1.x;
	float b2 = p3.y - m2 * p3.x;

	float x = (b2 - b1) / (m1 - m2);
	float y = m1 * x + b1;

	Point intersection = {x, y};
	return intersection;
}

int isOnSegment(Point p, Point p1, Point p2) {
	assert(isOnLine(p, p1, p2));
	// this function assumes that p is
	// on the line connecting p1 and p2
	
	return (p1.x <= p.x && p.x <= p2.x) || (p2.x <= p.x && p.x <= p1.x);
}

int segmentsIntersect(Point p1, Point p2, Point p3, Point p4) {
	Point c = intersectionPoint(p1, p2, p3, p4);
	return isOnSegment(c, p1, p2) && isOnSegment(c, p3, p4);
}

int maintest() {
	Point p = {3,1};
	// y = 2x + 2
	Point p0 = {0,2};
	Point p1 = {3,8};
	Point p2 = {5,12};
	// y = -x + 2
	Point p3 = {3,-1};
	Point p4 = {5,-3};
	Point p5 = {-2,4};
	assert(slope(p1,p2) == 2);

	Point c = closestPointOnLine(p, p1, p2);
	assert(eq(c.x, 0.2));
	assert(eq(c.y, 2.4));

	c = intersectionPoint(p1, p2, p3, p4);
	assert(eq(c.x, 0));
	assert(eq(c.y, 2));
	assert(isOnLine(c, p1, p2));

	assert(!isOnSegment(c, p1, p2));
	assert(isOnSegment(c, p0, p2));
	assert(isOnSegment(c, p1, p0));

	assert(!segmentsIntersect(p1, p2, p3, p4));
	assert(!segmentsIntersect(p1, p2, p3, p5));
	assert(segmentsIntersect(p0, p2, p3, p5));

	return 0;
}
