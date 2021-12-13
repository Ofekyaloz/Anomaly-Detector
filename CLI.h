#ifndef CLI_H_
#define CLI_H_

#include <string.h>
#include "commands.h"

using namespace std;

// CLI - command line interface has default IO and vector of commands
class CLI {
    DefaultIO* dio;
    vector<Command*> commandOptions;
public:
    CLI(DefaultIO* dio);
    void start();
    virtual ~CLI();
};

#endif /* CLI_H_ */
