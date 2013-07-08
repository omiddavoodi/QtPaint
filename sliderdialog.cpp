#include "sliderdialog.h"

sliderdialog::sliderdialog(QWidget *parent) :
    QDialog(parent)
{
    this->setModal(true);

    this->resize(200,100);

    ledit = new QLineEdit(this);
    ledit->setGeometry(10,10,180,24);
    connect(ledit,SIGNAL(textEdited(QString)),this,SLOT(lineEditChanged()));

    slider = new QSlider(Qt::Horizontal, this);
    slider->setGeometry(10,40,180,24);
    connect(slider,SIGNAL(sliderMoved(int)),this,SLOT(sliderChanged(int)));
    connect(slider,SIGNAL(sliderPressed()),this,SLOT(sliderChanged()));
    connect(slider,SIGNAL(sliderReleased()),this,SLOT(sliderChanged()));

    ok = new QPushButton("OK",this);
    ok->setGeometry(10,70,95,20);
    cancel = new QPushButton("Cancel",this);
    cancel->setGeometry(105,70,95,20);
    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));

    resultValue = 0;
}

int sliderdialog::getResultValue()
{
    return this->resultValue;
}

void sliderdialog::setMax(int max)
{
    slider->setMaximum(max);
}

void sliderdialog::setMin(int min)
{
    slider->setMinimum(min);
}

void sliderdialog::setCurrent(int current)
{
    slider->setValue(current);
    ledit->setText(QVariant(slider->value()).toString());
}

void sliderdialog::accept()
{
    this->resultValue = slider->value();
    this->setResult(1);
    this->close();
}

void sliderdialog::sliderChanged(int a)
{
    ledit->setText(QVariant(a).toString());
}

void sliderdialog::sliderChanged()
{
    ledit->setText(QVariant(slider->value()).toString());
}

void sliderdialog::lineEditChanged()
{
    int newval = QVariant(ledit->text()).toInt();
    newval = (newval > slider->maximum()? slider->maximum() : newval);
    newval = (newval < slider->minimum()? slider->minimum() : newval);
    ledit->setText(QVariant(newval).toString());
    slider->setValue(newval);
}
