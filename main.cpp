#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.m_GroupName = 0;
    w.m_data.setCurrent(0);
    QuizEntry m1("Сколько байт в килобайте","1000","1","1024","512",3);
    QuizEntry m2("Сколько герц в гигагерце","1 000 000 000", "1 000 000", "1 000", "0",1);
    QuizEntry m3();
    QuizEntry m4();
    QuizEntry m5();
    QuizEntry m6();
    QuizEntry m7();
    QuizEntry m8();
    QuizEntry m9();
    QuizEntry m10();
   //w.m_data.add(m1);
   // w.m_data.add(m2);
   // w.m_data.WriteDB();
    w.m_data.ReadDB();
    w.Output(w.m_data.getCurrent());

    w.show();

    return a.exec();
}
