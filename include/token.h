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
    UNKNOWN = -1,
    NO_ALG,
    WAVE,
    DBSCAN
};

std::string to_string(ALG alg);
ALG stoalg(const std::string& ald);

class ExeAlgorithmToken : public Token
{
    ALG _alg;
    std::vector<std::string> _params;
public:
    ExeAlgorithmToken(ALG num, std::vector<std::string> params);
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
    CreateToken(ENTITY e, const std::vector<std::string>& params);
    void Evaluate(Controller& ctrl) const override;
private:
    ENTITY _e;
    std::vector<std::string> _parameters;
};

enum class UTILS
{
    UNKNOWN = -1,
    HELP,
    LOG,
    END
};

UTILS stoutils(const std::string& ut);

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