#include "testTImeSeries.h"
#include <map>
#include <vector>
#include "anomaly_detection_util.h"
#include "timeseries.h"
#include "SimpleAnomalyDetector.h"
#include <string.h>


int main() {
    TimeSeries *t = new TimeSeries("/home/ofek/CLionProjects/The_Best_Project");
//    finalTest();
//    printf("%s", t);
    SimpleAnomalyDetector simple;
    simple.detect(*t);

    cout << "hey" << endl;
    return 0;
}