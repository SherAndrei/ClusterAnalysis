#include "parser.h"
#include <vector>
#include <utility>
#include <sstream>
#include <exception>

std::pair<std::vector<double>, int> parse_parameters(std::istringstream& iss, size_t params_num)
{
    std::vector<double> p(params_num - 1);
    int n = 0;
    double current;
    
    for(size_t i = 0; i < params_num - 1; i++) {
        iss >> std::ws; //убрали пробелы
        if(iss.peek() != ',') {
            iss >> current;
            p[i] = current;
        } else p[i] = 0.;
        iss.ignore(1);
        if(iss.fail())
            throw std::logic_error("Bad parameters! Use HELP");
    }

    iss >> std::ws; //убрали пробелы
    if(iss.peek() != EOF)
        iss >> n;

    // смотрим что дальше
    iss >> std::ws; //убрали пробелы
    if(iss.eof())
        return {p, n};
    
    throw std::logic_error("Bad parameters! Use HELP"); 
    return {};
}

std::shared_ptr<Token> parse(const std::string& command)
{
    std::vector<std::shared_ptr<Token>> result;
    std::istringstream iss(command);
    std::string word;
    bool ok = true;
    //находим первое слово
    ok = ok && (iss >> word);
    if(ok && word == "CREATE") {
        // считываем следующее слово
        ok = ok && (iss >> word);
        if(ok && word == "CLOUD") {
            auto params = parse_parameters(iss, 5);
            return std::make_shared<CreateToken>(ENTITY::CLOUD, params.first, params.second);
        } else if (ok && word == "STARSKY") {
            auto params = parse_parameters(iss, 5);
            return std::make_shared<CreateToken>(ENTITY::STARSKY, params.first, params.second);
        } else {
            throw std::logic_error("Bad create! Use HELP"); 
        }
    } else if (ok && word == "PRINT") {
        // считываем следующее слово
        ok = ok && (iss >> word);
        if(ok && word == "ALLPOINTS") {
            return std::make_shared<PrintToken>(ALG::NO_ALG);
        } else if (ok && word == "WAVE") {
            return std::make_shared<PrintToken>(ALG::WAVE);
        } else {
            throw std::logic_error("Bad print! Use HELP"); 
        }
    } else if (ok && word == "ALG") {
        ok = ok && (iss >> word);
        if (ok && word == "WAVE") {
            auto params = parse_parameters(iss, 2);
            return std::make_shared<ExeAlgorithmToken>(ALG::WAVE, params.first);
        } else {
            throw std::logic_error("Bad alg! Use HELP"); 
        }
    }
    else if (ok && word == "HELP")
        return std::make_shared<UtilsToken>(UTILS::HELP);
    else if (ok && word == "LOG")
        return std::make_shared<UtilsToken>(UTILS::LOG);
    else if (ok && word == "END")
        return std::make_shared<UtilsToken>(UTILS::END);

    throw std::logic_error("Bad input! Use HELP");
    return std::make_shared<EmptyToken>();
}