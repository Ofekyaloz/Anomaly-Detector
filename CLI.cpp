#include "CLI.h"
#include "commands.h"

CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
    this->commandsOptions.push_back(new UploadCsv(dio));
    this->commandsOptions.push_back(new ThresholdSettings(dio));
    this->commandsOptions.push_back(new RunDetect(dio));
    this->commandsOptions.push_back(new DisplayResults(dio));
    this->commandsOptions.push_back(new AnalyzeResults(dio));
    this->commandsOptions.push_back(new Exit(dio));
}



void CLI::start(){
    CommandInfo info;
    dio->write("Welcome to the Anomaly Detection Server. \n"
               "Please choose an option:\n");
    for (int i = 0; i < 6; ++i) {
        dio->write(to_string(i+1) + ". " + this->commandsOptions[i]->getTitle() + "\n");
    }
    int choice = stoi(dio->read());
    if ( choice >= 1 && choice <= 6) {
        commandsOptions[choice]->execute(&info);
    }

}


CLI::~CLI() {
}

