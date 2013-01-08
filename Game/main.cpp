#include <QtGui/QApplication>
#include "mainwindow.h"
#include "QWidgetSet"
#include "QPushButton"
#include "QHostAddress"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   /* QPushButton *ServerButton = new QPushButton("server");
        QObject::connect(ServerButton,SIGNAL(clicked()), &a, SLOT(server()));
        QPushButton *ClientButton = new QPushButton("client");
            QObject::connect(ClientButton,SIGNAL(clicked()), &a, SLOT(client()));*/
      /*  ServerButton->show();
        ClientButton->show();*/
   MainWindow w(1);
    w.show();
    return a.exec();
}

void QApplication::server()
{
    MainWindow w(1);
    w.show();
}

void MainWindow::client()
{
    MainWindow w(2);
    w.show();
}

