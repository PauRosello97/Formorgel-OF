#pragma once
#include "FloatInput.h"

class Osc
{
    FloatInput b;
    float value;

public:
    Osc() : value(50), b(value)
    {}

    void modify_value() {
        b.modify_value();
    }

    float get_value() const {
        return value;
    }
};

