#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDate>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QLineEdit>
#include <QDebug>
#include <QDebug>
#include <QComboBox>

const QString MainWindow::SERVER_IP = "172.20.10.3";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_socket(new QTcpSocket(this))
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    connect(m_socket, &QAbstractSocket::errorOccurred,
            this, &MainWindow::onEroareConectare);

    m_socket->connectToHost(SERVER_IP, SERVER_PORT);

    QStringList parcuri = {"Herastrau", "Cismigiu", "Sebastian",
                           "Carol", "Tineret", "Drumul Taberei"};
    QStringList zone    = {"Lac", "Alee Principala", "Zona Caini",
                        "Scena", "Loc de joaca"};

    if (ui->roleCombo)     { ui->roleCombo->clear();     ui->roleCombo->addItems({"Administrator","Angajat"}); }
    if (ui->comboParcTask) { ui->comboParcTask->clear();  ui->comboParcTask->addItems(parcuri); }
    if (ui->comboZonaTask) { ui->comboZonaTask->clear();  ui->comboZonaTask->addItems(zone);   }
    if (ui->comboLocatie)  { ui->comboLocatie->clear();   ui->comboLocatie->addItems(parcuri);  }
    if (ui->comboParcGuest){ ui->comboParcGuest->clear(); ui->comboParcGuest->addItems(parcuri);}
    if (ui->comboZonaGuest){ ui->comboZonaGuest->clear(); ui->comboZonaGuest->addItems(zone);  }

    for (auto* t : this->findChildren<QTableWidget*>()) {
        t->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        t->setSelectionBehavior(QAbstractItemView::SelectRows);
        t->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }

    auto connectBtn = [&](const QString& name, auto slot) {
        if (auto* btn = this->findChild<QPushButton*>(name))
            connect(btn, &QPushButton::clicked, this, slot);
    };

    connectBtn("btnLogin",            &MainWindow::loginSistem);
    connectBtn("btnLogoutAdmin",      &MainWindow::logoutSistem);
    connectBtn("btnLogoutAngajat",    &MainWindow::logoutSistem);
    connectBtn("btnLogoutGuest",      &MainWindow::logoutSistem);
    connectBtn("btnJoinGuest",        [=](){ ui->stackedWidget->setCurrentIndex(3); });

    connectBtn("btnGoTasks",    [=](){ ui->stackedWidget->setCurrentIndex(4); incarcaAngajati(); });
    connectBtn("btnGoEvents",   [=](){ ui->stackedWidget->setCurrentIndex(5); });
    connectBtn("btnGoSesizari", [=](){ ui->stackedWidget->setCurrentIndex(6); incarcaSesizari(); });
    connectBtn("btnGoIstoric",  [=](){ ui->stackedWidget->setCurrentIndex(7); });
    connectBtn("btnGoInventar", [=](){ ui->stackedWidget->setCurrentIndex(8); incarcaInventar(); });

    // Navigare pagina creare angajat - prin nume widget
    connectBtn("btnGoAngajati",   [=](){
        if (auto* p = ui->stackedWidget->findChild<QWidget*>("pageCreareAngajat"))
            ui->stackedWidget->setCurrentWidget(p);
    });
    connectBtn("btnGoCreareCont", [=](){
        if (auto* p = ui->stackedWidget->findChild<QWidget*>("pageCreareAngajat"))
            ui->stackedWidget->setCurrentWidget(p);
    });

    connectBtn("btnBackToDash",         [=](){ ui->stackedWidget->setCurrentIndex(1); });
    connectBtn("btnBackToDash_2",       [=](){ ui->stackedWidget->setCurrentIndex(1); });
    connectBtn("btnBackToDash_3",       [=](){ ui->stackedWidget->setCurrentIndex(1); });
    connectBtn("btnBackToDash_4",       [=](){ ui->stackedWidget->setCurrentIndex(1); });
    connectBtn("btnBackToDash_5",       [=](){ ui->stackedWidget->setCurrentIndex(1); });
    connectBtn("btnBackToDashAngajati", [=](){ ui->stackedWidget->setCurrentIndex(1); });
    connectBtn("btnBackDinCreare",      [=](){ ui->stackedWidget->setCurrentIndex(1); });

    connectBtn("btnAdaugaTaskManual", &MainWindow::adaugaTaskComplex);
    connectBtn("btnConvertTask",      &MainWindow::convertSesizare);

    connectBtn("btnIgnoraSesizarea", [=](){
        int row = ui->tableSesizariAdmin->currentRow();
        if (row == -1) { afiseazaEroare("Selectati o sesizare!"); return; }
        auto* itemId = ui->tableSesizariAdmin->item(row, 0);
        if (!itemId) return;
        QJsonObject cerere;
        cerere["actiune"]     = "ignora_sesizare";
        cerere["id_sesizare"] = itemId->text().toInt();
        QJsonObject r = trimiteCerere(cerere);
        if (r["succes"].toBool()) {
            ui->tableSesizariAdmin->removeRow(row);
            QMessageBox::information(this, "OK", "Sesizarea a fost ignorata.");
        } else {
            afiseazaEroare(r["eroare"].toString());
        }
    });

    connectBtn("btnAprobaEveniment", &MainWindow::gestioneazaEvenimente);
    connectBtn("btnAddInventar",     [=](){ gestionareInventar(true);  });
    connectBtn("btnUseInventar",     [=](){ gestionareInventar(false); });

    connectBtn("btnCreeazaAngajat",    &MainWindow::creeazaAngajat);
    connectBtn("btnReincarcaAngajati", &MainWindow::reincarcaAngajati);
    connectBtn("btnSalveazaAngajat",   &MainWindow::creeazaAngajat);

    connectBtn("btnStartTask",             [=](){ actiuniAngajat(1); });
    connectBtn("btnFinishTask",            [=](){ actiuniAngajat(2); });
    connectBtn("btnSendReport",            [=](){ actiuniAngajat(3); });
    connectBtn("btnSendSesizareTeren",     [=](){ actiuniAngajat(4); });
    connectBtn("btnTrimiteSesizareaGuest", [=](){ actiuniAngajat(5); });
}

