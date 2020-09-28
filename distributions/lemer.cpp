#include "lemer.h"

Lemer::Lemer(qint64 R, qint64 m, qint64 a, QObject *parent) : QObject(parent)
    , startR(R)
    , R(R)
    , m(m)
    , a(a)
{

}

qreal Lemer::generate()
{
    //R = (a * R) % m;
    R = ((a % m) * (R % m)) % m;
    return static_cast<qreal>(R) / m;
}
