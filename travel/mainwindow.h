#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "stdafx.h"
#include <QMainWindow>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QListView>
#include <QWidget>
#include <QPainter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimeEdit>
#include <QLineEdit>
#include<QTimer>
#include <QStandardItemModel>

class PaintedWidget : public QWidget
{
    Q_OBJECT
public:
    PaintedWidget(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
private:
    QPainter *painter;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(userP *cu, QWidget *parent = 0);
    ~MainWindow();
signals:
    void make();
private slots:
    void search();
    void logout();
    void showTime();
    void setLine();
    void saveInfo();
    void stopLine();
    void showAns(city&, city&, bool flag);
private:
    void listVehicle(city &st, city &ed, QStringList *strList);
    QLabel * label1, * label2, *label3, *CurTime, *limitTime, *limitCity, *chooseLine;
    QComboBox *start, *end, *stra;
    QPushButton * searchButton, * closeButton, *saveButton, *chooseButton, *stopButton;
    QListView *listview;
    QCheckBox *limitCities;
 //   QCheckBox **limitCity;//limitTime ;
    QStandardItemModel *standardModel;
    QLabel *name, *place;
    QComboBox *placeChose;
    QTimeEdit *LMT;
    QLineEdit *nameEdit;//, *LMT;
    QComboBox *choose;
//    PaintedWidget * paintDemo;
    QVBoxLayout * mainLayout;
    QWidget *mainwidget;
    userP * curU;
    QTimer * qclock;
    QVBoxLayout *makeLayout();
};

class Logintt : public QWidget
{    Q_OBJECT

 public:
     Logintt(QWidget *parent = 0);
     ~Logintt();
 private slots:
     void valid();
     void showTimelog();
 private:
      QLabel *username, *password, *curTime;
      QLineEdit *user, *pass;
      QTimer *qclock2;
      QPushButton *loginButton,*closeButton;
};

class Admin: public QWidget{
    Q_OBJECT

public:
    Admin(userP *, QWidget *parent = 0);
    ~Admin();
private slots:
    void search();
    void logout();
    void freshTimeLog();
private:
    QLabel *username, *curTime;
    QLineEdit *user;
    userP *curU;
    QPushButton *searchButton, *logoutButton;
    QTimer *qclock3;
    QListView *listUser;
    QStandardItemModel *standardModel;
};

#endif // MAINWINDOW_H
