#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QFile>
#include <QDateTime>
#include <QString>
#include <QStringList>
#include <QTime>
#include <string>
using std::string;
#include <algorithm>
#include <Crypto562/osrng.h>
using CryptoPP::AutoSeededRandomPool;
#include <Crypto562/cryptlib.h>
using CryptoPP::Exception;
#include <Crypto562/hex.h>
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;
#include <Crypto562/filters.h>
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;
#include <Crypto562/aes.h>
using CryptoPP::AES;
#include <Crypto562/modes.h>
using CryptoPP::OFB_Mode;
#define EncryptionKey "U82HuXLNzbX3f6r";
#define EncryptionKey_2 "epDKqfVtYXhdXgb";
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    instance.SetFilename("database.bin");
    instance.ReadDatabase();
    ui->tableWidget->setRowCount(instance.GetSize());
    ui->tableWidget->setAttribute(Qt::WA_Disabled,true);
    ui->tableWidget->setColumnCount(5);
    QStringList low;
    low.push_back("Имя");
    low.push_back("Фамилия");
    low.push_back("Номер Группы");
    low.push_back("Баллы");
    low.push_back("Дата");
    ui->tableWidget->setHorizontalHeaderLabels(low);
    for(int i=0;i<instance.GetSize();i++)
    {
        QTableWidgetItem *pName = new QTableWidgetItem;
        QTableWidgetItem *pLastName = new QTableWidgetItem;
        QTableWidgetItem *pGroupName = new QTableWidgetItem;
        QTableWidgetItem *pTime = new QTableWidgetItem;
        QTableWidgetItem *pScore = new QTableWidgetItem;
        QString GroupNameConv,ScoreConv;
        GroupNameConv.setNum(static_cast<double>(instance[i].GetGroupName()));
        ScoreConv.setNum(static_cast<double>(instance[i].GetScore()));
        pName->setText(instance[i].GetName());
        pLastName->setText(instance[i].GetLastName());
        pGroupName->setText(GroupNameConv);
        pTime->setText(instance[i].GetTime());
        pScore->setText(ScoreConv);
        ui->tableWidget->setItem(i,0,pName);
        ui->tableWidget->setItem(i,1,pLastName);
        ui->tableWidget->setItem(i,2,pGroupName);
        ui->tableWidget->setItem(i,3,pScore);
        ui->tableWidget->setItem(i,4,pTime);
    }
    ui->pushButton->setVisible(false);
    ui->num_->setVisible(false);
    ui->lResult->setVisible(false);
    ui->lResultNUM->setVisible(false);
    ui->radioButton->setVisible(false);
    ui->radioButton_2->setVisible(false);
    ui->radioButton_3->setVisible(false);
    ui->radioButton_4->setVisible(false);
    ui->choosen->setVisible(false);
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->pushButton_2->setVisible(false);
    ui->pushButton_3->setVisible(false);
    ui->totalCount->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}
int AccountInstance::GetGroupName()
{
    return m_GroupName;
}
int AccountInstance::GetScore()
{
    return m_Score;
}
QString AccountInstance::GetLastName()
{
    return m_LastName;
}
QString AccountInstance::GetName()
{
    return m_Name;
}
QString AccountInstance::GetTime()
{
    return m_Time;
}
void AccountInstance::SetGroupName(int src)
{
    m_GroupName = src;
}
void AccountInstance::SetLastName(QString src)
{
    m_LastName = src;
}
void QuizDatabase::ShuffleDatabase()
{

}

void AccountInstance::SetName(QString src)
{
    m_Name = src;
}
void AccountInstance::SetScore(int src)
{
    m_Score = src;
}
void AccountInstance::SetTime(QString src)
{
    m_Time = src;
}
AccountInstance &AccountInstance::operator =(const AccountInstance &obj)
{
    m_Time = obj.m_Time;
    m_Score = obj.m_Score;
    m_Name = obj.m_Name;
    m_LastName = obj.m_LastName;
    m_GroupName = obj.m_GroupName;
    return *this;
}
AccountInstance::AccountInstance(QString srcName, QString srcLastName, int srcGroupName, int srcScore, QString srcTime)
{
    SetName(srcName);
    SetLastName(srcLastName);
    SetGroupName(srcGroupName);
    SetScore(srcScore);
    SetTime(srcTime);
}
AccountInstance::AccountInstance()
{
}



