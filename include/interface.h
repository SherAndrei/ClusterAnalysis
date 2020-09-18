#pragma once
#include "controller.h"
#include <iostream>
#include <fstream>
#include <string>

class Interface
{
public:
    Interface(int new_id = 1)
        : ID(new_id) {}
    void/*???*/ get_command(std::istream& os);
    // void/*???*/ get_command_from_cons(std::ostream& os);
    // void/*???*/ get_command_from_file(std::ofstream& ofile);
    void/*???*/ log() const;
    //Печать всего списка реализованных команд в help.txt
    void/*???*/ help() const;
    void start();
private:
    const int ID;
    bool record_log = true;
    std::string _log = {};
    std::string _log_name = {};
    Controller controller;
};