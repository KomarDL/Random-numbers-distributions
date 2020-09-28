#include "uniformgenerator.h"

UniformGenerator::UniformGenerator(Lemer *lmr, QObject *parent) : BaseGenerator("Равномерное", lmr, parent)
{
    paramAmount = 2;
    paramNames[0] = "a";
    paramNames[1] = "b";
}

qreal UniformGenerator::_generate()
{
    return params[0] + (params[1] - params[0]) * lemer->generate();
}
