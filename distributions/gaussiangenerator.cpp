#include "gaussiangenerator.h"
#include <QtMath>

GaussianGenerator::GaussianGenerator(Lemer *lmr, QObject *parent) : BaseGenerator("Гауссово", lmr, parent)
{
    paramAmount = 2;
    paramNames[0] = "m";
    paramNames[1] = "σ";
}

qreal GaussianGenerator::_generate()
{
    auto R = 0.;
    for(auto i = 0; i < 6; ++i) {
        R += lemer->generate();
    }
    return params[0] + params[1] * qSqrt(2.) * (R - 3);
}
