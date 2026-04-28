#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    // --- 1. POPULARE DATE ---
    QStringList parcuri = {"Herastrau", "Cismigiu", "Sebastian", "Carol", "Tineret", "Drumul Taberei"};
    QStringList zone = {"Lac", "Alee Principala", "Zona Caini", "Scena", "Loc de joaca"};
    QStringList angajati = {"Dogaru Sebastian", "Constantinescu Mihai", "Ciocan Andrei", "Dumitru Rares", "Jitaru Tudor", "Vidan Andrei"};

    if(ui->roleCombo) { ui->roleCombo->clear(); ui->roleCombo->addItems({"Administrator", "Angajat"}); }
    if(ui->comboParcTask) { ui->comboParcTask->clear(); ui->comboParcTask->addItems(parcuri); }
    if(ui->comboZonaTask) { ui->comboZonaTask->clear(); ui->comboZonaTask->addItems(zone); }
    if(ui->listAngajatiTask) {
        ui->listAngajatiTask->clear();
        ui->listAngajatiTask->addItems(angajati);
        ui->listAngajatiTask->setSelectionMode(QAbstractItemView::MultiSelection);
    }

    // Populare pentru pagina de Evenimente (bazat pe noul screenshot)
    if(ui->comboLocatie) { ui->comboLocatie->clear(); ui->comboLocatie->addItems(parcuri); }
    if(ui->comboParcGuest) { ui->comboParcGuest->clear(); ui->comboParcGuest->addItems(parcuri); }
    if(ui->comboZonaGuest) { ui->comboZonaGuest->clear(); ui->comboZonaGuest->addItems(zone); }

    // Stil Tabele
    QList<QTableWidget*> tables = this->findChildren<QTableWidget*>();
    for(auto t : tables) {
        t->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        t->setSelectionBehavior(QAbstractItemView::SelectRows);
    }

    // --- 2. CONEXIUNI MANUALE ---
    auto connectBtn = [&](QString name, auto slot) {
        QPushButton* btn = this->findChild<QPushButton*>(name);
        if(btn) connect(btn, &QPushButton::clicked, this, slot);
    };

    connectBtn("btnLogin", &MainWindow::loginSistem);
    connectBtn("btnLogoutAdmin", &MainWindow::logoutSistem);
    connectBtn("btnLogoutAngajat", &MainWindow::logoutSistem);
    connectBtn("btnLogoutGuest", &MainWindow::logoutSistem);
    connectBtn("btnJoinGuest", [=](){ ui->stackedWidget->setCurrentIndex(3); });

    // Navigare Dashboard
    connectBtn("btnGoTasks", [=](){ ui->stackedWidget->setCurrentIndex(4); });
    connectBtn("btnGoEvents", [=](){ ui->stackedWidget->setCurrentIndex(5); });
    connectBtn("btnGoSesizari", [=](){ ui->stackedWidget->setCurrentIndex(6); });
    connectBtn("btnGoIstoric", [=](){ ui->stackedWidget->setCurrentIndex(7); });
    connectBtn("btnGoInventar", [=](){ ui->stackedWidget->setCurrentIndex(8); });

    // TOATE BUTOANELE TALE DE BACK (Redenumite ca în screenshot)
    connectBtn("btnBackToDash", [=](){ ui->stackedWidget->setCurrentIndex(1); });
    connectBtn("btnBackToDash_2", [=](){ ui->stackedWidget->setCurrentIndex(1); });
    connectBtn("btnBackToDash_3", [=](){ ui->stackedWidget->setCurrentIndex(1); });
    connectBtn("btnBackToDash_4", [=](){ ui->stackedWidget->setCurrentIndex(1); });
    connectBtn("btnBackToDash_5", [=](){ ui->stackedWidget->setCurrentIndex(1); });

    // Actiuni Admin
    connectBtn("btnAdaugaTaskManual", &MainWindow::adaugaTaskComplex);
    connectBtn("btnConvertTask", &MainWindow::convertSesizare);
    connectBtn("btnAprobaEveniment", &MainWindow::gestioneazaEvenimente);
    connectBtn("btnAddInventar", [=](){ gestionareInventar(true); });
    connectBtn("btnUseInventar", [=](){ gestionareInventar(false); });

    // Actiuni Angajat & Guest
    connectBtn("btnStartTask", [=](){ actiuniAngajat(1); });
    connectBtn("btnFinishTask", [=](){ actiuniAngajat(2); });
    connectBtn("btnSendReport", [=](){ actiuniAngajat(3); });
    connectBtn("btnSendSesizareTeren", [=](){ actiuniAngajat(4); });
    connectBtn("btnTrimiteSesizareaGuest", [=](){ actiuniAngajat(5); });
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::loginSistem() {
    QString user = ui->userInput->text().trimmed();
    QString rol = ui->roleCombo->currentText();
    if(rol == "Administrator" && user == "admin") ui->stackedWidget->setCurrentIndex(1);
    else if(rol == "Angajat") ui->stackedWidget->setCurrentIndex(2);
    else if(rol == "Guest") ui->stackedWidget->setCurrentIndex(3);
    else QMessageBox::warning(this, "Eroare", "Date incorecte!");
}

