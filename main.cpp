
#include <iostream>
#include <vector>
#include <fstream>
#include "anomaly_detection_util.h"
#include "timeseries.h"

using namespace std;

bool wrong(float val, float expected){
    return val<expected-0.001 || val>expected+0.001;
}

// this is a simple test to put you on the right track
int main(){
    TimeSeries("csv_table.txt");



    return 0;
}