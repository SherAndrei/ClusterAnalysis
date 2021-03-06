#pragma once

#include <string>
#include <vector>

class Controller;

class Token {
 protected:
  virtual ~Token() = default;
 public:
  virtual void Evaluate(Controller& ctrl) const = 0;
};

enum class ALG {
    UNKNOWN = -1,
    WAVE,
    DBSCAN,
    KMEANS,
    FOREL,
    HIERAR,
    EM
};


std::string algtos(ALG alg);
ALG stoalg(const std::string& ald);

class SearchToken : public Token {
    ALG _alg;
    std::vector<std::string> _params;
 public:
    SearchToken(ALG num, const std::vector<std::string>& params);
    void Evaluate(Controller& ctrl) const override;
};


enum class OUTPUT {
    UNKNOWN = -1,
    ALL,
    ALG,
    GRAPH,
    HISTOGRAM
};


OUTPUT stooutput(const std::string& word);

class PrintToken : public Token  {
    OUTPUT _out;
    ALG _alg;
 public:
    explicit PrintToken(OUTPUT out, ALG alg = ALG::UNKNOWN);
    void Evaluate(Controller& ctrl) const override;
};


enum class ENTITY {
    UNKNOWN = -1,
    CLOUD,
    STARSKY
};


class GenerateToken : public Token {
 public:
    GenerateToken(ENTITY e, const std::vector<std::string>& params);
    void Evaluate(Controller& ctrl) const override;
 private:
    ENTITY _e;
    std::vector<std::string> _parameters;
};


enum class UTILS {
    UNKNOWN = -1,
    HELP,
    LOG,
    END
};


UTILS stoutils(const std::string& ut);

class UtilsToken : public Token {
    UTILS _u;
 public:
    explicit UtilsToken(UTILS u);
    void Evaluate(Controller& ctrl) const override;
};

enum class MODE {
    UNKNOWN = -1,
    GENERATE,
    SEARCH
};


MODE stomode(const std::string& mo);

class ModeToken : public Token {
    MODE _m;
 public:
    explicit ModeToken(MODE m);
    void Evaluate(Controller& ctrl) const override;
};

