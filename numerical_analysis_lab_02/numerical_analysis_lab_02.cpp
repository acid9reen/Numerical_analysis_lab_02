#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <QString>
#include <QTableWidgetItem>
#include "numerical_analysis_lab_02.h"
#include "functions.h"
#include "solver.h"

using namespace functions;
using std::vector;


QString approx(double num)
{
    std::ostringstream streamObj;
    streamObj << std::scientific << num;

    return QString::fromStdString(streamObj.str());
}


Numerical_analysis_lab_02::Numerical_analysis_lab_02(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.test_solve_btn, &QPushButton::clicked, this, &Numerical_analysis_lab_02::plot_test_task);
    connect(ui.main_solve_btn, &QPushButton::clicked, this, &Numerical_analysis_lab_02::plot_main_task);
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

    ui.test_solution_plot->setRubberBand(QChartView::RectangleRubberBand);
    ui.test_solution_plot->setRenderHint(QPainter::Antialiasing);
    ui.test_solution_plot->setChart(chart);
}

void Numerical_analysis_lab_02::plot_main_task()
{
    int n = ui.main_n_input->text().toInt();

    // Clear table
    while (ui.main_table->rowCount() > 0)
    {
        ui.main_table->removeRow(0);
    }

    // Main task plot
    auto* series_1 = new QLineSeries();
    auto* series_2 = new QLineSeries();
    auto* chart = new QChart();

    auto solver_1 = new Solver
    (
        n,
        0.5,
        k_1_main, q_1_main, f_1_main,
        k_2_main, q_2_main, f_2_main
    );

    vector<double> vs_1 = solver_1->solve();
    double x_curr = 0;
    double step = 1. / n;

    for (auto it = begin(vs_1); it != end(vs_1); ++it)
    {
        series_1->append(x_curr, *it);
        x_curr += step;
    }

    auto solver_2 = new Solver
    (
        n * 2,
        0.5,
        k_1_main, q_1_main, f_1_main,
        k_2_main, q_2_main, f_2_main
    );

    vector<double> vs_2 = solver_2->solve();
    x_curr = 0;
    step = 1. / (n * 2);

    for (auto it = begin(vs_2); it != end(vs_2); ++it)
    {
        series_2->append(x_curr, *it);
        x_curr += step;
    }

    chart->legend()->hide();
    chart->addSeries(series_1);
    chart->addSeries(series_2);
    chart->createDefaultAxes();
    chart->setTitle("Solution");

    ui.main_solution_plot->setRubberBand(QChartView::RectangleRubberBand);
    ui.main_solution_plot->setRenderHint(QPainter::Antialiasing);
    ui.main_solution_plot->setChart(chart);


    // Error plot

    auto* error_series = new QLineSeries();
    auto* error_chart = new QChart();
    
    x_curr = 0;
    step = 1. / n;
    double max_delta_u_v = 0;
    double max_delta_u_v_x_coord = 0;

    for (size_t i = 0; i < vs_1.size(); i++)
    {   
        double delta_u_v = vs_1[i] - vs_2[2 * i];

        ui.main_table->insertRow(i);
        ui.main_table->setItem(i, 0, new QTableWidgetItem(approx(x_curr)));
        ui.main_table->setItem(i, 1, new QTableWidgetItem(approx(vs_1[i])));
        ui.main_table->setItem(i, 2, new QTableWidgetItem(approx(vs_2[2 * i])));
        ui.main_table->setItem(i, 3, new QTableWidgetItem(approx(delta_u_v)));


        if (delta_u_v > max_delta_u_v)
        {
            max_delta_u_v = delta_u_v;
            max_delta_u_v_x_coord = x_curr;
        }

        error_series->append(x_curr, abs(delta_u_v));
        x_curr += step;
    }

    ui.max_delta_v_v->setText(approx(max_delta_u_v));
    ui.max_delta_v_v_x_coord->setText(approx(max_delta_u_v_x_coord));

    error_chart->legend()->hide();
    error_chart->addSeries(error_series);
    error_chart->createDefaultAxes();
    error_chart->setTitle("Error");

    ui.main_error_plot->setRubberBand(QChartView::RectangleRubberBand);
    ui.main_error_plot->setRenderHint(QPainter::Antialiasing);
    ui.main_error_plot->setChart(error_chart);
}
