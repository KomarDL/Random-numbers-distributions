#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lemergenerator.h"
#include "uniformgenerator.h"
#include "gaussiangenerator.h"
#include "expgenerator.h"
#include "gammagenerator.h"
#include "trianglegenerator.h"
#include "simpsongenerator.h"

#define GET_GENERATOR(index) static_cast<BaseGenerator*>(ui->distributionComboBox->itemData(index).value<void*>())

constexpr auto RAND_SEQ_SIZE = 2'000'000;
constexpr auto INTERVAL_AMOUNT = 20;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupInputs();
    setupHistogram();
    setupDistributionBox();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupDistributionBox()
{
    setBoxItem(new LemerGenerator);
    setBoxItem(new UniformGenerator);
    setBoxItem(new GaussianGenerator);
    setBoxItem(new ExpGenerator);
    setBoxItem(new GammaGenerator);
    setBoxItem(new TriangleGenerator);
    setBoxItem(new SimpsonGenerator);
}

void MainWindow::setupHistogram()
{
    histogram = new QCPBars(ui->view->xAxis, ui->view->yAxis);
    histogram->setAntialiased(false);
    histogram->setBrush(Qt::green);
    histogram->setPen(QPen(Qt::darkGreen));

    line = new QCPCurve(ui->view->xAxis, ui->view->yAxis);
    QPen dotLine(Qt::black);
    dotLine.setStyle(Qt::DotLine);
    dotLine.setWidthF(2);
    line->setPen(dotLine);

    ui->view->xAxis->setTickLabelRotation(45);
    ui->view->xAxis->setNumberPrecision(2);
    QFont ticksFont(ui->aSpinBox->font());
    ticksFont.setPointSize(12);
    ui->view->xAxis->setTickLabelFont(std::move(ticksFont));
}

void MainWindow::setupInputs()
{
    hideAll();

    ui->aSpinBox->setRange(0, INT_MAX);
    ui->mSpinBox->setRange(0, INT_MAX);
    ui->rSpinBox->setRange(0, INT_MAX);
    ui->aSpinBox->setValue(16807);
    ui->mSpinBox->setValue(21474837);
    ui->rSpinBox->setValue(2782874);
}

void MainWindow::setBoxItem(BaseGenerator *generator)
{
    ui->distributionComboBox->addItem(generator->getName(),
                                      QVariant::fromValue(static_cast<void*>(generator)));
}

void MainWindow::hideAll()
{
    ui->aperiodLabel->hide();
    ui->periodLabel->hide();
    ui->firstParamLabel->hide();
    ui->firstParamDoubleSpinBox->hide();
    ui->secondParamLabel->hide();
    ui->secondParamDoubleSpinBox->hide();
}

QVector<qreal> MainWindow::generateNumbers(BaseGenerator *const generator)
{
    QVector<qreal> result;
    result.reserve(RAND_SEQ_SIZE);
    for (size_t i = 0; i < RAND_SEQ_SIZE; ++i) {
        result.push_back(generator->generate());
    }
    return result;
}

QPair<qint64, qint64> MainWindow::getAperiodAndPeriodLen(const QVector<qreal> &numbers)
{
    QPair<qint64, qint64> result;

    //get period
    auto searchRes = std::find(numbers.rbegin() + 2, numbers.rend(), numbers.last());
    result.second = searchRes - numbers.rbegin();

    //get aperiod
    for(auto i = 0; (i < numbers.size()) && (i + result.second < numbers.size()); ++i) {
        if (numbers[i] == numbers[i + result.second]) {
            result.first = i + result.second;
            break;
        }
    }

    return result;
}

qreal MainWindow::getExpectedValue(const QVector<qreal> &numbers)
{
    auto sum = 0.;
    for(const auto& item : numbers) {
        sum += item;
    }
    return sum / numbers.size();
}

qreal MainWindow::getDispersion(const QVector<qreal> &numbers, const qreal &expectedValue)
{
    auto sum = 0.;
    for(const auto& item : numbers) {
        sum += (item - expectedValue) * (item - expectedValue);
    }
    return sum / numbers.size();
}

qreal MainWindow::getStandardDeviation(const QVector<qreal> &numbers, const qreal &expectedValue)
{
    auto sum = 0.;
    for(const auto& item : numbers) {
        sum += (item - expectedValue) * (item - expectedValue);
    }
    return qSqrt(sum / numbers.size());
}

qreal MainWindow::getIndirectSigns(const QVector<qreal> &numbers)
{
    auto K = 0;
    for(auto i = 0; i < numbers.size() - 1; i += 2) {
        auto tmp = numbers[i] * numbers[i] + numbers[i + 1] * numbers[i + 1];
        if (tmp < 1.) {
            ++K;
        }
    }
    return (2. * K) / numbers.size();
}

