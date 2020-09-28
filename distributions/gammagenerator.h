#ifndef GAMMAGENERATOR_H
#define GAMMAGENERATOR_H

#include <QObject>
#include "basegenerator.h"

class GammaGenerator : public BaseGenerator
{
public:
    GammaGenerator(Lemer* lmr = new Lemer, QObject *parent = nullptr);
protected:
    qreal _generate() override;
};

#endif // GAMMAGENERATOR_H