AccountDatabase::AccountDatabase(QString src)
{
    m_Filename = src;
}

void AccountDatabase::Add(AccountInstance obj)
{
    m_database.push_back(obj);
}
int AccountDatabase::GetSize()
{
    return static_cast<int>(m_database.size());
}
void AccountDatabase::WriteDatabase()
{
   QFile file(m_Filename);
   file.open(QIODevice::WriteOnly|QIODevice::Text);
   QTextStream out(&file);
   out << Encrypt(m_database.size()) << "\n";
   for(size_t i=0;i<m_database.size();i++)
   {
       out << Encrypt(m_database[i].GetName()) << "\n";
       out << Encrypt(m_database[i].GetLastName()) << "\n";
       out << Encrypt(m_database[i].GetGroupName()) << "\n";
       out << Encrypt(m_database[i].GetScore()) << "\n";
       out << Encrypt(m_database[i].GetTime()) << "\n";
   }
   file.close();
}
QString AccountDatabase::Encrypt(int in)
{
    QString t_output;
    byte key[AES::DEFAULT_KEYLENGTH] = EncryptionKey;
    byte iv[AES::BLOCKSIZE] = EncryptionKey_2;
    OFB_Mode<AES>::Encryption t_Encrypt;
    t_Encrypt.SetKeyWithIV(key,sizeof(key),iv);
    string t_Str,t_strNonHex,t_strCompletelyEncrypted;
    QString temp;
    temp.setNum(in);
    t_Str = temp.toStdString();
    StringSource(t_Str,true,new StreamTransformationFilter(t_Encrypt,new StringSink(t_strNonHex)));
    StringSource(t_strNonHex,true,new HexEncoder(new StringSink(t_strCompletelyEncrypted)));
    t_output = QString::fromStdString(t_strCompletelyEncrypted);
    return t_output;
}
QString AccountDatabase::Encrypt(QString src)
{
    QString t_output;
    byte key[AES::DEFAULT_KEYLENGTH] = EncryptionKey;
    byte iv[AES::BLOCKSIZE] = EncryptionKey_2;
    OFB_Mode<AES>::Encryption t_Encrypt;
    t_Encrypt.SetKeyWithIV(key,sizeof(key),iv);
    string t_Str,t_strNonHex,t_strCompletelyEncrypted;
    t_Str = src.toStdString();
    StringSource(t_Str,true,new StreamTransformationFilter(t_Encrypt,new StringSink(t_strNonHex)));
    StringSource(t_strNonHex,true,new HexEncoder(new StringSink(t_strCompletelyEncrypted)));
    t_output = QString::fromStdString(t_strCompletelyEncrypted);
    return t_output;
}
QString AccountDatabase::DecryptToStr(QString &src)
{
    QString t_input;
    byte key[AES::DEFAULT_KEYLENGTH] = EncryptionKey;
    byte iv[AES::BLOCKSIZE] = EncryptionKey_2;
    OFB_Mode<AES>::Decryption t_Decrypt;
    t_Decrypt.SetKeyWithIV(key,sizeof(key),iv);
    string t_Str,t_strNonHex,t_strCompletelyEncrypted;
    t_strCompletelyEncrypted = src.toStdString();
    StringSource(t_strCompletelyEncrypted,true,new HexDecoder(new StringSink(t_strNonHex)));
    StringSource(t_strNonHex,true,new StreamTransformationFilter(t_Decrypt,new StringSink(t_Str)));
    t_input = QString::fromStdString(t_Str);
    return t_input;
}
int AccountDatabase::DecryptToInt(QString &src)
{
    QString t_input;
    int lResult;
    QString temp;
    byte key[AES::DEFAULT_KEYLENGTH] = EncryptionKey;
    byte iv[AES::BLOCKSIZE] = EncryptionKey_2;
    OFB_Mode<AES>::Decryption t_Decrypt;
    t_Decrypt.SetKeyWithIV(key,sizeof(key),iv);
    string t_Str,t_strNonHex,t_strCompletelyEncrypted;
    t_strCompletelyEncrypted = src.toStdString();
    StringSource(t_strCompletelyEncrypted,true,new HexDecoder(new StringSink(t_strNonHex)));
    StringSource(t_strNonHex,true,new StreamTransformationFilter(t_Decrypt,new StringSink(t_Str)));
    t_input = QString::fromStdString(t_Str);
    lResult = t_input.toInt();
    return lResult;
}

