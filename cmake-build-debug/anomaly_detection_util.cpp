//
// Created by gili on 15/10/2021.
//

#include "anomaly_detection_util.h"

float avg(float* x, int size){
    int sum = 0;
    for(int i = 0; i < size; i++){
        sum += x[i];
    }
    return sum / size;
}

float var(float* x, int size) {
    float sum = 0;

    for(int i = 0; i < size; i++){
        sum += x[i] * x[i];
    }
    float miu = avg(x, size);
    return sum / size - miu * miu;
}

float cov(float* x, float* y, int size){
    float sum = 0;

    for(int i = 0; i < size; i++){
        sum += x[i] * y[i];
    }

    return sum / size - avg(x, size) * avg(y, size);
}
