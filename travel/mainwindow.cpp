#include "stdafx.h"
#include <QPainter>
#include <QWidget>
#include "mainwindow.h"
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QListView>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QTextCodec>
#include <QPaintEvent>
#include <QTimer>
#include <QTimeEdit>
#include <QMessageBox>
#include<cmath>

int rec[251];

Admin::Admin(userP *cu, QWidget *parent):curU(cu),
    QWidget(parent){
    username = new QLabel(tr("username"));
    user = new QLineEdit;
    searchButton = new QPushButton(tr("查询"));
    logoutButton = new QPushButton(tr("登出"));
    listUser = new QListView;
    listUser->setFixedSize(480,230);
    standardModel = new QStandardItemModel;
    char temp[41];
    sprintf(temp, "当前时间: %02d:%02d", MAP->getTime().getHour(), MAP->getTime().getMin());
    curTime = new QLabel(QString(temp));
    qclock3 = new QTimer;
    connect(qclock3, SIGNAL(timeout()), this, SLOT(freshTimeLog()));
    qclock3->start(INTERVAL);
    connect(logoutButton, SIGNAL(clicked(bool)), this, SLOT(logout()));
    connect(searchButton, SIGNAL(clicked(bool)), this, SLOT(search()));

    QStringList strList;
    for (int i = 0; i < userP::getCount();i++){
    //    if (!allUsers[i]->isAdmin())
        strList.append(QString::fromStdString(allUsers[i]->getName()));
    }
    standardModel->clear();
    for (int i = 0 ; i <strList.size(); i++){
        QString stri = static_cast<QString>(strList.at(i));
        QStandardItem *item = new QStandardItem(stri);
        standardModel->appendRow(item);
    }
    listUser->setModel(standardModel);

    QHBoxLayout *upLayout = new QHBoxLayout;
    upLayout->addWidget(username);
    upLayout->addWidget(user);
    upLayout->addWidget(searchButton);
    upLayout->addWidget(logoutButton);
    QVBoxLayout *downLayout = new QVBoxLayout;
    downLayout->addWidget(curTime);
    downLayout->addLayout(upLayout);
    downLayout->addWidget(listUser);

    setLayout(downLayout);
    setFixedSize(500,300);
}

Admin::~Admin(){
    delete username;
    delete user;
    delete logoutButton;
    delete searchButton;
    delete listUser;
    delete standardModel;

    qclock3->stop();
    disconnect(qclock3,SIGNAL(timeout()),this,SLOT(freshTimeLog()));
    delete qclock3;
    _log(MAP->getTime().toString() + " "+curU->getName()+" logged out");
}
void Admin::freshTimeLog(){
    time cur = MAP->getTime();
    int h = cur.getHour();
    int m= cur.getMin();
    char temp[31];
    sprintf(temp, "当前时间: %02d:%02d", h,m);
    MAP->time_fresh();
    curTime->setText(QString(temp));
}

void Admin::logout(){
    Logintt *log = new Logintt;
    log->show();
    qclock3->stop();
    disconnect(qclock3,SIGNAL(timeout()),this,SLOT(freshTimeLog()));
    _log(MAP->getTime().toString() + " "+curU->getName()+" logged out");
    close();
}

