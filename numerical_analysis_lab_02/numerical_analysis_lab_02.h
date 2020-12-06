#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_numerical_analysis_lab_02.h"

class Numerical_analysis_lab_02 : public QMainWindow
{
    Q_OBJECT

public:
    Numerical_analysis_lab_02(QWidget *parent = Q_NULLPTR);

private:
    Ui::Numerical_analysis_lab_02Class ui;
};
