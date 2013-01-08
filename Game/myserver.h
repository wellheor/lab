#ifndef MYSERVER_H
#define MYSERVER_H

#include <QWidget>
#include "QTcpServer"
#include <QTcpSocket>

namespace Ui {
class MyServer;
}

class MyServer : public QWidget
{
    Q_OBJECT

public:
    MyServer(int nPort,QWidget *parent = 0);
    ~MyServer();

protected:


private:
    Ui::MyServer *ui;

private:
    QTcpServer* m_ptcpServer;
    quint16 m_nNextBlockSize;
private:
    void sendToClient(QTcpSocket* pScoket,const QString& str);
public slots:
    virtual void slotNewConnection();
    void slotReadClient();


};

#endif // MYSERVER_H
