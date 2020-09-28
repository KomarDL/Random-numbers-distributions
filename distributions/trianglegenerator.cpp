#include "trianglegenerator.h"

TriangleGenerator::TriangleGenerator(Lemer *lmr, QObject *parent) : BaseGenerator("Треугольное", lmr, parent)
{
    paramAmount = 2;
    paramNames[0] = "a";
    paramNames[1] = "b";
}

qreal TriangleGenerator::_generate()
{
    auto R1 = lemer->generate();
    for (auto i = 0; i < 10; ++i) {
        (void)lemer->generate();
    }
    auto R2 = lemer->generate();
    return params[0] + (params[1] - params[0]) * std::max(R1, R2);
}
