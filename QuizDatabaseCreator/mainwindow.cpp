#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QFile>
#include <QDateTime>
#include <QString>
#include <QStringList>
#include <QTime>
#include <QProcess>
#include <time.h>
#include <utility>
using std::swap;
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
#define EncryptionKey "U82HuXLNzbX3f6r"
#define EncryptionKey_2 "epDKqfVtYXhdXgb"
#define MagicNumber 3831732

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pDatabaseView = nullptr;
    m_data.ReadDB();
    ui->Question->setPlaceholderText("Введите вопрос");
    ui->Answer_1->setPlaceholderText("Введите вариант ответа 1");
    ui->Answer_2->setPlaceholderText("Введите вариант ответа 2");
    ui->Answer_3->setPlaceholderText("Введите вариант ответа 3");
    ui->Answer_4->setPlaceholderText("Введите вариант ответа 4");
    ui->Right_Answer->setPlaceholderText("Введите номер правильного ответа");
    QString EntryCount;
    EntryCount.setNum(static_cast<double>(m_data.getSize()));
    ui->EntryCount->setText(EntryCount);
}

MainWindow::~MainWindow()
{
    delete ui;
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
    QFile file("quiz.db");
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&file);
    out << Encrypt(m_database.size()) << "\n";
    //out << m_database.size() << "\n";
    for(size_t i=0;i<m_database.size();i++)
    {
        out << Encrypt(m_database[i].getQuestion()) << "\n";
        out << Encrypt(m_database[i].getAnswer1()) << "\n";
        out << Encrypt(m_database[i].getAnswer2()) << "\n";
        out << Encrypt(m_database[i].getAnswer3()) << "\n";
        out << Encrypt(m_database[i].getAnswer4()) << "\n";
        int m_RightAnswer = m_database[i].getRightAnswer();
        m_RightAnswer *= (MagicNumber +i * 3);
        out << Encrypt(m_RightAnswer) << "\n";
        //out << m_database[i].getRightAnswer() + 483274*i << "\n";
    }
    file.close();
}

void QuizDatabase::ReadDB()
{
    QFile file("quiz.db");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&file);
    m_database.clear();
    QString t_buf;
    t_buf = in.readLine();
    int temp = DecryptToInt(t_buf);
    for(int i=0;i<temp;i++)
    {
        QuizEntry tempElem;
        t_buf = in.readLine();
        tempElem.setQuestion(DecryptToStr(t_buf));
        t_buf = in.readLine();
        tempElem.setAnswer1(DecryptToStr(t_buf));
        t_buf = in.readLine();
        tempElem.setAnswer2(DecryptToStr(t_buf));
        t_buf = in.readLine();
        tempElem.setAnswer3(DecryptToStr(t_buf));
        t_buf = in.readLine();
        tempElem.setAnswer4(DecryptToStr(t_buf));
        t_buf = in.readLine();
        int readed = DecryptToInt(t_buf);
        readed = readed / (MagicNumber + i * 3);
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
QuizEntry &QuizDatabase::operator [] (int index)
{
    return m_database[index];
}
QuizDatabase &QuizDatabase::operator = (const QuizDatabase &obj)
{
    m_database.clear();
    for(int i = 0;i<static_cast<int>(obj.m_database.size());i++)
    {
        m_database.push_back(obj.m_database[i]);
    }
    return *this;
}

int QuizDatabase::DecryptToInt(QString &src)
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
QString QuizDatabase::DecryptToStr(QString &src)
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
QString QuizDatabase::Encrypt(int in)
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
QString QuizDatabase::Encrypt(QString src)
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
void MainWindow::ClearPrivateData()
{
    m_Question.clear();
    m_Answ1.clear();
    m_Answ2.clear();
    m_Answ3.clear();
    m_Answ4.clear();
    m_RightAnsw = 0;
}

void MainWindow::on_Question_textEdited(const QString &arg1)
{
    m_Question = arg1;
}
bool MainWindow::CheckForNonEmpty()
{
    if(((m_Answ1.isEmpty()&&m_Answ2.isEmpty()&&m_Answ3.isEmpty()&&m_Answ4.isEmpty()&&m_Question.isEmpty())==false)&&(m_RightAnsw!=0))
    {
            return true;
    }
    else
    {
            return false;
    }
}

void MainWindow::on_Answer_1_textEdited(const QString &arg1)
{
    m_Answ1 = arg1;
}

void MainWindow::on_Answer_2_textEdited(const QString &arg1)
{
    m_Answ2 = arg1;
}

void MainWindow::on_Answer_3_textEdited(const QString &arg1)
{
    m_Answ3 = arg1;
}

void MainWindow::on_Answer_4_textEdited(const QString &arg1)
{
    m_Answ4 = arg1;
}

void MainWindow::on_Right_Answer_textEdited(const QString &arg1)
{
    m_RightAnsw = arg1.toInt();
}

void MainWindow::on_AddToDatabase_pressed()
{
    if(CheckForNonEmpty()==true)
    {
        QuizEntry pNew;
        pNew.setAnswer1(m_Answ1);
        pNew.setAnswer2(m_Answ2);
        pNew.setAnswer3(m_Answ3);
        pNew.setAnswer4(m_Answ4);
        pNew.setQuestion(m_Question);
        pNew.setRightAnswer(m_RightAnsw);
        m_data.add(pNew);
        ClearPrivateData();
        ui->Answer_1->clear();
        ui->Answer_2->clear();
        ui->Answer_3->clear();
        ui->Answer_4->clear();
        ui->Question->clear();
        ui->Right_Answer->clear();
        QString EntryCount;
        EntryCount.setNum(static_cast<double>(m_data.getSize()));
        ui->EntryCount->setText(EntryCount);
        if(pDatabaseView!=nullptr)
        {
            pDatabaseView->UpdateDatabase(m_data);
        }
    }
    else
    {
    }
}

void MainWindow::on_action_2_triggered()
{
    exit(0);
}

void MainWindow::on_action_triggered()
{
    m_data.WriteDB();
}

void MainWindow::on_action_3_triggered()
{
    pDatabaseView = new Dialog;
    pDatabaseView->UpdateDatabase(m_data);
    pDatabaseView->show();
}
