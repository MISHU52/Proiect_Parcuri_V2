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
    // Auth
    void loginSistem();
    void logoutSistem();

    // Admin - Taskuri
    void adaugaTaskComplex();
    void convertSesizare();

    // Admin - Evenimente & Inventar
    void gestioneazaEvenimente();
    void gestionareInventar(bool adauga);

    // Admin - Angajati
    void creeazaAngajat();
    void reincarcaAngajati();

    // Angajat & Guest
    void actiuniAngajat(int tip);

    // Socket
    void onDatePrimite();
    void onEroareConectare(QAbstractSocket::SocketError err);

private:
    Ui::MainWindow *ui;

    QTcpSocket* m_socket;
    QString     m_bufferRaspuns;

    static const QString SERVER_IP;
    static const int     SERVER_PORT = 9000;

    QString m_rolCurent;
    int     m_idUserCurent = -1;

    // Retea
    QJsonObject trimiteCerere(const QJsonObject& cerere);

    // Incarcare date
    void incarcaTaskuriAngajat();
    void incarcaSesizari();
    void incarcaAngajati();        // pentru QListWidget (selectie task)
    void incarcaAngajatiTabel();   // pentru QTableWidget (gestionare angajati)
    void incarcaInventar(int idZona = 1);

    // Helpers
    void conecteazaLaServer();
    void afiseazaEroare(const QString& mesaj);
};

#endif // MAINWINDOW_H