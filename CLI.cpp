#include "CLI.h"
#include "commands.h"

// command line interface where the commands are introduced
CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
    this->commandOptions.push_back(new UploadCsv(dio));
    this->commandOptions.push_back(new ThresholdSettings(dio));
    this->commandOptions.push_back(new RunDetect(dio));
    this->commandOptions.push_back(new DisplayResults(dio));
    this->commandOptions.push_back(new AnalyzeResults(dio));
    this->commandOptions.push_back(new Exit(dio));
}

// start the CLI by introduce the options to the client
void CLI::start() {
    CommandInfo info;
    int choice = 0;
    while (choice != 6) {
        dio->write("Welcome to the Anomaly Detection Server.\nPlease choose an option:\n");
        for (int i = 0; i < commandOptions.size(); ++i) {
            dio->write(to_string(i + 1) + "." + this->commandOptions[i]->getTitle());
        }
        choice = dio->read()[0] - '0';
        if (choice >= 1 && choice <= 6) {
            commandOptions[choice - 1]->execute(&info);
        }
    }
}

// destructor
CLI::~CLI() {
    for (int i = 0; i < commandOptions.size(); i++) {
        delete commandOptions[i];
    }
}

