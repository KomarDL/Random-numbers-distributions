#include "gammagenerator.h"
#include <QtMath>

GammaGenerator::GammaGenerator(Lemer *lmr, QObject *parent) : BaseGenerator("Гамма", lmr, parent)
{
    paramAmount = 2;
    paramNames[0] = "η";
    paramNames[1] = "λ";
}

qreal GammaGenerator::_generate()
{
    qint64 counter = params[0];
    auto R = 1.;
    for (int i = 0; i < counter; ++i) {
        R *= lemer->generate();
    }
    return (1/params[1]) * qLn(lemer->generate());
}
