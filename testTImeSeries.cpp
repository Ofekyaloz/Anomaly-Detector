#include "testTImeSeries.h"
#include "timeseries.h"
#include <iostream>

void finalTest() {
    TimeSeries *t = new TimeSeries("text.txt");
    int count = 0;
    count += testColSize(*t);
    count += testRowSize(*t);
    count += testRowSubject(*t);
    count += testCol(*t);

    cout << count << " tests have failed" << endl;
}

int testColSize(TimeSeries t) {
    if(t.getColSize() != 4){
        cout << "Test column size failed!" << endl;
        return 1;
    }
    return 0;
}

int testRowSize(TimeSeries t) {
    if(t.getRowSize() != 4){
        cout << "Test row size failed!" << endl;
        return 1;
    }
    return 0;
}

int testRowSubject(TimeSeries t) {
    if(t.getColSubject(1) != "Speed"){
        cout << "Test row subject failed!" << endl;
        return 1;
    }
    return 0;
}

int testCol(TimeSeries t) {
    vector<float> v;
    v.push_back(250);
    v.push_back(251);
    v.push_back(251.7);
    v.push_back(253.1);

    for(int i = 0; i < v.size(); i++){
        if(t.getCol(1)[i] != v[i]){
            cout << "Test column values failed!" << endl;
            return 1;
        }
    }
    return 0;
}