
#include <map>
#include <vector>
#include "anomaly_detection_util.h"
#include "timeseries.h"
#include <string.h>


int main() {
    TimeSeries *t = new TimeSeries("/home/ofek/CLionProjects/The_Best_Project");
    printf("%s", t);
    cout << "hey" << endl;
    return 0;
}