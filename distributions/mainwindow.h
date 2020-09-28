#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "basegenerator.h"
#include <QPair>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_calcPushButton_clicked();

    void on_distributionComboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    QCPBars* histogram;
    QCPCurve* line;

    void setupDistributionBox();
    void setupHistogram();
    void setupInputs();
    void setBoxItem(BaseGenerator* generator);
    void hideAll();

    QVector<qreal> generateNumbers(BaseGenerator *const generator);
    QPair<qint64, qint64> getAperiodAndPeriodLen(const QVector<qreal>& numbers);
    qreal getExpectedValue(const QVector<qreal>& numbers);
    qreal getDispersion(const QVector<qreal>& numbers, const qreal& expectedValue);
    qreal getStandardDeviation(const QVector<qreal>& numbers, const qreal& expectedValue);
    qreal getIndirectSigns(const QVector<qreal>& numbers);
    void displayHistogram(const QVector<qreal>& numbers);
    QVector<QPair<qreal, qreal>> getIntervals(const qreal& min, const qreal& max);
    QVector<qreal> getBarsHeight(const QVector<qreal> &numbers, const QVector<QPair<qreal, qreal>> &intervals);
    QVector<qreal> getBarPositions(const QVector<QPair<qreal, qreal>> &intervals);
    void setGeneratorParam(BaseGenerator* generator);

    void transformUI(BaseGenerator* generator);

    template<typename T>
    void setParams(BaseGenerator* baseGenerator) {

    }
};
#endif // MAINWINDOW_H
