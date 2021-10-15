//
// Created by gili on 15/10/2021.
//

#include "anomaly_detection_util.h"

float var(float* x, int size) {
    float avg = 0, sum = 0;

    for(int i = 0; i < size; i++){
        avg += x[i];
        sum += x[i] * x[i];
    }
    avg /= size;
    sum /= size;

    return sum - avg * avg;
}

float cov(float* x, float* y, int size){
    float avgX = 0, avgY = 0;

    for(int i = 0; i < size; i++){
        avgX += x[i];
        avgY += x[i];
    }
}
