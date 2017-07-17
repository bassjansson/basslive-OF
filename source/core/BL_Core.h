#pragma once

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

namespace BassLive
{
    // UInt, ULong, Float
    typedef u_int  UInt;
    typedef u_long ULong; // was: tick
    typedef float  Float;





//////////////// OLD ////////////////

    // List
    template<class ValueType>
    class List : public vector<ValueType> {};


    // Parameter
    template<class ValueType>
    struct Parameter
    {
        string name;
        string description;

        ValueType value;
    };


    // Processor
    template<class InputValueType, class OutputValueType>
    class Processor
    {
        List<Parameter<InputValueType>> inputs;
        List<Parameter<OutputValueType>> outputs;
    };
}
