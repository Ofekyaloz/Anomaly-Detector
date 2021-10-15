//
// Created by gili on 15/10/2021.
//

#include "anomaly_detection_util.h"

float var(float* x, int size) {
    float miu = 0, sum = 0;

    for(int i = 0; i < size; i++){
        miu += x[i];
        sum += x[i] * x[i];
    }
    miu /= size;
    sum /= size;

    return sum - miu * miu;
}

float cov(float* x, float* y, int size){

}
