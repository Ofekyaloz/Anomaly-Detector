#include <string.h>
#include <vector>
#include "../anomaly_detection_util.h"
#include "../AnomalyDetector.h"
#include "../timeseries.h"

struct correlatedFeatures{
    string feature1,feature2; // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
};

class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
    std::vector<correlatedFeatures> correlated;

public:
    SimpleAnomalyDetector();
    virtual ~SimpleAnomalyDetector();

    virtual void learnNormal(const TimeSeries& ts) {
        int i,j, colSize = ts.getcolSize(), rowSize = ts.getRowSize;
        float treshold = 0.7;
        for (int i = 0; i < colSize; i++) {
            int m = 0, c = -1;
            for (int j = i + 1; j < colSize; j++ ) {
                float p = pearson(ts.getCol(i), ts.getCol(j), rowSize);
                if (p > m) {
                    m = p;
                    c = j;
                }
            }
            if (c != -1) {
                Point* ps[rowsSize];
                std::vector v1 = ts.getCol(i), v2 = ts.getCol(j);
                for (int h = 0; h < rowsSize; h++)
                    ps[h]=new Point(v1[h], v2[h]);
                correlatedFeatures correlatedFeatures(ts.getRowSubject(i), ts.getRowSubject(j), m, lin_reg(ps, rowsSize), treshold);
                correlated.push_back(correlateFeatures);
            }
        }
        int corlen = correlated.size();
        for ( i = 0; i < corlen; ++i) {
            for (j = 0; j < ; ++j) {
                vector<float> v1 = ts.getCol(correlated[i].feature1), v2 = ts.getCol(correlated[i].feature2);


            }

        }

    }
    virtual std::vector<AnomalyReport> detect(const TimeSeries& ts);
    std::vector<correlatedFeatures> getNormalModel();
};