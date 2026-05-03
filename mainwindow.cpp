#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDate>
#include <QEventLoop>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

// ============================================================
// ATENȚIE: SCHIMBĂ ACEST IP CU IP-UL COLEGULUI TĂU DE PE HOTSPOT
// ============================================================
const QString MainWindow::SERVER_IP = "172.20.10.3";
// ============================================================

// ============================================================
// CONSTRUCTOR
// ============================================================
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_socket(new QTcpSocket(this))
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    // --------------------------------------------------------
    // Conectare semnale socket
    // --------------------------------------------------------
    //connect(m_socket, &QTcpSocket::readyRead,
      //      this, &MainWindow::onDatePrimite);
    connect(m_socket, &QAbstractSocket::errorOccurred,
            this, &MainWindow::onEroareConectare);

    // Conectare la server la pornire
    conecteazaLaServer();

    // --------------------------------------------------------
    // Populare date statice in combouri
    // --------------------------------------------------------
    QStringList parcuri = {"Herastrau", "Cismigiu", "Sebastian",
                           "Carol", "Tineret", "Drumul Taberei"};
    QStringList zone    = {"Lac", "Alee Principala", "Zona Caini",
                        "Scena", "Loc de joaca"};

    if (ui->roleCombo) {
        ui->roleCombo->clear();
        ui->roleCombo->addItems({"Administrator", "Angajat"});
    }
    if (ui->comboParcTask)   { ui->comboParcTask->clear();   ui->comboParcTask->addItems(parcuri); }
    if (ui->comboZonaTask)   { ui->comboZonaTask->clear();   ui->comboZonaTask->addItems(zone);   }
    if (ui->comboLocatie)    { ui->comboLocatie->clear();    ui->comboLocatie->addItems(parcuri);  }
    if (ui->comboParcGuest)  { ui->comboParcGuest->clear();  ui->comboParcGuest->addItems(parcuri);}
    if (ui->comboZonaGuest)  { ui->comboZonaGuest->clear();  ui->comboZonaGuest->addItems(zone);  }

    // Stil tabele
    QList<QTableWidget*> tables = this->findChildren<QTableWidget*>();
    for (auto t : tables) {
        t->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        t->setSelectionBehavior(QAbstractItemView::SelectRows);
    }

    // --------------------------------------------------------
    // Conexiuni butoane
    // --------------------------------------------------------
    auto connectBtn = [&](QString name, auto slot) {
        QPushButton* btn = this->findChild<QPushButton*>(name);
        if (btn) connect(btn, &QPushButton::clicked, this, slot);
    };

    connectBtn("btnLogin",         &MainWindow::loginSistem);
    connectBtn("btnLogoutAdmin",   &MainWindow::logoutSistem);
    connectBtn("btnLogoutAngajat", &MainWindow::logoutSistem);
    connectBtn("btnLogoutGuest",   &MainWindow::logoutSistem);
    connectBtn("btnJoinGuest",     [=](){ ui->stackedWidget->setCurrentIndex(3); });

    // Navigare Dashboard Admin
    connectBtn("btnGoTasks",    [=](){ ui->stackedWidget->setCurrentIndex(4); incarcaAngajati();  });
    connectBtn("btnGoEvents",   [=](){ ui->stackedWidget->setCurrentIndex(5); });
    connectBtn("btnGoSesizari", [=](){ ui->stackedWidget->setCurrentIndex(6); incarcaSesizari();  });
    connectBtn("btnGoIstoric",  [=](){ ui->stackedWidget->setCurrentIndex(7); });
    connectBtn("btnGoInventar", [=](){ ui->stackedWidget->setCurrentIndex(8); incarcaInventar();  });

    // Butoane Back
    connectBtn("btnBackToDash",   [=](){ ui->stackedWidget->setCurrentIndex(1); });
    connectBtn("btnBackToDash_2", [=](){ ui->stackedWidget->setCurrentIndex(1); });
    connectBtn("btnBackToDash_3", [=](){ ui->stackedWidget->setCurrentIndex(1); });
    connectBtn("btnBackToDash_4", [=](){ ui->stackedWidget->setCurrentIndex(1); });
    connectBtn("btnBackToDash_5", [=](){ ui->stackedWidget->setCurrentIndex(1); });

    // Actiuni Admin
    connectBtn("btnAdaugaTaskManual", &MainWindow::adaugaTaskComplex);
    connectBtn("btnConvertTask",      &MainWindow::convertSesizare);
    connectBtn("btnAprobaEveniment",  &MainWindow::gestioneazaEvenimente);
    connectBtn("btnAddInventar",  [=](){ gestionareInventar(true);  });
    connectBtn("btnUseInventar",  [=](){ gestionareInventar(false); });

    // Actiuni Angajat & Guest
    connectBtn("btnStartTask",          [=](){ actiuniAngajat(1); });
    connectBtn("btnFinishTask",         [=](){ actiuniAngajat(2); });
    connectBtn("btnSendReport",         [=](){ actiuniAngajat(3); });
    connectBtn("btnSendSesizareTeren",  [=](){ actiuniAngajat(4); });
    connectBtn("btnTrimiteSesizareaGuest", [=](){ actiuniAngajat(5); });
}

