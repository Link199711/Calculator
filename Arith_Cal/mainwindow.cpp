#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cal.cpp"
#include <QString>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addchar(QChar ch)
{

    QString str = ui->lineEdit->text();
    str = str + ch;
    ui->lineEdit->setText(str);
}

void MainWindow::on_pushButton_clicked()
{
    QString str = ui->lineEdit->text(),str3;

    // 判断是输入等于号还是进行计算
    if (str.length() == 1) // 输入等于号
    {
        str.append('=');
        ui->lineEdit->setText(str);
        return;
    }

    string str2 = str.toStdString();
    if (str2[0] <= 'z' && str2[0] >= 'a' && str2[1] == '=') // 进行赋值操作
    {
        QChar tem = str2[0];
        char name = str2[0];
        str2 = str2.substr(2);
        store[name - 'a'] = cal(str2);
        str3 = str3 + + name + " = ";
        str3.append(QString::number(store[name - 'a'],10));
    }
    else // 若不是赋值操作，直接计算表达式
    {
        int res = cal(str2);
        str3 = QString::number(res,10);
    }
    ui->lineEdit_2->setText(str3);
}

void MainWindow::on_pushButton_1_clicked()
{
    addchar('1');
}

void MainWindow::on_pushButton_2_clicked()
{
    addchar('2');
}

void MainWindow::on_pushButton_3_clicked()
{
    addchar('3');
}

void MainWindow::on_pushButton_4_clicked()
{
    addchar('4');
}

void MainWindow::on_pushButton_5_clicked()
{
    addchar('5');
}

void MainWindow::on_pushButton_6_clicked()
{
    addchar('6');
}

void MainWindow::on_pushButton_7_clicked()
{
    addchar('7');
}

void MainWindow::on_pushButton_8_clicked()
{
    addchar('8');
}

void MainWindow::on_pushButton_9_clicked()
{
    addchar('9');
}

void MainWindow::on_pushButton_10_clicked()
{
    addchar('*');
}

void MainWindow::on_pushButton_11_clicked()
{
    addchar('0');
}

void MainWindow::on_pushButton_12_clicked()
{
    addchar('+');
}

void MainWindow::on_pushButton_13_clicked()
{
    addchar('/');
}

void MainWindow::on_pushButton_14_clicked()
{
    addchar('-');
}

void MainWindow::on_pushButton_15_clicked()
{
    addchar('(');
}

void MainWindow::on_pushButton_16_clicked()
{
    addchar(')');
}

void MainWindow::on_pushButton_17_clicked()
{
    close();
}

void MainWindow::on_pushButton_18_clicked()
{
    QString str = ui->lineEdit->text();
    str = str.left(str.length() - 1);
    ui->lineEdit->setText(str);
}

void MainWindow::on_pushButton_19_clicked()
{
    addchar('^');
}

void MainWindow::on_pushButton_20_clicked()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
}