void Admin::search(){
    std::string toSearch = user->text().toStdString();
    if (toSearch.size() == 0){
        QMessageBox msgbox;
        msgbox.setText("Input username!");
        msgbox.exec();
        _log(MAP->getTime().toString() + " *Admin: "+ curU->getName()+
             " failed to search " +user->text().toStdString());
        return;
    }
    userP *temp = getUser(user->text().toStdString());
    if (temp == NULL){
        QMessageBox msgbox;
        msgbox.setText(QString::fromStdString("User " + user->text().toStdString() + " not found!"));
        msgbox.exec();
        _log(MAP->getTime().toString() + " *Admin: "+ curU->getName()+
             " failed to search " +user->text().toStdString());
        return;
    }
    QMessageBox msgbox;
    std::string tempS;
    if (temp->isAdmin()){
        tempS = "Admin :" + user->text().toStdString() + "\nLive in : " +
                allCities[temp->getCurCitt()]->name()+"\n Administrator";
    }else{
        tempS = "User : " + user->text().toStdString() + "\nLive in : " + allCities[temp->getCurCitt()]->name()+"\n";
        if (temp->isOnbord()){
            bool _flag = false;
            for (int i = 0; i < temp->getLineC(); i++){
                if (MAP->getTime() > allVehicles[temp->line[i]]->getStartTime() &&
                        allVehicles[temp->line[i]]->getEndTime() > MAP->getTime()){
                    tempS += "On Vehicle "+ allVehicles[temp->line[i]]->getName();
                    _flag = true;
                    break;
                }
            }
            if (!_flag){
                _flag = false;
                for (int i = 0; i < temp->getLineC(); i++){
                    if (allVehicles[temp->line[i]]->getStartTime() > MAP->getTime()){
                        tempS += "Waiting for Vehicle "+ allVehicles[temp->line[i]]->getName();
                        _flag = true;
                        break;
                    }
                }
            }
            if (!_flag){
                temp->setOnbord(false);
                tempS += "Not on board";
            }
        }else{
            tempS += "Not on board";
        }
    }
    msgbox.setText(QString::fromStdString(tempS));
    msgbox.exec();
    _log(MAP->getTime().toString() + " *Admin: "+ curU->getName()+
         " succeed to search " +user->text().toStdString());
    return;
}

