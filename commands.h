#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"
#include "SimpleAnomalyDetector.h"
#include "timeseries.h"

using namespace std;

class DefaultIO{
public:
    virtual string read()=0;
    virtual void write(string text)=0;
    virtual void write(float f)=0;
    virtual void read(float* f)=0;
    virtual ~DefaultIO(){}

    // you may add additional methods here

    void readToFile(string fileName) {
        ofstream out(fileName);
        string data = "";

        while (data != "Done.") {
            data = read();
            out << data << endl;
        }
        out.close();
    }


};

struct CommandInfo {
    float threshold;
    vector<AnomalyReport> detects;

};

// you may add here helper classes


// you may edit this class
class Command{
protected:
    DefaultIO* dio;
public:
    Command(DefaultIO* dio):dio(dio){}
    virtual void execute(CommandInfo* info)=0;
    virtual ~Command(){}
};

// implement here your command classes
class UploadCsv: public Command{

public:
    UploadCsv(DefaultIO* dio): Command(dio) {};

    virtual void execute(CommandInfo* info) override {
        dio->write("Please upload your local train CSV file.\n");
        dio->readToFile("trainCSV");
        dio->write("Upload complete.\n");
        dio->write("Please upload your local test CSV file.\n");
        dio->readToFile("testCSV");
        dio->write("Upload complete.\n");
    }
};


class ThresholdSettings: public Command{
    ThresholdSettings(DefaultIO* dio): Command(dio) {};

    virtual void execute(CommandInfo* info) override {
        while (1) {
            dio->write("The current correlation threshold is ");
            dio->write(info->threshold);
            dio->write("\nPlease Enter threshold value: \n");
            float newThreshold;
            dio->read(&newThreshold);
            if (newThreshold <= 0 || newThreshold > 1) {
                dio->write("please choose a value between 0 and 1.\n");
                continue;
            }
            info->threshold = newThreshold;
            break;
        }
    }
};

class RunDetect: public Command{
    RunDetect(DefaultIO* dio): Command(dio) {};
    virtual void execute(CommandInfo* info) override {
        timeseries
    }
};

class DisplayResults: public Command{

};

class AnalyzeResults: public Command{

};

class Exit: public Command{

};

#endif /* COMMANDS_H_ */
