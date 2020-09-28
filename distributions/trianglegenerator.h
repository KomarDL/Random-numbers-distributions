#ifndef TRIANGLEGENERATOR_H
#define TRIANGLEGENERATOR_H

#include <QObject>
#include "basegenerator.h"

class TriangleGenerator : public BaseGenerator
{
public:
    TriangleGenerator(Lemer* lmr = new Lemer, QObject *parent = nullptr);
protected:
    qreal _generate() override;
};

#endif // TRIANGLEGENERATOR_H
