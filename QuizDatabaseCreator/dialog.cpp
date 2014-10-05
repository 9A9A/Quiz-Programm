#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->tableWidget->verticalHeader()->setVisible(false);
   // ui->tableWidget->setSizePolicy(QSizePolicy::horizontalStretch,QSizePolicy::verticalStretch);
}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::SetTableWidgetSize(int h, int w)
{
    ui->tableWidget->resize(w,h);
}

void Dialog::UpdateDatabase(QuizDatabase &obj)
{
    ui->tableWidget->setAttribute(Qt::WA_Disabled,true);
    m_data = obj;
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setRowCount(m_data.getSize()*6);
    QStringList label;
    label.push_back("База данных");
    ui->tableWidget->setHorizontalHeaderLabels(label);
    for(int i=0,j=0;i<m_data.getSize();i++)
    {
        QTableWidgetItem *pQuestion = new QTableWidgetItem;
        QTableWidgetItem *pAnsw1 = new QTableWidgetItem;
        QTableWidgetItem *pAnsw2 = new QTableWidgetItem;
        QTableWidgetItem *pAnsw3 = new QTableWidgetItem;
        QTableWidgetItem *pAnsw4 = new QTableWidgetItem;
        QTableWidgetItem *pRightAnsw = new QTableWidgetItem;
        QString QSTRQuestion = "Вопрос : ";
        QString QSTRAnsw1 = "Ответ 1 : ";
        QSTRAnsw1.append(m_data[i].getAnswer1());
        QString QSTRAnsw2 = "Ответ 2 : ";
        QSTRAnsw2.append(m_data[i].getAnswer2());
        QString QSTRAnsw3 = "Ответ 3 : ";
        QSTRAnsw3.append(m_data[i].getAnswer3());
        QString QSTRAnsw4 = "Ответ 4 : ";
        QSTRAnsw4.append(m_data[i].getAnswer4());
        QString from;
        from.setNum(m_data[i].getRightAnswer());
        QString QSTRRightAnsw = "Правильный вариант ответа : ";
        QSTRRightAnsw.append(from);
        QSTRQuestion.append(m_data[i].getQuestion());
        pQuestion->setText(QSTRQuestion);
        pAnsw1->setText(QSTRAnsw1);
        pAnsw2->setText(QSTRAnsw2);
        pAnsw3->setText(QSTRAnsw3);
        pAnsw4->setText(QSTRAnsw4);
        pRightAnsw->setText(QSTRRightAnsw);
        ui->tableWidget->setItem(j++,0,pQuestion);
        ui->tableWidget->setItem(j++,0,pAnsw1);
        ui->tableWidget->setItem(j++,0,pAnsw2);
        ui->tableWidget->setItem(j++,0,pAnsw3);
        ui->tableWidget->setItem(j++,0,pAnsw4);
        ui->tableWidget->setItem(j++,0,pRightAnsw);
    }
}
