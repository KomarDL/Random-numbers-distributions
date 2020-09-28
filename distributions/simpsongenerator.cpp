#include "simpsongenerator.h"

SimpsonGenerator::SimpsonGenerator(Lemer *lmr, QObject *parent) : BaseGenerator("Симпсона", lmr, parent)
{
    paramAmount = 2;
    paramNames[0] = "a";
    paramNames[1] = "b";
}

void SimpsonGenerator::setLemer(Lemer *lmr)
{
    unGen.setLemer(lmr);
}

qreal SimpsonGenerator::_generate()
{
    unGen.setFirstParam(params[0] / 2);
    unGen.setSecondParam(params[1] / 2);
    return unGen.generate() + unGen.generate();
}
