#pragma once
#include "cloud.h"
#include "field.h"

class Buffer
{
public:
    void get_field(const Field& another);
    void set_field(const Field& another);
private:
    Field buff_field = {};

public:
    void get_cloud(const Cloud& another);
    void set_cloud(const Cloud& another);
private:
    Cloud buff_cloud = {};
};