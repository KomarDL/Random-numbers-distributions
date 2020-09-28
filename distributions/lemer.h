#ifndef LEMER_H
#define LEMER_H

#include <QObject>

class Lemer : public QObject
{
    Q_OBJECT

    qint64 startR{};
    qint64 R{};
    qint64 m{};
    qint64 a{};
public:
    Lemer(qint64 R = 0, qint64 m = 0, qint64 a = 0 , QObject* parent = nullptr);

    void setR(qint64 R) { startR = R; reset(); }
    qint64 getR() const noexcept { return R; }
    void setM(qint64 m) { this->m = m; }
    qint64 getM() const noexcept { return m; }
    void setA(qint64 a) { this->a = a; }
    qint64 getA() const noexcept { return a; }

    void reset() { R = startR; }
    qreal generate();
};

#endif // LEMER_H