MainWindow::~MainWindow() {
    if (m_socket->state() == QAbstractSocket::ConnectedState)
        m_socket->disconnectFromHost();
    delete ui;
}

// ============================================================
// GESTIONARE SOCKET
// ============================================================
void MainWindow::conecteazaLaServer() {
    // Te rog să te asiguri că SERVER_PORT este definit în .h (ex: 9000)
    m_socket->connectToHost(SERVER_IP, SERVER_PORT);
}

// Trimite o cerere JSON si asteapta raspunsul (REPARAT)
QJsonObject MainWindow::trimiteCerere(const QJsonObject& cerere) {
    // Reconecteaza daca e cazul
    if (m_socket->state() != QAbstractSocket::ConnectedState) {
        m_socket->connectToHost(SERVER_IP, SERVER_PORT);
        if (!m_socket->waitForConnected(3000)) {
            return {{"succes", false},
                    {"eroare", "Nu ma pot conecta la server. Verifica IP-ul si asigura-te ca serverul ruleaza."}};
        }
    }

    // Trimite JSON + newline (protocolul initial)
    QByteArray date = QJsonDocument(cerere).toJson(QJsonDocument::Compact) + "\n";
    m_socket->write(date);
    m_socket->flush();

    // Asteapta raspunsul (max 5 secunde) - FĂRĂ CONDIȚIE STRICTĂ PE '\n'
    QString raspunsComplet;
    if (m_socket->waitForReadyRead(5000)) {
        raspunsComplet = QString::fromUtf8(m_socket->readAll());
        // Mai așteptăm 50ms doar în caz că JSON-ul este mare și a fost spart în 2 pachete
        while(m_socket->waitForReadyRead(50)) {
            raspunsComplet += QString::fromUtf8(m_socket->readAll());
        }
    } else {
        return {{"succes", false},
                {"eroare", "Timeout: Serverul nu a raspuns. Verifica daca a primit cererea."}};
    }

    // Parseaza JSON-ul primit
    QJsonDocument doc = QJsonDocument::fromJson(raspunsComplet.trimmed().toUtf8());
    if (doc.isNull()) {
        return {{"succes", false}, {"eroare", "Raspuns invalid primit de la server: " + raspunsComplet}};
    }

    return doc.object();
}

void MainWindow::onDatePrimite() {
    // Date nesolicitate (notificari push) - pentru extensii viitoare
    m_bufferRaspuns += QString::fromUtf8(m_socket->readAll());
}

void MainWindow::onEroareConectare(QAbstractSocket::SocketError) {
    // Nu afisam eroare la pornire, incercam din nou la urmatoarea actiune
}

void MainWindow::afiseazaEroare(const QString& mesaj) {
    QMessageBox::warning(this, "Eroare", mesaj);
}

