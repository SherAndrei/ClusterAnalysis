#pragma once
#include "controller.h"
#include <iostream>
#include <sstream>

class Interface
{
public:
    Interface(int new_id, bool record_rule);
    void start();
    void get_command(std::istream& os);
    void log_in(const std::string& inp);
    void log_out() const;
    void help()    const;

private:
    const int  ID = 1;
    const bool record_log = true;
    std::ostringstream _log = {};
    Controller controller;
};