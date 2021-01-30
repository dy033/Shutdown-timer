#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QMessageBox>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowMinimizeButtonHint|Qt::WindowCloseButtonHint);
    ui->time->setDateTime(QDateTime::currentDateTime());
    ui->time->setMinimumDate(QDate::currentDate());
    ui->time->setMinimumTime(QTime::currentTime());
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString plan_time;

void MainWindow::on_cancel_clicked()
{
    QProcess p(0);
    p.start("cmd", QStringList()<<"/c"<<"shutdown -a");
    p.waitForStarted();
    p.waitForFinished();
    QString tip="您已取消自动关机！";
    QMessageBox::information(this,tr("提示"),tip,QMessageBox::Ok);
}


void MainWindow::on_ok_clicked()
{
    int result;
    int flag;
    int inth,intm,ints;
    QDateTime stop_time;
    if(ui->bytimes->isChecked())
    {

        inth= ui->hour->text().toInt();
        intm=ui->minute->text().toInt();
        ints=ui->second->text().toInt();
        result=inth*3600+intm*60+ints;
        flag=result;
        plan_time=QString::number(result);

    }
    else if(ui->bytime->isChecked())
    {
        QDateTime current_date_time = QDateTime::currentDateTime();
        stop_time=ui->time->dateTime();
        int result=current_date_time.secsTo(stop_time);
        flag=result;
        plan_time=QString::number(result);


    }

    if(flag<=3)
    {
       int choose;
       choose= QMessageBox::question(this, tr("关机"),
                                          QString(tr("确认3秒内关机？")),
                                          QMessageBox::Yes | QMessageBox::No);
       if(choose==QMessageBox::No)
             return;
    }

    QProcess p(0);
    p.start("cmd", QStringList()<<"/c"<<"shutdown -s -t "<<plan_time);
    if(ui->bytimes->isChecked())
    {
        QString tip="";
        tip=tip+"您的电脑将于\n"+QString::number(inth)+"小时"+QString::number(intm)+"分钟"+QString::number(ints)+"秒后\n自动关机";
        QMessageBox::information(this,tr("提示"),tip,QMessageBox::Ok);
    }
    else if(ui->bytime->isChecked())
    {
        QString tip="";
        tip=tip+"您的电脑将于\n"+stop_time.toString("yyyy-MM-dd hh:mm:ss")+"\n自动关机";
        QMessageBox::information(this,tr("提示"),tip,QMessageBox::Ok);
    }

}

