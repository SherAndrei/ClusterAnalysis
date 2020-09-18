#pragma once
#include "controller.h"
#include <iostream>
#include <sstream>

class Interface
{
public:
    Interface(int new_id = 1, bool record_rule = true)
        : ID(new_id), record_log(record_rule) {}
    void start();
    void get_command(std::istream& os);
    void log();
    void help() const;
private:
    const int ID;
    const bool record_log;
    std::ostringstream _log = {};
    Controller controller;
};