// ============================================================
// LOGIN / LOGOUT
// ============================================================
void MainWindow::loginSistem() {
    QString user  = ui->userInput->text().trimmed();
    QString parola = ui->passInput->text().trimmed();
    QString rol   = ui->roleCombo->currentText();

    if (user.isEmpty()) {
        afiseazaEroare("Introduceti username-ul!");
        return;
    }

    // Trimite cererea de login la server
    QJsonObject cerere;
    cerere["actiune"]  = "login";
    cerere["username"] = user;
    cerere["parola"]   = parola.isEmpty() ? user : parola;

    QJsonObject raspuns = trimiteCerere(cerere);

    if (raspuns["succes"].toBool()) {
        m_rolCurent    = raspuns["rol"].toString();
        m_idUserCurent = raspuns["id_user"].toInt();

        // Navigheaza la pagina corespunzatoare rolului
        if (m_rolCurent == "Admin") {
            ui->stackedWidget->setCurrentIndex(1);
        } else if (m_rolCurent == "Angajat") {
            ui->stackedWidget->setCurrentIndex(2);
            incarcaTaskuriAngajat();
        } else {
            afiseazaEroare("Rol necunoscut: " + m_rolCurent);
        }
    } else {
        // Daca serverul nu e disponibil, fallback la modul demo
        if (raspuns["eroare"].toString().contains("conecta")) {
            if (rol == "Administrator" && user == "admin") {
                m_rolCurent = "Admin";
                ui->stackedWidget->setCurrentIndex(1);
                QMessageBox::information(this, "Mod Demo",
                                         "Server indisponibil. Rulezi in mod demo (fara baza de date).");
            } else if (rol == "Angajat") {
                m_rolCurent = "Angajat";
                ui->stackedWidget->setCurrentIndex(2);
                QMessageBox::information(this, "Mod Demo",
                                         "Server indisponibil. Rulezi in mod demo.");
            } else {
                afiseazaEroare("Date incorecte sau server indisponibil.");
            }
        } else {
            afiseazaEroare(raspuns["eroare"].toString());
        }
    }
}

void MainWindow::logoutSistem() {
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        QJsonObject cerere;
        cerere["actiune"] = "logout";
        trimiteCerere(cerere);
    }

    m_rolCurent    = "";
    m_idUserCurent = -1;
    ui->userInput->clear();
    ui->passInput->clear();
    ui->stackedWidget->setCurrentIndex(0);
}

// ============================================================
// INCARCARE DATE DIN SERVER
// ============================================================
void MainWindow::incarcaTaskuriAngajat() {
    QJsonObject cerere;
    cerere["actiune"] = "get_taskuri_mele";
    QJsonObject raspuns = trimiteCerere(cerere);

    if (!raspuns["succes"].toBool()) return;

    ui->tableTaskuriAngajat->setRowCount(0);
    QJsonArray taskuri = raspuns["date"].toArray();

    for (const QJsonValue& v : taskuri) {
        QJsonObject t = v.toObject();
        int r = ui->tableTaskuriAngajat->rowCount();
        ui->tableTaskuriAngajat->insertRow(r);
        ui->tableTaskuriAngajat->setItem(r, 0,
                                         new QTableWidgetItem(QString::number(t["id"].toInt())));
        ui->tableTaskuriAngajat->setItem(r, 1,
                                         new QTableWidgetItem(t["tip"].toString()));
        ui->tableTaskuriAngajat->setItem(r, 2,
                                         new QTableWidgetItem(t["descriere"].toString()));
        ui->tableTaskuriAngajat->setItem(r, 3,
                                         new QTableWidgetItem(t["status"].toString()));
    }
}

void MainWindow::incarcaSesizari() {
    QJsonObject cerere;
    cerere["actiune"] = "get_sesizari";
    QJsonObject raspuns = trimiteCerere(cerere);

    if (!raspuns["succes"].toBool()) return;

    ui->tableSesizariAdmin->setRowCount(0);
    QJsonArray sesizari = raspuns["date"].toArray();

    for (const QJsonValue& v : sesizari) {
        QJsonObject s = v.toObject();
        int r = ui->tableSesizariAdmin->rowCount();
        ui->tableSesizariAdmin->insertRow(r);
        ui->tableSesizariAdmin->setItem(r, 0,
                                        new QTableWidgetItem(QString::number(s["id"].toInt())));
        ui->tableSesizariAdmin->setItem(r, 1,
                                        new QTableWidgetItem("Cetatean"));
        ui->tableSesizariAdmin->setItem(r, 2,
                                        new QTableWidgetItem(QString::number(s["idZona"].toInt())));
        ui->tableSesizariAdmin->setItem(r, 3,
                                        new QTableWidgetItem(s["descriere"].toString()));
        ui->tableSesizariAdmin->setItem(r, 4,
                                        new QTableWidgetItem(s["data"].toString()));
    }
}

