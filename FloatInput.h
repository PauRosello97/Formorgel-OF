#pragma once
class FloatInput
{
    float& value;

public:
    FloatInput(float& v) : value(v) {};

    void modify_value() {
        value++;
    }
};
