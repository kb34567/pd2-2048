#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVector>
#include <QKeyEvent>
#include <QDebug>
#include <iostream>
#include <QGraphicsView>
#include <QGraphicsScene>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
  int getnew();
  bool full();
  void first();
  void keyPressEvent(QKeyEvent * event);
  void picture();
  void showarray(int board[4][4]);
  friend void keyPressEvent(QKeyEvent * event);
  friend void picture();
  friend void showarray(int board[4][4]);
  bool moveornot();
  bool win();

private slots:
  void on_pushButton_clicked();

  void on_pushButton_3_clicked();

  void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    int board[4][4]={};
    int check[4][4]={};
    int move[4][4]={};
    double score,scoreun;
};

#endif // MAINWINDOW_H
