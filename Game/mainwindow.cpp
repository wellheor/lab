#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scene.h"
#include <QGraphicsView>
#include <mygraphicsview.h>
#include <QMouseEvent>
#include <QFile>
#include <QTextStream>
#include "QTcpSocket"
#include "QHostAddress"
#include "QTime"
#include "QDataStream"

MainWindow::MainWindow(int nPort, QWidget *parent) :    QMainWindow(parent),    ui(new Ui::MainWindow)
{
    QFile file("Map.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QString line;
    while(!in.atEnd())
    {
       line = line + " " + in.readLine();
       //qDebug(line.toStdString().c_str());
     }
    QStringList values = line.split(" ");
    file.close();

    ui->setupUi(this);
    map = new int[255];
    if(values.count() == 226)
    {
        for(int x = 0; x < 15; x++)
        {
            for(int y = 0; y < 15; y ++)
            {
                map[x+15*y] = atoi(values[1+x+15*y].toStdString().c_str());
            }
        }
    }
    scene = new Scene;
    scene->setSceneRect(0,0,750,750);
    ui->view->setScene(scene);
    scene->makeMap(map);

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int x = event->pos().x();
    int y = event->pos().y() - 40;
    if(y < 790)
    {
        div_t x1 = div(x,50);
        div_t y1 = div(y,50);
        int position = x1.quot+15*y1.quot;
       // map[position] = 2;

        if(ui->firstPlayerRadioButton->isChecked())
        {
            int value = map[position];
            qDebug((QString::number(value)).toStdString().c_str());
            if(value == 2)
            {
                map[position + 1] = 4;
                slotGameToServer(((position +1)*10) + 4);
            }
            if(value == 4)
            {
                if(x1.quot != 0 && map[position - 1] == 1)
                {
                    map[position - 1] = 6;
                    slotGameToServer(((position -1)*10) + 6);
                    qDebug((QString::number(oldPosition)).toStdString().c_str());
                    oldPosition = position;
                }
                if(y1.quot != 0 && map[position - 15] == 1)
                {
                    map[position - 15] = 6;
                    slotGameToServer(((position -15)*10) + 6);
                    qDebug((QString::number(oldPosition)).toStdString().c_str());
                    oldPosition = position;
                }
                if(x1.quot != 14 && map[position + 1] == 1)
                {
                    map[position + 1] = 6;
                    slotGameToServer(((position + 1)*10) + 6);
                    qDebug((QString::number(oldPosition)).toStdString().c_str());
                    oldPosition = position;
                }
                if(y1.quot != 14 && map[position + 15] == 1)
                {
                    map[position + 15] = 6;
                    slotGameToServer(((position +15)*10) + 6);
                    qDebug((QString::number(oldPosition)).toStdString().c_str());
                    oldPosition = position;
                }
            }
            if(value == 6)
            {
                qDebug((QString::number(oldPosition)).toStdString().c_str());
                map[position] = 4;
                slotGameToServer(((position)*10) + 4);
                map[oldPosition] = 1;
                for(int x = 0; x < 15; x++)
                {
                    for(int y = 0; y < 15; y ++)
                    {
                        if(map[x+15*y] == 6)
                        map[x+15*y] = 1;
                        slotGameToServer(((x+15*y)*10) + 1);
                    }
                }

            }
            if(value == 3)
            {
                if(oldPosition == position - 1 || oldPosition == position - 15 || oldPosition == position + 15)
                {
                    map[position] = 2;
                    slotGameToServer(((position)*10) + 2);
                }
            }
        }
        if(ui->secondPlayerRadioButton->isChecked())
        {
            int value = map[position];
            qDebug((QString::number(value)).toStdString().c_str());
            if(value == 3)
            {
                map[position - 1] = 5;
                slotGameToServer(((position -1)*10) + 5);
            }
            if(value == 5)
            {
                if(x1.quot != 0 && map[position - 1] == 1)
                {
                    map[position - 1] = 6;
                    slotGameToServer(((position -1)*10) + 6);
                }
                if(y1.quot != 0 && map[position - 15] == 1)
                {
                    map[position - 15] = 6;
                    slotGameToServer(((position -15)*10) + 6);
                }
                if(x1.quot != 14 && map[position + 1] == 1)
                {
                    map[position + 1] = 6;
                    slotGameToServer(((position +1)*10) + 6);
                }
                if(y1.quot != 14 && map[position + 15] == 1)
                {
                    map[position + 15] = 6;
                    slotGameToServer(((position +15) * 10) + 6);
                }
            }
        }
        scene->makeMap(map);
    }
    //QGraphicsView::mousePressEvent(event);
}

void MainWindow::slotReadyRead()
{
    qDebug("slotReadyRead");
    QDataStream in(m_pTcpSocket);
    in.setVersion(QDataStream::Qt_4_7);
    for (;;) {
        if(!m_nNextBlockSize){
            if(m_pTcpSocket->bytesAvailable()<sizeof(quint16))
            {
                break;
            }
            in>>m_nNextBlockSize;
        }
        if(m_pTcpSocket->bytesAvailable()<m_nNextBlockSize)
        {
            break;
        }
QTime time;
QString str;
in>>time>>str;

ui->textEdit->append(time.toString()+" "+str);
m_nNextBlockSize=0;
    }
}
void MainWindow::slotError(QAbstractSocket::SocketError err)
{
    qDebug("slotError");
    QString strError=
            "Error: "+(err==QAbstractSocket::HostNotFoundError?
                "The host was not found":
                err==QAbstractSocket::RemoteHostClosedError?
                    "The remote host is closed":
                    err==QAbstractSocket::ConnectionRefusedError?
                        "The connection was refused":
                        QString(m_pTcpSocket->errorString())
                        );
    ui->textEdit->append(strError);
}
void MainWindow::slotSendToServer()
{
    qDebug("slotSendToServer");
    QByteArray arrBlock;
    QDataStream out(&arrBlock,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_7);
    out<<quint16(0)<<QTime::currentTime()<<ui->lineEdit->text();

    out.device()->seek(0);
    out<<quint16(arrBlock.size()-sizeof(quint16));

    m_pTcpSocket->write(arrBlock);
    ui->lineEdit->setText("");
}
void MainWindow::slotGameToServer(int cod)
{
    QString str = QString::number(cod);
    qDebug() << str;
    QByteArray arrBlock;
    QDataStream out(&arrBlock,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_7);
    out<<quint16(0)<<QTime::currentTime()<<str;
    out.device()->seek(0);
    out<<quint16(arrBlock.size()-sizeof(quint16));
    m_pTcpSocket->write(arrBlock);
}
void MainWindow::slotConnected()
{
    qDebug("slotConnected");
    ui->textEdit->append("Received the connected() signal");
}
void MainWindow::slotNewConnection()
{
    qDebug("NewConnection");
    QTcpSocket* pClientSocket=m_ptcpServer->nextPendingConnection();
    connect(pClientSocket,SIGNAL(disconnected()),pClientSocket,SLOT(deleteLater()));
    connect(pClientSocket,SIGNAL(readyRead()),this,SLOT(slotReadClient()));
    sendToClient(pClientSocket,"Server Response: Connected!");
}
void MainWindow::sendToClient(QTcpSocket *pScoket, const QString &str)
{
    qDebug("SendToClient");
    QByteArray arrBlock;
    QDataStream out(&arrBlock,QIODevice::WriteOnly);
    out.setVersion((QDataStream::Qt_4_8));
    out<<quint16(0)<<QTime::currentTime()<<str;
    out.device()->seek(0);
    out<<quint16(arrBlock.size()-sizeof(quint16));
    pScoket->write(arrBlock);
}
void MainWindow::slotReadClient()
{
    qDebug("ReadClient");
    QTcpSocket* pClientSocket=(QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion((QDataStream::Qt_4_8));
    qDebug("1");
    for(;;)
    {
        qDebug("2");
        if(!m_nNextBlock)
        {
            qDebug("3");
            if(pClientSocket->bytesAvailable()<sizeof(quint16))break;
            in >> m_nNextBlock;
        }
        //if(pClientSocket->bytesAvailable() < m_nNextBlock) break;
        QTime time;
        QString str;
        in>>time>>str;
        int cod = str.toInt();
        if (cod>0)
        {
            int ch = cod%10;
            int position = (cod-ch)/10;
            map[position] = ch;
        }
        QString strMessage = time.toString()+"Client has sended - "+str;
        ui->textEdit->append(strMessage);
        m_nNextBlock = 0;
        str="otv";
        sendToClient(pClientSocket,"Server Response: Received \""+str+"\"");
    }
    scene->makeMap(map);
   /* if (cod<0)
    {
        int ch = cod%10;
        position = (cod-ch)/10;
        map[position] = ch;
    }*/
}

void MainWindow::on_pushButton_2_clicked()
{
    //ui->setupUi(this);
    ui->secondPlayerRadioButton->toggle();
    qDebug("button2");
    m_pTcpSocket=new QTcpSocket(this);
    m_pTcpSocket->connectToHost("127.0.0.1",3333);
       connect(m_pTcpSocket,SIGNAL(connected()),SLOT(slotConnected()));
       connect(m_pTcpSocket,SIGNAL(readyRead()),SLOT(slotReadyRead()));
       connect(m_pTcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(slotError(QAbstractSocket::SocketError)));
       slotSendToServer();
       //connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(slotSendToServer()));

       scene = new Scene;
       scene->setSceneRect(0,0,750,750);
       ui->view->setScene(scene);
       scene->makeMap(map);
}

void MainWindow::on_pushButton_clicked()
{
    ui->firstPlayerRadioButton->toggle();
    m_ptcpServer= new QTcpServer(this);
    if(!m_ptcpServer->listen(QHostAddress::Any,3333))
    {
        ui->textEdit->setText("Server error");
        m_ptcpServer->close();
        return;
    }
    connect(m_ptcpServer,SIGNAL(newConnection()),this,SLOT(slotNewConnection()));
    ui->textEdit->setText("Server is running");
}

void MainWindow::on_pushButton_3_clicked()
{
    qDebug("button3");
    slotSendToServer();
}
