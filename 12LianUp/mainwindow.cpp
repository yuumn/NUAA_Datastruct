#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>
//#include <QTest>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("连连看");
    setWindowIcon(QIcon(":/images/QQ图片20201203210501.jpg"));

    //背景音乐
    QMediaPlayer *player = new QMediaPlayer();
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player->setMedia(QUrl::fromLocalFile("D:\\Desktop\\DataStructure\\12LianUp\\qqYouXiBGM.wav"));
    //player->setMedia(QUrl::fromLocalFile(":/sounds/qqYouXiBGM.wav"));
    player->setVolume(60);
    player->play();

    getInit();
    setFixedSize(1100,600);
    //resize(1100,600);
    lastClickedH=0;
    lastClickedW=0;
    thish=0;
    thisw=0;

}

void MainWindow::getInit(){
    //随机数种子
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    //点击音效
    clickSound.setSource(QUrl::fromLocalFile(":/sounds/elec.wav"));

    btn = new QPushButton **[12];
    bp = new int *[12];
    bool bo[12][22];
    for(int i=0;i<=11;i++){
        btn[i] = new QPushButton *[22];
        bp[i]=new int [22];
        for(int j=0;j<=21;j++){
            bo[i][j]=0;
            btn[i][j] = new QPushButton;
        }
    }
    for(int i=0;i<=21;i++){
        bp[0][i]=0;
        bp[11][i]=0;
    }
    for(int i=0;i<=11;i++){
        bp[i][0]=0;
        bp[i][21]=0;
    }
    for(int i=1;i<=10;i++){
        for(int j=1;j<=20;j++){
            btn[i][j]->resize(50,50);
            btn[i][j]->move(j*50,i*50);
            btn[i][j]->setParent(this);
            btn[i][j]->show();
            btn[i][j]->setIconSize(QSize(45,45));
            btn[i][j]->setStyleSheet("\
                                     border-color: #0;\
                                     border-width: 2px;\
                                     border-style: solid;");
            connect(btn[i][j],&QPushButton::clicked,this,[=](){
                if(lastClickedH==0&&lastClickedW==0){
                    lastClickedH=i;
                    lastClickedW=j;
                    btn[lastClickedH][lastClickedW]->setStyleSheet("\
                                                                   border-color: #606060;\
                                                                   border-width: 2px;\
                                                                   border-style: solid;");
                }
                else{
                    thish=i;
                    thisw=j;
                    if(thish==lastClickedH&&thisw==lastClickedW){
                        btn[lastClickedH][lastClickedW]->setStyleSheet("\
                                    border-color: #0;\
                                    border-width: 2px;\
                                    border-style: solid;");
                        lastClickedH=0;
                        lastClickedW=0;
                        thish=0;
                        thisw=0;

                    }
                    else if(bp[thish][thisw]!=bp[lastClickedH][lastClickedW]){
                        btn[lastClickedH][lastClickedW]->setStyleSheet("\
                                    border-color: #0;\
                                    border-width: 2px;\
                                    border-style: solid;");
                        lastClickedH=0;
                        lastClickedW=0;
                        thish=0;
                        thisw=0;
                    }
                    else if(canNoCorner(lastClickedH,lastClickedW,thish,thisw)){
                        clickSound.play();
                        bp[lastClickedH][lastClickedW]=0;
                        bp[thish][thisw]=0;

                        delete btn[lastClickedH][lastClickedW];
                        delete btn[thish][thisw];
                        drawLine(lastClickedH,lastClickedW,thish,thisw);

                        QTime dieTime = QTime::currentTime().addMSecs(1000);
                        while( QTime::currentTime() < dieTime )
                          QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

                        deleteLine(lastClickedH,lastClickedW,thish,thisw);

                        lastClickedH=0;
                        lastClickedW=0;
                        thish=0;
                        thisw=0;
                    }
                    else if(canOneCorner(lastClickedH,lastClickedW,thish,thisw)){
                        clickSound.play();
                        bp[lastClickedH][lastClickedW]=0;
                        bp[thish][thisw]=0;

                        delete btn[lastClickedH][lastClickedW];
                        delete btn[thish][thisw];

                        lastClickedH=0;
                        lastClickedW=0;
                        thish=0;
                        thisw=0;
                    }
                    else if(canTwoCorner(lastClickedH,lastClickedW,thish,thisw)){
                        clickSound.play();
                        bp[lastClickedH][lastClickedW]=0;
                        bp[thish][thisw]=0;

                        delete btn[lastClickedH][lastClickedW];
                        delete btn[thish][thisw];

                        lastClickedH=0;
                        lastClickedW=0;
                        thish=0;
                        thisw=0;
                    }
                    else{
                        btn[lastClickedH][lastClickedW]->setStyleSheet("\
                                    border-color: #0;\
                                    border-width: 2px;\
                                    border-style: solid;");
                        lastClickedH=0;
                        lastClickedW=0;
                        thish=0;
                        thisw=0;
                    }

                }
            });

            if(bo[i][j]){
                continue;
            }
            QString s1;
            int z=qrand()%10+1;
            s1=":/images/x";
            if(z==10){
                s1+="10";
            }
            else{
                s1+=('0'+z);
            }
            s1+=".jpg";
            btn[i][j]->setIcon(QIcon(s1));
            bp[i][j]=z;
            bo[i][j]=1;
            int x=i,y=j;
            while(bo[x][y]){
                x=qrand()%10+1;
                y=qrand()%20+1;
            }
            btn[x][y]->setIcon(QIcon(s1));
            bo[x][y]=1;
            bp[x][y]=z;
        }
    }

}
bool MainWindow::canNoCorner(int lstH, int lstW, int thisH, int thisW){
    if(lstH==thisH){
        int y1=lstW<thisW?lstW:thisW;
        int y2=lstW>thisW?lstW:thisW;
        if(y1+1==y2){
            return 1;
        }
        for(int i=y1+1;i<y2;i++){
            if(bp[lstH][i]){
                return 0;
            }
        }
        return 1;
    }
    else if(lstW==thisW){
        int x1=lstH<thisH?lstH:thisH;
        int x2=lstH>thisH?lstH:thisH;
        if(x1+1==x2){
            return 1;
        }
        for(int i=x1+1;i<x2;i++){
            if(bp[i][lstW]){
                return 0;
            }
        }
        return 1;
    }
    else{
        return 0;
    }

}
bool MainWindow::canOneCorner(int lstH, int lstW, int thisH, int thisW){
    if(lstH==thisH||lstW==thisW){
        return 0;
    }
    int x1=lstH<thisH?lstH:thisH;
    int x2=lstH>thisH?lstH:thisH;
    int y1=lstW<thisW?lstW:thisW;
    int y2=lstW>thisW?lstW:thisW;

    if((x1==lstH&&y1==lstW)||(x1==thisH&&y1==thisW)){

        if(!bp[x2][y1]&&canNoCorner(x1,y1,x2,y1)&&canNoCorner(x2,y1,x2,y2)){
            drawLine(x1,y1,x2,y1);
            drawLine(x2,y1,x2,y2);
            drawCorner(x2,y1,2);

            QTime dieTime = QTime::currentTime().addMSecs(1000);
            while( QTime::currentTime() < dieTime )
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

            deleteLine(x1,y1,x2,y1);
            deleteLine(x2,y1,x2,y2);
            deleteCorner(x2,y1);

            return 1;
        }
        else if(!bp[x1][y2]&&canNoCorner(x1,y1,x1,y2)&&canNoCorner(x1,y2,x2,y2)){
            drawLine(x1,y1,x1,y2);
            drawLine(x1,y2,x2,y2);
            drawCorner(x1,y2,4);

            QTime dieTime = QTime::currentTime().addMSecs(1000);
            while( QTime::currentTime() < dieTime )
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

            deleteLine(x1,y1,x1,y2);
            deleteLine(x1,y2,x2,y2);
            deleteCorner(x1,y2);
            return 1;
        }

    }
    else{
        if(!bp[x1][y1]&&canNoCorner(x1,y1,x2,y1)&&canNoCorner(x1,y1,x1,y2)){
            drawLine(x1,y1,x2,y1);
            drawLine(x1,y1,x1,y2);
            drawCorner(x1,y1,1);

            QTime dieTime = QTime::currentTime().addMSecs(1000);
            while( QTime::currentTime() < dieTime )
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

            deleteLine(x1,y1,x2,y1);
            deleteLine(x1,y1,x1,y2);
            deleteCorner(x1,y1);

            return 1;
        }
        else if(!bp[x2][y2]&&canNoCorner(x2,y1,x2,y2)&&canNoCorner(x2,y2,x1,y2)){
            drawLine(x2,y1,x2,y2);
            drawLine(x2,y2,x1,y2);
            drawCorner(x2,y2,3);

            QTime dieTime = QTime::currentTime().addMSecs(1000);
            while( QTime::currentTime() < dieTime )
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

            deleteLine(x2,y1,x2,y2);
            deleteLine(x2,y2,x1,y2);
            deleteCorner(x2,y2);
            return 1;
        }
    }

    return 0;

}
bool MainWindow::canTwoCorner(int lstH, int lstW, int thisH, int thisW){
    int x1=lstH<thisH?lstH:thisH;
    int x2=lstH>thisH?lstH:thisH;
    int y1=lstW<thisW?lstW:thisW;
    int y2=lstW>thisW?lstW:thisW;

    for(int i=0;i<=21;i++){
        if(i==lstW||i==thisW){
            continue;
        }
        if((x1==lstH&&y1==lstW)||(x1==thisH&&y1==thisW)){
            if(!bp[x2][i]&&!bp[x1][i]&&canNoCorner(x1,i,x1,y1)&&canNoCorner(x1,i,x2,i)&&canNoCorner(x2,i,x2,y2)){
                drawLine(x1,i,x1,y1);
                drawLine(x1,i,x2,i);
                drawLine(x2,i,x2,y2);
                if(i<y1){
                    drawCorner(x1,i,1);
                    drawCorner(x2,i,2);
                }
                else if(y1<i&&i<y2){
                    drawCorner(x1,i,4);
                    drawCorner(x2,i,2);
                }
                else{
                    drawCorner(x1,i,4);
                    drawCorner(x2,i,3);
                }

                QTime dieTime = QTime::currentTime().addMSecs(1000);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

                deleteLine(x1,i,x1,y1);
                deleteLine(x1,i,x2,i);
                deleteLine(x2,i,x2,y2);
                if(i<y1){
                    deleteCorner(x1,i);
                    deleteCorner(x2,i);
                }
                else if(y1<i&&i<y2){
                    deleteCorner(x1,i);
                    deleteCorner(x2,i);
                }
                else{
                    deleteCorner(x1,i);
                    deleteCorner(x2,i);
                }

                return 1;
            }
        }
        else{
            if(!bp[x2][i]&&!bp[x1][i]&&canNoCorner(x2,i,x2,y1)&&canNoCorner(x2,i,x1,i)&&canNoCorner(x1,i,x1,y2)){
                drawLine(x2,i,x2,y1);
                drawLine(x2,i,x1,i);
                drawLine(x1,i,x1,y2);
                if(i<y1){
                    drawCorner(x1,i,1);
                    drawCorner(x2,i,2);
                }
                else if(y1<i&&i<y2){
                    drawCorner(x1,i,1);
                    drawCorner(x2,i,3);
                }
                else{
                    drawCorner(x1,i,4);
                    drawCorner(x2,i,3);
                }

                QTime dieTime = QTime::currentTime().addMSecs(1000);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

                deleteLine(x2,i,x2,y1);
                deleteLine(x2,i,x1,i);
                deleteLine(x1,i,x1,y2);
                if(i<y1){
                    deleteCorner(x1,i);
                    deleteCorner(x2,i);
                }
                else if(y1<i&&i<y2){
                    deleteCorner(x1,i);
                    deleteCorner(x2,i);
                }
                else{
                    deleteCorner(x1,i);
                    deleteCorner(x2,i);
                }

                return 1;
            }
        }
    }


    for(int i=0;i<=11;i++){
        if(i==lstH||i==thisH){
            continue;
        }
        if((x1==lstH&&y1==lstW)||(x1==thisH&&y1==thisW)){
            if(!bp[i][y1]&&!bp[i][y2]&&canNoCorner(i,y1,x1,y1)&&canNoCorner(i,y1,i,y2)&&canNoCorner(i,y2,x2,y2)){
                drawLine(i,y1,x1,y1);
                drawLine(i,y1,i,y2);
                drawLine(i,y2,x2,y2);
                if(i<x1){
                    drawCorner(i,y1,1);
                    drawCorner(i,y2,4);
                }
                else if(x1<i&&i<x2){
                    drawCorner(i,y1,2);
                    drawCorner(i,y2,4);
                }
                else{
                    drawCorner(i,y1,2);
                    drawCorner(i,y2,3);
                }

                QTime dieTime = QTime::currentTime().addMSecs(1000);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

                deleteLine(i,y1,x1,y1);
                deleteLine(i,y1,i,y2);
                deleteLine(i,y2,x2,y2);
                if(i<x1){
                    deleteCorner(i,y1);
                    deleteCorner(i,y2);
                }
                else if(x1<i&&i<x2){
                    deleteCorner(i,y1);
                    deleteCorner(i,y2);
                }
                else{
                    deleteCorner(i,y1);
                    deleteCorner(i,y2);
                }

                return 1;
            }
        }
        else{
            if(!bp[i][y1]&&!bp[i][y2]&&canNoCorner(i,y1,x2,y1)&&canNoCorner(i,y1,i,y2)&&canNoCorner(i,y2,x1,y2)){
                drawLine(i,y1,x2,y1);
                drawLine(i,y1,i,y2);
                drawLine(i,y2,x1,y2);
                if(i<x1){
                    drawCorner(i,y1,1);
                    drawCorner(i,y2,4);
                }
                else if(x1<i&&i<x2){
                    drawCorner(i,y1,1);
                    drawCorner(i,y2,3);
                }
                else{
                    drawCorner(i,y1,2);
                    drawCorner(i,y2,3);
                }

                QTime dieTime = QTime::currentTime().addMSecs(1000);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

                deleteLine(i,y1,x2,y1);
                deleteLine(i,y1,i,y2);
                deleteLine(i,y2,x1,y2);
                if(i<x1){
                    deleteCorner(i,y1);
                    deleteCorner(i,y2);
                }
                else if(x1<i&&i<x2){
                    deleteCorner(i,y1);
                    deleteCorner(i,y2);
                }
                else{
                    deleteCorner(i,y1);
                    deleteCorner(i,y2);
                }

                return 1;
            }
        }
    }
    return 0;

}
void MainWindow::drawLine(int lstH, int lstW, int thisH, int thisW){
    int x1=lstH<thisH?lstH:thisH;
    int x2=lstH>thisH?lstH:thisH;
    int y1=lstW<thisW?lstW:thisW;
    int y2=lstW>thisW?lstW:thisW;

    if(lstH==thisH){
        if(y1+1==y2){
            return;
        }
        for(int i=y1+1;i<y2;i++){
            btn[lstH][i] = new QPushButton;
            btn[lstH][i]->resize(50,50);
            btn[lstH][i]->move(i*50,lstH*50);
            btn[lstH][i]->setStyleSheet("\
                        border-color: #0;\
                        border-width: 2px;\
                        border-style: solid;");
            btn[lstH][i]->setParent(this);
            btn[lstH][i]->show();
            btn[lstH][i]->setIcon(QIcon(":/images/1640617407(1).png"));
            btn[lstH][i]->setIconSize(QSize(50,50));
        }

        return;
    }
    if(lstW==thisW){
        if(x1+1==x2){
            return;
        }
        for(int i=x1+1;i<x2;i++){
            btn[i][lstW] = new QPushButton;
            btn[i][lstW]->resize(50,50);
            btn[i][lstW]->move(lstW*50,i*50);
            btn[i][lstW]->setStyleSheet("\
                        border-color: #0;\
                        border-width: 2px;\
                        border-style: solid;");
            btn[i][lstW]->setParent(this);
            btn[i][lstW]->show();
            btn[i][lstW]->setIcon(QIcon(":/images/line1.jpg"));
            btn[i][lstW]->setIconSize(QSize(50,50));

        }

        return;
    }



}
void MainWindow::drawCorner(int thisH, int thisW,int flag){

    if(flag==1){
        btn[thisH][thisW] = new QPushButton;
        btn[thisH][thisW]->resize(50,50);
        btn[thisH][thisW]->move(thisW*50,thisH*50);
        btn[thisH][thisW]->setStyleSheet("\
                    border-color: #0;\
                    border-width: 2px;\
                    border-style: solid;");
        btn[thisH][thisW]->setParent(this);
        btn[thisH][thisW]->show();
        btn[thisH][thisW]->setIcon(QIcon(":/images/1640683118(1).png"));
        btn[thisH][thisW]->setIconSize(QSize(50,50));
    }
    else if(flag==2){
        btn[thisH][thisW] = new QPushButton;
        btn[thisH][thisW]->resize(50,50);
        btn[thisH][thisW]->move(thisW*50,thisH*50);
        btn[thisH][thisW]->setStyleSheet("\
                    border-color: #0;\
                    border-width: 2px;\
                    border-style: solid;");
        btn[thisH][thisW]->setParent(this);
        btn[thisH][thisW]->show();
        btn[thisH][thisW]->setIcon(QIcon(":/images/1640683159(1).png"));
        btn[thisH][thisW]->setIconSize(QSize(50,50));
    }
    else if(flag==3){
        btn[thisH][thisW] = new QPushButton;
        btn[thisH][thisW]->resize(50,50);
        btn[thisH][thisW]->move(thisW*50,thisH*50);
        btn[thisH][thisW]->setStyleSheet("\
                    border-color: #0;\
                    border-width: 2px;\
                    border-style: solid;");
        btn[thisH][thisW]->setParent(this);
        btn[thisH][thisW]->show();
        btn[thisH][thisW]->setIcon(QIcon(":/images/1640683175(1).png"));
        btn[thisH][thisW]->setIconSize(QSize(50,50));
    }
    else if(flag==4){
        btn[thisH][thisW] = new QPushButton;
        btn[thisH][thisW]->resize(50,50);
        btn[thisH][thisW]->move(thisW*50,thisH*50);
        btn[thisH][thisW]->setStyleSheet("\
                    border-color: #0;\
                    border-width: 2px;\
                    border-style: solid;");
        btn[thisH][thisW]->setParent(this);
        btn[thisH][thisW]->show();
        btn[thisH][thisW]->setIcon(QIcon(":/images/1640683197(1).png"));
        btn[thisH][thisW]->setIconSize(QSize(50,50));
    }

}
void MainWindow::deleteLine(int lstH, int lstW, int thisH, int thisW){
    int x1=lstH<thisH?lstH:thisH;
    int x2=lstH>thisH?lstH:thisH;
    int y1=lstW<thisW?lstW:thisW;
    int y2=lstW>thisW?lstW:thisW;

    if(lstH==thisH){
        if(y1+1==y2){
            return;
        }
        for(int i=y1+1;i<y2;i++){
            delete btn[lstH][i];
        }
        return;
    }
    if(lstW==thisW){
        if(x1+1==x2){
            return;
        }
        for(int i=x1+1;i<x2;i++){
            delete btn[i][lstW];
        }
        return;
    }
}

void MainWindow::deleteCorner(int thisH, int thisW){
    delete btn[thisH][thisW];
}

void MainWindow::closeEvent ( QCloseEvent * e )
{
    effect.setSource(QUrl::fromLocalFile(":/sounds/end.wav"));
    effect.play();
    //Sleep(10000);
    QTime t;
    t.start();
    while(t.elapsed()<1000)
        QCoreApplication::processEvents();
    e->accept();
}

MainWindow::~MainWindow()
{
    delete ui;
}
