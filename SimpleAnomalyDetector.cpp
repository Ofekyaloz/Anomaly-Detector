#include "timeseries.h"
#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"


SimpleAnomalyDetector::SimpleAnomalyDetector() {


}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {

}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
    int i,j, colSize = ts.getColSize();
    vector<correlatedFeatures> correlated;
    float treshold = 0.9;
    for (int i = 0; i < colSize; i++) {
        int m = 0, c = -1;
        for (int j = i + 1; j < colSize; j++ ) {
            float* f = &ts.getCol(i)[0];
            float* g = &ts.getCol(j)[0];
            float p = pearson(f, g, colSize);
            if (p > m) {
                m = p;
                c = j;
            }
        }
        if (c != -1) {
            Point* ps[colSize];
            vector<float> v1 = ts.getCol(i), v2 = ts.getCol(j);
            for (int h = 0; h < colSize; h++)
                ps[h]=new Point(v1[h], v2[h]);
            correlatedFeatures coreelated (ts.getRowSubject(i), ts.getRowSubject(j), m, linear_reg(ps, colSize), treshold);
            correlated.push_back(correlateFeatures);
        }
    }
    int corlen = correlated.size();
    for (i = 0; i < corlen; i++) {
        vector<float> v1 = ts.getCol(correlated[i].feature1), v2 = ts.getCol(correlated[i].feature2);
        float max = 0;
        for (j = 0; j < colSize; j++) {
            Point p = new Point(v1[j], v2[j]);
            float dis = dev(p, correlated[i].lin_reg);
            if (dis > max)
                max = dis;
        }
        distance.push_back(max);
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){

}
