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

class DefaultIO {
public:
    virtual string read() = 0;
    virtual void write(string text) = 0;
    virtual void write(float f) = 0;
    virtual void read(float *f) = 0;
    virtual ~DefaultIO() {}

    // read the csv information from a file and save the data in 'fileName'.
    void readToFile(string fileName) {
        ofstream out(fileName);
        string data = "";

        // read every line from the client until we get the word 'done'
        while ((data = read()) != "done\n") {
            out << data << endl;
        }
        out.close();
    }
};

// Report is a struct of AnomalyReport that presents in a row and with the same description.
struct Report {
    int startTime = 0;
    int endTime = 0;
    string description = "";
    bool TP = false;
};

// CommandInfo contains all the information the commands need to know and share between them
struct CommandInfo {
    float threshold = 0.9;
    vector<AnomalyReport> detects;
    vector<Report> reports;
    int numberOfRows = 0;
};

// Abstract interface which has execute function and DefaultIO and description fields
class Command{
protected:
    DefaultIO* dio;
    string description;
    
public:
    Command(DefaultIO* dio):dio(dio){}
    virtual void execute(CommandInfo* info)=0;
    virtual ~Command(){}

    // return the description of a command.
    string getTitle() {
        return this->description;
    }
};

// A command that allows the client to upload its train and test csv
class UploadCsv: public Command{
public:
    UploadCsv(DefaultIO* dio): Command(dio) {
         this->description = "upload a time series csv file\n";
    };

    // read two files, the train csv and the test csv.
    virtual void execute(CommandInfo* info) override {
        dio->write("Please upload your local train CSV file.\n");
        dio->readToFile("anomalyTrain.csv");
        dio->write("Upload complete.\n");
        dio->write("Please upload your local test CSV file.\n");
        dio->readToFile("anomalyTest.csv");
        dio->write("Upload complete.\n");
    }
};

// A command that allows the client to change the threshold of the anomaly detector
class ThresholdSettings: public Command{
public:
    ThresholdSettings(DefaultIO* dio): Command(dio) {
        this->description = "algorithm settings\n";
    };

    // update the threshold's value.
    virtual void execute(CommandInfo* info) override {
        while (true) {
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

// A command that allows the client to run the anomaly detector
class RunDetect: public Command{
public:
    RunDetect(DefaultIO* dio): Command(dio) {
        this->description = "detect anomalies\n";
    };

    // Run the HybridAnomalyDetector with the value of threshold and with the train and test csv files.
    virtual void execute(CommandInfo* info) override {
        TimeSeries train("anomalyTrain.csv");
        TimeSeries test("anomalyTest.csv");
        HybridAnomalyDetector detector;
        detector.setThreshold(info->threshold);
        detector.learnNormal(train);
        info->detects = detector.detect("anomalyTest.csv");
        info->numberOfRows = test.getColSize();

        // union a few anomalyReport together if they are with the same description and in a row.
        Report r;
        r.TP = false;
        for (AnomalyReport anomalyReport: info->detects) {
            if ((anomalyReport.timeStep != r.endTime + 1) && (anomalyReport.description != r.description)) {
                r.startTime = anomalyReport.timeStep;
                r.endTime = anomalyReport.timeStep;
                r.description = anomalyReport.description;
                info->reports.push_back(r);
                continue;
            }
            // increment the endTime.
            info->reports.back().endTime++;
        }

        dio->write("anomaly detection complete.\n");

    }
};

// A command that allows the client to display the results of the detector
class DisplayResults: public Command{
public:
    DisplayResults(DefaultIO* dio): Command(dio) {
        this->description = "display results\n";
    };

    // Print the timestep and the description of each report that we detected.
    virtual void execute(CommandInfo* info) override {
        for (AnomalyReport report: info->detects) {
            dio->write(to_string(report.timeStep) + "\t" + report.description + "\n");
        }
        dio->write("Done.\n");
    }

};

// A command that allows the client to analyze the results
class AnalyzeResults: public Command{
public:
    AnalyzeResults(DefaultIO* dio): Command(dio) {
        this->description = "upload anomalies and analyze results\n";
    }

    // check if two reports are true positive
    bool isTruePossitive(int start, int end, vector<Report> reports) {
        for (Report report: reports) {
            if ((report.startTime <= end && report.endTime >= start) || (report.startTime >= end && report.endTime <= start)) {
                report.TP = true;
                return true;
            }
        }
        return false;
    }

    // Analyze the results and display them.
    virtual void execute(CommandInfo* info) override {
        dio->write("Please upload your local anomalies file.\n");
        string data = "";
        float counterTP = 0, counterP = 0, sum = 0;
        
        // Read the lines until the word 'done' and check if the lines are true positive
        while ((data = dio->read()) != "done\n") {
            size_t coma = data.find(",");
            int start = stoi(data.substr(0, coma));
            int end = stoi(data.substr( coma + 1, data.length()));
            if (isTruePossitive(start, end, info->reports)) {
                counterTP++;
            }
            sum += end - start + 1;
            counterP++;
        }

        // Print the true positive rate and the false alarm rate
        float counterFP = info->reports.size() - counterTP;
        dio->write("Upload complete.\nTrue Positive Rate: ");
        dio->write(((int)(1000 * counterTP / counterP))/1000.0);
        dio->write("\nFalse Positive Rate: ");
        dio->write(((int)(1000.0 * counterFP / (info->numberOfRows - sum)))/1000.0);;
        dio->write("\n");
    }

};

// A command that allows the client to exit the simulator
class Exit: public Command{
public:
    Exit(DefaultIO* dio): Command(dio) {
        this->description = "exit\n";
    };

    virtual void execute(CommandInfo* info) override {
        return;
    }

};

#endif /* COMMANDS_H_ */
