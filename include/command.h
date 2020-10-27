#pragma once

#include <vector>
#include <string>
#include <memory>
#include "controller.h"

using namespace std;

struct Token {
  virtual void Evaluate(Controller& ctrl) const = 0;
};

enum class ALG
{
    NO_ALG = -1,
    WAVE,
    DBSCAN
};

class ExeAlgorithmToken : public Token
{
    ALG _alg;
    std::vector<double> _params;
public:
    ExeAlgorithmToken(ALG num, std::vector<double> params);
    void Evaluate(Controller& ctrl) const override;
};

class PrintToken : public Token 
{
    ALG _alg;
public:
    PrintToken(ALG num);
    void Evaluate(Controller& ctrl) const override;
};

enum class ENTITY
{
    UNKNOWN = -1,
    CLOUD,
    STARSKY
};

class CreateToken : public Token
{
public: 
    CreateToken(ENTITY e, const std::vector<double>& params, int points_num);
    void Evaluate(Controller& ctrl) const override;
private:
    ENTITY _e;
    std::vector<double> _parameters;
    int _N;
};

enum class UTILS
{
    UNKNOWN = -1,
    HELP,
    LOG,
    END
};

class UtilsToken : public Token
{
    UTILS _u;
public:
    UtilsToken(UTILS u);
    void Evaluate(Controller& ctrl) const override;
};

class EmptyToken : public Token
{
public:
    EmptyToken() = default;
    void Evaluate(Controller& ctrl) const override;
};