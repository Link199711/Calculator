#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "poly.cpp"
#include <QString>
#include <memory>
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

void MainWindow::on_pushButton_0_clicked()
{
    addchar('0');
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
    addchar('+');
}

void MainWindow::on_pushButton_11_clicked()
{
   addchar('x');
   addchar('^');
}

void MainWindow::on_pushButton_12_clicked()
{
    addchar('-');
}

void MainWindow::on_pushButton_13_clicked()
{
    addchar('.');
}

void MainWindow::on_pushButton_14_clicked()
{
    close();
}

void MainWindow::on_pushButton_15_clicked()
{
    QString str = ui->lineEdit->text(),str1,str2,ans;
    Poly tem;
    int i = 0;

    while(str[i] != ')') i ++;
    str1 = str.mid(1,i - 1);
    Poly p1(str1);

    if (str[i + 1] == '.')
    {
        str2 = str.mid(i + 2);
        ans = p1.compute(str2);
    }
    else
    {
        str2 = str.mid(i + 3,str.length() - 4 - i);
        Poly p2(str2);
        if (str[i + 1] == '+')
            tem = p1 + p2;
        if (str[i + 1] == '-')
            tem = p1 - p2;
        if (str[i + 1] == '*')
            tem = p1 * p2;
        ans = tem.transform();
    }

    ui->lineEdit_3->setText(ans);
}

void MainWindow::on_pushButton_16_clicked()
{
    QString str = ui->lineEdit->text();
    str = str.left(str.length() - 1);
    ui->lineEdit->setText(str);
}

void MainWindow::on_pushButton_17_clicked()
{
    addchar('(');
}

void MainWindow::on_pushButton_18_clicked()
{
    addchar(')');
}

void MainWindow::on_pushButton_19_clicked()
{
    addchar('*');
}

void MainWindow::on_pushButton_20_clicked()
{
    QString str = ui->lineEdit->text();
    Poly tem(str);
    str = tem.diff().transform();
    ui->lineEdit_3->setText(str);
}

void MainWindow::on_pushButton_21_clicked()
{
    QString str = ui->lineEdit->text();
    Poly tem(str);
    str = tem.print();
    ui->lineEdit_3->setText(str);
}

void MainWindow::on_pushButton_22_clicked()
{
    ui->lineEdit->setText("");
    ui->lineEdit_3->setText("");
}
