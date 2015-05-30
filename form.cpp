#include "form.h"
#include "ui_form.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QString>
#include <QKeyEvent>
//#include <QtCore>
//#include <QtGui>
#include <QApplication>
#include "ui_mainwindow.h"
#include <iostream>
using namespace std;


Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{

}

