#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDate>
#include <QTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QTextEdit>
#include <QTimeEdit>
#include <QDateEdit>
#include <QTimer>

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

    // Set today's date on inventory date picker
    if (auto* d = this->findChild<QDateEdit*>("dateAchizitieInventar"))
        d->setDate(QDate::currentDate());

    for (auto* t : this->findChildren<QTableWidget*>()) {
        t->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        t->setSelectionBehavior(QAbstractItemView::SelectRows);
        t->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }

    auto connectBtn = [&](const QString& name, auto slot) {
        if (auto* btn = this->findChild<QPushButton*>(name))
            connect(btn, &QPushButton::clicked, this, slot);
    };

    // AUTH
    connectBtn("btnLogin",         &MainWindow::loginSistem);
    connectBtn("btnLogoutAdmin",   &MainWindow::logoutSistem);
    connectBtn("btnLogoutAngajat", &MainWindow::logoutSistem);
    connectBtn("btnLogoutGuest",   &MainWindow::logoutSistem);
    connectBtn("btnJoinGuest",     [=](){ ui->stackedWidget->setCurrentIndex(3); });

    // NAVIGARE ADMIN
    connectBtn("btnGoTasks",    [=](){
        ui->stackedWidget->setCurrentIndex(4);
        incarcaAngajati();
        incarcaItemsInventar();
        // CERINTA 4: reincarca taskurile din DB la fiecare navigare
        // astfel raman consistente chiar dupa logout/login
        incarcaTaskuriAdmin();
    });
    connectBtn("btnGoEvents",   [=](){ ui->stackedWidget->setCurrentIndex(5); });
    connectBtn("btnGoSesizari", [=](){ ui->stackedWidget->setCurrentIndex(6); incarcaSesizari(); });
    connectBtn("btnGoIstoric",  [=](){ ui->stackedWidget->setCurrentIndex(7); incarcaIstoric(); });
    connectBtn("btnGoInventar", [=](){
        ui->stackedWidget->setCurrentIndex(8);
        incarcaInventar();
        incarcaCategoriiInventar();
        incarcaFurnizori();
        incarcaInventarAngajati();
        // Set today's date on date picker
        if (auto* d = this->findChild<QDateEdit*>("dateAchizitieInventar"))
            d->setDate(QDate::currentDate());
    });
    connectBtn("btnGoCreareCont",[=](){
        if (auto* p = ui->stackedWidget->findChild<QWidget*>("pageCreareAngajat"))
            ui->stackedWidget->setCurrentWidget(p);
    });
    connectBtn("btnGoRapoarte", [=](){
        if (auto* p = ui->stackedWidget->findChild<QWidget*>("pageRapoarte"))
            ui->stackedWidget->setCurrentWidget(p);
        incarcaAngajatiRapoarte();
    });

    // BACK
    connectBtn("btnBackToDash",       [=](){ ui->stackedWidget->setCurrentIndex(1); });
    connectBtn("btnBackToDash_2",     [=](){ ui->stackedWidget->setCurrentIndex(1); });
    connectBtn("btnBackToDash_3",     [=](){ ui->stackedWidget->setCurrentIndex(1); });
    connectBtn("btnBackToDash_4",     [=](){ ui->stackedWidget->setCurrentIndex(1); });
    connectBtn("btnBackToDash_5",     [=](){ ui->stackedWidget->setCurrentIndex(1); });
    connectBtn("btnBackDinCreare",    [=](){ ui->stackedWidget->setCurrentIndex(1); });
    connectBtn("btnBackDinRapoarte",  [=](){ ui->stackedWidget->setCurrentIndex(1); });

    // ADMIN - TASKURI
    connectBtn("btnAdaugaTaskManual", &MainWindow::adaugaTaskComplex);
    connectBtn("btnConvertTask",      &MainWindow::convertSesizare);

    // ASOCIERE ITEM LA TASK (cerinta 1+2: selectie din BD cu id)
    connectBtn("btnAsociaItem", [=](){
        auto* combo    = this->findChild<QComboBox*>("comboItemInventar");
        auto* spinCant = this->findChild<QSpinBox*>("spinCantitateTask");
        if (!combo || !spinCant) return;

        // Index 0 = "(Fara item)" - optional, nu blocheaza
        if (combo->currentIndex() == 0) {
            QMessageBox::information(this, "Info",
                "Niciun item selectat. Task-ul ramane fara item asociat.");
            return;
        }

        int idObiect     = combo->currentData(Qt::UserRole).toInt();
        QString numeItem = combo->currentText().section(" (stoc:", 0, 0).trimmed();
        int cantitate    = spinCant->value();

        int idTask = 0;
        int rowSel = ui->tableTaskuriAdmin->currentRow();
        if (rowSel >= 0) {
            auto* it = ui->tableTaskuriAdmin->item(rowSel, 0);
            if (it) idTask = it->text().toInt();
        }
        if (idTask <= 0 && ui->tableTaskuriAdmin->rowCount() > 0) {
            auto* it = ui->tableTaskuriAdmin->item(
                ui->tableTaskuriAdmin->rowCount() - 1, 0);
            if (it) idTask = it->text().toInt();
        }
        if (idTask <= 0) {
            afiseazaEroare("Creati mai intai un task, apoi asociati item-ul.");
            return;
        }

        QJsonObject cerere;
        cerere["actiune"]   = "asociaza_item_task";
        cerere["id_obiect"] = idObiect;
        cerere["cantitate"] = cantitate;
        cerere["id_task"]   = idTask;

        QJsonObject raspuns = trimiteCerere(cerere);
        if (raspuns["succes"].toBool()) {
            combo->setCurrentIndex(0);
            spinCant->setValue(1);
            incarcaItemsInventar();
            incarcaInventar();
            incarcaInventarAngajati();
            QMessageBox::information(this, "Succes",
                QString("Item '%1' x%2 asociat la task #%3!")
                    .arg(numeItem).arg(cantitate).arg(idTask));
        } else {
            afiseazaEroare(raspuns["eroare"].toString());
        }
    });

    // ADMIN - SESIZARI
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
        } else afiseazaEroare(r["eroare"].toString());
    });

    // ADMIN - EVENIMENTE
    connectBtn("btnAprobaEveniment", &MainWindow::gestioneazaEvenimente);

    // ADMIN - INVENTAR (CERINTA 2+3)
    connectBtn("btnAddInventar",    [=](){ gestionareInventar(true);  });
    connectBtn("btnUseInventar",    [=](){ gestionareInventar(false); });


    // ADMIN - ANGAJATI
    connectBtn("btnSalveazaAngajat", &MainWindow::creeazaAngajat);

    // RAPOARTE - click pe angajat
    if (auto* listaR = this->findChild<QListWidget*>("listAngajatiRapoarte")) {
        connect(listaR, &QListWidget::currentRowChanged, this, [=](int) {
            if (auto* item = listaR->currentItem())
                incarcaRapoarteAngajat(item->data(Qt::UserRole).toInt());
        });
    }


    connectBtn("btnFinishTask",            [=](){ actiuniAngajat(2); });
    connectBtn("btnSendReport",            [=](){ actiuniAngajat(3); }); // CERINTA 6: auto-select
    connectBtn("btnSendSesizareTeren",     [=](){ actiuniAngajat(4); });
    connectBtn("btnTrimiteSesizareaGuest", [=](){ actiuniAngajat(5); });

    // CERINTA 9: Timer pentru actualizare automata istoric la admin
    m_timerIstoric = new QTimer(this);
    m_timerIstoric->setInterval(30000); // 30 secunde
    connect(m_timerIstoric, &QTimer::timeout, this, [=](){
        if (m_rolCurent == "Admin" &&
            ui->stackedWidget->currentIndex() == 7)
            incarcaIstoric();
    });
    m_timerIstoric->start();
}

