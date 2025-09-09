#pragma once
#include <QWidget>
#include "IRGenerator.h"
#include "IRVisualizer.h"
#include "IRFileManager.h"
#include "Parameters.h"

class AppWindow : public QWidget {
    Q_OBJECT

public:
    AppWindow(QWidget *parent = nullptr);

private slots:
    void onGenerateIR();
    void onSaveIR();

private:
    IRGenerator irGen;
    IRVisualizer *visualizer;
    IRFileManager fileManager;
    Parameters params;

    // UI elements
    QLineEdit *nameEdit;
    QDoubleSpinBox *DSpin, *dpSpin, *doSpin, *betaSpin;
    QSpinBox *nSamplesSpin, *fsSpin;
    QPushButton *generateButton, *saveButton;
};
