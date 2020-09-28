#ifndef EXPGENERATOR_H
#define EXPGENERATOR_H

#include <QObject>
#include "basegenerator.h"

class ExpGenerator : public BaseGenerator
{
public:
    ExpGenerator(Lemer* lmr = new Lemer, QObject *parent = nullptr);
protected:
    qreal _generate() override;
};

#endif // EXPGENERATOR_H