MainWindow::~MainWindow() {
    // CERINTA 7: Garanteaza logout in logger chiar daca serverul e oprit
    if (m_idUserCurent > 0) {
        if (m_socket->state() != QAbstractSocket::ConnectedState) {
            m_socket->connectToHost(SERVER_IP, SERVER_PORT);
            m_socket->waitForConnected(1000);
        }
        if (m_socket->state() == QAbstractSocket::ConnectedState) {
            QJsonObject cerere;
            cerere["actiune"] = "logout";
            m_socket->write(QJsonDocument(cerere).toJson(QJsonDocument::Compact) + "\n");
            m_socket->waitForBytesWritten(1000);
        }
        m_socket->disconnectFromHost();
    }
    delete ui;
}

// ============================================================
// RETEA
// ============================================================
QJsonObject MainWindow::trimiteCerere(const QJsonObject& cerere) {
    // CERINTA 7: Reconecteaza inainte de fiecare cerere
    if (m_socket->state() != QAbstractSocket::ConnectedState) {
        m_socket->connectToHost(SERVER_IP, SERVER_PORT);
        if (!m_socket->waitForConnected(2000))
            return {{"succes", false},
                    {"eroare", QString("Server indisponibil (%1:%2)")
                        .arg(SERVER_IP).arg(SERVER_PORT)}};
    }

    m_socket->write(QJsonDocument(cerere).toJson(QJsonDocument::Compact) + "\n");
    if (!m_socket->waitForBytesWritten(3000))
        return {{"succes", false}, {"eroare", "Eroare la trimiterea cererii"}};

    QByteArray bufferRaw;
    while (!bufferRaw.contains('\n')) {
        if (!m_socket->waitForReadyRead(5000))
            return {{"succes", false}, {"eroare", "Timeout: serverul nu a raspuns"}};
        bufferRaw += m_socket->readAll();
    }

    QByteArray linie = bufferRaw.left(bufferRaw.indexOf('\n')).trimmed();
    QJsonParseError parseErr;
    QJsonDocument doc = QJsonDocument::fromJson(
        QString::fromUtf8(linie).toUtf8(), &parseErr);

    if (doc.isNull())
        return {{"succes", false},
                {"eroare", "Raspuns invalid: " + parseErr.errorString()}};
    return doc.object();
}