void AccountDatabase::ReadDatabase()
{
    QFile file(m_Filename);
   file.open(QIODevice::ReadOnly|QIODevice::Text);
   QTextStream in(&file);
   QString t_buf;
   t_buf = in.readLine();
   int temp = DecryptToInt(t_buf);
   for(int i=0;i<temp;i++)
   {
       int t_value;
       AccountInstance t_instance;
       t_buf = in.readLine();
       t_instance.SetName(DecryptToStr(t_buf));
       t_buf = in.readLine();
       t_instance.SetLastName(DecryptToStr(t_buf));
       t_buf = in.readLine();
       t_value = DecryptToInt(t_buf);
       t_instance.SetGroupName(t_value);
       t_buf = in.readLine();
       t_value = DecryptToInt(t_buf);
       t_instance.SetScore(t_value);
       t_buf = in.readLine();
       t_instance.SetTime(DecryptToStr(t_buf));
       Add(t_instance);
   }
   file.close();
}
void AccountDatabase::SetFilename(QString src)
{
    m_Filename = src;
}
QString AccountDatabase::GetFilename()
{
    return m_Filename;
}
AccountDatabase::AccountDatabase()
{
}


AccountInstance& AccountDatabase::operator [](int index)
{
    return m_database[index];
}

void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    if(arg1.isEmpty()==false)
    {
        m_Name = arg1;
    }
    else
    {
        m_Name = "N/A";
    }
}

void MainWindow::on_lineEdit_2_textEdited(const QString &arg1)
{
    if(arg1.isEmpty() == false)
    {
       m_LastName = arg1;
    }
    else
    {
        m_LastName = "N/A";
    }

}

void MainWindow::on_lineEdit_3_textEdited(const QString &arg1)
{
    m_GroupName = arg1.toInt();
}

void MainWindow::on_pushButton_4_pressed()
{

}
void MainWindow::on_pushButton_4_clicked()
{       AccountInstance t_instance;
        t_instance.SetName(m_Name);
        t_instance.SetLastName(m_LastName);
        t_instance.SetGroupName(m_GroupName);
        QDateTime curTime;
        QString _Format = "dd.MM.yyyy hh.mm.ss";
        QString _curTime;
        curTime = QDateTime::currentDateTime();
        _curTime = curTime.toString(_Format);
        t_instance.SetTime(_curTime);
        instance.Add(t_instance);
        ui->radioButton->setVisible(true);
        ui->radioButton_2->setVisible(true);
        ui->radioButton_3->setVisible(true);
        ui->num_->setVisible(true);
        ui->radioButton_4->setVisible(true);
        ui->choosen->setVisible(true);
        ui->label->setVisible(true);
        ui->label_2->setVisible(true);
        ui->label_3->setVisible(true);
        ui->label_4->setVisible(true);
        ui->pushButton->setVisible(true);
        ui->pushButton_2->setVisible(true);
        ui->pushButton_3->setVisible(true);
        ui->pushButton_4->setVisible(false);
        ui->lineEdit->setVisible(false);
        ui->lineEdit_2->setVisible(false);
        ui->lineEdit_3->setVisible(false);
        ui->tableWidget->setVisible(false);
        if(m_data[m_data.getCurrentId()].getChoosen()==0)
        {
            ui->choosen->setText("Вы еще не дали ответа.");
        }

}
void MainWindow::Output(QuizEntry obj)
{
    QString out;
    out.setNum(static_cast<double>(m_data.getCurrentId()+1));
    if(m_data[m_data.getCurrentId()].getChoosen()==0)
    {
        ui->choosen->setText("Вы еще не дали ответа.");
    }
    ui->num_->setText(out);
    ui->label->setText(obj.getQuestion());
    ui->radioButton->setText(obj.getAnswer1());
    ui->radioButton_2->setText(obj.getAnswer2());
    ui->radioButton_3->setText(obj.getAnswer3());
    ui->radioButton_4->setText(obj.getAnswer4());
    QString ch;
    ch.setNum(m_data.getSize());
    ui->label_2->setText(ch);
}
QuizEntry::QuizEntry()
{
}

