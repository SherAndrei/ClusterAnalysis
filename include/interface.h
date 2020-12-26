#pragma once
#include <string>
#include "controller.h"
#include "logger.h"

class Interface {
 public:
    Interface(int new_id, bool record_rule);
    void start(int argc, char* argv[]);
    void log_out() const;
    void help()    const;

 private:
    void read(std::istream&);

 private:
    Controller controller;
    Logger logger;
};
