#ifndef CONTRASTDIALOG_H
#define CONTRASTDIALOG_H

#include <QDialog>
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class ContrastDialog : public QDialog {
    Q_OBJECT

public:
    explicit ContrastDialog(QWidget *parent = nullptr);
    int getContrastValue() const;

signals:
    void contrastChanged(int contrast);

private slots:
    void onContrastChanged(int value);
    void onApplyButtonClicked();

private:
    QSlider *contrastSlider;
    QPushButton *applyButton;
    QLabel *sliderLabel;
    int contrastValue;
};

#endif // CONTRASTDIALOG_H
