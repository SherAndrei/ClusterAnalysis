#pragma once
#include <string>
#include <sstream>

class Logger {
 public:
    explicit Logger(const std::string& name = {});
    void log(const std::string& message);
    std::string str() const;

 private:
    std::string _name;
    std::ostringstream _oss;
};
