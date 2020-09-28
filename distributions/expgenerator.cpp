#include "expgenerator.h"
#include <QtMath>

ExpGenerator::ExpGenerator(Lemer* lmr, QObject *parent) : BaseGenerator("Экспоненциальное", lmr, parent)
{
    paramAmount = 1;
    paramNames[0] = "λ";
}

qreal ExpGenerator::_generate()
{
    return (-1/params[0]) * qLn(lemer->generate());
}
