#include "logger.h"

Logger::Logger(int ID, bool record_rule)
    : _ID(ID), _record_rule(record_rule) {}
void Logger::log(const std::string& message)  {
    if (_record_rule)
        _oss << "ID: " << _ID << ' ' << message << '\n';
}
std::string Logger::str() const {
    return _oss.str();
}
