#include <QApplication>
#include <QFile>
#include <QTextStream>

#include <Ksl/Chart.h>
#include <Ksl/LineRegr.h>

using namespace Ksl;


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Chart chart("Linear Regression");

    // emulate noisy data
    auto vx = linspace(0.0, 100.0);
    auto vy = vx * 2.3;
    vy += 20.0;
    for (auto &y : vy)
        y += -25.0 + 50.0*double(rand())/RAND_MAX;

    // create solver and perform regression
    LineRegr regr(vx, vy);
    regr.solve();

    // plot data and fitting line
    chart.xyPlot("Data", vx, vy, XYPlot::Circles, Qt::black, Qt::green);
    // plot fitting line
    chart.line("Fitted line", regr.result()[0], regr.result()[1], Qt::red);
    // plot a fancy text label
    chart.textLabel("KSL Rocks!", QPointF(30,150), Qt::red, 32.0);

    chart.show();
    return app.exec();
}