void MainWindow::onEroareConectare(QAbstractSocket::SocketError) {}
void MainWindow::onDatePrimite() {}
void MainWindow::afiseazaEroare(const QString& mesaj) {
    QMessageBox::warning(this, "Eroare", mesaj);
}

// ============================================================
// AUTH
// ============================================================
void MainWindow::loginSistem() {
    QString user        = ui->userInput->text().trimmed();
    QString parola      = ui->passInput->text().trimmed();
    QString rolSelectat = ui->roleCombo ? ui->roleCombo->currentText() : "";

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
        QString rolDB = raspuns["rol"].toString();

        bool rolCorect = (rolSelectat == "Administrator" && rolDB == "Admin") ||
                         (rolSelectat == "Angajat"       && rolDB == "Angajat");

        if (!rolCorect) {
            trimiteCerere({{"actiune", "logout"}});
            afiseazaEroare(rolDB == "Admin"
                ? "Acest cont este de Administrator.\nSelectati 'Administrator' din lista."
                : "Acest cont este de Angajat.\nSelectati 'Angajat' din lista.");
            return;
        }

        m_rolCurent    = rolDB;
        m_idUserCurent = raspuns["id_user"].toInt();

        if (m_rolCurent == "Admin") {
            ui->stackedWidget->setCurrentIndex(1);
        } else if (m_rolCurent == "Angajat") {
            ui->stackedWidget->setCurrentIndex(2);
            incarcaTaskuriAngajat();
            incarcaIstoricAngajat();
            incarcaInventarMeu();
        }
    } else {
        afiseazaEroare(raspuns["eroare"].toString());
    }
}

void MainWindow::logoutSistem() {
    // CERINTA 7: Trimite logout si asteapta confirmare
    if (m_socket->state() != QAbstractSocket::ConnectedState) {
        m_socket->connectToHost(SERVER_IP, SERVER_PORT);
        m_socket->waitForConnected(2000);
    }
    if (m_socket->state() == QAbstractSocket::ConnectedState)
        trimiteCerere({{"actiune", "logout"}});

    m_rolCurent    = "";
    m_idUserCurent = -1;
    ui->userInput->clear();
    ui->passInput->clear();
    ui->stackedWidget->setCurrentIndex(0);
}

