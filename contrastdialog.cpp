#include "contrastdialog.h"
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

ContrastDialog::ContrastDialog(QWidget *parent) : QDialog(parent), contrastValue(0) {
    setWindowTitle("Adjust Contrast");

    contrastSlider = new QSlider(Qt::Horizontal, this);
    contrastSlider->setRange(-255, 255);
    contrastSlider->setValue(0);
    contrastSlider->setTickInterval(10);

    sliderLabel = new QLabel(tr("Contrast: 0"), this);

    applyButton = new QPushButton(tr("Apply"), this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(sliderLabel);
    layout->addWidget(contrastSlider);
    layout->addWidget(applyButton);

    connect(contrastSlider, &QSlider::valueChanged, this, &ContrastDialog::onContrastChanged);
    connect(applyButton, &QPushButton::clicked, this, &ContrastDialog::onApplyButtonClicked);
}

int ContrastDialog::getContrastValue() const {
    return contrastValue;
}

void ContrastDialog::onContrastChanged(int value) {
    contrastValue = value;

    QString sign = (value > 0) ? "+" : "";
    sliderLabel->setText(QString(tr("Contrast: %1%2")).arg(sign).arg(value));
}

void ContrastDialog::onApplyButtonClicked() {
    emit contrastChanged(contrastValue);
    accept();
}
