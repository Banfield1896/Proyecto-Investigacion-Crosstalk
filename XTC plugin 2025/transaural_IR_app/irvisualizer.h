#pragma once
#include <QWidget>
#include <vector>

class IRVisualizer : public QWidget {
    Q_OBJECT

public:
    IRVisualizer(QWidget *parent = nullptr);
    void plot(const std::vector<float>& leftIR, const std::vector<float>& rightIR);
};
