#include "stdafx.h"
#include <QApplication>
#include <QTextCodec>


using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);    
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    a.setWindowIcon(QIcon(":/images/icon"));
    init();
   // MainWindow w(allUsers[0]);
    //w.show();
    Logintt log;
    log.show();
    return a.exec();
}
