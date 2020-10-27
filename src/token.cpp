#include "token.h"


ExeAlgorithmToken::ExeAlgorithmToken(ALG num, std::vector<std::string> params) : _alg(num), _params(params) {}
void ExeAlgorithmToken::Evaluate(Controller& ctrl) const 
{
    switch (_alg)
    {
    case ALG::WAVE: ctrl.wave(stod(_params[0]));
        break;
    case ALG::DBSCAN: ctrl.dbscan(stod(_params[0]), stoi(_params[1]));
        break;
    default:
        break;
    }
}

std::string to_string(ALG alg)
{
    switch (alg)
    {
    case ALG::WAVE:   return "WaveAlgorithm";
    case ALG::DBSCAN: return "DBScanAlgorithm";
    default:
        break;
    }    
    return {};
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

CreateToken::CreateToken(ENTITY e, const std::vector<std::string>& params) 
    : _e(e), _parameters(params) {}
void CreateToken::Evaluate(Controller& ctrl)  const
{
    switch (_e)
    {
    case ENTITY::CLOUD: {
        double meanX = stod(_parameters[0]);
        double meanY = stod(_parameters[1]);
        double varX  = stod(_parameters[2]);
        double varY  = stod(_parameters[3]);
        int N        = stoi(_parameters[4]);
        if(N < 0)
            throw std::out_of_range("Bad amount of points!" + _parameters[4]);
        ctrl.cloud(meanX, meanY, varX, varY, N);    
        break;
    }
    case ENTITY::STARSKY: {
        double minX = stod(_parameters[0]);
        double maxX = stod(_parameters[1]);
        double minY = stod(_parameters[2]);
        double maxY = stod(_parameters[3]);
        int N       = stoi(_parameters[4]);
        if(N < 0)
            throw std::out_of_range("Bad amount of points!" + _parameters[4]);
        ctrl.starsky(minX, maxX, minY, maxY, N);    
        break;
    }
    default:    
        break;
    }
}

UtilsToken::UtilsToken(UTILS u) : _u(u) {}
void UtilsToken::Evaluate(Controller& ctrl) const
{
    (void) ctrl;
    switch (_u)
    {
    case UTILS::HELP: throw 1;
    case UTILS::LOG:  throw 2;
    case UTILS::END:  throw 3;    
    default:
        break;
    }
}

UTILS stoutils(const std::string& ut)
{
         if (ut == "HELP") return  UTILS::HELP;
    else if (ut == "LOG")  return  UTILS::LOG;
    else if (ut == "END")  return  UTILS::END;
    else return UTILS::UNKNOWN;   
}