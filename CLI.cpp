#include "CLI.h"
#include "commands.h"

CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
    this->commandOptions.push_back(new UploadCsv(dio));
    this->commandOptions.push_back(new ThresholdSettings(dio));
    this->commandOptions.push_back(new RunDetect(dio));
    this->commandOptions.push_back(new DisplayResults(dio));
    this->commandOptions.push_back(new AnalyzeResults(dio));
    this->commandOptions.push_back(new Exit(dio));
}

void CLI::start() {
    CommandInfo info;
    dio->write("Welcome to the Anomaly Detection Server.\nPlease choose an option:\n");
    for (int i = 0; i < commandOptions.size(); ++i) {
        dio->write(to_string(i + 1) + "." + this->commandOptions[i]->getTitle());
    }
    int choice = dio->read()[0] - '0' + 1;
    if (choice >= 1 && choice <= 6) {
        commandOptions[choice]->execute(&info);
    }
}


CLI::~CLI() {
    for (int i = 0; i < commandOptions.size(); i++) {
        delete commandOptions[i];
    }
}

