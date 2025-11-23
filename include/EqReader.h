#ifndef EQREADER_H
#define EQREADER_H


#include "tinyexpr.h"
#include <stdio.h>
#include <string>
using namespace std;

class EqReader
{
    public:
        EqReader();
        virtual ~EqReader();

        float GetEqResult(float input);
        void SetEq(string eq);

    protected:

    private:
        double x_var;
        int err;
        te_expr *expr;
        string func;
};

#endif // EQREADER_H

