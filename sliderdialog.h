#ifndef SLIDERDIALOG_H
#define SLIDERDIALOG_H

#include <QDialog>
#include <QSlider>
#include <QPushButton>
#include <QLineEdit>

class sliderdialog : public QDialog
{
    Q_OBJECT
private:
    QPushButton *ok;
    QPushButton *cancel;
    QSlider *slider;
    QLineEdit *ledit;
    int resultValue;
public:
    explicit sliderdialog(QWidget *parent = 0);
    int getResultValue();
    void setMax(int max);
    void setMin(int min);
    void setCurrent(int current);


signals:
    
public slots:
    void accept();
    void sliderChanged(int);
    void sliderChanged();
    void lineEditChanged();
};

#endif // SLIDERDIALOG_H
