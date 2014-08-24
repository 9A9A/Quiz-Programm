#include "mainwindow.h"
#include <QApplication>
#include <QCryptographicHash>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.m_GroupName = 0;
    w.m_data.setCurrent(0);
    QuizEntry m1("Сколько байт в килобайте","1000","1","1024","512",3);
    QuizEntry m2("Сколько герц в гигагерце","1 000 000 000", "1 000 000", "1 000", "0",1);
    QuizEntry m3("Сколько пассажиров в элетричке","300","200","200","N/A",4);
    QuizEntry m4("Сколько бит в байте","1","4","6","8",4);
    QuizEntry m5("1","1","1","1","1",4);
    QuizEntry m6("2","2","1","1","1",4);
    QuizEntry m7("3","1","1","1","1",4);
    QuizEntry m8("4","1","1","1","1",4);
    QuizEntry m9("5","1","1","1","1",4);
    QuizEntry m10("6","1","1","1","1",4);
    w.m_data.add(m1);
    w.m_data.add(m2);
    w.m_data.add(m3);
    w.m_data.add(m4);
    w.m_data.add(m5);
    w.m_data.add(m6);
    w.m_data.add(m7);
    w.m_data.add(m8);
    w.m_data.add(m9);
    w.m_data.add(m10);

    w.m_data.ShuffleDatabase();
   //w.m_data.WriteDB();
   //w.m_data.ReadDB();
    w.Output(w.m_data.getCurrent());

    w.show();

    return a.exec();
}
