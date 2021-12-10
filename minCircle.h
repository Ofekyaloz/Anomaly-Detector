//
// Created by giligutfeld on 06/12/2021.
//


#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"
#include <math.h>
#include <vector>

using namespace std;

// ------------ DO NOT CHANGE -----------

class Circle{
public:
    Point center;
    float radius;
    Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------

float distance(const Point& p1, const Point& p2);
bool is_in_circle(const Circle& c, const Point& p);
Point get_circle_center(float x1, float y1, float x2, float y2);
Circle get_circle(const Point& p1, const Point& p2, const Point& p3);
Circle get_circle(const Point& p1, const Point& p2);
bool is_encloses_points(const Circle& c, const vector<Point*>& points);
Circle min_circle_trivial(vector<Point*>& points);
Circle welzl_algorithm(Point** points, vector<Point*> boundary_points, int n);
Circle findMinCircle(Point** points, size_t size);

#endif /* MINCIRCLE_H_ */