MainWindow::~MainWindow() {
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        QJsonObject cerere;
        cerere["actiune"] = "logout";
        // toUtf8() garanteaza ca diacriticele sunt trimise corect
        QByteArray dateJson = QJsonDocument(cerere).toJson(QJsonDocument::Compact);
        m_socket->write(dateJson + "\n");
        m_socket->waitForBytesWritten(500);
        m_socket->disconnectFromHost();
    }
    delete ui;
}

QJsonObject MainWindow::trimiteCerere(const QJsonObject& cerere) {
    if (m_socket->state() != QAbstractSocket::ConnectedState) {
        m_socket->connectToHost(SERVER_IP, SERVER_PORT);
        if (!m_socket->waitForConnected(3000))
            return {{"succes", false}, {"eroare", QString("Server indisponibil (%1:%2)").arg(SERVER_IP).arg(SERVER_PORT)}};
    }

    // toUtf8() garanteaza ca diacriticele sunt trimise corect
    QByteArray dateJson = QJsonDocument(cerere).toJson(QJsonDocument::Compact);
    m_socket->write(dateJson + "\n");
    if (!m_socket->waitForBytesWritten(3000))
        return {{"succes", false}, {"eroare", "Eroare la trimiterea cererii"}};

    QByteArray bufferRaw;
    while (!bufferRaw.contains('\n')) {
        if (!m_socket->waitForReadyRead(5000))
            return {{"succes", false}, {"eroare", "Timeout: serverul nu a raspuns"}};
        bufferRaw += m_socket->readAll();
    }

    // Extrage prima linie si forteaza interpretarea ca UTF-8
    QByteArray linie = bufferRaw.left(bufferRaw.indexOf('\n')).trimmed();
    QString asUtf8  = QString::fromUtf8(linie);

    QJsonParseError parseErr;
    QJsonDocument doc = QJsonDocument::fromJson(asUtf8.toUtf8(), &parseErr);

    if (doc.isNull())
        return {{"succes", false}, {"eroare", "Raspuns invalid: " + parseErr.errorString()}};

    return doc.object();
}

void MainWindow::onEroareConectare(QAbstractSocket::SocketError) {}
void MainWindow::onDatePrimite() {}
void MainWindow::afiseazaEroare(const QString& mesaj) {
    QMessageBox::warning(this, "Eroare", mesaj);
}

