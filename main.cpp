
#include <map>
#include <vector>
#include "anomaly_detection_util.h"
#include "timeseries.h"
#include <string.h>

bool wrong(float val, float expected){
    return val<expected-0.001 || val>expected+0.001;
}

// this is a simple test to put you on the right track
int main() {


    const char *CSVfileName = "time,speed,angel,height\\n0.1,20,30,40\\n0.2,30,40,50\\n0.3,40,50,60\\n0.4,50,60,70";
    TimeSeries *p = new TimeSeries(CSVfileName);
    ::map<string, vector<float>> map;


    bool new_line = false;
    string *str = (string *) CSVfileName;
    string sub;
    while (str != NULL)
        if (!new_line && str->find('\n')) {
            break;
        } else if (!new_line) {
            sub = strtok(NULL, ",");
            map[sub] = vector<float>();
        }
    }
    int N = 2;
    Point* ps[N];
    for(int i=0;i<N;i++)
        ps[i]=new Point(x[i],y[i]);

    Line l=linear_reg(ps,N);
    Point p(4,8);

    float v[]={var(x,N),cov(x,y,N),pearson(x,y,N),l.a,l.b,l.f(4),dev(p,l)};
    float e[]={8.25,16.63,0.999,2.015,0.113,8.176,0.176};


    for(int i=0;i<7;i++)
        if(wrong(v[i],e[i]))
            cout<<"error for check "<<i<<" (-14)"<<endl;


    for(int i=0;i<N;i++)
        delete ps[i];

    cout<<"done"<<endl;

    return 0;
}