void MainWindow::incarcaAngajati() {
    QJsonObject cerere;
    cerere["actiune"] = "get_angajati";
    QJsonObject raspuns = trimiteCerere(cerere);

    if (!raspuns["succes"].toBool()) return;

    if (ui->listAngajatiTask) {
        ui->listAngajatiTask->clear();
        QJsonArray angajati = raspuns["date"].toArray();
        for (const QJsonValue& v : angajati) {
            QJsonObject a = v.toObject();
            QString label = a["numeComplet"].toString() +
                            (a["esteLiber"].toBool() ? " [Liber]" : " [Ocupat]");
            auto* item = new QListWidgetItem(label);
            item->setData(Qt::UserRole, a["id"].toInt());
            ui->listAngajatiTask->addItem(item);
        }
    }
}

void MainWindow::incarcaInventar(int idZona) {
    QJsonObject cerere;
    cerere["actiune"] = "get_inventar_zona";
    cerere["id_zona"] = idZona;
    QJsonObject raspuns = trimiteCerere(cerere);

    if (!raspuns["succes"].toBool()) return;

    ui->tableInventar->setRowCount(0);
    QJsonArray obiecte = raspuns["date"].toArray();

    for (const QJsonValue& v : obiecte) {
        QJsonObject o = v.toObject();
        int r = ui->tableInventar->rowCount();
        ui->tableInventar->insertRow(r);
        ui->tableInventar->setItem(r, 0,
                                   new QTableWidgetItem(QString::number(o["id"].toInt())));
        ui->tableInventar->setItem(r, 1,
                                   new QTableWidgetItem(o["subtip"].toString()));
        ui->tableInventar->setItem(r, 2,
                                   new QTableWidgetItem("1"));
        ui->tableInventar->setItem(r, 3,
                                   new QTableWidgetItem(o["stare"].toString()));
    }
}

// ============================================================
// ACTIUNI ADMIN
// ============================================================
void MainWindow::adaugaTaskComplex() {
    QString taskDesc = ui->inputTaskAdmin->text().trimmed();
    if (taskDesc.isEmpty()) {
        afiseazaEroare("Completati descrierea taskului!");
        return;
    }

    // Obtine angajatul selectat
    QList<QListWidgetItem*> selectati = ui->listAngajatiTask->selectedItems();
    if (selectati.isEmpty()) {
        afiseazaEroare("Alegeti cel putin un angajat!");
        return;
    }

    int idAngajat = selectati.first()->data(Qt::UserRole).toInt();
    if (idAngajat <= 0) idAngajat = 1; // fallback demo

    // Trimite la server
    QJsonObject cerere;
    cerere["actiune"]    = "creeaza_task_daily";
    cerere["id_angajat"] = idAngajat;
    cerere["id_zona"]    = 1;
    cerere["descriere"]  = taskDesc;
    cerere["cost"]       = 50.0;
    cerere["deadline"]   = QDate::currentDate().addDays(7)
                             .toString("yyyy-MM-dd");

    QJsonObject raspuns = trimiteCerere(cerere);

    if (raspuns["succes"].toBool()) {
        int idTask = raspuns["id_task"].toInt();

        // Adauga in tabel vizual
        int r = ui->tableTaskuriAdmin->rowCount();
        ui->tableTaskuriAdmin->insertRow(r);
        ui->tableTaskuriAdmin->setItem(r, 0,
                                       new QTableWidgetItem(QString::number(idTask)));
        ui->tableTaskuriAdmin->setItem(r, 1,
                                       new QTableWidgetItem(taskDesc));
        ui->tableTaskuriAdmin->setItem(r, 2,
                                       new QTableWidgetItem(selectati.first()->text()));
        ui->tableTaskuriAdmin->setItem(r, 3,
                                       new QTableWidgetItem(ui->comboParcTask->currentText() +
                                                            " - " + ui->comboZonaTask->currentText()));
        ui->tableTaskuriAdmin->setItem(r, 4,
                                       new QTableWidgetItem("InProgress"));

        ui->inputTaskAdmin->clear();
        QMessageBox::information(this, "Succes",
                                 "Task creat cu ID=" + QString::number(idTask));
    } else {
        afiseazaEroare(raspuns["eroare"].toString());
    }
}

