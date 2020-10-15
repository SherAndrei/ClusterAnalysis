#pragma once
#include "cluster.h"
#include "field.h"

class Buffer
{
public:
    void get_field(const Field& another);
    void set_field(const Field& another);
private:
    Field buff_field = {};

public:
    void get_cluster(const Cluster& another);
    void set_cluster(const Cluster& another);
private:
    Cluster buff_cluster = {};
};