void MainWindow::displayHistogram(const QVector<qreal> &numbers)
{
    const auto [min, max] = std::minmax_element(numbers.begin(), numbers.end());
    auto intervals = getIntervals(*min, *max);
    auto barsHeight = getBarsHeight(numbers, intervals);
    auto highestBar = std::max_element(barsHeight.begin(), barsHeight.end());
    auto barWidth = intervals.first().second - intervals.first().first;
    auto barPositions = getBarPositions(intervals);
    QVector<qreal> lineX{*min, *max};
    QVector<qreal> lineY{1. / INTERVAL_AMOUNT, 1. / INTERVAL_AMOUNT};

    QSharedPointer<QCPAxisTickerFixed> ticker(new QCPAxisTickerFixed);
    ticker->setTickStep(barWidth);
    ticker->setTickCount(INTERVAL_AMOUNT + 1);
    ticker->setTickOrigin(barPositions.first());
    ui->view->xAxis->setTicker(ticker);

    histogram->setWidth(barWidth);
    histogram->setData(barPositions, barsHeight, true);
    line->setData(lineX, lineY);

    ui->view->xAxis->setRange(*min, *max + 0.0001);
    ui->view->yAxis->setRange(0, *highestBar + *highestBar * 0.1);
    ui->view->replot();
}

QVector<QPair<qreal, qreal> > MainWindow::getIntervals(const qreal& min, const qreal& max)
{
    const auto range = max - min;
    const auto intervalLen = range / INTERVAL_AMOUNT;
    QVector<QPair<qreal, qreal>> result;
    result.reserve(intervalLen);
    auto startInterval = min;
    for(auto i = 0; i < INTERVAL_AMOUNT; ++i) {
        result.push_back({startInterval, startInterval + intervalLen});
        startInterval += intervalLen;
    }
    return result;
}

QVector<qreal> MainWindow::getBarsHeight(const QVector<qreal> &numbers, const QVector<QPair<qreal, qreal> > &intervals)
{
    QVector<qreal> result;
    result.reserve(intervals.length());
    for(const auto& interval : intervals) {
        auto tmp = std::count_if(numbers.begin(), numbers.end(), [&interval](const qreal& item) {
            return item >= interval.first && item < interval.second;
        });
        result.push_back(static_cast<qreal>(tmp) / RAND_SEQ_SIZE);
    }
    return result;
}

QVector<qreal> MainWindow::getBarPositions(const QVector<QPair<qreal, qreal> > &intervals)
{
    QVector<qreal> result;
    result.reserve(intervals.length());
    auto halfInterval = (intervals.first().second - intervals.first().first) / 2;
    for(const auto& interval : intervals) {
        result.push_back(interval.first + halfInterval);
    }
    return result;
}

void MainWindow::setGeneratorParam(BaseGenerator *generator)
{
    switch (generator->getParamAmount()) {
    case 2:
        generator->setSecondParam(ui->secondParamDoubleSpinBox->value());
        Q_FALLTHROUGH();
    case 1:
        generator->setFirstParam(ui->firstParamDoubleSpinBox->value());
        break;
    }
}

void MainWindow::on_calcPushButton_clicked()
{
    auto lemer = new Lemer(ui->rSpinBox->value(), ui->mSpinBox->value(), ui->aSpinBox->value());
    auto generator = GET_GENERATOR(ui->distributionComboBox->currentIndex());
    generator->setLemer(lemer);
    setGeneratorParam(generator);
    auto randomNumbers = generateNumbers(generator);
    auto sectorLen = getAperiodAndPeriodLen(randomNumbers);
    auto expectedValue = getExpectedValue(randomNumbers);
    auto dispersion = getDispersion(randomNumbers, expectedValue);
    auto standardDeviation = getStandardDeviation(randomNumbers, expectedValue);
    auto indirectSigns = getIndirectSigns(randomNumbers);

    //display results
    ui->aperiodLabel->setText(QString("Длина периода = %1").arg(sectorLen.first));
    ui->periodLabel->setText(QString("Участок апериодичности = %1").arg(sectorLen.second));
    ui->expectedValueLabel->setText(QString("Мат.ожидание = %1").arg(expectedValue));
    ui->dispersionLabel->setText(QString("Дисперсия = %1").arg(dispersion));
    ui->standartDeviationLabel->setText(QString("Среднеквадратичное отклонение = %1").arg(standardDeviation));
    ui->indirectSignsLabel->setText(QString("Косвенные признаки = %1").arg(indirectSigns));
    displayHistogram(randomNumbers);
}

void MainWindow::on_distributionComboBox_currentIndexChanged(int index)
{
    // TODO: transform ui
    auto generator = GET_GENERATOR(index);
    transformUI(generator);
}

void MainWindow::transformUI(BaseGenerator *generator)
{
    hideAll();
    switch (generator->getParamAmount()) {
    case 0:
        ui->indirectSignsLabel->clear();
        ui->indirectSignsLabel->show();
        ui->aperiodLabel->clear();
        ui->aperiodLabel->show();
        ui->periodLabel->clear();
        ui->periodLabel->show();
        break;
    case 2:
        ui->secondParamLabel->setText(generator->getSecondParamName());
        ui->secondParamDoubleSpinBox->show();
        ui->secondParamLabel->show();
        Q_FALLTHROUGH();
    case 1:
        ui->firstParamLabel->setText(generator->getFirstParamName());
        ui->firstParamDoubleSpinBox->show();
        ui->firstParamLabel->show();
        ui->indirectSignsLabel->hide();
        break;

    }
}