// ============================================================
// INCARCARE DATE
// ============================================================
void MainWindow::incarcaTaskuriAngajat() {
    if (m_idUserCurent <= 0) return;
    QJsonObject raspuns = trimiteCerere({{"actiune", "get_taskuri_mele"}});
    if (!raspuns["succes"].toBool()) return;

    this->findChild<QTableWidget*>("tableTaskuriAngajat")->setRowCount(0);
    m_idTaskCurentAngajat = -1;

    QJsonArray taskuri = raspuns["date"].toArray();
    for (const QJsonValue& v : taskuri) {
        QJsonObject t = v.toObject();
        int     id   = t["id"].toInt();
        QString tip  = t["tip"].toString();
        QString desc = t["descriere"].toString();
        QString stat = t["status"].toString();

        // CERINTA 6: retine primul task activ
        if (m_idTaskCurentAngajat == -1 && stat == "InProgress")
            m_idTaskCurentAngajat = id;

        int r    = this->findChild<QTableWidget*>("tableTaskuriAngajat")->rowCount();
        int cols = this->findChild<QTableWidget*>("tableTaskuriAngajat")->columnCount();
        this->findChild<QTableWidget*>("tableTaskuriAngajat")->insertRow(r);
        this->findChild<QTableWidget*>("tableTaskuriAngajat")->setItem(r, 0, new QTableWidgetItem(QString::number(id)));
        if (cols >= 5) {
            this->findChild<QTableWidget*>("tableTaskuriAngajat")->setItem(r, 1, new QTableWidgetItem(desc));
            this->findChild<QTableWidget*>("tableTaskuriAngajat")->setItem(r, 2, new QTableWidgetItem("Zona 1"));
            this->findChild<QTableWidget*>("tableTaskuriAngajat")->setItem(r, 3, new QTableWidgetItem(tip));
            this->findChild<QTableWidget*>("tableTaskuriAngajat")->setItem(r, 4, new QTableWidgetItem(stat));
        } else {
            if (cols > 1) this->findChild<QTableWidget*>("tableTaskuriAngajat")->setItem(r, 1, new QTableWidgetItem(tip));
            if (cols > 2) this->findChild<QTableWidget*>("tableTaskuriAngajat")->setItem(r, 2, new QTableWidgetItem(desc));
            if (cols > 3) this->findChild<QTableWidget*>("tableTaskuriAngajat")->setItem(r, 3, new QTableWidgetItem(stat));
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

void MainWindow::incarcaAngajatiTabel() {
    QJsonObject raspuns = trimiteCerere({{"actiune", "get_angajati"}});
    if (!raspuns["succes"].toBool()) {
        afiseazaEroare("Nu am putut incarca angajatii:\n" + raspuns["eroare"].toString());
        return;
    }
    auto* tabel = this->findChild<QTableWidget*>("tableAngajati");
    if (!tabel) return;
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
        ui->tableInventar->setItem(r, 2, new QTableWidgetItem(QString::number(o["cantitate"].toInt())));
        ui->tableInventar->setItem(r, 3, new QTableWidgetItem(o["stare"].toString()));
    }
}

// CERINTA 2+3: Incarca categorii si furnizori in combouri
void MainWindow::incarcaCategoriiInventar() {
    auto* combo = this->findChild<QComboBox*>("comboCategorieInventar");
    if (!combo) return;
    QJsonObject raspuns = trimiteCerere({{"actiune", "get_categorii_obiecte"}});
    combo->clear();
    combo->addItem("(Selecteaza categorie...)");
    if (!raspuns["succes"].toBool()) return;
    for (const QJsonValue& v : raspuns["date"].toArray()) {
        QJsonObject c = v.toObject();
        QString label = c["tipGeneral"].toString() + " / " + c["subtip"].toString();
        combo->addItem(label);
        combo->setItemData(combo->count() - 1, c["id"].toInt(), Qt::UserRole);
    }
}

void MainWindow::incarcaFurnizori() {
    auto* combo = this->findChild<QComboBox*>("comboFurnizorInventar");
    if (!combo) return;
    QJsonObject raspuns = trimiteCerere({{"actiune", "get_furnizori"}});
    combo->clear();
    combo->addItem("(Selecteaza furnizor...)");
    if (!raspuns["succes"].toBool()) return;
    for (const QJsonValue& v : raspuns["date"].toArray()) {
        QJsonObject f = v.toObject();
        combo->addItem(f["nume"].toString());
        combo->setItemData(combo->count() - 1, f["id"].toInt(), Qt::UserRole);
    }
}

void MainWindow::incarcaItemsInventar() {
    auto* combo = this->findChild<QComboBox*>("comboItemInventar");
    if (!combo) return;
    QJsonObject raspuns = trimiteCerere({{"actiune", "get_inventar_depozit"}});
    combo->clear();
    combo->addItem("(Selecteaza item...)");
    if (!raspuns["succes"].toBool()) return;
    for (const QJsonValue& v : raspuns["date"].toArray()) {
        QJsonObject o = v.toObject();
        QString label = o["subtip"].toString() +
                        " (stoc: " + QString::number(o["cantitate"].toInt()) + ")";
        combo->addItem(label);
        combo->setItemData(combo->count() - 1, o["id"].toInt(), Qt::UserRole);
    }
}

// CERINTA 9: Istoric admin cu refresh automat
void MainWindow::incarcaInventarAngajati() {
    auto* tabel = this->findChild<QTableWidget*>("tableInventarAngajati");
    if (!tabel) return;

    QJsonObject raspuns = trimiteCerere({{"actiune", "get_inventar_angajati"}});
    tabel->setRowCount(0);
    if (!raspuns["succes"].toBool()) return;

    for (const QJsonValue& v : raspuns["date"].toArray()) {
        QJsonObject o = v.toObject();
        int r = tabel->rowCount();
        tabel->insertRow(r);
        tabel->setItem(r, 0, new QTableWidgetItem(QString::number(o["id"].toInt())));
        tabel->setItem(r, 1, new QTableWidgetItem(o["angajat"].toString()));
        tabel->setItem(r, 2, new QTableWidgetItem(o["subtip"].toString()));
        tabel->setItem(r, 3, new QTableWidgetItem("Task #" + o["task"].toString()));
        tabel->setItem(r, 4, new QTableWidgetItem(o["stare"].toString()));
    }
}

void MainWindow::incarcaInventarMeu() {
    auto* tabel = this->findChild<QTableWidget*>("tableInventarMeu");
    if (!tabel) return;

    QJsonObject raspuns = trimiteCerere({{"actiune", "get_inventar_meu"}});
    tabel->setRowCount(0);
    if (!raspuns["succes"].toBool()) return;

    for (const QJsonValue& v : raspuns["date"].toArray()) {
        QJsonObject o = v.toObject();
        int r = tabel->rowCount();
        tabel->insertRow(r);
        tabel->setItem(r, 0, new QTableWidgetItem(
            QString::number(o["idGestiune"].toInt())));
        tabel->setItem(r, 1, new QTableWidgetItem(o["subtip"].toString()));
        tabel->setItem(r, 2, new QTableWidgetItem(
            "Task #" + QString::number(o["idTask"].toInt())));
        tabel->setItem(r, 3, new QTableWidgetItem(o["stareGestiune"].toString()));
    }
}

void MainWindow::incarcaIstoric() {
    QJsonObject raspuns = trimiteCerere({{"actiune", "get_istoric_taskuri"}});
    if (!raspuns["succes"].toBool()) return;

    auto* tabel = this->findChild<QTableWidget*>("tableIstoric");
    auto* combo = this->findChild<QComboBox*>("comboFiltruIstoric");
    if (!tabel) return;

    QJsonArray date = raspuns["date"].toArray();

    if (combo && m_rolCurent == "Admin") {
        QString selectat = combo->currentText();
        combo->blockSignals(true);
        combo->clear();
        combo->addItem("Toti angajatii");
        QStringList unici;
        for (const QJsonValue& v : date) {
            QString ang = v.toObject()["angajat"].toString();
            if (!ang.isEmpty() && !unici.contains(ang)) unici.append(ang);
        }
        for (const QString& a : unici) combo->addItem(a);
        connect(combo, &QComboBox::currentTextChanged, this, [=](){ incarcaIstoric(); });
        combo->blockSignals(false);
        int idx = combo->findText(selectat);
        if (idx >= 0) combo->setCurrentIndex(idx);
    }

    QString filtru = (combo && combo->currentIndex() > 0) ? combo->currentText() : "";

    if (tabel->columnCount() > 3)
        tabel->setHorizontalHeaderItem(3, new QTableWidgetItem(
            m_rolCurent == "Admin" ? "Angajat" : "Status"));

    tabel->setRowCount(0);
    for (const QJsonValue& v : date) {
        QJsonObject t    = v.toObject();
        QString angajat  = t["angajat"].toString();
        if (!filtru.isEmpty() && angajat != filtru) continue;

        int r    = tabel->rowCount();
        int cols = tabel->columnCount();
        tabel->insertRow(r);
        if (cols > 0) tabel->setItem(r, 0, new QTableWidgetItem(t["data"].toString()));
        if (cols > 1) tabel->setItem(r, 1, new QTableWidgetItem(t["tip"].toString()));
        if (cols > 2) tabel->setItem(r, 2, new QTableWidgetItem(t["descriere"].toString()));
        if (cols > 3) tabel->setItem(r, 3, new QTableWidgetItem(
            m_rolCurent == "Admin" ? angajat : t["status"].toString()));
    }
}

// CERINTA 5+8: Istoric angajat cu ore lucrate
void MainWindow::incarcaIstoricAngajat() {
    auto* tabel = this->findChild<QTableWidget*>("tableIstoricAngajat");
    if (!tabel) return;

    QJsonObject raspuns = trimiteCerere({{"actiune", "get_istoric_taskuri"}});
    if (!raspuns["succes"].toBool()) return;

    tabel->setRowCount(0);
    for (const QJsonValue& v : raspuns["date"].toArray()) {
        QJsonObject t = v.toObject();
        int r = tabel->rowCount();
        tabel->insertRow(r);
        tabel->setItem(r, 0, new QTableWidgetItem(t["data"].toString()));
        tabel->setItem(r, 1, new QTableWidgetItem(t["descriere"].toString()));
        tabel->setItem(r, 2, new QTableWidgetItem(t["tip"].toString()));
        // CERINTA 8: ore lucrate = diff intre data_creare si data_finalizare
        QString oreLucrate = t["oreLucrate"].toString();
        tabel->setItem(r, 3, new QTableWidgetItem(oreLucrate.isEmpty() ? "-" : oreLucrate));
    }
}

// ============================================================
// CREARE ANGAJAT
// ============================================================
void MainWindow::creeazaAngajat() {
    auto getField = [&](const QString& name) -> QString {
        if (auto* w = this->findChild<QLineEdit*>(name)) return w->text().trimmed();
        return "";
    };
    auto clearField = [&](const QString& name) {
        if (auto* w = this->findChild<QLineEdit*>(name)) w->clear();
    };

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

void MainWindow::reincarcaAngajati() { incarcaAngajatiTabel(); }

// ============================================================
// ADMIN - TASKURI
// ============================================================
void MainWindow::incarcaTaskuriAdmin() {
    // CERINTA 4: Incarca taskurile active din DB - persista dupa logout
    QJsonObject raspuns = trimiteCerere({{"actiune", "get_taskuri_active_admin"}});
    if (!raspuns["succes"].toBool()) return;

    ui->tableTaskuriAdmin->setRowCount(0);
    for (const QJsonValue& v : raspuns["date"].toArray()) {
        QJsonObject t = v.toObject();
        int r = ui->tableTaskuriAdmin->rowCount();
        ui->tableTaskuriAdmin->insertRow(r);
        ui->tableTaskuriAdmin->setItem(r, 0, new QTableWidgetItem(QString::number(t["id"].toInt())));
        ui->tableTaskuriAdmin->setItem(r, 1, new QTableWidgetItem(t["descriere"].toString()));
        ui->tableTaskuriAdmin->setItem(r, 2, new QTableWidgetItem(t["numeAngajat"].toString()));
        ui->tableTaskuriAdmin->setItem(r, 3, new QTableWidgetItem(t["status"].toString()));
    }
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
        incarcaItemsInventar();
        QMessageBox::information(this, "Succes",
            "Task creat cu ID=" + QString::number(idTask));
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
        "Sesizarea #" + itemId->text() + " preluata.\nSelectati angajat si apasati 'Adauga Task'.");
}

// ============================================================
// CERINTA 1: ADMIN - EVENIMENTE cu verificare suprapunere
// ============================================================
void MainWindow::gestioneazaEvenimente() {
    QString numeEv = ui->inputNumeEveniment->text().trimmed();
    if (numeEv.isEmpty()) { afiseazaEroare("Introduceti numele evenimentului!"); return; }

    auto* timeStart   = this->findChild<QTimeEdit*>("timeStartEveniment");
    auto* timeSfarsit = this->findChild<QTimeEdit*>("timeSfarsitEveniment");

    QString oraStart   = timeStart   ? timeStart->time().toString("HH:mm")   : "10:00";
    QString oraSfarsit = timeSfarsit ? timeSfarsit->time().toString("HH:mm") : "22:00";

    // Verifica ore valide
    if (timeStart && timeSfarsit &&
        timeStart->time() >= timeSfarsit->time()) {
        afiseazaEroare("Ora de sfarsit trebuie sa fie dupa ora de start!");
        return;
    }

    QJsonObject cerere;
    cerere["actiune"]     = "creeaza_eveniment";
    cerere["id_zona"]     = 1;
    cerere["tip"]         = "Altele";
    cerere["denumire"]    = numeEv;
    cerere["data"]        = ui->dateEveniment->date().toString("yyyy-MM-dd");
    cerere["ora_start"]   = oraStart;
    cerere["ora_sfarsit"] = oraSfarsit;
    cerere["id_firma"]    = 3;

    QJsonObject raspuns = trimiteCerere(cerere);
    if (raspuns["succes"].toBool()) {
        int r = ui->tableEvenimenteAdmin->rowCount();
        ui->tableEvenimenteAdmin->insertRow(r);
        ui->tableEvenimenteAdmin->setItem(r, 0, new QTableWidgetItem(numeEv));
        ui->tableEvenimenteAdmin->setItem(r, 1, new QTableWidgetItem(
            ui->dateEveniment->date().toString("dd/MM/yyyy") +
            " " + oraStart + "-" + oraSfarsit));
        ui->tableEvenimenteAdmin->setItem(r, 2, new QTableWidgetItem(
            ui->comboLocatie->currentText()));
        ui->tableEvenimenteAdmin->setItem(r, 3, new QTableWidgetItem(
            "Programat (ID=" + QString::number(raspuns["id_eveniment"].toInt()) + ")"));
        ui->inputNumeEveniment->clear();
    } else {
        // CERINTA 1: eroare suprapunere vine de la triggerul SQL din backend
        afiseazaEroare(raspuns["eroare"].toString());
    }
}

// ============================================================
// CERINTE 2+3: ADMIN - INVENTAR cu categorii si furnizori
// ============================================================
void MainWindow::gestionareInventar(bool adauga) {
    if (adauga) {
        auto* comboCateg = this->findChild<QComboBox*>("comboCategorieInventar");
        auto* comboFurn  = this->findChild<QComboBox*>("comboFurnizorInventar");
        auto* spinCant   = this->findChild<QSpinBox*>("spinCantitate");
        auto* spinPret   = this->findChild<QDoubleSpinBox*>("spinPretInventar");
        auto* dateAchiz  = this->findChild<QDateEdit*>("dateAchizitieInventar");

        if (!comboCateg || !spinCant) return;

        if (comboCateg->currentIndex() == 0) {
            afiseazaEroare("Selectati o categorie de obiect!");
            return;
        }
        if (!comboFurn || comboFurn->currentIndex() == 0) {
            afiseazaEroare("Selectati un furnizor!");
            return;
        }

        int idCategorie = comboCateg->currentData(Qt::UserRole).toInt();
        int idFurnizor  = comboFurn->currentData(Qt::UserRole).toInt();
        int cantitate   = spinCant->value();
        double pret     = spinPret ? spinPret->value() : 100.0;
        QString data    = dateAchiz
                          ? dateAchiz->date().toString("yyyy-MM-dd")
                          : QDate::currentDate().toString("yyyy-MM-dd");

        QJsonObject cerere;
        cerere["actiune"]        = "adauga_in_depozit";
        cerere["id_categorie"]   = idCategorie;
        cerere["id_furnizor"]    = idFurnizor;
        cerere["cantitate"]      = cantitate;
        cerere["pret"]           = pret;
        cerere["data_achizitie"] = data;

        QJsonObject raspuns = trimiteCerere(cerere);
        if (raspuns["succes"].toBool()) {
            comboCateg->setCurrentIndex(0);
            comboFurn->setCurrentIndex(0);
            if (spinCant) spinCant->setValue(1);
            if (spinPret) spinPret->setValue(100.0);
            incarcaInventar();
            incarcaItemsInventar();
            incarcaInventarAngajati();
            QMessageBox::information(this, "Succes",
                "Obiect adaugat in depozit. ID=" +
                QString::number(raspuns["id_obiect"].toInt()));
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
            incarcaItemsInventar();
            QMessageBox::information(this, "Succes", "Obiect mutat in junk.");
        } else {
            afiseazaEroare(raspuns["eroare"].toString());
        }
    }
}

// ============================================================
// ANGAJAT & GUEST
// ============================================================
void MainWindow::actiuniAngajat(int tip) {
    switch (tip) {


    case 2: {
        auto* tabelTask = this->findChild<QTableWidget*>("tableTaskuriAngajat");
        int r = tabelTask ? tabelTask->currentRow() : -1;
        if (r == -1) { afiseazaEroare("Selectati un task!"); break; }

        auto* itemId = tabelTask->item(r, 0);
        if (!itemId) { afiseazaEroare("ID task invalid."); break; }
        int idTask = itemId->text().toInt();
        if (idTask <= 0) { afiseazaEroare("ID task invalid. Reincarca lista."); break; }

        // CERINTA 1: Verifica statusul - nu permite finalizarea unui task deja Done
        int colStatus = tabelTask->columnCount() >= 5 ? 4 : 3;
        auto* itemStatus = tabelTask->item(r, colStatus);
        if (itemStatus) {
            QString status = itemStatus->text();
            if (status == "Done" || status == "Anulat") {
                afiseazaEroare("Acest task este deja " + status + " si nu mai poate fi finalizat.");
                break;
            }
        }

        QJsonObject cerere;
        cerere["actiune"] = "finalizeaza_task";
        cerere["id_task"] = idTask;
        QJsonObject raspuns = trimiteCerere(cerere);
        if (raspuns["succes"].toBool()) {
            tabelTask->removeRow(r);
            m_idTaskCurentAngajat = -1;
            incarcaIstoricAngajat();
            incarcaInventarMeu();
            QMessageBox::information(this, "Succes",
                "Task finalizat! Raport creat automat.Itemele alocate au fost trimise in Junk.Task-ul apare acum in Istoricul tau.");
        } else {
            afiseazaEroare(raspuns["eroare"].toString());
        }
        break;
    }

    case 3: { // CERINTA 6: Auto-select task curent
        // Nu mai cerem selectie - folosim m_idTaskCurentAngajat
        int idTask = m_idTaskCurentAngajat;

        // Fallback: primul task din tabel
        if (idTask <= 0 && this->findChild<QTableWidget*>("tableTaskuriAngajat")->rowCount() > 0) {
            auto* it = this->findChild<QTableWidget*>("tableTaskuriAngajat")->item(0, 0);
            if (it) idTask = it->text().toInt();
        }

        if (idTask <= 0) {
            afiseazaEroare("Nu ai niciun task activ de raportat!");
            break;
        }

        QString detalii = this->findChild<QTextEdit*>("textDetaliiRaport")
                          ? this->findChild<QTextEdit*>("textDetaliiRaport")->toPlainText().trimmed()
                          : "";
        if (detalii.isEmpty()) {
            afiseazaEroare("Completati detaliile raportului!");
            break;
        }

        QJsonObject cerere;
        cerere["actiune"]   = "creeaza_raport";
        cerere["id_task"]   = idTask;
        cerere["descriere"] = detalii;
        QJsonObject raspuns = trimiteCerere(cerere);
        if (raspuns["succes"].toBool()) {
            if (this->findChild<QTextEdit*>("textDetaliiRaport")) this->findChild<QTextEdit*>("textDetaliiRaport")->clear();
            QMessageBox::information(this, "Succes", "Raportul a fost trimis!");
        } else {
            afiseazaEroare(raspuns["eroare"].toString());
        }
        break;
    }

    case 4: {
        if (!this->findChild<QLineEdit*>("inputSesizareTeren")) break;
        QString desc = this->findChild<QLineEdit*>("inputSesizareTeren")->text().trimmed();
        if (desc.isEmpty()) { afiseazaEroare("Completati sesizarea!"); break; }
        QJsonObject cerere;
        cerere["actiune"]   = "creeaza_sesizare";
        cerere["id_zona"]   = 1;
        cerere["descriere"] = desc;
        QJsonObject raspuns = trimiteCerere(cerere);
        if (raspuns["succes"].toBool()) {
            this->findChild<QLineEdit*>("inputSesizareTeren")->clear();
            QMessageBox::information(this, "Succes",
                "Sesizare trimisa! ID=" + QString::number(raspuns["id_sesizare"].toInt()));
        } else afiseazaEroare(raspuns["eroare"].toString());
        break;
    }

    case 5: {
        if (!this->findChild<QTextEdit*>("textSesizareGuest")) break;
        QString desc = this->findChild<QTextEdit*>("textSesizareGuest")->toPlainText().trimmed();
        if (desc.isEmpty()) { afiseazaEroare("Completati sesizarea!"); break; }
        QJsonObject cerere;
        cerere["actiune"]   = "creeaza_sesizare";
        cerere["id_zona"]   = 1;
        cerere["descriere"] = desc;
        QJsonObject raspuns = trimiteCerere(cerere);
        if (raspuns["succes"].toBool()) {
            this->findChild<QTextEdit*>("textSesizareGuest")->clear();
            QMessageBox::information(this, "Sesizare trimisa", "Sesizarea a fost inregistrata!\nID: " +
                QString::number(raspuns["id_sesizare"].toInt()));
        } else afiseazaEroare(raspuns["eroare"].toString());
        break;
    }
    }
}

// ============================================================
// RAPOARTE ANGAJATI
// ============================================================
void MainWindow::incarcaAngajatiRapoarte() {
    auto* lista = this->findChild<QListWidget*>("listAngajatiRapoarte");
    if (!lista) return;
    lista->clear();
    QJsonObject raspuns = trimiteCerere({{"actiune", "get_angajati_cu_rapoarte"}});
    if (!raspuns["succes"].toBool()) {
        lista->addItem("(Eroare la incarcare)");
        return;
    }
    QJsonArray angajati = raspuns["date"].toArray();
    if (angajati.isEmpty()) {
        lista->addItem("(Niciun angajat nu a trimis rapoarte)");
        return;
    }
    for (const QJsonValue& v : angajati) {
        QJsonObject a = v.toObject();
        auto* item = new QListWidgetItem(
            a["nume"].toString() + "  (" +
            QString::number(a["nrRapoarte"].toInt()) + " rapoarte)");
        item->setData(Qt::UserRole, a["id"].toInt());
        lista->addItem(item);
    }
    if (auto* lbl = this->findChild<QLabel*>("labelRapoarteAngajat"))
        lbl->setText("Selectati un angajat din stanga pentru a vedea rapoartele");
}

void MainWindow::incarcaRapoarteAngajat(int idAngajat) {
    if (idAngajat <= 0) return;
    QJsonObject cerere;
    cerere["actiune"]    = "get_rapoarte_angajat";
    cerere["id_angajat"] = idAngajat;
    QJsonObject raspuns  = trimiteCerere(cerere);
    auto* tabel = this->findChild<QTableWidget*>("tableRapoarte");
    if (!tabel) return;
    tabel->setRowCount(0);
    if (!raspuns["succes"].toBool()) {
        afiseazaEroare("Nu am putut incarca rapoartele:\n" + raspuns["eroare"].toString());
        return;
    }
    QJsonArray rapoarte = raspuns["date"].toArray();
    if (auto* lbl = this->findChild<QLabel*>("labelRapoarteAngajat"))
        lbl->setText(QString::number(rapoarte.size()) + " rapoarte gasite");
    for (const QJsonValue& v : rapoarte) {
        QJsonObject r = v.toObject();
        int row = tabel->rowCount();
        tabel->insertRow(row);
        tabel->setItem(row, 0, new QTableWidgetItem(r["task"].toString()));
        tabel->setItem(row, 1, new QTableWidgetItem(r["data"].toString()));
        tabel->setItem(row, 2, new QTableWidgetItem(r["tip"].toString()));
        tabel->setItem(row, 3, new QTableWidgetItem(r["descriere"].toString()));
    }
}