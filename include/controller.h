#pragma once
#include <vector>
#include <string>
#include "clustersearcher.h"
#include "clustergenerator.h"
#include "logger.h"
#include "token.h"
#include "field.h"

enum class MODE;
enum class ENTITY;
enum class ALG;

class Controller
{
public:
    Controller() = default;

    void generate(ENTITY en, const std::vector<std::string>& params);
    void search(ALG l, const std::vector<std::string>& params);
    void print (ALG l) const;
    void setup (MODE m);

private:
    MODE mode;
    Field field;
    ClusterGenerator cg;
    bool record_log = true;
    Logger lg;
};

