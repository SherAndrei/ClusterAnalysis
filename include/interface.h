#pragma once
#include "logger.h"
#include "controller.h"

class Interface {
 public:
    Interface(int new_id, bool record_rule);
    void start();
    void read(std::istream& os);
    void log_out() const;
    void help()    const;

 private:
    const int  ID = 1;
    const bool record_log = true;
    Logger logger;
    Controller controller;
};
