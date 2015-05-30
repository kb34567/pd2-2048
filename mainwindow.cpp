#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QString>
#include <QKeyEvent>
#include <QApplication>
#include <iostream>
#include <time.h>
#include <QMessageBox>
using namespace std;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//set the first two position
void MainWindow::first()
{
    score=0;
    int i,j,k,m;

    srand((unsigned)time(NULL));
    i = rand() % 4;
    j = rand() % 4;
    k = rand() % 4;
    m = rand() % 4;
if( board[i][j]==0 && board[k][m]==0 && (i != k || j != m ))
{
    board[i][j]=2;
    board[k][m]=2;
}
  MainWindow::picture();
}

void MainWindow::showarray(int board[4][4]){
    int i,j;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            std::cout<<board[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}
//add new square at free position
int MainWindow::getnew(){
   int j,i;
   do {
        i = rand() % 4;
        j = rand() % 4;
    }while( board[i][j]!=0); //若選到的position是空的就停止 決定是它了

   int x;
   x=rand()%10;
   if(x==0)
        board[i][j]=4; //4的機率是比2小
   else board[i][j]=2;

   return board[i][j];
}


//lose the game square full
bool MainWindow::full()
{
    bool full = true;
      for (int i = 0; i < 4; ++i)
          for (int j = 0; j < 4; ++j)
              if (board[i][j] == 0)
              {
                  full = false; //not full
                  break;
              }
    return full;
}

bool MainWindow::win()
{
    bool win = false;
      for (int i = 0; i < 4; ++i)
          for (int j = 0; j < 4; ++j)
              if (board[i][j] == 2048)
              {
                  win = true; //win
                  break;
              }
    return win;
}


bool MainWindow::moveornot()
{
    bool dontmove = true;
      for (int i = 0; i < 4; i++)
          for (int j = 0; j < 4; j++)
              if (board[i][j] != move[i][j])
              {
                  dontmove = false; //can move
                  break;
              }
    return dontmove;
}

//press key to move
void MainWindow::keyPressEvent(QKeyEvent *e)
{
   int check [4][4]={};
   switch(e->key()){

   case Qt::Key_Up:

       for(int i=0;i<4;i++) //set check array
           for(int j=0;j<4;j++)
             {
                check[i][j]=0;
             }


       for(int i=0;i<4;i++) //set 上一個移動的 array
           for(int j=0;j<4;j++)
             {
                move[i][j]=board[i][j];
             }

//get together
       for(int j=0;j<4;j++)
       {
             for(int i=0;i<4;i++)
             {
                 if( check[i][j]!=1 && (i+1)>=0 && (board[i+1][j]==board[i][j]) && board[i][j]!=0)
                 {
                     board[i][j]=2*board[i+1][j];
                     board[i+1][j]=0;
                     check[i][j]=1;
                     scoreun=score;
                     score=score+10;
                 }

                 if( check[i][j]!=1 && (i+2)>=0 && board[i+1][j]==0 && board[i+2][j]==board[i][j] && board[i][j]!=0)
                 {
                     board[i][j]=2*board[i+2][j];
                     board[i+2][j]=0;
                     check[i][j]=1;
                     scoreun=score;
                     score=score+10;
                 }

                 if( check[i][j]!=1 && (i+3)>=0 && board[i+2][j]==0 && board[i+1][j]==0 && board[i+3][j]==board[i][j] && board[i][j]!=0)
                 {
                     board[i][j]=2*board[i+3][j];
                     board[i+3][j]=0;
                     check[i][j]=1;
                     scoreun=score;
                     score=score+10;
                 }
            }
            ui->lcdNumber->display(score);
        }


//move
       for(int j=0;j<4;j++)
         {
             int count6 =0;
             while(count6<4)
             {
                 for(int i=0;i<3;i++)
                 {
                     if(board[i][j]==0)
                     {
                         board[i][j]=board[i+1][j];
                         board[i+1][j]=0;
                     }
                 }
              count6++;
              }
         }

         if(full()) {std::cout<<"full"<<" ";QMessageBox::information(this,"LOSE","you lose ! try again?" );}
         if(win())
            {
             std::cout<<"win"<<" ";
             picture();
             QMessageBox::information(this,"WIN","you win ! play again?" );
            }
         else
        {
             if(moveornot()){ std::cout<<"don't"<<endl;} //if move==board -> can't move
             else{
                    getnew();
                    picture();
                    showarray(board);
                  }
         }
                    break;


   case Qt::Key_Down:
       for(int i=0;i<4;i++)
           for(int j=0;j<4;j++)
             {
                check[i][j]=0;
             }

       for(int i=0;i<4;i++) //set 上一個移動的 array
           for(int j=0;j<4;j++)
             {
                move[i][j]=board[i][j];
             }


       for(int j=0;j<4;j++)
       {
             for(int i=3;i>=0;i--)
             {
                 if( check[i][j]!=1 && (i-1)>=0 && board[i-1][j]==board[i][j] && board[i][j]!=0)
                 {
                     board[i][j]=2*board[i-1][j];
                     board[i-1][j]=0;
                     check[i][j]=1;
                     scoreun=score;
                     score=score+10;
                 }

                 if( check[i][j]!=1 && (i-2)>=0 && board[i-1][j]==0 && board[i-2][j]==board[i][j] && board[i][j]!=0)
                 {
                     board[i][j]=2*board[i-2][j];
                     board[i-2][j]=0;
                     check[i][j]=1;
                     scoreun=score;
                     score=score+10;
                 }

                 if( check[i][j]!=1 && (i-3)>=0 && board[i-2][j]==0 && board[i-1][j]==0 && board[i-3][j]==board[i][j] && board[i][j]!=0)
                 {
                     board[i][j]=2*board[i-3][j];
                     board[i-3][j]=0;
                     check[i][j]=1;
                     scoreun=score;
                     score=score+10;
                 }
             }
               ui->lcdNumber->display(score);
        }

       for(int j=0;j<4;j++)
       {
            int count8 =0;
            while(count8<4)
            {
                for(int i=2;i>=0;i--)
                {
                    if(board[i+1][j]==0)
                    {
                        board[i+1][j]=board[i][j];
                        board[i][j]=0;
                    }
                }
            count8 ++;
            }
        }
        if(full()) {std::cout<<"full"<<" ";QMessageBox::information(this,"LOSE","you lose ! try again?" );}
        if(win())
           {
            std::cout<<"win"<<" ";
            picture();
            QMessageBox::information(this,"WIN","you win ! play again?" );
           }
        else
        {
            if(moveornot()){ std::cout<<"don't"<<endl;} //if move==board -> can't move
            else{
            getnew();
            picture();
            showarray(board);
            }
        }
        break;


   case Qt::Key_Left:
       for(int i=0;i<4;i++)
           for(int j=0;j<4;j++)
             {
                check[i][j]=0;
             }

       for(int i=0;i<4;i++) //set 上一個移動的 array
           for(int j=0;j<4;j++)
             {
                move[i][j]=board[i][j];
             }


       for(int i=0;i<4;i++)
       {
             for(int j=0;j<4;j++)
             {
                 if( check[i][j]!=1 && (j+1)<4 && board[i][j]==board[i][j+1] && board[i][j]!=0)
                 {
                     board[i][j]=2*board[i][j+1];
                     board[i][j+1]=0;
                     check[i][j]=1;
                     scoreun=score;
                     score=score+10;
                 }

                 if( check[i][j]!=1 && (j+2)<4 && board[i][j+1]==0 && board[i][j]==board[i][j+2] && board[i][j]!=0)
                 {
                     board[i][j]=2*board[i][j+2];
                     board[i][j+2]=0;
                     check[i][j]=1;
                     scoreun=score;
                     score=score+10;
                 }

                 if( check[i][j]!=1 && (j+3)<4 && board[i][j+1]==0 && board[i][j+2]==0 && board[i][j]==board[i][j+3] && board[i][j]!=0)
                 {
                     board[i][j]=2*board[i][j+3];
                     board[i][j+3]=0;
                     check[i][j]=1;
                     scoreun=score;
                     score=score+10;
                 }
             }
               ui->lcdNumber->display(score);
        }


         for(int i=0;i<4;i++)
         {
             int count4 =0;
             while(count4<4)
             {
                 for(int j=0;j<3;j++)
                 {
                     if(board[i][j]==0)
                     {
                         board[i][j]=board[i][j+1];
                         board[i][j+1]=0;
                     }
                 }
              count4++;
              }
         }
         if(full()) {std::cout<<"full"<<" ";QMessageBox::information(this,"LOSE","you lose ! try again?" );}
         if(win())
            {
             std::cout<<"win"<<" ";
             picture();
             QMessageBox::information(this,"WIN","you win ! play again?" );
            }
         else
        {
             if(moveornot()){ std::cout<<"don't"<<endl;} //if move==board -> can't move
             else{
             getnew();
             picture();
             showarray(board);
             }
         }
             break;

   case Qt::Key_Right:

       for(int i=0;i<4;i++)
           for(int j=0;j<4;j++)
             {
                check[i][j]=0;
             }

       for(int i=0;i<4;i++) //set 上一個移動的 array
           for(int j=0;j<4;j++)
             {
                move[i][j]=board[i][j];
             }


       for(int i=0;i<4;i++)
       {
             for(int j=3;j>=0;j--)
             {
                 if( check[i][j]!=1 && (j-1)>=0 && board[i][j]==board[i][j-1] && board[i][j]!=0)
                 {

                     board[i][j]=2*board[i][j-1];
                     board[i][j-1]=0;
                     check[i][j]=1;
                     scoreun=score;
                     score=score+10;
                 }

                 if( check[i][j]!=1 && (j-2)>=0 && board[i][j-1]==0 && board[i][j]==board[i][j-2] && board[i][j]!=0)
                 {
                     board[i][j]=2*board[i][j-2];
                     board[i][j-2]=0;
                     check[i][j]=1;
                     scoreun=score;
                     score=score+10;
                 }

                 if( check[i][j]!=1 && (j-3)>=0 && board[i][j-1]==0 && board[i][j-2]==0 && board[i][j]==board[i][j-3] && board[i][j]!=0)
                 {
                     board[i][j]=2*board[i][j-3];
                     board[i][j-3]=0;
                     check[i][j]=1;
                     scoreun=score;
                     score=score+10;
                 }
             }
               ui->lcdNumber->display(score);
        }

         for(int i=0;i<4;i++)
         {
             int count2 =0;
             while(count2<4)
             {
                 for(int j=2;j>=0;j--)
                 {
                     if(board[i][j+1]==0)
                     {
                         board[i][j+1]=board[i][j];
                         board[i][j]=0;
                     }
                 }
              count2++;
              }
         }

         if(full()) {std::cout<<"full"<<" "; picture();QMessageBox::information(this,"LOSE","you lose ! try again?" );}
         if(win())
            {
             std::cout<<"win"<<" ";
             picture();
             QMessageBox::information(this,"WIN","you win ! play again?" );
            }
         else
             {
                if(moveornot()){ std::cout<<"don't"<<endl;} //if move==board -> can't move
                else{
                getnew();
                picture();
                showarray(board);
                }
             }
            break;
}
}


//put picture
void MainWindow::picture()
{
    QPixmap pic0(":/new/prefix1/0.jpg");
    QPixmap pic2(":/new/prefix1/2.jpg");
    QPixmap pic4(":/new/prefix1/4.jpg");
    QPixmap pic8(":/new/prefix1/8.jpg");
    QPixmap pic16(":/new/prefix1/16.jpg");
    QPixmap pic32(":/new/prefix1/32.jpg");
    QPixmap pic64(":/new/prefix1/64.jpg");
    QPixmap pic128(":/new/prefix1/128.jpg");
    QPixmap pic256(":/new/prefix1/256.jpg");
    QPixmap pic512(":/new/prefix1/512.jpg");
    QPixmap pic1024(":/new/prefix1/1024.jpg");
    QPixmap pic2048(":/new/prefix1/2048.jpg");

    if(board[0][0]==0) ui->label_2->setPixmap(pic0);
    if(board[0][0]==2) ui->label_2->setPixmap(pic2);
    if(board[0][0]==4) ui->label_2->setPixmap(pic4);
    if(board[0][0]==8) ui->label_2->setPixmap(pic8);
    if(board[0][0]==16) ui->label_2->setPixmap(pic16);
    if(board[0][0]==32) ui->label_2->setPixmap(pic32);
    if(board[0][0]==64) ui->label_2->setPixmap(pic64);
    if(board[0][0]==128) ui->label_2->setPixmap(pic128);
    if(board[0][0]==256) ui->label_2->setPixmap(pic256);
    if(board[0][0]==512) ui->label_2->setPixmap(pic512);
    if(board[0][0]==1024) ui->label_2->setPixmap(pic1024);
    if(board[0][0]==2048) ui->label_2->setPixmap(pic2048);

    if(board[0][1]==0) ui->label_3->setPixmap(pic0);
    if(board[0][1]==2) ui->label_3->setPixmap(pic2);
    if(board[0][1]==4) ui->label_3->setPixmap(pic4);
    if(board[0][1]==8) ui->label_3->setPixmap(pic8);
    if(board[0][1]==16) ui->label_3->setPixmap(pic16);
    if(board[0][1]==32) ui->label_3->setPixmap(pic32);
    if(board[0][1]==64) ui->label_3->setPixmap(pic64);
    if(board[0][1]==128) ui->label_3->setPixmap(pic128);
    if(board[0][1]==256) ui->label_3->setPixmap(pic256);
    if(board[0][1]==512) ui->label_3->setPixmap(pic512);
    if(board[0][1]==1024) ui->label_3->setPixmap(pic1024);
    if(board[0][1]==2048) ui->label_3->setPixmap(pic2048);

    if(board[0][2]==0) ui->label_4->setPixmap(pic0);
    if(board[0][2]==2) ui->label_4->setPixmap(pic2);
    if(board[0][2]==4) ui->label_4->setPixmap(pic4);
    if(board[0][2]==8) ui->label_4->setPixmap(pic8);
    if(board[0][2]==16) ui->label_4->setPixmap(pic16);
    if(board[0][2]==32) ui->label_4->setPixmap(pic32);
    if(board[0][2]==64) ui->label_4->setPixmap(pic64);
    if(board[0][2]==128) ui->label_4->setPixmap(pic128);
    if(board[0][2]==256) ui->label_4->setPixmap(pic256);
    if(board[0][2]==512) ui->label_4->setPixmap(pic512);
    if(board[0][2]==1024) ui->label_4->setPixmap(pic1024);
    if(board[0][2]==2048) ui->label_4->setPixmap(pic2048);

    if(board[0][3]==0) ui->label_5->setPixmap(pic0);
    if(board[0][3]==2) ui->label_5->setPixmap(pic2);
    if(board[0][3]==4) ui->label_5->setPixmap(pic4);
    if(board[0][3]==8) ui->label_5->setPixmap(pic8);
    if(board[0][3]==16) ui->label_5->setPixmap(pic16);
    if(board[0][3]==32) ui->label_5->setPixmap(pic32);
    if(board[0][3]==64) ui->label_5->setPixmap(pic64);
    if(board[0][3]==128) ui->label_5->setPixmap(pic128);
    if(board[0][3]==256) ui->label_5->setPixmap(pic256);
    if(board[0][3]==512) ui->label_5->setPixmap(pic512);
    if(board[0][3]==1024) ui->label_5->setPixmap(pic1024);
    if(board[0][3]==2048) ui->label_5->setPixmap(pic2048);

    if(board[1][0]==0) ui->label_6->setPixmap(pic0);
    if(board[1][0]==2) ui->label_6->setPixmap(pic2);
    if(board[1][0]==4) ui->label_6->setPixmap(pic4);
    if(board[1][0]==8) ui->label_6->setPixmap(pic8);
    if(board[1][0]==16) ui->label_6->setPixmap(pic16);
    if(board[1][0]==32) ui->label_6->setPixmap(pic32);
    if(board[1][0]==64) ui->label_6->setPixmap(pic64);
    if(board[1][0]==128) ui->label_6->setPixmap(pic128);
    if(board[1][0]==256) ui->label_6->setPixmap(pic256);
    if(board[1][0]==512) ui->label_6->setPixmap(pic512);
    if(board[1][0]==1024) ui->label_6->setPixmap(pic1024);
    if(board[1][0]==2048) ui->label_6->setPixmap(pic2048);

    if(board[1][1]==0) ui->label_7->setPixmap(pic0);
    if(board[1][1]==2) ui->label_7->setPixmap(pic2);
    if(board[1][1]==4) ui->label_7->setPixmap(pic4);
    if(board[1][1]==8) ui->label_7->setPixmap(pic8);
    if(board[1][1]==16) ui->label_7->setPixmap(pic16);
    if(board[1][1]==32) ui->label_7->setPixmap(pic32);
    if(board[1][1]==64) ui->label_7->setPixmap(pic64);
    if(board[1][1]==128) ui->label_7->setPixmap(pic128);
    if(board[1][1]==256) ui->label_7->setPixmap(pic256);
    if(board[1][1]==512) ui->label_7->setPixmap(pic512);
    if(board[1][1]==1024) ui->label_7->setPixmap(pic1024);
    if(board[1][1]==2048) ui->label_7->setPixmap(pic2048);

    if(board[1][2]==0) ui->label_8->setPixmap(pic0);
    if(board[1][2]==2) ui->label_8->setPixmap(pic2);
    if(board[1][2]==4) ui->label_8->setPixmap(pic4);
    if(board[1][2]==8) ui->label_8->setPixmap(pic8);
    if(board[1][2]==16) ui->label_8->setPixmap(pic16);
    if(board[1][2]==32) ui->label_8->setPixmap(pic32);
    if(board[1][2]==64) ui->label_8->setPixmap(pic64);
    if(board[1][2]==128) ui->label_8->setPixmap(pic128);
    if(board[1][2]==256) ui->label_8->setPixmap(pic256);
    if(board[1][2]==512) ui->label_8->setPixmap(pic512);
    if(board[1][2]==1024) ui->label_8->setPixmap(pic1024);
    if(board[1][2]==2048) ui->label_8->setPixmap(pic2048);

    if(board[1][3]==0) ui->label_9->setPixmap(pic0);
    if(board[1][3]==2) ui->label_9->setPixmap(pic2);
    if(board[1][3]==4) ui->label_9->setPixmap(pic4);
    if(board[1][3]==8) ui->label_9->setPixmap(pic8);
    if(board[1][3]==16) ui->label_9->setPixmap(pic16);
    if(board[1][3]==32) ui->label_9->setPixmap(pic32);
    if(board[1][3]==64) ui->label_9->setPixmap(pic64);
    if(board[1][3]==128) ui->label_9->setPixmap(pic128);
    if(board[1][3]==256) ui->label_9->setPixmap(pic256);
    if(board[1][3]==512) ui->label_9->setPixmap(pic512);
    if(board[1][3]==1024) ui->label_9->setPixmap(pic1024);
    if(board[1][3]==2048) ui->label_9->setPixmap(pic2048);

    if(board[2][0]==0) ui->label_10->setPixmap(pic0);
    if(board[2][0]==2) ui->label_10->setPixmap(pic2);
    if(board[2][0]==4) ui->label_10->setPixmap(pic4);
    if(board[2][0]==8) ui->label_10->setPixmap(pic8);
    if(board[2][0]==16) ui->label_10->setPixmap(pic16);
    if(board[2][0]==32) ui->label_10->setPixmap(pic32);
    if(board[2][0]==64) ui->label_10->setPixmap(pic64);
    if(board[2][0]==128) ui->label_10->setPixmap(pic128);
    if(board[2][0]==256) ui->label_10->setPixmap(pic256);
    if(board[2][0]==512) ui->label_10->setPixmap(pic512);
    if(board[2][0]==1024) ui->label_10->setPixmap(pic1024);
    if(board[2][0]==2048) ui->label_10->setPixmap(pic2048);

    if(board[2][1]==0) ui->label_11->setPixmap(pic0);
    if(board[2][1]==2) ui->label_11->setPixmap(pic2);
    if(board[2][1]==4) ui->label_11->setPixmap(pic4);
    if(board[2][1]==8) ui->label_11->setPixmap(pic8);
    if(board[2][1]==16) ui->label_11->setPixmap(pic16);
    if(board[2][1]==32) ui->label_11->setPixmap(pic32);
    if(board[2][1]==64) ui->label_11->setPixmap(pic64);
    if(board[2][1]==128) ui->label_11->setPixmap(pic128);
    if(board[2][1]==256) ui->label_11->setPixmap(pic256);
    if(board[2][1]==512) ui->label_11->setPixmap(pic512);
    if(board[2][1]==1024) ui->label_11->setPixmap(pic1024);
    if(board[2][1]==2048) ui->label_11->setPixmap(pic2048);

    if(board[2][2]==0) ui->label_12->setPixmap(pic0);
    if(board[2][2]==2) ui->label_12->setPixmap(pic2);
    if(board[2][2]==4) ui->label_12->setPixmap(pic4);
    if(board[2][2]==8) ui->label_12->setPixmap(pic8);
    if(board[2][2]==16) ui->label_12->setPixmap(pic16);
    if(board[2][2]==32) ui->label_12->setPixmap(pic32);
    if(board[2][2]==64) ui->label_12->setPixmap(pic64);
    if(board[2][2]==128) ui->label_12->setPixmap(pic128);
    if(board[2][2]==256) ui->label_12->setPixmap(pic256);
    if(board[2][2]==512) ui->label_12->setPixmap(pic512);
    if(board[2][2]==1024) ui->label_12->setPixmap(pic1024);
    if(board[2][2]==2048) ui->label_12->setPixmap(pic2048);

    if(board[2][3]==0) ui->label_13->setPixmap(pic0);
    if(board[2][3]==2) ui->label_13->setPixmap(pic2);
    if(board[2][3]==4) ui->label_13->setPixmap(pic4);
    if(board[2][3]==8) ui->label_13->setPixmap(pic8);
    if(board[2][3]==16) ui->label_13->setPixmap(pic16);
    if(board[2][3]==32) ui->label_13->setPixmap(pic32);
    if(board[2][3]==64) ui->label_13->setPixmap(pic64);
    if(board[2][3]==128) ui->label_13->setPixmap(pic128);
    if(board[2][3]==256) ui->label_13->setPixmap(pic256);
    if(board[2][3]==512) ui->label_13->setPixmap(pic512);
    if(board[2][3]==1024) ui->label_13->setPixmap(pic1024);
    if(board[2][3]==2048) ui->label_13->setPixmap(pic2048);

    if(board[3][0]==0) ui->label_14->setPixmap(pic0);
    if(board[3][0]==2) ui->label_14->setPixmap(pic2);
    if(board[3][0]==4) ui->label_14->setPixmap(pic4);
    if(board[3][0]==8) ui->label_14->setPixmap(pic8);
    if(board[3][0]==16) ui->label_14->setPixmap(pic16);
    if(board[3][0]==32) ui->label_14->setPixmap(pic32);
    if(board[3][0]==64) ui->label_14->setPixmap(pic64);
    if(board[3][0]==128) ui->label_14->setPixmap(pic128);
    if(board[3][0]==256) ui->label_14->setPixmap(pic256);
    if(board[3][0]==512) ui->label_14->setPixmap(pic512);
    if(board[3][0]==1024) ui->label_14->setPixmap(pic1024);
    if(board[3][0]==2048) ui->label_14->setPixmap(pic2048);

    if(board[3][1]==0) ui->label_15->setPixmap(pic0);
    if(board[3][1]==2) ui->label_15->setPixmap(pic2);
    if(board[3][1]==4) ui->label_15->setPixmap(pic4);
    if(board[3][1]==8) ui->label_15->setPixmap(pic8);
    if(board[3][1]==16) ui->label_15->setPixmap(pic16);
    if(board[3][1]==32) ui->label_15->setPixmap(pic32);
    if(board[3][1]==64) ui->label_15->setPixmap(pic64);
    if(board[3][1]==128) ui->label_15->setPixmap(pic128);
    if(board[3][1]==256) ui->label_15->setPixmap(pic256);
    if(board[3][1]==512) ui->label_15->setPixmap(pic512);
    if(board[3][1]==1024) ui->label_15->setPixmap(pic1024);
    if(board[3][1]==2048) ui->label_15->setPixmap(pic2048);

    if(board[3][2]==0) ui->label_16->setPixmap(pic0);
    if(board[3][2]==2) ui->label_16->setPixmap(pic2);
    if(board[3][2]==4) ui->label_16->setPixmap(pic4);
    if(board[3][2]==8) ui->label_16->setPixmap(pic8);
    if(board[3][2]==16) ui->label_16->setPixmap(pic16);
    if(board[3][2]==32) ui->label_16->setPixmap(pic32);
    if(board[3][2]==64) ui->label_16->setPixmap(pic64);
    if(board[3][2]==128) ui->label_16->setPixmap(pic128);
    if(board[3][2]==256) ui->label_16->setPixmap(pic256);
    if(board[3][2]==512) ui->label_16->setPixmap(pic512);
    if(board[3][2]==1024) ui->label_16->setPixmap(pic1024);
    if(board[3][2]==2048) ui->label_16->setPixmap(pic2048);

    if(board[3][3]==0) ui->label_17->setPixmap(pic0);
    if(board[3][3]==2) ui->label_17->setPixmap(pic2);
    if(board[3][3]==4) ui->label_17->setPixmap(pic4);
    if(board[3][3]==8) ui->label_17->setPixmap(pic8);
    if(board[3][3]==16) ui->label_17->setPixmap(pic16);
    if(board[3][3]==32) ui->label_17->setPixmap(pic32);
    if(board[3][3]==64) ui->label_17->setPixmap(pic64);
    if(board[3][3]==128) ui->label_17->setPixmap(pic128);
    if(board[3][3]==256) ui->label_17->setPixmap(pic256);
    if(board[3][3]==512) ui->label_17->setPixmap(pic512);
    if(board[3][3]==1024) ui->label_17->setPixmap(pic1024);
    if(board[3][3]==2048) ui->label_17->setPixmap(pic2048);
}


void MainWindow::on_pushButton_clicked()
{
    first();
}


void MainWindow::on_pushButton_3_clicked()
{
    score=0;
    ui->lcdNumber->display(score);
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
        {
            board[i][j]=0;
        }
    first();
}

void MainWindow::on_pushButton_4_clicked()
{
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
        {
            board[i][j]=move[i][j];
            score=scoreun;
            ui->lcdNumber->display(score);
            move[i][j]=board[i][j];
        }
    picture();
}
