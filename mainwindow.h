#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
namespace Ui {
class MainWindow;
}

class QuizEntry
{
public:
    // set variables
    QuizEntry();
    QuizEntry(const QuizEntry &);
    QuizEntry(const QString,const QString, const QString, const QString,const QString, int);
    void    setQuestion(const QString);
    void    setAnswer1(const QString);
    void    setAnswer2(const QString);
    void    setAnswer3(const QString);
    void    setAnswer4(const QString);
    void    setRightAnswer(int);
    void    checkAnswer(int);
    void    Output();
    bool    check(int);
    int     getChoosen();
    QuizEntry& operator = (const QuizEntry &);
    // get variables
    QString getQuestion();
    QString getAnswer1();
    QString getAnswer2();
    QString getAnswer3();
    QString getAnswer4();
    int     getRightAnswer();
private:
    int     m_TakedAnswer;
    QString m_Question;
    QString m_Answer1;
    QString m_Answer2;
    QString m_Answer3;
    QString m_Answer4;
    int     m_RightAnswer;
};

class QuizDatabase
{
public:
    void    WriteDB();
    void    ReadDB();
    QuizEntry getCurrent();
    int     getCurrentId();
    QuizEntry getId(int);
    void    setCurrent(int);
    void    add(const QuizEntry &);
    int     getSize();
    QuizEntry &operator [](int);
private:
    int     m_current;
    std::vector<QuizEntry> m_database;
};

class AccountInstance
{
public:
    AccountInstance();
    AccountInstance(QString,QString,int,int,QString);
    QString GetName();
    QString GetLastName();
    int     GetGroupName();
    int     GetScore();
    QString GetTime();
    QString GetDate();
    void    SetName(QString);
    void    SetLastName(QString);
    void    SetScore(int);
    void    SetTime(QString);
    void    SetGroupName(int);
    void    SetDate(QString);
    AccountInstance &operator = (const AccountInstance &);

private:
    QString m_Name;
    QString m_LastName;
    int     m_GroupName;
    int     m_Score;
    QString m_Time;
};

class AccountDatabase
{
public:
    AccountDatabase();
    AccountDatabase(QString);
    void    Add(AccountInstance);
    void    ReadDatabase();
    void    WriteDatabase();
    int     GetSize();
    void    SetFilename(QString);
    QString GetFilename();
    AccountInstance &operator [](int);
private:
    QString m_Filename;
    std::vector<AccountInstance> m_database;
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    AccountDatabase instance;
    QString m_Name;
    QString m_LastName;
    int     m_GroupName;
    void Output(QuizEntry);
    QuizDatabase m_data;
private slots:
    void on_pushButton_pressed();

    void on_pushButton_2_pressed();

    void on_radioButton_toggled(bool checked);

    void on_radioButton_2_toggled(bool checked);

    void on_radioButton_3_toggled(bool checked);

    void on_radioButton_4_toggled(bool checked);


    void on_lineEdit_textEdited(const QString &arg1);

    void on_lineEdit_2_textEdited(const QString &arg1);

    void on_lineEdit_3_textEdited(const QString &arg1);

    void on_pushButton_4_pressed();

    void on_pushButton_4_clicked();


    void on_pushButton_3_pressed();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
