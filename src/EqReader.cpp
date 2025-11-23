#include "EqReader.h"

EqReader::EqReader()
{
    //ctor
}

EqReader::~EqReader()
{
    //dtor
}

float EqReader::GetEqResult(float input)
{
    te_variable vars[] = {{"x", &x_var}};
    expr = te_compile(func.c_str(), vars, 1, &err);

    x_var = (double)input;
    return (float)te_eval(expr);
}


void EqReader::SetEq(string eq)
{
    func = eq;
}

