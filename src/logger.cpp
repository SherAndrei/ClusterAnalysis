#include "logger.h"

Logger::Logger(const std::string& name) : _name(name) {}
void Logger::log(const std::string& message) 
{
    _oss << _name << ' ' << message << '\n';
}
std::string Logger::str() const
{
    return _oss.str();
}
