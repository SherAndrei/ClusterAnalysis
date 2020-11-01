#include "token.h"

SearchToken::SearchToken(ALG num, const std::vector<std::string>& params) : _alg(num), _params(params) {}
void SearchToken::Evaluate(Controller& ctrl) const 
{
    ctrl.search(_alg, _params);
}

std::string to_string(ALG alg)
{
    switch (alg)
    {
    case ALG::WAVE:   return "WaveAlgorithm";
    case ALG::DBSCAN: return "DBScanAlgorithm";
    default: return {};
    }       
}

ALG stoalg(const std::string& alg)
{
         if (alg == "WAVE")      return  ALG::WAVE;
    else if (alg == "DBSCAN")    return  ALG::DBSCAN;
    else if (alg == "ALLPOINTS") return  ALG::NO_ALG;
    else return ALG::UNKNOWN;
}

PrintToken::PrintToken(ALG num) : _alg(num) {}
void PrintToken::Evaluate(Controller& ctrl) const 
{
    ctrl.print(_alg);
}

GenerateToken::GenerateToken(ENTITY e, const std::vector<std::string>& params) 
    : _e(e), _parameters(params) {}
void GenerateToken::Evaluate(Controller& ctrl)  const
{
    ctrl.generate(_e, _parameters);
}

ModeToken::ModeToken(MODE m) : _m(m) {}
void ModeToken::Evaluate(Controller& ctrl) const
{
    ctrl.setup(_m);
}

MODE stomode(const std::string& mo) {
         if (mo == "GENERATE") return MODE::GENERATE;
    else if (mo == "SEARCH")   return MODE::SEARCH;
    else return MODE::UNKNOWN;
}

UtilsToken::UtilsToken(UTILS u) : _u(u) {}
void UtilsToken::Evaluate(Controller& ctrl) const
{
    (void) ctrl;
    throw _u;
}

UTILS stoutils(const std::string& ut)
{
         if (ut == "HELP") return  UTILS::HELP;
    else if (ut == "LOG")  return  UTILS::LOG;
    else if (ut == "END")  return  UTILS::END;
    else return UTILS::UNKNOWN;   
}