#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

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

private:
    Ui::MainWindow *ui;
};
#endif