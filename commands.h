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

struct Report {
    int startTime = 0;
    int endTime = 0;
    string description = "";
    bool TP = false;
};

struct CommandInfo {
    float threshold;
    vector<AnomalyReport> detects;
    vector<Report> reports;
    int numberOfRows;
};


// you may add here helper classes


// you may edit this class
class Command{
protected:
    DefaultIO* dio;
    string description;
public:
    Command(DefaultIO* dio):dio(dio){}
    virtual void execute(CommandInfo* info)=0;
    virtual ~Command(){}
    string getTitle() {
        return this->description;
    }
};

// implement here your command classes
class UploadCsv: public Command{

public:
    UploadCsv(DefaultIO* dio): Command(dio) {
         this->description = "upload a time series csv file\n";
    };

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
    ThresholdSettings(DefaultIO* dio): Command(dio) {
        this->description = "algorithm settings\n";
    };

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
    RunDetect(DefaultIO* dio): Command(dio) {
        this->description = "detect anomalies\n";
    };
    virtual void execute(CommandInfo* info) override {
        TimeSeries train("trainCSV");
        TimeSeries test ("testCSV");
        HybridAnomalyDetector detector;
        detector.setThreshold(info->threshold);
        detector.learnNormal(train);
        info->detects = detector.detect("testCSV");
        info->numberOfRows = test.getColSize();

        Report r;
//        r.description = "";
//        r.endTime = 0;
//        r.startTime = 0;
        r.TP = false;
        for (AnomalyReport anomalyReport: info->detects) {
            if ((anomalyReport.timeStep != r.endTime + 1) && (anomalyReport.description != r.description)) {
                r.startTime = anomalyReport.timeStep;
                r.endTime = anomalyReport.timeStep;
                r.description = anomalyReport.description;
                info->reports.push_back(r);
                continue;
            }
            r.endTime++;
        }

        dio->write("anomaly detection complete.\n");

    }
};

class DisplayResults: public Command{
    DisplayResults(DefaultIO* dio): Command(dio) {
        this->description = "display results\n";
    };
    virtual void execute(CommandInfo* info) override {
        for (AnomalyReport report: info->detects) {
            dio->write(report.timeStep + "\t" + report.description + "\n");
        }
        dio->write("Done.\n");
    }

};

class AnalyzeResults: public Command{
    AnalyzeResults(DefaultIO* dio): Command(dio) {
        this->description = "upload anomalies and analyze results\n";
    }
    virtual void execute(CommandInfo* info) override {
        dio->write("Please upload your local anomalies file.\n");
        string data = "";
        while ((data = dio->read()) != "Done.") {
            size_t coma = data.find(",");
            int start = stoi(data.substr(0, coma));
            int end = stoi(data.substr( coma + 1, data.length()));

        }
    }

};

class Exit: public Command{
    Exit(DefaultIO* dio): Command(dio) {
        this->description = "exit";
    };
    virtual void execute(CommandInfo* info) override {
        return;
    }

};

#endif /* COMMANDS_H_ */
