#ifndef GAUSSIANGENERATOR_H
#define GAUSSIANGENERATOR_H

#include <QObject>
#include "basegenerator.h"

class GaussianGenerator : public BaseGenerator
{
public:
    GaussianGenerator(Lemer* lmr = new Lemer, QObject *parent = nullptr);
protected:
    qreal _generate() override;
};

#endif // GAUSSIANGENERATOR_H
