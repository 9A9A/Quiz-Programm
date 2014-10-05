#ifndef QUIZCLASSHEADER_H
#define QUIZCLASSHEADER_H

#endif // QUIZCLASSHEADER_H
#define CRYPTOPP_DEFAULT_NO_DLL
#include <Crypto562/dll.h>
#ifdef CRYPTOPP_WIN32_AVAILABLE
#include <windows.h>
#endif
#pragma once


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
    QString    Encrypt(QString);
    QString    Encrypt(int );
    QString DecryptToStr(QString &);
    int     DecryptToInt(QString &);
    QuizEntry getCurrent();
    int     getCurrentId();
    QuizEntry getId(int);
    void    setCurrent(int);
    void    add(const QuizEntry &);
    int     getSize();
    QuizDatabase &operator = (const QuizDatabase &);
    QuizEntry &operator [](int);
    void    ShuffleDatabase();
private:
    int     m_current;
    std::vector<QuizEntry> m_database;
};
