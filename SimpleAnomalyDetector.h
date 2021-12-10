/*
 * Authors: Gili Gutfeld - 209284512
 * Ofek Yaloz - 206666729
 */

#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>

struct correlatedFeatures {
    string feature1, feature2;  // names of the correlated features
    float corrlation, threshold;
    Line lin_reg;
    Point center;
};

class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
    vector<correlatedFeatures> cf;
protected:float threshold;

public:
    SimpleAnomalyDetector();
    virtual ~SimpleAnomalyDetector();
    virtual void learnNormal(const TimeSeries& ts);
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);

    vector<correlatedFeatures> getNormalModel(){
        return cf;
    }

protected:
    virtual void checkCorrelation(const TimeSeries& ts, int c1, int c2, float m, Point** points);
    float getThreshold(Point** points,int size,Line lin_reg);
    Point** pointsToArray(vector<float> v1, vector<float> v2, int size);
};



#endif /* SIMPLEANOMALYDETECTOR_H_ */