#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <scene.h>
#include "QTcpServer"
#include <QTcpSocket>
#include "QTextEdit"
#include "QLineEdit"
#include "QTime"

namespace Ui {
    class MainWindow;

}

class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    explicit MainWindow(int nPort, QWidget *parent = 0);
    int oldPosition;
    int *map;
    Scene * scene;
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event);

private slots:
    void on_pushButton_clicked();
    void slotReadyRead(                 );
    void slotError (QAbstractSocket::SocketError);
    void slotSendToServer(              );
    void slotGameToServer(int cod );
    void slotConnected (                );
    virtual void slotNewConnection();
    void slotReadClient();
    void client();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
void sendToClient(QTcpSocket* pScoket,const QString& str);
    Ui::MainWindow *ui;
    QTcpSocket* m_pTcpSocket;
    /*QTextEdit* m_ptxtInfo;
    QLineEdit* m_ptxtInput;*/
    quint16 m_nNextBlockSize;
    QTcpServer* m_ptcpServer;
    quint16 m_nNextBlock;
};

#endif // MAINWINDOW_H
