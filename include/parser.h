#pragma once

#include <memory>
#include <string>
#include "token.h"

std::shared_ptr<Token> parse(const std::string& command);
