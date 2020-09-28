#ifndef BASEGENERATOR_H
#define BASEGENERATOR_H

#include <QObject>
#include <QPointF>
#include <memory>
#include "lemer.h"

class BaseGenerator : public QObject
{
    Q_OBJECT
private:
    const QString name;
protected:
    static constexpr auto MAX_PARAM_AMOUNT = 2;
    std::array<qreal, MAX_PARAM_AMOUNT> params;
    std::array<QString, MAX_PARAM_AMOUNT> paramNames;
    qint8 paramAmount;

    std::unique_ptr<Lemer> lemer;
    virtual qreal _generate() = 0;
public:
    explicit BaseGenerator(QString name, Lemer* lmr = {}, QObject *parent = nullptr);
    virtual ~BaseGenerator();

    quint8 getParamAmount() const noexcept { return paramAmount; }
    void setFirstParam(const qreal param) noexcept { params[0] = param; }
    qreal getFirstParam() const noexcept { return params[0]; }
    void setSecondParam(const qreal param)  noexcept { params[1] = param; }
    qreal getSecondParam() const noexcept { return params[1]; }
    QString getFirstParamName() const noexcept { return paramNames[0]; }
    QString getSecondParamName() const noexcept { return paramNames[1]; }

    QString getName() const noexcept { return name; }

    virtual void setLemer(Lemer* lmr) { lemer.reset(lmr); }
    Lemer& getLemer() { return *lemer; }

public slots:
    qreal generate();
signals:
    void generated(qreal);


};

#endif // BASEGENERATOR_H
