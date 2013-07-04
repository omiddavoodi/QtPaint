#include "resizedialog.h"
#include <QDebug>

resizeDialog::resizeDialog(int width, int height, QWidget *parent) :
    QDialog(parent)
{
    this->setModal(true);

    this->resize(200,120);
    wlabel = new QLabel("Image Width", this);
    wlabel->setGeometry(10,10,180,20);
    hlabel = new QLabel("Image Height", this);
    hlabel->setGeometry(10,52,180,20);
    wledit = new QLineEdit(QVariant(width).toString(), this);
    wledit->setGeometry(10,32,180,20);
    hledit = new QLineEdit(QVariant(height).toString(), this);
    hledit->setGeometry(10,72,180,20);
    ok = new QPushButton("OK",this);
    ok->setGeometry(10,92,95,20);
    cancel = new QPushButton("Cancel",this);
    cancel->setGeometry(105,92,95,20);
    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
    this->returnSize = QSize(0,0);
}

resizeDialog::~resizeDialog()
{
    delete wlabel;
    delete hlabel;
    delete wledit;
    delete hledit;
    delete ok;
    delete cancel;
}

void resizeDialog::accept()
{
    this->returnSize = QSize(QVariant(wledit->text()).toInt(),QVariant(hledit->text()).toInt());
    this->setResult(1);
    this->close();
}

/*void resizeDialog::reject()
{
    this->returnSize = QSize(0,0);
    this->setResult(0);
    this->close();
}
*/
