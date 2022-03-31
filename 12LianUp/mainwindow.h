#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QGridLayout>
#include <QPushButton>
//#include <QInputDialog>
#include <QDebug>
#include <QTime>
#include <QMenu>
#include <QMenuBar>
//#include <QMessageBox>
//#include <QtTest/QtTest>
#include <QSoundEffect>
#include <QtGlobal>
#include <QString>
#include <QLabel>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QCloseEvent>
//#inclue <QThread>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void getInit();


private:
    Ui::MainWindow *ui;
    QPushButton ***btn;//pushbutton数组
    int hb, wb;//高多少个格子，宽多少个格子
    int **bp;
    int **types;//格子的类型的数组。0代表被清理了，1-15格子代表一种格子（图片）
    int lastClickedH, lastClickedW;//上一个点击的坐标
    int thish,thisw;//这一次点击的坐标
    int remains;//剩余多少个格子
    QSoundEffect clickSound;//点击音效
    QSoundEffect effect;
//    QMediaPlayer player;
    bool canNoCorner(int lstH, int lstW, int thisH, int thisW);
    bool canOneCorner(int lstH, int lstW, int thisH, int thisW);
    bool canTwoCorner(int lstH, int lstW, int thisH, int thisW);
    void drawLine(int lstH, int lstW, int thisH, int thisW);
    void drawCorner(int thisH, int thisW,int flag);
    void deleteLine(int lstH, int lstW, int thisH, int thisW);
    void deleteCorner(int thisH, int thisW);
    void closeEvent(QCloseEvent *event);
//    void restart();
};

#endif // MAINWINDOW_H
