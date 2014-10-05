#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "QuizClassHeader.h"
#pragma once
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void SetTableWidgetSize(int,int);

private:
    QuizDatabase m_data;
    Ui::Dialog *ui;

public:
    void UpdateDatabase(QuizDatabase &);
};

#endif // DIALOG_H
