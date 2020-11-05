#pragma once

#include <string>
#include <vector>

class Controller;

using namespace std;

struct Token {
  virtual void Evaluate(Controller& ctrl) const = 0;
};

enum class ALG
{
    UNKNOWN = -1,
    WAVE,
    DBSCAN
};

std::string algtos(ALG alg);
ALG stoalg(const std::string& ald);

class SearchToken : public Token
{
    ALG _alg;
    std::vector<std::string> _params;
public:
    SearchToken(ALG num, const std::vector<std::string>& params);
    void Evaluate(Controller& ctrl) const override;
};

enum class OUTPUT
{
    UNKNOWN = -1,
    ALL,
    ALG,
    GRAPH,
    HISTOGRAM
};

OUTPUT stooutput(const std::string& word);

class PrintToken : public Token 
{
    OUTPUT _out;
    ALG _alg;
public:
    PrintToken(OUTPUT out, ALG alg = ALG::UNKNOWN);
    void Evaluate(Controller& ctrl) const override;
};

enum class ENTITY
{
    UNKNOWN = -1,
    CLOUD,
    STARSKY
};

class GenerateToken : public Token
{
public: 
    GenerateToken(ENTITY e, const std::vector<std::string>& params);
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


enum class MODE
{
    UNKNOWN = -1,
    GENERATE,
    SEARCH
};

MODE stomode(const std::string& mo);

class ModeToken : public Token
{
    MODE _m;
public:
    ModeToken(MODE m);
    void Evaluate(Controller& ctrl) const override;
};
