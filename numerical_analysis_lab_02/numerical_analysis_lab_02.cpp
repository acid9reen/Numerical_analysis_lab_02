#include <vector>
#include "numerical_analysis_lab_02.h"
#include "functions.h"
#include "solver.h"

using namespace functions;
using std::vector;


Numerical_analysis_lab_02::Numerical_analysis_lab_02(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.test_solve_btn, &QPushButton::clicked, this, &Numerical_analysis_lab_02::plot_test_task);
}

void Numerical_analysis_lab_02::plot_test_task()
{
    int n = ui.test_n_input->text().toInt();
    auto* series = new QLineSeries();
    auto* chart = new QChart();

    auto solver = new Solver
    (
        n,
        0.5,
        k_1_test, q_1_test, f_1_test,
        k_2_test, q_2_test, f_2_test
    );

    vector<double> vs = solver->solve();
    double x_curr = 0;
    double step = 1. / n;


    for (auto it = begin(vs); it != end(vs); ++it) 
    {
        series->append(x_curr, *it);
        x_curr += step;
    }

    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Solution");

    ui.test_solution_plot->setRenderHint(QPainter::Antialiasing);
    ui.test_solution_plot->setChart(chart);
}
