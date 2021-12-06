//
// Created by giligutfeld on 06/12/2021.
//

#ifndef THE_BEST_PROJECT_MINCIRCLE_H
#define THE_BEST_PROJECT_MINCIRCLE_H

#include <algorithm>
#include <assert.h>
#include <math.h>
#include <vector>
#include "anomaly_detection_util.h"

// Structure to represent a 2D circle
class Circle {
public:
    Point p;
    float r;
    Circle(Point p, float r):p(p),r(r){}
};

Circle welzl(const std::vector<Point>& P);

#endif //THE_BEST_PROJECT_MINCIRCLE_H
