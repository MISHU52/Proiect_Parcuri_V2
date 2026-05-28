#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>

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
    void incarcaFirmeOrganizatoare();
    void incarcaEvenimente();
    void gestionareInventar(bool adauga);
    void creeazaAngajat();
    void reincarcaAngajati();
    void actiuniAngajat(int tip);
    void onDatePrimite();
    void onEroareConectare(QAbstractSocket::SocketError err);

private:
    Ui::MainWindow *ui;
    QTcpSocket*     m_socket;
    QTimer*         m_timerIstoric;
    QString         m_bufferRaspuns;

    static const QString SERVER_IP;
    static const int     SERVER_PORT = 9000;

    QString m_rolCurent;
    int     m_idUserCurent        = -1;
    int     m_idTaskCurentAngajat = -1; // cerinta 6

    QJsonObject trimiteCerere(const QJsonObject& cerere);

    void incarcaTaskuriAngajat();
    void incarcaSesizari();
    void incarcaAngajati();
    void incarcaAngajatiTabel();
    void incarcaInventar(int idZona = 1);
    void incarcaCategoriiInventar();
    void incarcaFurnizori();
    void incarcaItemsInventar();
    void incarcaIstoric();
    void incarcaInventarAngajati();
    void incarcaInventarMeu();
    void incarcaContracteFurnizori();
    void incarcaTaskuriAdmin();
    void incarcaIstoricAngajat();
    void incarcaAngajatiRapoarte();
    void incarcaRapoarteAngajat(int idAngajat);

    void conecteazaLaServer();
    void afiseazaEroare(const QString& mesaj);
};

#endif // MAINWINDOW_H