void MainWindow::convertSesizare() {
    int row = ui->tableSesizariAdmin->currentRow();
    if (row == -1) {
        afiseazaEroare("Selectati o sesizare din lista!");
        return;
    }

    int idSesizare = ui->tableSesizariAdmin->item(row, 0)->text().toInt();
    QString desc   = ui->tableSesizariAdmin->item(row, 3)
                       ? ui->tableSesizariAdmin->item(row, 3)->text()
                       : "Reparatie";

    // Navigheaza la pagina de taskuri si pre-completeaza
    ui->stackedWidget->setCurrentIndex(4);
    ui->inputTaskAdmin->setText("REPARARE: " + desc);

    // Stocam id-ul sesizarii pentru conversie
    // (se va folosi la urmatorul adaugaTaskComplex)
    ui->inputTaskAdmin->setProperty("idSesizare", idSesizare);
}

void MainWindow::gestioneazaEvenimente() {
    QString numeEv = ui->inputNumeEveniment->text().trimmed();
    if (numeEv.isEmpty()) {
        afiseazaEroare("Introduceti numele evenimentului!");
        return;
    }

    QString data     = ui->dateEveniment->date().toString("yyyy-MM-dd");
    QString locatie  = ui->comboLocatie->currentText();

    // Trimite la server
    QJsonObject cerere;
    cerere["actiune"]     = "creeaza_eveniment";
    cerere["id_zona"]     = 1;
    cerere["tip"]         = "Altele";
    cerere["denumire"]    = numeEv;
    cerere["data"]        = data;
    cerere["ora_start"]   = "10:00";
    cerere["ora_sfarsit"] = "22:00";
    cerere["id_firma"]    = 3;

    QJsonObject raspuns = trimiteCerere(cerere);

    if (raspuns["succes"].toBool()) {
        int idEv = raspuns["id_eveniment"].toInt();

        int r = ui->tableEvenimenteAdmin->rowCount();
        ui->tableEvenimenteAdmin->insertRow(r);
        ui->tableEvenimenteAdmin->setItem(r, 0,
                                          new QTableWidgetItem(numeEv));
        ui->tableEvenimenteAdmin->setItem(r, 1,
                                          new QTableWidgetItem(ui->dateEveniment->date()
                                                                   .toString("dd/MM/yyyy")));
        ui->tableEvenimenteAdmin->setItem(r, 2,
                                          new QTableWidgetItem(locatie));
        ui->tableEvenimenteAdmin->setItem(r, 3,
                                          new QTableWidgetItem("Programat ✅ (ID=" +
                                                               QString::number(idEv) + ")"));
        ui->inputNumeEveniment->clear();
    } else {
        afiseazaEroare(raspuns["eroare"].toString());
    }
}

void MainWindow::gestionareInventar(bool adauga) {
    if (adauga) {
        // Adauga in depozit
        QJsonObject cerere;
        cerere["actiune"]      = "adauga_in_depozit";
        cerere["id_categorie"] = 1;
        cerere["cantitate"]    = ui->spinCantitate->value();
        cerere["pret"]         = 100.0;
        cerere["data_achizitie"] = QDate::currentDate().toString("yyyy-MM-dd");

        QJsonObject raspuns = trimiteCerere(cerere);

        if (raspuns["succes"].toBool()) {
            int r = ui->tableInventar->rowCount();
            ui->tableInventar->insertRow(r);
            ui->tableInventar->setItem(r, 0,
                                       new QTableWidgetItem(
                                           QString::number(raspuns["id_obiect"].toInt())));
            ui->tableInventar->setItem(r, 1,
                                       new QTableWidgetItem(ui->inputNumeMaterial->text()));
            ui->tableInventar->setItem(r, 2,
                                       new QTableWidgetItem(
                                           QString::number(ui->spinCantitate->value())));
            ui->tableInventar->setItem(r, 3,
                                       new QTableWidgetItem("Functional"));
            QMessageBox::information(this, "Succes", "Obiect adaugat in depozit.");
        } else {
            afiseazaEroare(raspuns["eroare"].toString());
        }
    } else {
        // Muta in junk
        int row = ui->tableInventar->currentRow();
        if (row == -1) {
            afiseazaEroare("Selectati un obiect din inventar!");
            return;
        }

        int idObiect = ui->tableInventar->item(row, 0)->text().toInt();
        if (idObiect <= 0) {
            afiseazaEroare("ID obiect invalid.");
            return;
        }

        QJsonObject cerere;
        cerere["actiune"]   = "muta_in_junk";
        cerere["id_obiect"] = idObiect;

        QJsonObject raspuns = trimiteCerere(cerere);

        if (raspuns["succes"].toBool()) {
            ui->tableInventar->removeRow(row);
            QMessageBox::information(this, "Succes", "Obiect mutat in junk.");
        } else {
            afiseazaEroare(raspuns["eroare"].toString());
        }
    }
}