QuizEntry::QuizEntry(const QuizEntry &obj)
{
    *this = obj;
}
QuizEntry::QuizEntry(const QString Que,const QString Answ1, const QString Answ2, const QString Answ3,const QString Answ4, int Right)
{
    m_Question = Que;
    m_Answer1 = Answ1;
    m_Answer2 = Answ2;
    m_Answer3 = Answ3;
    m_Answer4 = Answ4;
    m_RightAnswer = Right;
}
QuizEntry& QuizEntry::operator =(const QuizEntry &obj)
{
    m_Question = obj.m_Question;
    m_Answer1 = obj.m_Answer1;
    m_Answer2 = obj.m_Answer2;
    m_Answer3 = obj.m_Answer3;
    m_Answer4 = obj.m_Answer4;
    m_RightAnswer = obj.m_RightAnswer;
    return *this;
}
void QuizEntry::setQuestion(const QString src)
{
    m_Question = src;
}
void QuizEntry::setAnswer1(const QString src)
{
    m_Answer1 = src;
}
void QuizEntry::setAnswer2(const QString src)
{
    m_Answer2 = src;
}
void QuizEntry::setAnswer3(const QString src)
{
    m_Answer3 = src;
}
void QuizEntry::setAnswer4(const QString src)
{
    m_Answer4 = src;
}
QString QuizEntry::getQuestion()
{
    return m_Question;
}
QString QuizEntry::getAnswer1()
{
    return m_Answer1;
}
QString QuizEntry::getAnswer2()
{
    return m_Answer2;
}
QString QuizEntry::getAnswer3()
{
    return m_Answer3;
}
QString QuizEntry::getAnswer4()
{
    return m_Answer4;
}
void QuizEntry::setRightAnswer(int in)
{
    m_RightAnswer = in;
}

int QuizEntry::getRightAnswer()
{
    return m_RightAnswer;
}
void QuizEntry::checkAnswer(int in)
{
    m_TakedAnswer = in;
}

bool QuizEntry::check(int in)
{
    if(m_RightAnswer == in)
    {
        return true;
    }
    else
    {
        return false;
    }
}
QuizEntry QuizDatabase::getCurrent()
{
    return m_database[m_current];
}
QuizEntry QuizDatabase::getId(int in)
{
    return m_database[in];
}
int QuizEntry::getChoosen()
{
    return m_TakedAnswer;
}
void QuizDatabase::add(const QuizEntry &src)
{
    m_database.push_back(src);
}
void QuizDatabase::WriteDB()
{
    QFile file("c://test.bin");
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&file);
    out << m_database.size() << "\n";
    for(size_t i=0;i<m_database.size();i++)
    {
        out << m_database[i].getQuestion() << "\n";
        out << m_database[i].getAnswer1() << "\n";
        out << m_database[i].getAnswer2() << "\n";
        out << m_database[i].getAnswer3() << "\n";
        out << m_database[i].getAnswer4() << "\n";
        out << m_database[i].getRightAnswer() + 483274*i << "\n";
    }
    file.close();
}