void MainWindow::loginSistem() {
    QString user   = ui->userInput->text().trimmed();
    QString parola = ui->passInput->text().trimmed();
    QString rol    = ui->roleCombo->currentText();

    if (user.isEmpty() || parola.isEmpty()) {
        afiseazaEroare("Completati username-ul si parola!");
        return;
    }

    QJsonObject cerere;
    cerere["actiune"]  = "login";
    cerere["username"] = user;
    cerere["parola"]   = parola;

    QJsonObject raspuns = trimiteCerere(cerere);

    if (raspuns["succes"].toBool()) {
        m_rolCurent    = raspuns["rol"].toString();
        m_idUserCurent = raspuns["id_user"].toInt();
        if (m_rolCurent == "Admin") {
            ui->stackedWidget->setCurrentIndex(1);
        } else if (m_rolCurent == "Angajat") {
            ui->stackedWidget->setCurrentIndex(2);
            incarcaTaskuriAngajat();
        } else {
            afiseazaEroare("Rol necunoscut: " + m_rolCurent);
        }
    } else {
        QString eroare = raspuns["eroare"].toString();
        if (eroare.contains("indisponibil") || eroare.contains("Timeout")) {
            if (rol == "Administrator" && user == "admin") {
                m_rolCurent = "Admin";
                ui->stackedWidget->setCurrentIndex(1);
                QMessageBox::information(this, "Mod Demo", "Server indisponibil. Datele nu se salveaza.");
                return;
            }
        }
        afiseazaEroare(eroare);
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

void MainWindow::incarcaTaskuriAngajat() {
    if (m_idUserCurent <= 0) return;
    QJsonObject raspuns = trimiteCerere({{"actiune", "get_taskuri_mele"}});
    if (!raspuns["succes"].toBool()) return;

    // DEBUG TEMPORAR - afiseaza JSON-ul primit
    qDebug() << "JSON taskuri primit:" << QJsonDocument(raspuns).toJson();

    // DEBUG: afiseaza JSON-ul primit de la server
    qDebug() << "JSON taskuri primit:" << QJsonDocument(raspuns).toJson();

    ui->tableTaskuriAngajat->setRowCount(0);
    for (const QJsonValue& v : raspuns["date"].toArray()) {
        QJsonObject t = v.toObject();
        int id     = t["id"].toInt();
        QString tip      = t["tip"].toString();
        QString descriere= t["descriere"].toString();
        QString status   = t["status"].toString();

        int r = ui->tableTaskuriAngajat->rowCount();
        ui->tableTaskuriAngajat->insertRow(r);

        int cols = ui->tableTaskuriAngajat->columnCount();
        // Scrie ID in coloana 0 intotdeauna
        ui->tableTaskuriAngajat->setItem(r, 0,
                                         new QTableWidgetItem(QString::number(id)));

        if (cols >= 5) {
            // Tabelul colegului: ID | Sarcina | Locatie | Resurse | Status
            ui->tableTaskuriAngajat->setItem(r, 1, new QTableWidgetItem(descriere));
            ui->tableTaskuriAngajat->setItem(r, 2, new QTableWidgetItem("Zona 1"));
            ui->tableTaskuriAngajat->setItem(r, 3, new QTableWidgetItem(tip));
            ui->tableTaskuriAngajat->setItem(r, 4, new QTableWidgetItem(status));
        } else {
            // Fallback pentru alte structuri de tabel
            if (cols > 1) ui->tableTaskuriAngajat->setItem(r, 1, new QTableWidgetItem(tip));
            if (cols > 2) ui->tableTaskuriAngajat->setItem(r, 2, new QTableWidgetItem(descriere));
            if (cols > 3) ui->tableTaskuriAngajat->setItem(r, 3, new QTableWidgetItem(status));
        }
    }
}

void MainWindow::incarcaSesizari() {
    QJsonObject raspuns = trimiteCerere({{"actiune", "get_sesizari"}});
    if (!raspuns["succes"].toBool()) {
        afiseazaEroare("Eroare sesizari: " + raspuns["eroare"].toString());
        return;
    }
    ui->tableSesizariAdmin->setRowCount(0);
    for (const QJsonValue& v : raspuns["date"].toArray()) {
        QJsonObject s = v.toObject();
        int r = ui->tableSesizariAdmin->rowCount();
        ui->tableSesizariAdmin->insertRow(r);
        ui->tableSesizariAdmin->setItem(r, 0, new QTableWidgetItem(QString::number(s["id"].toInt())));
        ui->tableSesizariAdmin->setItem(r, 1, new QTableWidgetItem("Cetatean"));
        ui->tableSesizariAdmin->setItem(r, 2, new QTableWidgetItem(QString::number(s["idZona"].toInt())));
        ui->tableSesizariAdmin->setItem(r, 3, new QTableWidgetItem(s["descriere"].toString()));
        ui->tableSesizariAdmin->setItem(r, 4, new QTableWidgetItem(s["data"].toString()));
    }
}

void MainWindow::incarcaAngajati() {
    QJsonObject raspuns = trimiteCerere({{"actiune", "get_angajati"}});
    if (!raspuns["succes"].toBool() || !ui->listAngajatiTask) return;
    ui->listAngajatiTask->clear();

    QJsonArray angajati = raspuns["date"].toArray();
    if (angajati.isEmpty()) {
        ui->listAngajatiTask->addItem("(Niciun angajat. Creati din meniu)");
        return;
    }
    for (const QJsonValue& v : angajati) {
        QJsonObject a = v.toObject();
        auto* item = new QListWidgetItem(
            a["numeComplet"].toString() +
            (a["esteLiber"].toBool() ? " [Liber]" : " [Ocupat]"));
        item->setData(Qt::UserRole, a["id"].toInt());
        ui->listAngajatiTask->addItem(item);
    }
}

// incarcaAngajatiTabel — foloseste findChild in loc de ui->tableAngajati
// deoarece tabelul poate sa nu existe in UI-ul colegului
void MainWindow::incarcaAngajatiTabel() {
    QJsonObject raspuns = trimiteCerere({{"actiune", "get_angajati"}});
    if (!raspuns["succes"].toBool()) {
        afiseazaEroare("Nu am putut incarca angajatii:\n" + raspuns["eroare"].toString());
        return;
    }

    // Cauta tabelul dupa nume — compatibil cu orice UI
    auto* tabel = this->findChild<QTableWidget*>("tableAngajati");
    if (!tabel) return; // tabelul nu exista in UI-ul colegului, ignoram

    tabel->setRowCount(0);
    for (const QJsonValue& v : raspuns["date"].toArray()) {
        QJsonObject a = v.toObject();
        int r = tabel->rowCount();
        tabel->insertRow(r);
        tabel->setItem(r, 0, new QTableWidgetItem(QString::number(a["id"].toInt())));
        tabel->setItem(r, 1, new QTableWidgetItem(a["numeComplet"].toString()));
        tabel->setItem(r, 2, new QTableWidgetItem(a["username"].toString()));
        tabel->setItem(r, 3, new QTableWidgetItem(QString::number(a["idZona"].toInt())));
        tabel->setItem(r, 4, new QTableWidgetItem(a["esteLiber"].toBool() ? "Liber" : "Ocupat"));
    }
}

void MainWindow::incarcaInventar(int idZona) {
    QJsonObject raspuns = trimiteCerere({{"actiune", "get_inventar_zona"}, {"id_zona", idZona}});
    if (!raspuns["succes"].toBool()) return;
    ui->tableInventar->setRowCount(0);
    for (const QJsonValue& v : raspuns["date"].toArray()) {
        QJsonObject o = v.toObject();
        int r = ui->tableInventar->rowCount();
        ui->tableInventar->insertRow(r);
        ui->tableInventar->setItem(r, 0, new QTableWidgetItem(QString::number(o["id"].toInt())));
        ui->tableInventar->setItem(r, 1, new QTableWidgetItem(o["subtip"].toString()));
        ui->tableInventar->setItem(r, 2, new QTableWidgetItem("1"));
        ui->tableInventar->setItem(r, 3, new QTableWidgetItem(o["stare"].toString()));
    }
}

void MainWindow::creeazaAngajat() {
    // Citeste campurile cu findChild — compatibil cu UI-ul colegului
    auto getField = [&](const QString& name) -> QString {
        if (auto* w = this->findChild<QLineEdit*>(name))
            return w->text().trimmed();
        return "";
    };
    auto clearField = [&](const QString& name) {
        if (auto* w = this->findChild<QLineEdit*>(name))
            w->clear();
    };

    // Numele exacte din Object Inspector-ul colegului
    QString username = getField("inputNumeAngajatNou");
    QString parola   = getField("inputParolaAngajatNou");
    QString nume     = getField("lineEdit");
    QString prenume  = getField("lineEdit_2");

    if (nume.isEmpty())    nume    = username;
    if (prenume.isEmpty()) prenume = "-";

    QString email = username.toLower().replace(" ", ".") + "@parc.ro";

    int idZona = 1;
    if (auto* combo = this->findChild<QComboBox*>("comboZonaAngajat"))
        idZona = combo->currentIndex() + 1;

    if (username.isEmpty()) { afiseazaEroare("Completati username-ul!"); return; }
    if (parola.length() < 4){ afiseazaEroare("Parola trebuie sa aiba minim 4 caractere!"); return; }

    QJsonObject cerere;
    cerere["actiune"]  = "register_angajat";
    cerere["username"] = username;
    cerere["parola"]   = parola;
    cerere["nume"]     = nume;
    cerere["prenume"]  = prenume;
    cerere["email"]    = email;
    cerere["id_zona"]  = idZona;

    QJsonObject raspuns = trimiteCerere(cerere);

    if (raspuns["succes"].toBool()) {
        clearField("inputNumeAngajatNou");
        clearField("inputParolaAngajatNou");
        clearField("lineEdit");
        clearField("lineEdit_2");

        ui->stackedWidget->setCurrentIndex(1);

        QMessageBox::information(this, "Cont creat",
                                 QString("Angajatul %1 %2 a fost inregistrat!\nUsername: %3\nEmail: %4")
                                     .arg(prenume, nume, username, email));
    } else {
        afiseazaEroare("Nu s-a putut crea contul:\n" + raspuns["eroare"].toString());
    }
}

void MainWindow::reincarcaAngajati() {
    incarcaAngajatiTabel();
    QMessageBox::information(this, "OK", "Lista a fost reincarcata.");
}

void MainWindow::adaugaTaskComplex() {
    QString desc = ui->inputTaskAdmin->text().trimmed();
    if (desc.isEmpty()) { afiseazaEroare("Completati descrierea taskului!"); return; }

    QList<QListWidgetItem*> sel = ui->listAngajatiTask->selectedItems();
    if (sel.isEmpty()) { afiseazaEroare("Alegeti un angajat din lista!"); return; }

    int idAngajat = sel.first()->data(Qt::UserRole).toInt();
    if (idAngajat <= 0) {
        afiseazaEroare("Angajatul selectat nu are ID valid.\nCreati mai intai un angajat.");
        return;
    }

    int idSesizare = ui->inputTaskAdmin->property("idSesizare").toInt();

    QJsonObject cerere;
    cerere["actiune"]    = (idSesizare > 0) ? "creeaza_task_din_sesizare" : "creeaza_task_daily";
    cerere["id_angajat"] = idAngajat;
    cerere["id_zona"]    = 1;
    cerere["descriere"]  = desc;
    cerere["cost"]       = 50.0;
    cerere["deadline"]   = QDate::currentDate().addDays(7).toString("yyyy-MM-dd");
    if (idSesizare > 0) cerere["id_sesizare"] = idSesizare;

    QJsonObject raspuns = trimiteCerere(cerere);

    if (raspuns["succes"].toBool()) {
        int idTask = raspuns["id_task"].toInt();
        int r = ui->tableTaskuriAdmin->rowCount();
        ui->tableTaskuriAdmin->insertRow(r);
        ui->tableTaskuriAdmin->setItem(r, 0, new QTableWidgetItem(QString::number(idTask)));
        ui->tableTaskuriAdmin->setItem(r, 1, new QTableWidgetItem(desc));
        ui->tableTaskuriAdmin->setItem(r, 2, new QTableWidgetItem(sel.first()->text()));
        ui->tableTaskuriAdmin->setItem(r, 3, new QTableWidgetItem("InProgress"));
        ui->inputTaskAdmin->clear();
        ui->inputTaskAdmin->setProperty("idSesizare", 0);
        QMessageBox::information(this, "Succes", "Task creat cu ID=" + QString::number(idTask));
    } else {
        afiseazaEroare(raspuns["eroare"].toString());
    }
}

void MainWindow::convertSesizare() {
    int row = ui->tableSesizariAdmin->currentRow();
    if (row == -1) { afiseazaEroare("Selectati o sesizare din lista!"); return; }

    auto* itemId   = ui->tableSesizariAdmin->item(row, 0);
    auto* itemDesc = ui->tableSesizariAdmin->item(row, 3);
    if (!itemId) { afiseazaEroare("Date sesizare invalide."); return; }

    ui->inputTaskAdmin->setText("REPARARE: " + (itemDesc ? itemDesc->text() : "problema"));
    ui->inputTaskAdmin->setProperty("idSesizare", itemId->text().toInt());
    ui->stackedWidget->setCurrentIndex(4);

    if (ui->listAngajatiTask->count() == 0) incarcaAngajati();

    QMessageBox::information(this, "Sesizare preluata",
                             "Sesizarea #" + itemId->text() + " preluata.\nSelectati un angajat si apasati 'Adauga Task'.");
}

void MainWindow::gestioneazaEvenimente() {
    QString numeEv = ui->inputNumeEveniment->text().trimmed();
    if (numeEv.isEmpty()) { afiseazaEroare("Introduceti numele evenimentului!"); return; }

    QJsonObject cerere;
    cerere["actiune"]     = "creeaza_eveniment";
    cerere["id_zona"]     = 1;
    cerere["tip"]         = "Altele";
    cerere["denumire"]    = numeEv;
    cerere["data"]        = ui->dateEveniment->date().toString("yyyy-MM-dd");
    cerere["ora_start"]   = "10:00";
    cerere["ora_sfarsit"] = "22:00";
    cerere["id_firma"]    = 3;

    QJsonObject raspuns = trimiteCerere(cerere);

    if (raspuns["succes"].toBool()) {
        int r = ui->tableEvenimenteAdmin->rowCount();
        ui->tableEvenimenteAdmin->insertRow(r);
        ui->tableEvenimenteAdmin->setItem(r, 0, new QTableWidgetItem(numeEv));
        ui->tableEvenimenteAdmin->setItem(r, 1, new QTableWidgetItem(ui->dateEveniment->date().toString("dd/MM/yyyy")));
        ui->tableEvenimenteAdmin->setItem(r, 2, new QTableWidgetItem(ui->comboLocatie->currentText()));
        ui->tableEvenimenteAdmin->setItem(r, 3, new QTableWidgetItem(
                                                    "Programat (ID=" + QString::number(raspuns["id_eveniment"].toInt()) + ")"));
        ui->inputNumeEveniment->clear();
    } else {
        afiseazaEroare(raspuns["eroare"].toString());
    }
}

void MainWindow::gestionareInventar(bool adauga) {
    if (adauga) {
        int     cant = ui->spinCantitate ? ui->spinCantitate->value() : 1;
        QString nume = ui->inputNumeMaterial ? ui->inputNumeMaterial->text().trimmed() : "Material";

        QJsonObject cerere;
        cerere["actiune"]        = "adauga_in_depozit";
        cerere["id_categorie"]   = 1;
        cerere["cantitate"]      = cant;
        cerere["pret"]           = 100.0;
        cerere["data_achizitie"] = QDate::currentDate().toString("yyyy-MM-dd");

        QJsonObject raspuns = trimiteCerere(cerere);
        if (raspuns["succes"].toBool()) {
            int r = ui->tableInventar->rowCount();
            ui->tableInventar->insertRow(r);
            ui->tableInventar->setItem(r, 0, new QTableWidgetItem(QString::number(raspuns["id_obiect"].toInt())));
            ui->tableInventar->setItem(r, 1, new QTableWidgetItem(nume));
            ui->tableInventar->setItem(r, 2, new QTableWidgetItem(QString::number(cant)));
            ui->tableInventar->setItem(r, 3, new QTableWidgetItem("Functional"));
            QMessageBox::information(this, "Succes", "Obiect adaugat in depozit.");
        } else {
            afiseazaEroare(raspuns["eroare"].toString());
        }
    } else {
        int row = ui->tableInventar->currentRow();
        if (row == -1) { afiseazaEroare("Selectati un obiect din inventar!"); return; }

        auto* itemId = ui->tableInventar->item(row, 0);
        if (!itemId) return;
        int idObiect = itemId->text().toInt();
        if (idObiect <= 0) { afiseazaEroare("ID obiect invalid."); return; }

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

void MainWindow::actiuniAngajat(int tip) {
    switch (tip) {

    case 1: {
        int r = ui->tableTaskuriAngajat->currentRow();
        if (r == -1) { afiseazaEroare("Selectati un task!"); break; }
        ui->tableTaskuriAngajat->setItem(r, 3, new QTableWidgetItem("In Lucru"));
        break;
    }

    case 2: {
        int r = ui->tableTaskuriAngajat->currentRow();
        if (r == -1) { afiseazaEroare("Selectati un task!"); break; }
        auto* itemId = ui->tableTaskuriAngajat->item(r, 0);
        if (!itemId) { afiseazaEroare("ID task invalid."); break; }

        int idTask = itemId->text().toInt();
        if (idTask <= 0) { afiseazaEroare("ID task invalid. Reincarca lista."); break; }

        QJsonObject cerere;
        cerere["actiune"] = "finalizeaza_task";
        cerere["id_task"] = idTask;
        QJsonObject raspuns = trimiteCerere(cerere);

        if (raspuns["succes"].toBool()) {
            ui->tableTaskuriAngajat->removeRow(r);
            QMessageBox::information(this, "Succes", "Task finalizat! Raport creat automat.");
        } else {
            afiseazaEroare(raspuns["eroare"].toString());
        }
        break;
    }

    case 3: {
        int r = ui->tableTaskuriAngajat->currentRow();
        if (r == -1) { afiseazaEroare("Selectati un task!"); break; }
        auto* itemId = ui->tableTaskuriAngajat->item(r, 0);
        if (!itemId) break;

        QString detalii = ui->textDetaliiRaport
                              ? ui->textDetaliiRaport->toPlainText().trimmed()
                              : "Raport de status.";
        if (detalii.isEmpty()) detalii = "Raport de status trimis de angajat.";

        QJsonObject cerere;
        cerere["actiune"]   = "creeaza_raport";
        cerere["id_task"]   = itemId->text().toInt();
        cerere["descriere"] = detalii;
        QJsonObject raspuns = trimiteCerere(cerere);

        if (raspuns["succes"].toBool()) {
            if (ui->textDetaliiRaport) ui->textDetaliiRaport->clear();
            QMessageBox::information(this, "Succes", "Raportul a fost trimis!");
        } else {
            afiseazaEroare(raspuns["eroare"].toString());
        }
        break;
    }

    case 4: {
        if (!ui->inputSesizareTeren) break;
        QString desc = ui->inputSesizareTeren->text().trimmed();
        if (desc.isEmpty()) { afiseazaEroare("Completati sesizarea!"); break; }

        QJsonObject cerere;
        cerere["actiune"]   = "creeaza_sesizare";
        cerere["id_zona"]   = 1;
        cerere["descriere"] = desc;
        QJsonObject raspuns = trimiteCerere(cerere);

        if (raspuns["succes"].toBool()) {
            ui->inputSesizareTeren->clear();
            QMessageBox::information(this, "Succes",
                                     "Sesizare trimisa! ID=" + QString::number(raspuns["id_sesizare"].toInt()));
        } else {
            afiseazaEroare(raspuns["eroare"].toString());
        }
        break;
    }

    case 5: {
        if (!ui->textSesizareGuest) break;
        QString desc = ui->textSesizareGuest->toPlainText().trimmed();
        if (desc.isEmpty()) { afiseazaEroare("Completati sesizarea!"); break; }

        QJsonObject cerere;
        cerere["actiune"]   = "creeaza_sesizare";
        cerere["id_zona"]   = 1;
        cerere["descriere"] = desc;
        QJsonObject raspuns = trimiteCerere(cerere);

        if (raspuns["succes"].toBool()) {
            ui->textSesizareGuest->clear();
            QMessageBox::information(this, "Sesizare trimisa",
                                     "Sesizarea a fost inregistrata!\nID: " +
                                         QString::number(raspuns["id_sesizare"].toInt()));
        } else {
            afiseazaEroare("Sesizarea nu a putut fi trimisa:\n" + raspuns["eroare"].toString());
        }
        break;
    }

    }
}