void MainWindow::logoutSistem() {
    ui->userInput->clear();
    ui->passInput->clear();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::adaugaTaskComplex() {
    QString taskDesc = ui->inputTaskAdmin->text();
    QString locatie = ui->comboParcTask->currentText() + " - " + ui->comboZonaTask->currentText();
    QStringList selectati;
    QList<QListWidgetItem*> items = ui->listAngajatiTask->selectedItems();
    for(auto item : items) selectati << item->text();

    if(taskDesc.isEmpty() || selectati.isEmpty()) {
        QMessageBox::warning(this, "Atentie", "Completati sarcina si alegeti angajatii!");
        return;
    }

    int r = ui->tableTaskuriAdmin->rowCount();
    ui->tableTaskuriAdmin->insertRow(r);
    ui->tableTaskuriAdmin->setItem(r, 0, new QTableWidgetItem(QString::number(r+1)));
    ui->tableTaskuriAdmin->setItem(r, 1, new QTableWidgetItem(taskDesc));
    ui->tableTaskuriAdmin->setItem(r, 2, new QTableWidgetItem(selectati.join(", ")));
    ui->tableTaskuriAdmin->setItem(r, 3, new QTableWidgetItem(locatie));
    ui->tableTaskuriAdmin->setItem(r, 4, new QTableWidgetItem("In asteptare"));
    ui->inputTaskAdmin->clear();
}

void MainWindow::convertSesizare() {
    int row = ui->tableSesizariAdmin->currentRow();
    if(row == -1) return;
    ui->stackedWidget->setCurrentIndex(4);
    ui->inputTaskAdmin->setText("REPARARE: " + ui->tableSesizariAdmin->item(row, 3)->text());
}

void MainWindow::gestioneazaEvenimente() {
    // Folosim numele din Object Inspector-ul tau: inputNumeEveniment, dateEveniment, comboLocatie
    if(ui->inputNumeEveniment->text().isEmpty()) {
        QMessageBox::warning(this, "Info", "Introduceti numele evenimentului!");
        return;
    }

    int r = ui->tableEvenimenteAdmin->rowCount();
    ui->tableEvenimenteAdmin->insertRow(r);
    ui->tableEvenimenteAdmin->setItem(r, 0, new QTableWidgetItem(ui->inputNumeEveniment->text()));
    ui->tableEvenimenteAdmin->setItem(r, 1, new QTableWidgetItem(ui->dateEveniment->date().toString("dd/MM/yyyy")));
    ui->tableEvenimenteAdmin->setItem(r, 2, new QTableWidgetItem(ui->comboLocatie->currentText()));
    ui->tableEvenimenteAdmin->setItem(r, 3, new QTableWidgetItem("Programat ✅"));
    ui->inputNumeEveniment->clear();
}

void MainWindow::gestionareInventar(bool adauga) {
    if(adauga) {
        int r = ui->tableInventar->rowCount();
        ui->tableInventar->insertRow(r);
        ui->tableInventar->setItem(r, 1, new QTableWidgetItem(ui->inputNumeMaterial->text()));
        ui->tableInventar->setItem(r, 2, new QTableWidgetItem(QString::number(ui->spinCantitate->value())));
        ui->tableInventar->setItem(r, 3, new QTableWidgetItem(ui->comboParcMaterial->currentText()));
    } else {
        int row = ui->tableInventar->currentRow();
        if(row != -1) {
            int cant = ui->tableInventar->item(row, 2)->text().toInt();
            ui->tableInventar->setItem(row, 2, new QTableWidgetItem(QString::number(cant - ui->spinCantitate->value())));
        }
    }
}

void MainWindow::actiuniAngajat(int tip) {
    int r = ui->tableTaskuriAngajat->currentRow();
    switch(tip) {
    case 1: if(r != -1) ui->tableTaskuriAngajat->setItem(r, 3, new QTableWidgetItem("În Lucru")); break;
    case 2: if(r != -1) ui->tableTaskuriAngajat->removeRow(r); break;
    case 3: QMessageBox::information(this, "Info", "Raport trimis!"); break;
    case 4: {
        int rowS = ui->tableSesizariAdmin->rowCount();
        ui->tableSesizariAdmin->insertRow(rowS);
        ui->tableSesizariAdmin->setItem(rowS, 1, new QTableWidgetItem("Angajat"));
        ui->tableSesizariAdmin->setItem(rowS, 3, new QTableWidgetItem(ui->inputSesizareTeren->text()));
        break;
    }
    case 5: {
        int rowG = ui->tableSesizariAdmin->rowCount();
        ui->tableSesizariAdmin->insertRow(rowG);
        ui->tableSesizariAdmin->setItem(rowG, 1, new QTableWidgetItem("Cetatean (Guest)"));
        ui->tableSesizariAdmin->setItem(rowG, 2, new QTableWidgetItem(ui->comboParcGuest->currentText()));
        ui->tableSesizariAdmin->setItem(rowG, 3, new QTableWidgetItem(ui->textSesizareGuest->toPlainText()));
        QMessageBox::information(this, "Succes", "Sesizare trimisa!");
        break;
    }
    }
}