void QuizDatabase::ReadDB()
{
    QFile file("c://test.bin");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&file);
    QString t_buf;
    t_buf = in.readLine();
    int temp = t_buf.toInt();
    for(int i=0;i<temp;i++)
    {
        QuizEntry tempElem;
        t_buf = in.readLine();
        tempElem.setQuestion(t_buf);
        t_buf = in.readLine();
        tempElem.setAnswer1(t_buf);
        t_buf = in.readLine();
        tempElem.setAnswer2(t_buf);
        t_buf = in.readLine();
        tempElem.setAnswer3(t_buf);
        t_buf = in.readLine();
        tempElem.setAnswer4(t_buf);
        t_buf = in.readLine();
        int readed = t_buf.toInt();
        readed = readed - 483274*i;
        tempElem.setRightAnswer(readed);
        tempElem.checkAnswer(0);
        add(tempElem);
    }
    file.close();
}
void QuizDatabase::setCurrent(int in)
{
    m_current = in;
}
int QuizDatabase::getCurrentId()
{
    return m_current;
}
int QuizDatabase::getSize()
{
    return static_cast<int>(m_database.size());
}
void MainWindow::on_pushButton_3_pressed()
{
    if((m_data.getCurrentId()-1)>=0)
    {
        m_data.setCurrent(m_data.getCurrentId()-1);
    }
    Output(m_data.getCurrent());
    QString out,ch;
    ch.setNum(m_data.getSize());
    ui->label_2->setText(ch);
    out.setNum(static_cast<double>(m_data.getCurrentId()+1));
    ui->num_->setText(out);
    ui->radioButton->setAutoExclusive(false);
    ui->radioButton->setChecked(false);
    ui->radioButton->setAutoExclusive(true);
    ui->radioButton_2->setAutoExclusive(false);
    ui->radioButton_2->setChecked(false);
    ui->radioButton_2->setAutoExclusive(true);
    ui->radioButton_3->setAutoExclusive(false);
    ui->radioButton_3->setChecked(false);
    ui->radioButton_3->setAutoExclusive(true);
    ui->radioButton_4->setAutoExclusive(false);
    ui->radioButton_4->setChecked(false);
    ui->radioButton_4->setAutoExclusive(true);
    if(m_data[m_data.getCurrentId()].getChoosen()==0)
    {
        ui->choosen->setText("Вы еще не дали ответа.");
    }
    if(m_data[m_data.getCurrentId()].getChoosen()==1)
    {
        ui->radioButton->setChecked(true);
    }
    else if(m_data[m_data.getCurrentId()].getChoosen()==2)
    {
        ui->radioButton_2->setChecked(true);
    }
    else if(m_data[m_data.getCurrentId()].getChoosen()==3)
    {
        ui->radioButton_3->setChecked(true);
    }
    else if(m_data[m_data.getCurrentId()].getChoosen()==4)
    {
        ui->radioButton_4->setChecked(true);
    }
}
void MainWindow::on_pushButton_2_pressed()
{
    if((m_data.getCurrentId()+1)<m_data.getSize())
    {
        m_data.setCurrent(m_data.getCurrentId()+1);
    }
    Output(m_data.getCurrent());
    QString out;
    out.setNum(static_cast<double>(m_data.getCurrentId()+1));
    ui->num_->setText(out);
    ui->radioButton->setAutoExclusive(false);
    ui->radioButton->setChecked(false);
    ui->radioButton->setAutoExclusive(true);
    ui->radioButton_2->setAutoExclusive(false);
    ui->radioButton_2->setChecked(false);
    ui->radioButton_2->setAutoExclusive(true);
    ui->radioButton_3->setAutoExclusive(false);
    ui->radioButton_3->setChecked(false);
    ui->radioButton_3->setAutoExclusive(true);
    ui->radioButton_4->setAutoExclusive(false);
    ui->radioButton_4->setChecked(false);
    ui->radioButton_4->setAutoExclusive(true);
    if(m_data[m_data.getCurrentId()].getChoosen()==0)
    {
        ui->choosen->setText("Вы еще не дали ответа.");
    }
    if(m_data[m_data.getCurrentId()].getChoosen()==1)
    {
        ui->radioButton->setChecked(true);
    }
    else if(m_data[m_data.getCurrentId()].getChoosen()==2)
    {
        ui->radioButton_2->setChecked(true);
    }
    else if(m_data[m_data.getCurrentId()].getChoosen()==3)
    {
        ui->radioButton_3->setChecked(true);
    }
    else if(m_data[m_data.getCurrentId()].getChoosen()==4)
    {
        ui->radioButton_4->setChecked(true);
    }
}
QuizEntry &QuizDatabase::operator [] (int index)
{
    return m_database[index];
}

