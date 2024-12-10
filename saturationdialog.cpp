#include "saturationdialog.h"
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

SaturationDialog::SaturationDialog(QWidget *parent)
    : QDialog(parent), saturationValue(0) {
    setWindowTitle("Adjust Saturation");

    saturationSlider = new QSlider(Qt::Horizontal, this);
    saturationSlider->setRange(-100, 100);
    saturationSlider->setValue(0);
    saturationSlider->setTickInterval(10);

    sliderLabel = new QLabel(tr("Saturation: 0"), this);

    applyButton = new QPushButton(tr("Apply"), this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(sliderLabel);
    layout->addWidget(saturationSlider);
    layout->addWidget(applyButton);

    connect(saturationSlider, &QSlider::valueChanged, this, &SaturationDialog::onSaturationChanged);
    connect(applyButton, &QPushButton::clicked, this, &SaturationDialog::onApplyClicked);
}

int SaturationDialog::getSaturationValue() const {
    return saturationValue;
}

void SaturationDialog::onSaturationChanged(int value) {
    saturationValue = value;

    QString sign = (value > 0) ? "+" : "";
    sliderLabel->setText(QString(tr("Saturation: %1%2")).arg(sign).arg(value));
}

void SaturationDialog::onApplyClicked() {
    emit saturationChanged(saturationValue);
    accept();
}
