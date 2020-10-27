#include "token.h"


ExeAlgorithmToken::ExeAlgorithmToken(ALG num, std::vector<double> params) : _alg(num), _params(params) {}
void ExeAlgorithmToken::Evaluate(Controller& ctrl) const 
{
    switch (_alg)
    {
    case ALG::WAVE: ctrl.wave(_params.front());
        break;
    default:
        break;
    }
}


PrintToken::PrintToken(ALG num) : _alg(num) {}
void PrintToken::Evaluate(Controller& ctrl) const 
{
    switch (_alg)
    {
    case ALG::NO_ALG: ctrl.print(ALG::NO_ALG);
        break;
    case ALG::WAVE: ctrl.print(ALG::WAVE);
        break;
    default:
        break;
    }
}

CreateToken::CreateToken(ENTITY e, const std::vector<double>& params) 
    : _e(e), _parameters(params), _N(params.back()) {}
void CreateToken::Evaluate(Controller& ctrl)  const
{
    switch (_e)
    {
    case ENTITY::CLOUD: ctrl.cloud(_parameters[0], 
                                   _parameters[1], 
                                   _parameters[2], 
                                   _parameters[3], _N);
        break;
    case ENTITY::STARSKY: ctrl.starsky(_parameters[0], 
                                       _parameters[1], 
                                       _parameters[2], 
                                       _parameters[3], _N);
        break;
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