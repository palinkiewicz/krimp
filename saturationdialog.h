#ifndef SATURATIONDIALOG_H
#define SATURATIONDIALOG_H

#include <QDialog>
#include <QSlider>
#include <QLabel>
#include <QPushButton>

class SaturationDialog : public QDialog {
    Q_OBJECT

public:
    explicit SaturationDialog(QWidget *parent = nullptr);
    int getSaturationValue() const;

signals:
    void saturationChanged(int saturation);

private:
    QSlider *saturationSlider;
    QLabel *sliderLabel;
    QPushButton *applyButton;
    int saturationValue;

private slots:
    void onSaturationChanged(int value);
    void onApplyClicked();
};

#endif // SATURATIONDIALOG_H