// ============================================================
// ACTIUNI ANGAJAT & GUEST
// ============================================================
void MainWindow::actiuniAngajat(int tip) {
    switch (tip) {

    case 1: { // Start task — vizual doar
        int r = ui->tableTaskuriAngajat->currentRow();
        if (r != -1)
            ui->tableTaskuriAngajat->setItem(
                r, 3, new QTableWidgetItem("In Lucru"));
        break;
    }

    case 2: { // Finalizeaza task
        int r = ui->tableTaskuriAngajat->currentRow();
        if (r == -1) { afiseazaEroare("Selectati un task!"); break; }

        int idTask = ui->tableTaskuriAngajat->item(r, 0)->text().toInt();

        QJsonObject cerere;
        cerere["actiune"] = "finalizeaza_task";
        cerere["id_task"] = idTask;
        QJsonObject raspuns = trimiteCerere(cerere);

        if (raspuns["succes"].toBool()) {
            ui->tableTaskuriAngajat->removeRow(r);
            QMessageBox::information(this, "Succes",
                                     "Task finalizat! Raport de finalizare creat automat.");
        } else {
            afiseazaEroare(raspuns["eroare"].toString());
        }
        break;
    }

    case 3: { // Trimite raport de status
        int r = ui->tableTaskuriAngajat->currentRow();
        if (r == -1) { afiseazaEroare("Selectati un task!"); break; }

        int idTask = ui->tableTaskuriAngajat->item(r, 0)->text().toInt();

        QJsonObject cerere;
        cerere["actiune"]   = "creeaza_raport";
        cerere["id_task"]   = idTask;
        cerere["descriere"] = "Raport status trimis de angajat.";
        QJsonObject raspuns = trimiteCerere(cerere);

        if (raspuns["succes"].toBool())
            QMessageBox::information(this, "Succes", "Raport trimis catre admin!");
        else
            afiseazaEroare(raspuns["eroare"].toString());
        break;
    }

    case 4: { // Sesizare de la angajat pe teren
        QString desc = ui->inputSesizareTeren->text().trimmed();
        if (desc.isEmpty()) { afiseazaEroare("Completati sesizarea!"); break; }

        QJsonObject cerere;
        cerere["actiune"]   = "creeaza_sesizare";
        cerere["id_zona"]   = 1;
        cerere["descriere"] = desc;
        QJsonObject raspuns = trimiteCerere(cerere);

        if (raspuns["succes"].toBool()) {
            int rowS = ui->tableSesizariAdmin->rowCount();
            ui->tableSesizariAdmin->insertRow(rowS);
            ui->tableSesizariAdmin->setItem(rowS, 0,
                                            new QTableWidgetItem(
                                                QString::number(raspuns["id_sesizare"].toInt())));
            ui->tableSesizariAdmin->setItem(rowS, 1,
                                            new QTableWidgetItem("Angajat"));
            ui->tableSesizariAdmin->setItem(rowS, 3,
                                            new QTableWidgetItem(desc));
            ui->inputSesizareTeren->clear();
            QMessageBox::information(this, "Succes", "Sesizare trimisa!");
        } else {
            afiseazaEroare(raspuns["eroare"].toString());
        }
        break;
    }

    case 5: { // Sesizare de la Guest
        QString desc = ui->textSesizareGuest->toPlainText().trimmed();
        if (desc.isEmpty()) { afiseazaEroare("Completati sesizarea!"); break; }

        QJsonObject cerere;
        cerere["actiune"]   = "creeaza_sesizare";
        cerere["id_zona"]   = 1;
        cerere["descriere"] = desc;
        QJsonObject raspuns = trimiteCerere(cerere);

        if (raspuns["succes"].toBool()) {
            QMessageBox::information(this, "Succes",
                                     "Sesizare trimisa cu succes!\nID: " +
                                         QString::number(raspuns["id_sesizare"].toInt()));
            ui->textSesizareGuest->clear();
        } else {
            // Guest poate sesiza si fara server (e permis)
            QMessageBox::information(this, "Succes",
                                     "Sesizare inregistrata local.");
        }
        break;
    }

    }
}