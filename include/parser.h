#pragma once

#include <memory>
#include "token.h"

std::shared_ptr<Token> parse(const std::string& command);