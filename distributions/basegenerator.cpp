#include "basegenerator.h"

BaseGenerator::BaseGenerator(QString name, Lemer *lmr, QObject *parent)
    : QObject(parent)
    , name(name)
    , lemer(lmr)
{
}

BaseGenerator::~BaseGenerator()
{

}

qreal BaseGenerator::generate()
{
    auto result = _generate();
    emit generated(result);
    return result;
}

