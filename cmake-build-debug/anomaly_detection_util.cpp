//
// Created by gili on 15/10/2021.
//

#include "anomaly_detection_util.h"

float var(float* x, int size) {
    float miu = 0, temp, sum = 0;
    for(int i = 0; i<size; i++){
        miu += x[i];
    }
    miu /= size;

    for(int i = 0; i < size; i++){
        temp = x[i] - miu;
        temp *= temp;
        sum += temp;
    }

    sum /= size;

    return sum;
}

float cov(float* x, float* y, int size){

}
