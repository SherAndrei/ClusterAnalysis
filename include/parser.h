#pragma once

#include <vector>
#include <memory>
#include "command.h"

std::shared_ptr<Token> parse(const std::string& command);