void MainWindow::on_radioButton_toggled(bool checked)
{
    if(checked == true)
    {
        m_data[m_data.getCurrentId()].checkAnswer(1);
        QString choosen;
        choosen.setNum(static_cast<double>(m_data[m_data.getCurrentId()].getChoosen()));
        ui->choosen->setText(choosen);
    }
    QString choosen;
    choosen.setNum(static_cast<double>(m_data[m_data.getCurrentId()].getChoosen()));
    ui->choosen->setText(choosen);
}
void MainWindow::on_radioButton_2_toggled(bool checked)
{
    if(checked == true)
    {
        m_data[m_data.getCurrentId()].checkAnswer(2);
        QString choosen;
        choosen.setNum(static_cast<double>(m_data[m_data.getCurrentId()].getChoosen()));
        ui->choosen->setText(choosen);
    }
    QString choosen;
    choosen.setNum(static_cast<double>(m_data[m_data.getCurrentId()].getChoosen()));
    ui->choosen->setText(choosen);
}

void MainWindow::on_radioButton_3_toggled(bool checked)
{
    if(checked == true)
    {
        m_data[m_data.getCurrentId()].checkAnswer(3);
        QString choosen;
        choosen.setNum(static_cast<double>(m_data[m_data.getCurrentId()].getChoosen()));
        ui->choosen->setText(choosen);
    }
    QString choosen;
    choosen.setNum(static_cast<double>(m_data[m_data.getCurrentId()].getChoosen()));
    ui->choosen->setText(choosen);
}

void MainWindow::on_radioButton_4_toggled(bool checked)
{
    if(checked == true)
    {
        m_data[m_data.getCurrentId()].checkAnswer(4);
        QString choosen;
        choosen.setNum(static_cast<double>(m_data[m_data.getCurrentId()].getChoosen()));
        ui->choosen->setText(choosen);
    }
    QString choosen;
    choosen.setNum(static_cast<double>(m_data[m_data.getCurrentId()].getChoosen()));
    ui->choosen->setText(choosen);
}





void MainWindow::on_pushButton_pressed()
{
    int score=0;
    for(int i=0;i<m_data.getSize();i++)
    {
        if(m_data[i].getChoosen()==m_data[i].getRightAnswer())
        {
            score++;
        }
    }
    ui->totalCount->setVisible(true);
    QString total;
    total.setNum(static_cast<double>(m_data.getSize()));
    ui->totalCount->setText(total);
    instance[instance.GetSize()-1].SetScore(score);
    ui->radioButton->setVisible(false);
    ui->radioButton_2->setVisible(false);
    ui->radioButton_3->setVisible(false);
    ui->radioButton_4->setVisible(false);
    ui->choosen->setVisible(false);
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->pushButton_2->setVisible(false);
    ui->pushButton_3->setVisible(false);
    ui->pushButton->setVisible(false);
    ui->num_->setVisible(false);
    ui->lResult->setVisible(true);
    ui->lResultNUM->setVisible(true);
    instance.WriteDatabase();
    QString ResultNUM;
    ResultNUM.setNum(static_cast<double>(score));
    ui->lResultNUM->setText(ResultNUM);

}
