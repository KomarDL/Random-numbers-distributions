#ifndef LEMERGENERATOR_H
#define LEMERGENERATOR_H

#include <QObject>
#include "basegenerator.h"

class LemerGenerator : public BaseGenerator
{
    Q_OBJECT
public:
    LemerGenerator(Lemer* lmr = new Lemer, QObject *parent = nullptr);
protected:
    qreal _generate() override;
};

#endif // LEMERGENERATOR_H
