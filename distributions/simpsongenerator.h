#ifndef SIMPSONGENERATOR_H
#define SIMPSONGENERATOR_H

#include <QObject>
#include "basegenerator.h"
#include "uniformgenerator.h"

class SimpsonGenerator : public BaseGenerator
{
public:
    SimpsonGenerator(Lemer* lmr = new Lemer, QObject *parent = nullptr);
    void setLemer(Lemer *lmr) override;
protected:
    qreal _generate() override;
private:
    UniformGenerator unGen;
};

#endif // SIMPSONGENERATOR_H
