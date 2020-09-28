#include "lemergenerator.h"

LemerGenerator::LemerGenerator(Lemer *lmr, QObject *parent) : BaseGenerator("Последовательность Лемера", lmr, parent)
{
    paramAmount = 0;
}

qreal LemerGenerator::_generate()
{
    return lemer->generate();
}
