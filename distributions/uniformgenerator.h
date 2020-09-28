#ifndef UNIFORMGENERATOR_H
#define UNIFORMGENERATOR_H

#include <QObject>
#include "basegenerator.h"

class UniformGenerator : public BaseGenerator
{
public:
    UniformGenerator(Lemer* lmr = new Lemer, QObject *parent = nullptr);

protected:
    qreal _generate() override;
};

#endif // UNIFORMGENERATOR_H
