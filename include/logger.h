#pragma once
#include <string>
#include <sstream>

class Logger {
 public:
    explicit Logger(int ID, bool record_rule = true);
    void log(const std::string& message);
    std::string str() const;
 private:
    int _ID;
    bool _record_rule;
    std::ostringstream _oss;
};
