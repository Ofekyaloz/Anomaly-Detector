

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
    float minThreshold;

public:
	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();
    virtual void checkCorrelation(const TimeSeries& ts, int c1, int c2, float m, Point** points);
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
