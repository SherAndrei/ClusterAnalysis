#include "parser.h"
#include <vector>
#include <sstream>
#include <exception>

static std::vector<std::string> parse_parameters(std::istringstream& iss, size_t params_num) {
    std::vector<std::string> p(params_num);
    std::string current;
    size_t counter = 0u;

    while (iss >> current) {
        if (counter < params_num)
            p[counter] = current;
        counter++;
    }

    if (counter != params_num)
        throw std::invalid_argument("Bad parameters! Use HELP");

    return p;
}

std::shared_ptr<Token> parse(const std::string& command) {
    std::istringstream iss(command);
    std::string word;
    bool ok = true;
    // находим первое слово
    ok = ok && (iss >> word);
    if (ok && word == "SETUP") {
        // считываем следующее слово
        ok = ok && (iss >> word);
        if (ok && word == "SEARCH") {
            return std::make_shared<ModeToken>(MODE::SEARCH);
        } else if (ok && word == "GENERATE") {
            return std::make_shared<ModeToken>(MODE::GENERATE);
        } else {
            throw std::invalid_argument("Bad setup mode! Use HELP");
        }
    } else if (ok && word == "GENERATE") {
        ok = ok && (iss >> word);
        if (ok && word == "CLOUD") {
            auto params = parse_parameters(iss, 5);
            return std::make_shared<GenerateToken>(ENTITY::CLOUD, params);
        } else if (ok && word == "STARSKY") {
            auto params = parse_parameters(iss, 5);
            return std::make_shared<GenerateToken>(ENTITY::STARSKY, params);
        } else {
            throw std::invalid_argument("Bad generate! Use HELP");
        }
    } else if (ok && word == "SEARCH") {
        ok = ok && (iss >> word);
        if (ok && word == "WAVE") {
            auto params = parse_parameters(iss, 1);
            return std::make_shared<SearchToken>(ALG::WAVE, params);
        } else if (ok && word == "DBSCAN") {
            auto params = parse_parameters(iss, 2);
            return std::make_shared<SearchToken>(ALG::DBSCAN, params);
        } else {
            throw std::invalid_argument("Bad search! Use HELP");
        }
    } else if (ok && word == "MODE") {
        // считываем следующее слово
        ok = ok && (iss >> word);
        if (ok)
            return std::make_shared<ModeToken>(stomode(word));
    } else if (ok && word == "PRINT") {
        ok = ok && (iss >> word);
        if (ok && word == "ALG") {
            ok = ok && (iss >> word);
            if (ok)
                return std::make_shared<PrintToken>(OUTPUT::ALG, stoalg(word));
        } else if (ok) {
            return std::make_shared<PrintToken>(stooutput(word));
        }
    } else if (ok && (word == "HELP" || word == "LOG" || word == "END")) {
        return std::make_shared<UtilsToken>(stoutils(word));
    }

    throw std::invalid_argument("Bad input! Use HELP");
    return {};
}