Logintt::Logintt(QWidget *parent):
    QWidget(parent){
    username = new QLabel(tr("Username"));
    password = new QLabel(tr("Password"));
    username->setAlignment(Qt::AlignCenter);
    password->setAlignment(Qt::AlignCenter);

    char temp[41];
    sprintf(temp, "当前时间: %02d:%02d", MAP->getTime().getHour(), MAP->getTime().getMin());
    user = new QLineEdit;
    curTime = new QLabel(QString(temp));
    pass = new QLineEdit;
    pass->setEchoMode(QLineEdit::Password);

    loginButton = new QPushButton(tr("Login"));
    loginButton->setDefault(true);
    closeButton = new QPushButton(tr("Exit"));

    qclock2 = new QTimer;
    connect(qclock2, SIGNAL(timeout()), this, SLOT(showTimelog()));
    qclock2->start(INTERVAL);

    connect(closeButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(loginButton, SIGNAL(clicked(bool)), this, SLOT(valid()));

    QHBoxLayout *upupLayout = new QHBoxLayout;
    upupLayout->addWidget(curTime);
    QHBoxLayout *upLayout= new QHBoxLayout;
    upLayout->addWidget(username);
    upLayout->addWidget(user);
    QHBoxLayout *middleLayout= new QHBoxLayout;
    middleLayout->addWidget(password);
    middleLayout->addWidget(pass);
    QHBoxLayout *downLayout= new QHBoxLayout;
    downLayout->addWidget(loginButton);
    downLayout->addWidget(closeButton);

    QVBoxLayout *loginLayout = new QVBoxLayout;
    loginLayout->addLayout(upupLayout);
    loginLayout->addLayout(upLayout);
    loginLayout->addLayout(middleLayout);
    loginLayout->addLayout(downLayout);

    setLayout(loginLayout);
    setFixedSize(250,100);
    setWindowTitle(tr("Login"));
}

void Logintt::valid(){
    userP * u = getUser(user->text().toStdString());
    if (u != NULL && pass->text().toStdString() == u->getPass()){
        if (!u->isAdmin()){
            MainWindow *win = new MainWindow(u);
            win->show();
        }else{
            Admin *adm  = new Admin(u);
            adm->show();
        }
        qclock2->stop();
        disconnect(qclock2, SIGNAL(timeout()), this, SLOT(showTimelog()));
        if (u->isAdmin())
            _log(MAP->getTime().toString() + " *ADMIN: "+user->text().toStdString()+" login successfully");
        else
            _log(MAP->getTime().toString() + " "+user->text().toStdString()+" login successfully");
        close();
    }else{
        _log(MAP->getTime().toString() + " username "+ user->text().toStdString()+
             " tried to login with wrong password");
        QMessageBox msgbox;
        msgbox.setText("Wrong username or password!");
        msgbox.exec();
    }
}

Logintt::~Logintt(){
    delete username;
    delete password;
    delete user;
    delete pass;
    delete loginButton;
    delete qclock2;
    delete closeButton;
}

PaintedWidget::PaintedWidget(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(500,350);
}

void PaintedWidget::paintEvent(QPaintEvent *)
{
    painter = new QPainter(this);
    QPixmap chinamap(":/images/map");
    painter->drawPixmap(0,0,500,345,chinamap);
}

void PaintedWidget::mousePressEvent(QMouseEvent *event){
    painter->save();
    painter->setBrush(Qt::red);
    painter->drawEllipse(event->x(), event->y(), 19,19);
    painter->restore();
    for(int i = 0 ; i< city::getCount();i++){
    //    std::cout << allCities[i]->getX() << " " <<allCities[i]->getY()<<std::endl;
        if  ( (abs(event->x()-allCities[i]->getX()) <= 5)&&
             (abs(event->y() - allCities[i]->getY()) <= 5)){
            std::cout << allCities[i]->name() << " " << allCities[i]->getX() <<" "<<
                         allCities[i]->getY() << " " << std::endl << event->x() <<
                         event->y() << std::endl;
            if (allCities[i]->getFlag() == false){
                allCities[i]->setFlag(true);
                painter->save();
                painter->setPen(Qt::red);
                painter->setBrush(Qt::red);
                painter->drawEllipse(allCities[i]->getX(),
                                     allCities[i]->getY(),
                                     18,18);
                painter->restore();
                std::cout << "Have painted"<<std::endl;
            }else{
                allCities[i]->setFlag(false);
                QPixmap chinamap(":/images/map");
                painter->drawPixmap(0,0,500,345,chinamap);
                for (int j =0; j < city::getCount();j++){
                    if (allCities[j]->getFlag() == true){
                        painter->save();
                        painter->setPen(Qt::NoPen);
                        painter->setBrush(Qt::red);
                        painter->drawEllipse(allCities[j]->getX(),
                                             allCities[j]->getY(),
                                             5,5);
                        painter->restore();
                    }
                }
            }
            break;
        }
    }
}

void MainWindow::showTime(){
    time cur = MAP->getTime();
    int h = cur.getHour();
    int m= cur.getMin();
    char temp[31];
    sprintf(temp, "当前时间: %02d:%02d", h,m);
    MAP->time_fresh();
    CurTime->setText(QString(temp));
}

void Logintt::showTimelog(){
    time cur = MAP->getTime();
    int h = cur.getHour();
    int m= cur.getMin();
    char temp[31];
    sprintf(temp, "当前时间: %02d:%02d", h,m);
    MAP->time_fresh();
    curTime->setText(QString(temp));
}

int getCurCity(userP *u){
    if (!u->isOnbord())
        return -1;
    for (int i = 0; i < u->getLineC(); i++){
        if (MAP->getTime() > allVehicles[u->line[i]]->getStartTime() &&
                allVehicles[u->line[i]]->getEndTime() > MAP->getTime()){
            return allVehicles[u->line[i]]->getDestCity().getID();
        }
    }
    for (int i = 1; i < u->getLineC(); i++){
            if (allVehicles[u->line[i]]->getStartTime() > MAP->getTime()){
                return allVehicles[u->line[i-1]]->getDestCity().getID();
            }
        }
    u->setOnbord(false);
    return -1;
}

void MainWindow::stopLine(){
    curU->setOnbord(false);
}

void MainWindow::setLine(){
    if (getCurCity(curU)!= -1){
        QMessageBox msgbox;
        msgbox.setText("Still on board!");
        msgbox.exec();
        return;
    }
    int line = choose->currentIndex();
    curU->setOnbord(true);
    if(MAP->getPerValid()){
        if (line == 0){
            curU->setLineC(MAP->perfectLength);
            for (int i = 0 ; i < MAP->perfectLength; i++)
                curU->line[i] = MAP->perfect[i];
        } else{
            curU->setLineC(1);
            curU->line[0] = rec[line-1];
        }
    }else{
        curU->setLineC(1);
        curU->line[0] = rec[line];
    }
    QMessageBox msgbox;
    msgbox.setText("You are on board now!");
    msgbox.exec();
}

MainWindow::MainWindow(userP *cu, QWidget *parent)
    : QMainWindow(parent),curU(cu)
{
    label1 = new QLabel(tr("起点"));
    label2 = new QLabel(tr("终点"));
    label3 = new QLabel(tr("策略"));
    place = new QLabel(tr("Location"));
    chooseLine = new QLabel(tr("线路"));
    name = new QLabel(tr("Username"));
    char temp[41];
    sprintf(temp, "当前时间: %02d:%02d", MAP->getTime().getHour(), MAP->getTime().getMin());
    CurTime = new QLabel(QString(temp));
    limitTime = new QLabel(tr("时间限制"));
    limitCity = new QLabel(tr("途经城市(需在选中旅游策略)"));

    qclock = new QTimer;
    connect(qclock,SIGNAL(timeout()),this,SLOT(showTime()));
    qclock->start(INTERVAL);    // can be set to 10 to test algorithms

    label1->setAlignment(Qt::AlignCenter);
    label2->setAlignment(Qt::AlignCenter);
    label3->setAlignment(Qt::AlignCenter);
    name->setAlignment(Qt::AlignLeft);
    place->setAlignment(Qt::AlignLeft);
    CurTime->setAlignment(Qt::AlignLeft);
    CurTime->setFixedSize(90,20);
    limitTime->setAlignment(Qt::AlignLeft);
    limitTime->setFixedSize(50,20);
    limitCity->setAlignment(Qt::AlignLeft);
    chooseLine->setAlignment(Qt::AlignLeft);

    nameEdit = new QLineEdit;
    LMT = new QTimeEdit;

    nameEdit->setFixedSize(70,20);
    nameEdit->setText(QString::fromStdString(curU->getName()));
    LMT->setFixedSize(80,20);
    LMT->setTime(QTime(0,0));
    LMT->setMinimumTime(QTime(0,0));
    LMT->setMaximumTime(QTime(72,0));

    start = new QComboBox();
    end = new QComboBox();
    stra = new QComboBox();
    placeChose = new QComboBox();
    choose = new QComboBox();
    choose->clear();
    choose->addItem(QString("None"));

//    limitTime = new QCheckBox(tr("Time Limitation"));
//    limitCity = new QCheckBox(tr("City In Road"));
//    limitTime->setMinimumSize(50,20);
//    limitCity->setMinimumSize(50,20);

    limitCities = new QCheckBox [city::getCount()];
    for (int i = 0 ; i < city::getCount(); i++){
        start->addItem(QString::fromStdString(allCities[i]->name()));
        end->addItem(QString::fromStdString(allCities[i]->name()));
        placeChose->addItem(QString::fromStdString(allCities[i]->name()));
        limitCities[i].setText(QString::fromStdString((allCities[i]->name())));
    }

    start->setCurrentIndex(curU->getCurCitt());
    placeChose->setCurrentIndex(curU->getCurCitt());

    stra->addItem(QString(tr("未选择")));
    stra->addItem(QString(tr("低价")));
    stra->addItem(QString(tr("迅捷")));
    stra->addItem(QString(tr("旅游")));

    searchButton = new QPushButton(tr("Search"));
    searchButton->setDefault(true);
    closeButton = new QPushButton(tr("Logout"));
    saveButton = new QPushButton(tr("Save"));
    chooseButton = new QPushButton(tr("Go"));
    stopButton = new QPushButton(tr("Stop"));
    searchButton->setFixedSize(50,20);
    saveButton->setFixedSize(50,20);
    closeButton->setFixedSize(50,20);
    chooseButton->setFixedSize(50,20);
    stopButton->setFixedSize(50,20);

    listview = new QListView;
    listview->setFixedSize(342,220);
    standardModel = new QStandardItemModel;

 //   paintDemo = new PaintedWidget;

    connect(closeButton, SIGNAL(clicked(bool)),this , SLOT(logout()));
    connect(searchButton, SIGNAL(clicked(bool)), this, SLOT(search()));
    connect(chooseButton, SIGNAL(clicked(bool)), this, SLOT(setLine()));
    connect(saveButton, SIGNAL(clicked(bool)),this, SLOT(saveInfo()));
    connect(stopButton, SIGNAL(clicked(bool)),this, SLOT(stopLine()));

    mainwidget = new QWidget;

    mainLayout = makeLayout();
    mainwidget->setLayout(mainLayout);
    setCentralWidget(mainwidget);
//    paintDemo->show();
    setFixedHeight(sizeHint().height());
    setFixedWidth(sizeHint().width());
    setWindowTitle(tr("System"));
    setWindowIcon(QIcon(":/images/icon"));
}

QVBoxLayout* MainWindow::makeLayout(){
    QHBoxLayout *leftupupLayout = new QHBoxLayout;
    leftupupLayout->addWidget(CurTime);
    leftupupLayout->addWidget(closeButton);
    QVBoxLayout *leftleftLayout = new QVBoxLayout;
    leftleftLayout->addWidget(label1);
    leftleftLayout->addWidget(label2);
    leftleftLayout->addWidget(label3);
    leftleftLayout->setAlignment(Qt::AlignLeft);
// Left Right Layout     Combobox
    QVBoxLayout *leftrightLayout = new QVBoxLayout;
    leftrightLayout->addWidget(start);
    leftrightLayout->addWidget(end);
    leftrightLayout->addWidget(stra);
    leftrightLayout->setAlignment(Qt::AlignLeft);
// Left Top&Up Layout      Fix
    QHBoxLayout *leftTopLayout = new QHBoxLayout;
    leftTopLayout->addLayout(leftleftLayout);
    leftTopLayout->addLayout(leftrightLayout);
    QVBoxLayout *leftUpLayout = new QVBoxLayout;
    leftUpLayout->addLayout(leftupupLayout);
    leftUpLayout->addLayout(leftTopLayout);

// Left Middle Layout   CheckBox
    QHBoxLayout *leftMiddleLayout = new QHBoxLayout;
    leftMiddleLayout->addWidget(limitTime);
    leftMiddleLayout->addWidget(LMT);
    //leftMiddleLayout->addWidget(limitCity);
    leftMiddleLayout->setAlignment(Qt::AlignLeft);
// LeftMiddle Down Layout   User
    QVBoxLayout *LeftMiddleDownLayout = new QVBoxLayout;
    QHBoxLayout *l1 = new QHBoxLayout;
    QHBoxLayout *l2 = new QHBoxLayout;
    l1->addWidget(place);
    l1->addWidget(placeChose);
    l2->addWidget(name);
    l2->addWidget(nameEdit);
    LeftMiddleDownLayout->addLayout(l2);
    LeftMiddleDownLayout->addLayout(l1);
    LeftMiddleDownLayout->setAlignment(Qt::AlignLeft);
// Left Down Layout  Button
    QHBoxLayout *leftDownLayout = new QHBoxLayout;
    leftDownLayout->addWidget(searchButton);
    leftDownLayout->addWidget(saveButton);
    QHBoxLayout *leftDownDownLayout = new QHBoxLayout;
    leftDownDownLayout->addWidget(chooseLine);
    leftDownDownLayout->addWidget(choose);
// Left Layout      Select
    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(leftUpLayout);
    leftLayout->addLayout(leftMiddleLayout);
    leftLayout->addLayout(LeftMiddleDownLayout);
    leftLayout->addLayout(leftDownDownLayout);
    leftLayout->addLayout(leftDownLayout);
    leftLayout->setAlignment(Qt::AlignLeft);
// Right Layout     show
    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(listview);
// Top Layout show
    QHBoxLayout *UpLayout = new QHBoxLayout;
    UpLayout->addLayout(leftLayout);
    UpLayout->addLayout(rightLayout);
// DownLayout
    QVBoxLayout *DownLayout = new QVBoxLayout;
    QHBoxLayout *temp = new QHBoxLayout;
    temp->addWidget(limitCity);
    temp->addWidget(chooseButton);
    DownLayout->addLayout(temp);
    temp = new QHBoxLayout;
    for (int i =1 ; i <= city::getCount() ; i++){
        temp->addWidget(&(limitCities[i-1]));
        if (i % 6 == 0){
            DownLayout->addLayout(temp);
            temp = new QHBoxLayout;
        }
    }
    if (city::getCount()%6 != 0)
        DownLayout->addLayout(temp);

// Main Layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    //mainLayout->addLayout(toptop);
    mainLayout->addLayout(UpLayout);
    mainLayout->addLayout(DownLayout);

    return mainLayout;
}

MainWindow::~MainWindow()
{
    delete label1; delete label2; delete label3; delete CurTime;
    delete start; delete end; delete stra;
    delete listview; delete LMT; delete []limitCities; delete limitCity;
    delete standardModel; delete name; delete place;delete placeChose;
    delete choose; delete chooseButton; delete chooseLine;
    delete nameEdit; //delete paintDemo;
    qclock->stop();
    disconnect(qclock,SIGNAL(timeout()),this,SLOT(showTime()));
    delete qclock;
    delete mainwidget;
    _log(MAP->getTime().toString() + " "+curU->getName()+" logged out");
}

void MainWindow::showAns(city&st,city&ed,bool flag){
    QStringList strList;
    using std::string;
    if (st.getID() == ed.getID()){
        std::string ts("No route from ");
        ts = ts+st.name()+std::string(" to ")+ed.name();
        strList.append(QString::fromStdString(ts));
    }else if (flag){
        std::string ts("Best route from ");
        ts = ts+st.name()+std::string(" to ")+ed.name();
        strList.append(QString::fromStdString(ts));
        if (MAP->succ == true){
            char temp[301];
            sprintf(temp,"TOTAL COST %d     TOTAL TIME %02d:%02d", MAP->totalCost,
                    MAP->totalTime/60, MAP->totalTime%60);
            strList.append(QString::fromStdString(std::string(temp)));
            for (int i = 0 ; i < MAP->perfectLength;i++){
                string s1 = allVehicles[MAP->perfect[i]]->getStartCity().name();
                string s2 = allVehicles[MAP->perfect[i]]->getDestCity().name();
                s1 = s1 + string("->") + s2;
                sprintf(temp, "  START %02d:%02d  END %02d:%02d  PRICE: %d",
                        allVehicles[MAP->perfect[i]]->getStartTime().getHour(),
                        allVehicles[MAP->perfect[i]]->getStartTime().getMin(),
                        allVehicles[MAP->perfect[i]]->getEndTime().getHour(),
                        allVehicles[MAP->perfect[i]]->getEndTime().getMin(),
                        allVehicles[MAP->perfect[i]]->getCost());
                strList.append(QString::fromStdString(s1+string(temp)));
            }
        } else{
            std::string ts("No such perfect routes");
            strList.append(QString::fromStdString(ts));
        }
        strList.append(" ");
    }
    listVehicle(st,ed,&strList);
    standardModel->clear();
    int nCount = strList.size();
    for (int i = 0 ; i <nCount; i++){
        QString stri = static_cast<QString>(strList.at(i));
        QStandardItem *item = new QStandardItem(stri);
        standardModel->appendRow(item);
    }
    listview->setModel(standardModel);
}

void MainWindow::listVehicle(city &st, city &ed, QStringList *strList){
    using namespace std;
    char temp[201];
    if (LMT->text()==QString("0:00"))
        sprintf(temp, "Direct route with no limit time");
    else
        sprintf(temp, "Direct route with limit time %02d:%02d:", LMT->time().hour(),LMT->time().minute());
    strList->append(QString::fromStdString(string(temp)));
    int record[201][3], top = 0;
    for (int i = 0 ; i < vehicle::getCount();i++){
        if (allVehicles[i]->getStartCity().getID()==st.getID() &&
                allVehicles[i]->getDestCity().getID()==ed.getID()){
            if (LMT->text() != QString("0:00")){
                if (allVehicles[i]->getLastTime().getMins() > 60*LMT->time().hour()+LMT->time().minute())
                    continue;
            }
            rec[top] = i;
            record[top][0] = i;
            record[top][2] = allVehicles[i]->getCost();
            record[top++][1] = allVehicles[i]->getStartTime().getMins();
        }
    }
    if (top ==0){
        sprintf(temp, "No such routes");
        strList->append(QString::fromStdString(string(temp)));
    }
    choose->clear();
    if (MAP->getPerValid())
        choose->addItem("Best");
    for (int i = 0 ; i < top ; i++){
        sprintf(temp, "%d", i+1);
        choose->addItem(temp);
    }
    for (int i = top-1 ; i>=1;i--){
        for (int j = 1; j <= i;j++){
            if ( record[j][1] < record[j-1][1] || (record[j][1] == record[j-1][1] && record[j][2] < record[j-1][2])){
                int temp;
                temp = record[j][0]; record[j][0] = record[j-1][0]; record[j-1][0] = temp;
                temp = record[j][1]; record[j][1] = record[j-1][1]; record[j-1][1] = temp;
                temp = record[j][2]; record[j][2] = record[j-1][2]; record[j-1][2] = temp;
            }
        }
    }
    char num[21];
    for (int i = 0; i < top; i++){
        sprintf(num, "%02d: ", i+1);
        string s1 = allVehicles[record[i][0]]->getStartCity().name();
        string s2 = allVehicles[record[i][0]]->getDestCity().name();
        s1 = s1 + string("->") + s2;
        sprintf(temp, "  START %02d:%02d  END %02d:%02d  PRICE: %d",
                 allVehicles[i]->getStartTime().getHour(),
                 allVehicles[i]->getStartTime().getMin(),
                 allVehicles[i]->getEndTime().getHour(),
                 allVehicles[i]->getEndTime().getMin(),
                 allVehicles[i]->getCost());
        strList->append(QString::fromStdString(num+s1+string(temp)));
        }
}


void MainWindow::saveInfo(){
    if (nameEdit->text().toStdString().size() == 0){
        QMessageBox msgbox;
        msgbox.setText(tr("Invalid Username"));
        msgbox.exec();
    } else{
        std::string logs = "User " + curU->getName() + " in "+ allCities[curU->getCurCitt()]->name();
        curU->setCurCitt(placeChose->currentIndex());
        curU->setName(nameEdit->text().toStdString());
        logs = logs+ " change to User " + curU->getName() + " in " + allCities[curU->getCurCitt()]->name();
        _log(logs);
        QMessageBox msgbox;
        msgbox.setText(tr("信息保存成功"));
        msgbox.exec();
    }
}


void MainWindow::logout(){
    Logintt *log = new Logintt;
    log->show();
    qclock->stop();
    disconnect(qclock,SIGNAL(timeout()),this,SLOT(showTime()));
    _log(MAP->getTime().toString() + " "+curU->getName()+" logged out");
    close();
}

void MainWindow::search(){
    using namespace std;
    city *st = allCities[start->currentIndex()];
    city *ed = allCities[end->currentIndex()];
    city temp[31];
    std::string logg = MAP->getTime().toString() + " User " + curU->getName() +" search lines from " +
            st->name() +" to " + ed->name();
    _log(logg);
    int count = 0;
    switch (stra->currentIndex()){
    case 0:
        MAP->setLine(false);
        showAns(*st,*ed,false);
        break;
    case 1:
        if (LMT->text().toStdString() == "0:00")
            MAP->dijkstra_cost(*st,*ed,MAP->getTime());
        else{
            time lim = time(LMT->time().hour(), LMT->time().minute());
            MAP->limit_time_cost(*st, *ed, lim, MAP->getTime());
        }
        showAns(*st,*ed, true);
        break;
    case 2:
        MAP->spfa_last(*st,*ed,MAP->getTime());
        showAns(*st,*ed,true);
        break;
    case 3:
        for (int i = 0 ; i < city::getCount(); i++){
            if (limitCities[i].isChecked()){
                temp[count++] = *allCities[i];
            }
        }
        MAP->needed_cost(*st,*ed, temp, count);
        showAns(*st, *ed, true);
        break;
    default:
        break;
    }
}
