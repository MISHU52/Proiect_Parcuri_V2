#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loginSistem();
    void logoutSistem();
    void adaugaTaskComplex();
    void convertSesizare();
    void gestioneazaEvenimente();
    void gestionareInventar(bool adauga);
    void actiuniAngajat(int tip);

    // Slot pentru datele primite de la server
    void onDatePrimite();
    void onEroareConectare(QAbstractSocket::SocketError err);

private:
    Ui::MainWindow *ui;

    // --------------------------------------------------------
    // Conexiune TCP la backend C++
    // --------------------------------------------------------
    QTcpSocket* m_socket;
    QString     m_bufferRaspuns;

    static const QString SERVER_IP;
    static const int     SERVER_PORT = 9000;

    // --------------------------------------------------------
    // Starea sesiunii curente
    // --------------------------------------------------------
    QString m_rolCurent;
    int     m_idUserCurent = -1;

    // --------------------------------------------------------
    // Metode helper
    // --------------------------------------------------------
    void        conecteazaLaServer();
    QJsonObject trimiteCerere(const QJsonObject& cerere);
    void        incarcaTaskuriAngajat();
    void        incarcaSesizari();
    void        incarcaAngajati();
    void        incarcaInventar(int idZona = 1);
    void        afiseazaEroare(const QString& mesaj);
};

#endif // MAINWINDOW_H