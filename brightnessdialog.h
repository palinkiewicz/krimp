#ifndef BRIGHTNESSDIALOG_H
#define BRIGHTNESSDIALOG_H

#include <QDialog>
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class BrightnessDialog : public QDialog {
    Q_OBJECT

public:
    explicit BrightnessDialog(QWidget *parent = nullptr);
    int getBrightnessValue() const;

signals:
    void brightnessChanged(int brightness);

private slots:
    void onBrightnessChanged(int value);
    void onApplyButtonClicked();

private:
    QSlider *brightnessSlider;
    QPushButton *applyButton;
    QLabel *sliderLabel;
    int brightnessValue;
};

#endif // BRIGHTNESSDIALOG_H
