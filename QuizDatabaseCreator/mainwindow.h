#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dialog.h>
#include <vector>
#include "QuizClassHeader.h"
#pragma once
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void ClearPrivateData();
    bool CheckForNonEmpty();

private slots:

    void on_Question_textEdited(const QString &arg1);

    void on_Answer_1_textEdited(const QString &arg1);

    void on_Answer_2_textEdited(const QString &arg1);

    void on_Answer_3_textEdited(const QString &arg1);

    void on_Answer_4_textEdited(const QString &arg1);

    void on_Right_Answer_textEdited(const QString &arg1);

    void on_AddToDatabase_pressed();

    void on_action_2_triggered();

    void on_action_triggered();

    void on_action_3_triggered();

private:
    Dialog *pDatabaseView;
    QString m_Question;
    QString m_Answ1;
    QString m_Answ2;
    QString m_Answ3;
    QString m_Answ4;
    int     m_RightAnsw;
    Ui::MainWindow *ui;
protected:
    QuizDatabase m_data;
};

#endif // MAINWINDOW_H
