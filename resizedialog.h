#ifndef RESIZEDIALOG_H
#define RESIZEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class resizeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit resizeDialog(int width, int height, QWidget *parent = 0);
    QLabel *wlabel;
    QLabel *hlabel;
    QLineEdit *wledit;
    QLineEdit *hledit;
    QPushButton *ok;
    QPushButton *cancel;
    QSize returnSize;
signals:
    
public slots:
    void accept();
    //void reject();
};

#endif // RESIZEDIALOG_H
