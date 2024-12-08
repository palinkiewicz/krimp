#include "brightnessdialog.h"
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

BrightnessDialog::BrightnessDialog(QWidget *parent) : QDialog(parent), brightnessValue(0) {
    setWindowTitle("Adjust Brightness");

    brightnessSlider = new QSlider(Qt::Horizontal, this);
    brightnessSlider->setRange(-255, 255);
    brightnessSlider->setValue(0);
    brightnessSlider->setTickInterval(10);

    sliderLabel = new QLabel(tr("Brightness: 0"), this);

    applyButton = new QPushButton(tr("Apply"), this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(sliderLabel);
    layout->addWidget(brightnessSlider);
    layout->addWidget(applyButton);

    connect(brightnessSlider, &QSlider::valueChanged, this, &BrightnessDialog::onBrightnessChanged);
    connect(applyButton, &QPushButton::clicked, this, &BrightnessDialog::onApplyButtonClicked);
}

int BrightnessDialog::getBrightnessValue() const {
    return brightnessValue;
}

void BrightnessDialog::onBrightnessChanged(int value) {
    brightnessValue = value;

    QString sign = (value > 0) ? "+" : "";
    sliderLabel->setText(QString(tr("Brightness: %1%2")).arg(sign).arg(value));
}

void BrightnessDialog::onApplyButtonClicked() {
    emit brightnessChanged(brightnessValue);
    accept();
}
