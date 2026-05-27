/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QComboBox *roleCombo;
    QLineEdit *userInput;
    QLineEdit *passInput;
    QPushButton *btnLogin;
    QPushButton *btnJoinGuest;
    QWidget *page_1;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnGoTasks;
    QPushButton *btnGoEvents;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnGoSesizari;
    QPushButton *btnGoIstoric;
    QHBoxLayout *hLayoutInventarRapoarte;
    QPushButton *btnGoInventar;
    QPushButton *btnGoRapoarte;
    QPushButton *btnGoCreareCont;
    QPushButton *btnLogoutAdmin;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_4;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_3;
    QTableWidget *tableTaskuriAngajat;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnStartTask;
    QPushButton *btnFinishTask;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupRaport;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_6;
    QTextEdit *textDetaliiRaport;
    QPushButton *btnSendReport;
    QGroupBox *groupSesizareTeren;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_7;
    QLineEdit *inputSesizareTeren;
    QPushButton *btnSendSesizareTeren;
    QPushButton *btnLogoutAngajat;
    QWidget *page_3;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_4;
    QLabel *label_8;
    QComboBox *comboParcGuest;
    QLabel *label_9;
    QComboBox *comboZonaGuest;
    QLabel *label_10;
    QTextEdit *textSesizareGuest;
    QPushButton *btnTrimiteSesizareaGuest;
    QPushButton *btnLogoutGuest;
    QWidget *page_4;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_5;
    QTableWidget *tableTaskuriAdmin;
    QComboBox *comboParcTask;
    QComboBox *comboZonaTask;
    QLineEdit *inputTaskAdmin;
    QListWidget *listAngajatiTask;
    QVBoxLayout *vLayoutAsociere;
    QHBoxLayout *hLayoutAsociereRow;
    QLabel *labelItemTask;
    QComboBox *comboItemInventar;
    QLabel *labelCantTask;
    QSpinBox *spinCantitateTask;
    QPushButton *btnAsociaItem;
    QPushButton *btnAdaugaTaskManual;
    QPushButton *btnBackToDash;
    QWidget *page_5;
    QVBoxLayout *verticalLayout_17;
    QLabel *labelTitluEvenimente;
    QFrame *frameFormular;
    QVBoxLayout *verticalLayout_16;
    QLineEdit *inputNumeEveniment;
    QDateEdit *dateEveniment;
    QComboBox *comboLocatie;
    QTableWidget *tableEvenimenteAdmin;
    QPushButton *btnAprobaEveniment;
    QPushButton *btnBackToDash_2;
    QWidget *page_6;
    QVBoxLayout *verticalLayout_18;
    QLabel *label_31;
    QTableWidget *tableSesizariAdmin;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *btnIgnoraSesizarea;
    QPushButton *btnConvertTask;
    QPushButton *btnBackToDash_3;
    QWidget *page_7;
    QVBoxLayout *verticalLayout_21;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_33;
    QComboBox *comboFiltruIstoric;
    QTableWidget *tableIstoric;
    QPushButton *btnBackToDash_4;
    QWidget *page_8;
    QVBoxLayout *verticalLayout_20;
    QLabel *label_32;
    QTableWidget *tableInventar;
    QFrame *frame;
    QVBoxLayout *verticalLayout_19;
    QHBoxLayout *horizontalLayout_12;
    QLineEdit *inputNumeMaterial;
    QSpinBox *spinCantitate;
    QComboBox *comboParcMaterial;
    QPushButton *btnAddInventar;
    QPushButton *btnUseInventar;
    QPushButton *btnBackToDash_5;
    QWidget *pageCreareAngajat;
    QVBoxLayout *verticalLayout_11;
    QLabel *qLabel;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *inputNumeAngajatNou;
    QLineEdit *inputParolaAngajatNou;
    QPushButton *btnSalveazaAngajat;
    QPushButton *btnBackDinCreare;
    QWidget *pageRapoarte;
    QVBoxLayout *vLayoutRapoarte;
    QLabel *labelTitluRapoarte;
    QSplitter *splitterRapoarte;
    QWidget *widgetStanga;
    QVBoxLayout *vLayoutStanga;
    QLabel *labelAngajatiR;
    QListWidget *listAngajatiRapoarte;
    QWidget *widgetDreapta;
    QVBoxLayout *vLayoutDreapta;
    QLabel *labelRapoarteAngajat;
    QTableWidget *tableRapoarte;
    QPushButton *btnBackDinRapoarte;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 650);
        MainWindow->setStyleSheet(QString::fromUtf8("/* Fundalul principal */\n"
"#centralwidget {\n"
"    background-color: #cfd8dc;\n"
"}\n"
"\n"
"/* Titlul principal */\n"
"QLabel {\n"
"    color: #2c3e50;\n"
"    font-family: \"Segoe UI\", sans-serif;\n"
"}\n"
"\n"
"/* C\303\242mpurile de text (User \310\231i Parol\304\203) */\n"
"QLineEdit {\n"
"    background-color: white;\n"
"    border: 1px solid #b0bec5;\n"
"    border-radius: 5px;\n"
"    padding: 8px;\n"
"    color: #37474f;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 2px solid #3498db;\n"
"}\n"
"\n"
"/* Butonul de Login (Verde) */\n"
"QPushButton#btnLogin {\n"
"    background-color: #2ecc71;\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"    padding: 10px;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QPushButton#btnLogin:hover {\n"
"    background-color: #27ae60;\n"
"}\n"
"\n"
"/* Butonul de Guest (Albastru) */\n"
"QPushButton#btnJoinGuest {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"    padding: 10px;\n"
"    font-size: "
                        "14px;\n"
"}\n"
"\n"
"QPushButton#btnJoinGuest:hover {\n"
"    background-color: #2980b9;\n"
"}\n"
"\n"
"/* Butoanele de Logout (Ro\310\231u/Portocaliu) */\n"
"QPushButton#btnLogoutAdmin, QPushButton#btnLogoutAngajat, QPushButton#btnBackGuest {\n"
"    background-color: #e74c3c;\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"    padding: 8px;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        QFont font;
        font.setBold(true);
        stackedWidget->setFont(font);
        page = new QWidget();
        page->setObjectName("page");
        verticalLayout_2 = new QVBoxLayout(page);
        verticalLayout_2->setSpacing(15);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(page);
        label->setObjectName("label");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Segoe UI")});
        font1.setPointSize(28);
        font1.setBold(true);
        font1.setUnderline(false);
        label->setFont(font1);
        label->setFrameShape(QFrame::Shape::NoFrame);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label);

        roleCombo = new QComboBox(page);
        roleCombo->addItem(QString());
        roleCombo->addItem(QString());
        roleCombo->setObjectName("roleCombo");
        QFont font2;
        font2.setPointSize(14);
        roleCombo->setFont(font2);

        verticalLayout_2->addWidget(roleCombo);

        userInput = new QLineEdit(page);
        userInput->setObjectName("userInput");

        verticalLayout_2->addWidget(userInput);

        passInput = new QLineEdit(page);
        passInput->setObjectName("passInput");
        QFont font3;
        font3.setPointSize(10);
        passInput->setFont(font3);
        passInput->setEchoMode(QLineEdit::EchoMode::Password);

        verticalLayout_2->addWidget(passInput);

        btnLogin = new QPushButton(page);
        btnLogin->setObjectName("btnLogin");

        verticalLayout_2->addWidget(btnLogin);

        btnJoinGuest = new QPushButton(page);
        btnJoinGuest->setObjectName("btnJoinGuest");

        verticalLayout_2->addWidget(btnJoinGuest);

        stackedWidget->addWidget(page);
        page_1 = new QWidget();
        page_1->setObjectName("page_1");
        page_1->setStyleSheet(QString::fromUtf8("/* Stil general pentru butoanele din meniu */\n"
"QPushButton {\n"
"    background-color: #ffffff;\n"
"    border: 2px solid #2c3e50; /* O culoare elegant\304\203 de bleumarin \303\256nchis */\n"
"    border-radius: 12px;\n"
"    color: #2c3e50;\n"
"    font-family: \"Segoe UI\", sans-serif;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    padding: 10px;\n"
"    min-height: 60px; /* Le facem mai \303\256nalte s\304\203 par\304\203 butoane de dashboard */\n"
"}\n"
"\n"
"/* Efect c\303\242nd treci cu mouse-ul peste butoane */\n"
"QPushButton:hover {\n"
"    background-color: #34495e;\n"
"    color: white;\n"
"    border: 2px solid #34495e;\n"
"}\n"
"\n"
"/* Stil pentru butonul de LogOut (s\304\203 ias\304\203 \303\256n eviden\310\233\304\203) */\n"
"QPushButton#btnLogoutAdmin {\n"
"    background-color: #e74c3c; /* Ro\310\231u */\n"
"    border: none;\n"
"    color: white;\n"
"    min-height: 45px;\n"
"    border-radius: 8px;\n"
"}\n"
"\n"
"QPushButton#btnLogoutAdmin:hover {\n"
"    background-color: "
                        "#c0392b; /* Ro\310\231u mai \303\256nchis la hover */\n"
"}\n"
"\n"
"/* Butonul de Gestiune Inventar (care e singur pe r\303\242nd) */\n"
"QPushButton#btnGoInventar {\n"
"    border: 2px solid #27ae60; /* Verde */\n"
"    color: #27ae60;\n"
"}\n"
"\n"
"QPushButton#btnGoInventar:hover {\n"
"    background-color: #27ae60;\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton#btnGoRapoarte {\n"
"    border: 2px solid #8e44ad;\n"
"    color: #8e44ad;\n"
"}\n"
"\n"
"QPushButton#btnGoRapoarte:hover {\n"
"    background-color: #8e44ad;\n"
"    color: white;\n"
"}"));
        verticalLayout_3 = new QVBoxLayout(page_1);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_2 = new QLabel(page_1);
        label_2->setObjectName("label_2");
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Segoe UI")});
        font4.setPointSize(16);
        font4.setBold(true);
        label_2->setFont(font4);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        btnGoTasks = new QPushButton(page_1);
        btnGoTasks->setObjectName("btnGoTasks");

        horizontalLayout->addWidget(btnGoTasks);

        btnGoEvents = new QPushButton(page_1);
        btnGoEvents->setObjectName("btnGoEvents");

        horizontalLayout->addWidget(btnGoEvents);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        btnGoSesizari = new QPushButton(page_1);
        btnGoSesizari->setObjectName("btnGoSesizari");

        horizontalLayout_3->addWidget(btnGoSesizari);

        btnGoIstoric = new QPushButton(page_1);
        btnGoIstoric->setObjectName("btnGoIstoric");

        horizontalLayout_3->addWidget(btnGoIstoric);


        verticalLayout_3->addLayout(horizontalLayout_3);

        hLayoutInventarRapoarte = new QHBoxLayout();
        hLayoutInventarRapoarte->setObjectName("hLayoutInventarRapoarte");
        btnGoInventar = new QPushButton(page_1);
        btnGoInventar->setObjectName("btnGoInventar");

        hLayoutInventarRapoarte->addWidget(btnGoInventar);

        btnGoRapoarte = new QPushButton(page_1);
        btnGoRapoarte->setObjectName("btnGoRapoarte");

        hLayoutInventarRapoarte->addWidget(btnGoRapoarte);


        verticalLayout_3->addLayout(hLayoutInventarRapoarte);

        btnGoCreareCont = new QPushButton(page_1);
        btnGoCreareCont->setObjectName("btnGoCreareCont");

        verticalLayout_3->addWidget(btnGoCreareCont);

        btnLogoutAdmin = new QPushButton(page_1);
        btnLogoutAdmin->setObjectName("btnLogoutAdmin");

        verticalLayout_3->addWidget(btnLogoutAdmin);

        stackedWidget->addWidget(page_1);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        page_2->setStyleSheet(QString::fromUtf8("/* Stil pentru GroupBox (ramele din jurul sec\310\233iunilor) */\n"
"QGroupBox {\n"
"    font-weight: bold;\n"
"    border: 2px solid #bdc3c7;\n"
"    border-radius: 10px;\n"
"    margin-top: 20px;\n"
"    padding-top: 15px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 10px;\n"
"    padding: 0 5px;\n"
"    color: #27ae60; /* Verdele angajatului */\n"
"}\n"
"\n"
"/* Butonul de Raport (Verde) */\n"
"QPushButton#btnSendReport {\n"
"    background-color: #27ae60;\n"
"    color: white;\n"
"    border-radius: 8px;\n"
"    min-height: 40px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"/* Butonul de Sesizare (Albastru \303\256nchis/Grey) */\n"
"QPushButton#btnSendSesizareTeren {\n"
"    background-color: #34495e;\n"
"    color: white;\n"
"    border-radius: 8px;\n"
"    min-height: 40px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton#btnSendReport:hover, QPushButton#btnSendSesizareTeren:hover {\n"
"    background-color: #2c3e50;\n"
"    opacity: 0.9;\n"
"}"));
        verticalLayout_4 = new QVBoxLayout(page_2);
        verticalLayout_4->setSpacing(20);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(15, 15, 15, 15);
        tabWidget = new QTabWidget(page_2);
        tabWidget->setObjectName("tabWidget");
        tab = new QWidget();
        tab->setObjectName("tab");
        verticalLayout_9 = new QVBoxLayout(tab);
        verticalLayout_9->setSpacing(15);
        verticalLayout_9->setObjectName("verticalLayout_9");
        verticalLayout_9->setContentsMargins(20, 20, 20, 20);
        label_3 = new QLabel(tab);
        label_3->setObjectName("label_3");
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Segoe UI")});
        font5.setPointSize(14);
        font5.setBold(true);
        label_3->setFont(font5);

        verticalLayout_9->addWidget(label_3);

        tableTaskuriAngajat = new QTableWidget(tab);
        if (tableTaskuriAngajat->columnCount() < 5)
            tableTaskuriAngajat->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableTaskuriAngajat->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableTaskuriAngajat->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableTaskuriAngajat->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableTaskuriAngajat->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableTaskuriAngajat->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableTaskuriAngajat->setObjectName("tableTaskuriAngajat");

        verticalLayout_9->addWidget(tableTaskuriAngajat);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(15);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(20, 20, 20, 20);
        btnStartTask = new QPushButton(tab);
        btnStartTask->setObjectName("btnStartTask");

        horizontalLayout_2->addWidget(btnStartTask);

        btnFinishTask = new QPushButton(tab);
        btnFinishTask->setObjectName("btnFinishTask");

        horizontalLayout_2->addWidget(btnFinishTask);


        verticalLayout_9->addLayout(horizontalLayout_2);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        verticalLayout_6 = new QVBoxLayout(tab_2);
        verticalLayout_6->setObjectName("verticalLayout_6");
        groupRaport = new QGroupBox(tab_2);
        groupRaport->setObjectName("groupRaport");
        verticalLayout_8 = new QVBoxLayout(groupRaport);
        verticalLayout_8->setObjectName("verticalLayout_8");
        label_6 = new QLabel(groupRaport);
        label_6->setObjectName("label_6");

        verticalLayout_8->addWidget(label_6);

        textDetaliiRaport = new QTextEdit(groupRaport);
        textDetaliiRaport->setObjectName("textDetaliiRaport");

        verticalLayout_8->addWidget(textDetaliiRaport);

        btnSendReport = new QPushButton(groupRaport);
        btnSendReport->setObjectName("btnSendReport");

        verticalLayout_8->addWidget(btnSendReport);


        verticalLayout_6->addWidget(groupRaport);

        groupSesizareTeren = new QGroupBox(tab_2);
        groupSesizareTeren->setObjectName("groupSesizareTeren");
        verticalLayout_7 = new QVBoxLayout(groupSesizareTeren);
        verticalLayout_7->setObjectName("verticalLayout_7");
        label_7 = new QLabel(groupSesizareTeren);
        label_7->setObjectName("label_7");

        verticalLayout_7->addWidget(label_7);

        inputSesizareTeren = new QLineEdit(groupSesizareTeren);
        inputSesizareTeren->setObjectName("inputSesizareTeren");

        verticalLayout_7->addWidget(inputSesizareTeren);

        btnSendSesizareTeren = new QPushButton(groupSesizareTeren);
        btnSendSesizareTeren->setObjectName("btnSendSesizareTeren");

        verticalLayout_7->addWidget(btnSendSesizareTeren);


        verticalLayout_6->addWidget(groupSesizareTeren);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_4->addWidget(tabWidget);

        btnLogoutAngajat = new QPushButton(page_2);
        btnLogoutAngajat->setObjectName("btnLogoutAngajat");

        verticalLayout_4->addWidget(btnLogoutAngajat);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        page_3->setStyleSheet(QString::fromUtf8("/* Butonul de Trimite Sesizarea (Albastru) */\n"
"QPushButton#btnTrimiteSesizareaGuest {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"    border-radius: 8px;\n"
"    padding: 10px;\n"
"    font-weight: bold;\n"
"    border: none;\n"
"}\n"
"\n"
"QPushButton#btnTrimiteSesizareaGuest:hover {\n"
"    background-color: #2980b9;\n"
"}\n"
"\n"
"QPushButton#btnTrimiteSesizareaGuest:pressed {\n"
"    background-color: #1c598a;\n"
"}\n"
"\n"
"/* Butonul de LogOut / Back (Ro\310\231u) */\n"
"QPushButton#btnLogoutGuest, QPushButton#btnLogoutAdmin, QPushButton#btnLogoutAngajat {\n"
"    background-color: #e74c3c;\n"
"    color: white;\n"
"    border-radius: 8px;\n"
"    padding: 10px;\n"
"    font-weight: bold;\n"
"    border: none;\n"
"}\n"
"\n"
"QPushButton#btnLogoutGuest:hover, QPushButton#btnLogoutAdmin:hover, QPushButton#btnLogoutAngajat:hover {\n"
"    background-color: #c0392b;\n"
"}\n"
"\n"
"QPushButton#btnLogoutGuest:pressed, QPushButton#btnLogoutAdmin:pressed, QPushButton#btnLogoutAngajat:pressed "
                        "{\n"
"    background-color: #a93226;\n"
"}"));
        verticalLayout_5 = new QVBoxLayout(page_3);
        verticalLayout_5->setSpacing(15);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(20, 20, 20, 20);
        label_4 = new QLabel(page_3);
        label_4->setObjectName("label_4");
        label_4->setFont(font5);

        verticalLayout_5->addWidget(label_4);

        label_8 = new QLabel(page_3);
        label_8->setObjectName("label_8");

        verticalLayout_5->addWidget(label_8);

        comboParcGuest = new QComboBox(page_3);
        comboParcGuest->setObjectName("comboParcGuest");

        verticalLayout_5->addWidget(comboParcGuest);

        label_9 = new QLabel(page_3);
        label_9->setObjectName("label_9");

        verticalLayout_5->addWidget(label_9);

        comboZonaGuest = new QComboBox(page_3);
        comboZonaGuest->setObjectName("comboZonaGuest");

        verticalLayout_5->addWidget(comboZonaGuest);

        label_10 = new QLabel(page_3);
        label_10->setObjectName("label_10");

        verticalLayout_5->addWidget(label_10);

        textSesizareGuest = new QTextEdit(page_3);
        textSesizareGuest->setObjectName("textSesizareGuest");

        verticalLayout_5->addWidget(textSesizareGuest);

        btnTrimiteSesizareaGuest = new QPushButton(page_3);
        btnTrimiteSesizareaGuest->setObjectName("btnTrimiteSesizareaGuest");

        verticalLayout_5->addWidget(btnTrimiteSesizareaGuest);

        btnLogoutGuest = new QPushButton(page_3);
        btnLogoutGuest->setObjectName("btnLogoutGuest");

        verticalLayout_5->addWidget(btnLogoutGuest);

        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        page_4->setStyleSheet(QString::fromUtf8("/* --- STIL TABEL ADMIN --- */\n"
"QTableWidget#tableTaskuriAdmin {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #dcdde1;\n"
"    border-radius: 10px;\n"
"    gridline-color: #f5f6fa;\n"
"    selection-background-color: #3498db;\n"
"    selection-color: white;\n"
"    outline: none;\n"
"}\n"
"\n"
"/* Stil pentru antetul tabelului (Capul de tabel) */\n"
"QHeaderView::section {\n"
"    background-color: #2c3e50; /* Bleumarin \303\256nchis */\n"
"    color: white;\n"
"    padding: 10px;\n"
"    border: none;\n"
"    font-weight: bold;\n"
"    font-size: 13px;\n"
"}\n"
"\n"
"/* --- STIL ZONA DE INPUT (Ce trebuie facut / Angajat) --- */\n"
"QLineEdit#inputTaskAdmin, QComboBox#comboAngajatAdmin {\n"
"    border: 2px solid #bdc3c7;\n"
"    border-radius: 8px;\n"
"    padding: 8px 12px;\n"
"    background-color: white;\n"
"    color: #2c3e50;\n"
"    min-height: 25px;\n"
"}\n"
"\n"
"QLineEdit#inputTaskAdmin:focus {\n"
"    border: 2px solid #3498db; /* Albastru la click */\n"
"}\n"
"\n"
"/* --- BUTONUL"
                        " DE AD\304\202UGARE TASK (Verde) --- */\n"
"QPushButton#btnAdaugaTaskManual {\n"
"    background-color: #27ae60;\n"
"    color: white;\n"
"    border-radius: 8px;\n"
"    font-weight: bold;\n"
"    min-height: 45px;\n"
"}\n"
"\n"
"QPushButton#btnAdaugaTaskManual:hover {\n"
"    background-color: #219150;\n"
"}\n"
"\n"
"/* --- BUTONUL GO BACK (Gri discret) --- */\n"
"QPushButton#btnBackToDash {\n"
"    background-color: transparent;\n"
"    border: 2px solid #95a5a6;\n"
"    color: #7f8c8d;\n"
"    border-radius: 8px;\n"
"    font-weight: bold;\n"
"    min-height: 35px;\n"
"}\n"
"\n"
"QPushButton#btnBackToDash:hover {\n"
"    background-color: #95a5a6;\n"
"    color: white;\n"
"}\n"
"\n"
"/* --- TITLUL PAGINII --- */\n"
"QLabel#label_9 {\n"
"    color: #2c3e50;\n"
"    font-size: 22px;\n"
"    font-weight: bold;\n"
"    margin-bottom: 10px;\n"
"}"));
        verticalLayout_10 = new QVBoxLayout(page_4);
        verticalLayout_10->setObjectName("verticalLayout_10");
        label_5 = new QLabel(page_4);
        label_5->setObjectName("label_5");
        label_5->setFont(font5);

        verticalLayout_10->addWidget(label_5);

        tableTaskuriAdmin = new QTableWidget(page_4);
        if (tableTaskuriAdmin->columnCount() < 4)
            tableTaskuriAdmin->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableTaskuriAdmin->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableTaskuriAdmin->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableTaskuriAdmin->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableTaskuriAdmin->setHorizontalHeaderItem(3, __qtablewidgetitem8);
        tableTaskuriAdmin->setObjectName("tableTaskuriAdmin");
        tableTaskuriAdmin->horizontalHeader()->setCascadingSectionResizes(false);
        tableTaskuriAdmin->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableTaskuriAdmin->horizontalHeader()->setStretchLastSection(true);
        tableTaskuriAdmin->verticalHeader()->setCascadingSectionResizes(false);
        tableTaskuriAdmin->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableTaskuriAdmin->verticalHeader()->setStretchLastSection(false);

        verticalLayout_10->addWidget(tableTaskuriAdmin);

        comboParcTask = new QComboBox(page_4);
        comboParcTask->setObjectName("comboParcTask");

        verticalLayout_10->addWidget(comboParcTask);

        comboZonaTask = new QComboBox(page_4);
        comboZonaTask->setObjectName("comboZonaTask");

        verticalLayout_10->addWidget(comboZonaTask);

        inputTaskAdmin = new QLineEdit(page_4);
        inputTaskAdmin->setObjectName("inputTaskAdmin");

        verticalLayout_10->addWidget(inputTaskAdmin);

        listAngajatiTask = new QListWidget(page_4);
        listAngajatiTask->setObjectName("listAngajatiTask");

        verticalLayout_10->addWidget(listAngajatiTask);

        vLayoutAsociere = new QVBoxLayout();
        vLayoutAsociere->setObjectName("vLayoutAsociere");
        hLayoutAsociereRow = new QHBoxLayout();
        hLayoutAsociereRow->setObjectName("hLayoutAsociereRow");
        labelItemTask = new QLabel(page_4);
        labelItemTask->setObjectName("labelItemTask");

        hLayoutAsociereRow->addWidget(labelItemTask);

        comboItemInventar = new QComboBox(page_4);
        comboItemInventar->addItem(QString());
        comboItemInventar->setObjectName("comboItemInventar");
        comboItemInventar->setEnabled(true);

        hLayoutAsociereRow->addWidget(comboItemInventar);

        labelCantTask = new QLabel(page_4);
        labelCantTask->setObjectName("labelCantTask");

        hLayoutAsociereRow->addWidget(labelCantTask);

        spinCantitateTask = new QSpinBox(page_4);
        spinCantitateTask->setObjectName("spinCantitateTask");
        spinCantitateTask->setMinimum(1);
        spinCantitateTask->setMaximum(999);
        spinCantitateTask->setValue(1);

        hLayoutAsociereRow->addWidget(spinCantitateTask);


        vLayoutAsociere->addLayout(hLayoutAsociereRow);

        btnAsociaItem = new QPushButton(page_4);
        btnAsociaItem->setObjectName("btnAsociaItem");

        vLayoutAsociere->addWidget(btnAsociaItem);


        verticalLayout_10->addLayout(vLayoutAsociere);

        btnAdaugaTaskManual = new QPushButton(page_4);
        btnAdaugaTaskManual->setObjectName("btnAdaugaTaskManual");

        verticalLayout_10->addWidget(btnAdaugaTaskManual);

        btnBackToDash = new QPushButton(page_4);
        btnBackToDash->setObjectName("btnBackToDash");

        verticalLayout_10->addWidget(btnBackToDash);

        stackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        page_5->setStyleSheet(QString::fromUtf8("/* Stil pentru containerul formularului */\n"
"QFrame#frameFormular {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #dcdde1;\n"
"    border-radius: 12px;\n"
"}\n"
"\n"
"/* Stil pentru input-uri */\n"
"QLineEdit#inputNumeEveniment, QDateEdit#dateEveniment, QComboBox#comboLocatie {\n"
"    border: 2px solid #ecf0f1;\n"
"    border-radius: 6px;\n"
"    padding: 8px;\n"
"    min-height: 30px;\n"
"}\n"
"\n"
"/* Butonul de Programare */\n"
"QPushButton#btnAprobaEveniment {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"    border-radius: 8px;\n"
"    font-weight: bold;\n"
"    font-size: 15px;\n"
"    min-height: 50px;\n"
"}\n"
"\n"
"QPushButton#btnAprobaEveniment:hover {\n"
"    background-color: #2980b9;\n"
"}\n"
"\n"
"/* Tabelul */\n"
"QTableWidget#tableEvenimenteAdmin {\n"
"    background-color: white;\n"
"    border-radius: 10px;\n"
"    gridline-color: #f1f2f6;\n"
"}"));
        verticalLayout_17 = new QVBoxLayout(page_5);
        verticalLayout_17->setSpacing(15);
        verticalLayout_17->setObjectName("verticalLayout_17");
        verticalLayout_17->setContentsMargins(30, 30, 30, 30);
        labelTitluEvenimente = new QLabel(page_5);
        labelTitluEvenimente->setObjectName("labelTitluEvenimente");
        QFont font6;
        font6.setFamilies({QString::fromUtf8("Segoe UI")});
        font6.setPointSize(15);
        font6.setBold(true);
        labelTitluEvenimente->setFont(font6);

        verticalLayout_17->addWidget(labelTitluEvenimente);

        frameFormular = new QFrame(page_5);
        frameFormular->setObjectName("frameFormular");
        frameFormular->setFrameShape(QFrame::Shape::StyledPanel);
        frameFormular->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_16 = new QVBoxLayout(frameFormular);
        verticalLayout_16->setSpacing(15);
        verticalLayout_16->setObjectName("verticalLayout_16");
        inputNumeEveniment = new QLineEdit(frameFormular);
        inputNumeEveniment->setObjectName("inputNumeEveniment");

        verticalLayout_16->addWidget(inputNumeEveniment);

        dateEveniment = new QDateEdit(frameFormular);
        dateEveniment->setObjectName("dateEveniment");
        dateEveniment->setCalendarPopup(true);

        verticalLayout_16->addWidget(dateEveniment);

        comboLocatie = new QComboBox(frameFormular);
        comboLocatie->setObjectName("comboLocatie");

        verticalLayout_16->addWidget(comboLocatie);


        verticalLayout_17->addWidget(frameFormular);

        tableEvenimenteAdmin = new QTableWidget(page_5);
        if (tableEvenimenteAdmin->columnCount() < 4)
            tableEvenimenteAdmin->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableEvenimenteAdmin->setHorizontalHeaderItem(0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableEvenimenteAdmin->setHorizontalHeaderItem(1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableEvenimenteAdmin->setHorizontalHeaderItem(2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableEvenimenteAdmin->setHorizontalHeaderItem(3, __qtablewidgetitem12);
        tableEvenimenteAdmin->setObjectName("tableEvenimenteAdmin");
        tableEvenimenteAdmin->horizontalHeader()->setCascadingSectionResizes(false);
        tableEvenimenteAdmin->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_17->addWidget(tableEvenimenteAdmin);

        btnAprobaEveniment = new QPushButton(page_5);
        btnAprobaEveniment->setObjectName("btnAprobaEveniment");

        verticalLayout_17->addWidget(btnAprobaEveniment);

        btnBackToDash_2 = new QPushButton(page_5);
        btnBackToDash_2->setObjectName("btnBackToDash_2");

        verticalLayout_17->addWidget(btnBackToDash_2);

        stackedWidget->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName("page_6");
        page_6->setStyleSheet(QString::fromUtf8("/* Stil pentru tabelul de sesiz\304\203ri */\n"
"QTableWidget#tableSesizariAdmin {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #dcdde1;\n"
"    gridline-color: #f5f6fa;\n"
"}\n"
"\n"
"/* Butonul Ignor\304\203 - Ro\310\231u pentru a indica \310\231tergerea */\n"
"QPushButton#btnIgnoraSesizarea {\n"
"    background-color: transparent;\n"
"    border: 2px solid #e74c3c;\n"
"    color: #e74c3c;\n"
"    border-radius: 8px;\n"
"    font-weight: bold;\n"
"    min-height: 40px;\n"
"}\n"
"\n"
"QPushButton#btnIgnoraSesizarea:hover {\n"
"    background-color: #e74c3c;\n"
"    color: white;\n"
"}\n"
"\n"
"/* Butonul de Conversie - Albastru \303\256nchis/Professional */\n"
"QPushButton#btnConvertTask {\n"
"    background-color: #2c3e50;\n"
"    color: white;\n"
"    border-radius: 8px;\n"
"    font-weight: bold;\n"
"    min-height: 40px;\n"
"}\n"
"\n"
"QPushButton#btnConvertTask:hover {\n"
"    background-color: #34495e;\n"
"}"));
        verticalLayout_18 = new QVBoxLayout(page_6);
        verticalLayout_18->setSpacing(15);
        verticalLayout_18->setObjectName("verticalLayout_18");
        verticalLayout_18->setContentsMargins(30, 30, 30, 30);
        label_31 = new QLabel(page_6);
        label_31->setObjectName("label_31");
        label_31->setFont(font6);

        verticalLayout_18->addWidget(label_31);

        tableSesizariAdmin = new QTableWidget(page_6);
        if (tableSesizariAdmin->columnCount() < 4)
            tableSesizariAdmin->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableSesizariAdmin->setHorizontalHeaderItem(0, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableSesizariAdmin->setHorizontalHeaderItem(1, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableSesizariAdmin->setHorizontalHeaderItem(2, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableSesizariAdmin->setHorizontalHeaderItem(3, __qtablewidgetitem16);
        tableSesizariAdmin->setObjectName("tableSesizariAdmin");
        tableSesizariAdmin->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_18->addWidget(tableSesizariAdmin);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        btnIgnoraSesizarea = new QPushButton(page_6);
        btnIgnoraSesizarea->setObjectName("btnIgnoraSesizarea");

        horizontalLayout_10->addWidget(btnIgnoraSesizarea);

        btnConvertTask = new QPushButton(page_6);
        btnConvertTask->setObjectName("btnConvertTask");

        horizontalLayout_10->addWidget(btnConvertTask);


        verticalLayout_18->addLayout(horizontalLayout_10);

        btnBackToDash_3 = new QPushButton(page_6);
        btnBackToDash_3->setObjectName("btnBackToDash_3");

        verticalLayout_18->addWidget(btnBackToDash_3);

        stackedWidget->addWidget(page_6);
        page_7 = new QWidget();
        page_7->setObjectName("page_7");
        page_7->setStyleSheet(QString::fromUtf8("/* Stil tabel Istoric */\n"
"QTableWidget#tableIstoric {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #dcdde1;\n"
"    border-radius: 10px;\n"
"    gridline-color: #f1f2f6;\n"
"    alternate-background-color: #f8f9fa; /* R\303\242nduri gri deschis alternante */\n"
"}\n"
"\n"
"/* Antetul tabelului */\n"
"QHeaderView::section {\n"
"    background-color: #2c3e50; /* Bleumarin \303\256nchis */\n"
"    color: white;\n"
"    padding: 8px;\n"
"    font-weight: bold;\n"
"    border: none;\n"
"}\n"
"\n"
"/* Stil pentru celulele selectate */\n"
"QTableWidget::item:selected {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"}"));
        verticalLayout_21 = new QVBoxLayout(page_7);
        verticalLayout_21->setObjectName("verticalLayout_21");
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        label_33 = new QLabel(page_7);
        label_33->setObjectName("label_33");
        label_33->setFont(font6);

        horizontalLayout_13->addWidget(label_33);

        comboFiltruIstoric = new QComboBox(page_7);
        comboFiltruIstoric->setObjectName("comboFiltruIstoric");

        horizontalLayout_13->addWidget(comboFiltruIstoric);


        verticalLayout_21->addLayout(horizontalLayout_13);

        tableIstoric = new QTableWidget(page_7);
        if (tableIstoric->columnCount() < 4)
            tableIstoric->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableIstoric->setHorizontalHeaderItem(0, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableIstoric->setHorizontalHeaderItem(1, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableIstoric->setHorizontalHeaderItem(2, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableIstoric->setHorizontalHeaderItem(3, __qtablewidgetitem20);
        tableIstoric->setObjectName("tableIstoric");
        tableIstoric->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_21->addWidget(tableIstoric);

        btnBackToDash_4 = new QPushButton(page_7);
        btnBackToDash_4->setObjectName("btnBackToDash_4");

        verticalLayout_21->addWidget(btnBackToDash_4);

        stackedWidget->addWidget(page_7);
        page_8 = new QWidget();
        page_8->setObjectName("page_8");
        page_8->setStyleSheet(QString::fromUtf8("/* Stil pentru SpinBox (selectorul de numere) */\n"
"QSpinBox {\n"
"    border: 2px solid #bdc3c7;\n"
"    border-radius: 6px;\n"
"    padding: 5px;\n"
"    min-width: 70px;\n"
"    background-color: white;\n"
"}\n"
"\n"
"/* Butonul de Ad\304\203ugare (Verde) */\n"
"QPushButton#btnAddInventar {\n"
"    background-color: #2ecc71;\n"
"    color: white;\n"
"    border-radius: 8px;\n"
"    font-weight: bold;\n"
"    min-height: 40px;\n"
"}\n"
"\n"
"/* Butonul de Sc\304\203dere (Portocaliu/Galben) */\n"
"QPushButton#btnUseInventar {\n"
"    background-color: #f1c40f;\n"
"    color: #2c3e50;\n"
"    border-radius: 8px;\n"
"    font-weight: bold;\n"
"    min-height: 40px;\n"
"}"));
        verticalLayout_20 = new QVBoxLayout(page_8);
        verticalLayout_20->setObjectName("verticalLayout_20");
        label_32 = new QLabel(page_8);
        label_32->setObjectName("label_32");
        label_32->setFont(font6);

        verticalLayout_20->addWidget(label_32);

        tableInventar = new QTableWidget(page_8);
        if (tableInventar->columnCount() < 4)
            tableInventar->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableInventar->setHorizontalHeaderItem(0, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableInventar->setHorizontalHeaderItem(1, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableInventar->setHorizontalHeaderItem(2, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableInventar->setHorizontalHeaderItem(3, __qtablewidgetitem24);
        tableInventar->setObjectName("tableInventar");
        tableInventar->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_20->addWidget(tableInventar);

        frame = new QFrame(page_8);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_19 = new QVBoxLayout(frame);
        verticalLayout_19->setObjectName("verticalLayout_19");
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        inputNumeMaterial = new QLineEdit(frame);
        inputNumeMaterial->setObjectName("inputNumeMaterial");

        horizontalLayout_12->addWidget(inputNumeMaterial);

        spinCantitate = new QSpinBox(frame);
        spinCantitate->setObjectName("spinCantitate");

        horizontalLayout_12->addWidget(spinCantitate);

        comboParcMaterial = new QComboBox(frame);
        comboParcMaterial->setObjectName("comboParcMaterial");

        horizontalLayout_12->addWidget(comboParcMaterial);


        verticalLayout_19->addLayout(horizontalLayout_12);

        btnAddInventar = new QPushButton(frame);
        btnAddInventar->setObjectName("btnAddInventar");

        verticalLayout_19->addWidget(btnAddInventar);

        btnUseInventar = new QPushButton(frame);
        btnUseInventar->setObjectName("btnUseInventar");

        verticalLayout_19->addWidget(btnUseInventar);


        verticalLayout_20->addWidget(frame);

        btnBackToDash_5 = new QPushButton(page_8);
        btnBackToDash_5->setObjectName("btnBackToDash_5");

        verticalLayout_20->addWidget(btnBackToDash_5);

        stackedWidget->addWidget(page_8);
        pageCreareAngajat = new QWidget();
        pageCreareAngajat->setObjectName("pageCreareAngajat");
        pageCreareAngajat->setStyleSheet(QString::fromUtf8("/* Stil pentru fundalul paginii */\n"
"QWidget#pageCreareAngajat {\n"
"    background-color: #f5f7fa;\n"
"}\n"
"\n"
"/* Stil pentru titlu */\n"
"QLabel {\n"
"    font-size: 24px;\n"
"    font-weight: bold;\n"
"    color: #2d3436;\n"
"    margin-bottom: 20px;\n"
"}\n"
"\n"
"/* Stil pentru c\303\242mpurile de text (Input) */\n"
"QLineEdit {\n"
"    padding: 10px;\n"
"    border: 2px solid #dfe6e9;\n"
"    border-radius: 8px;\n"
"    background-color: white;\n"
"    font-size: 14px;\n"
"    min-width: 250px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 2px solid #0984e3; /* Albastru c\303\242nd dai click \303\256n el */\n"
"}\n"
"\n"
"/* Stil pentru butonul principal \"Creeaz\304\203 Cont\" */\n"
"QPushButton#btnSalveazaAngajat {\n"
"    background-color: #00b894; /* Verde modern */\n"
"    color: white;\n"
"    border-radius: 8px;\n"
"    padding: 12px;\n"
"    font-weight: bold;\n"
"    font-size: 15px;\n"
"    min-width: 150px;\n"
"}\n"
"\n"
"QPushButton#btnSalveazaAngajat:hover {\n"
"    background-color:"
                        " #55efc4; /* Verde mai deschis la hover */\n"
"}\n"
"\n"
"QPushButton#btnSalveazaAngajat:pressed {\n"
"    background-color: #00a884;\n"
"}\n"
"\n"
"/* Stil pentru butonul de Anuleaz\304\203 */\n"
"QPushButton#btnBackDinCreare {\n"
"    background-color: red;\n"
"    color: white;\n"
"    border: 2px solid #b2bec3;\n"
"    border-radius: 8px;\n"
"    padding: 8px;\n"
"    font-size: 13px;\n"
"}\n"
"\n"
"QPushButton#btnBackDinCreare:hover {\n"
"    background-color: #dfe6e9;\n"
"    color: #2d3436;\n"
"}"));
        verticalLayout_11 = new QVBoxLayout(pageCreareAngajat);
        verticalLayout_11->setObjectName("verticalLayout_11");
        qLabel = new QLabel(pageCreareAngajat);
        qLabel->setObjectName("qLabel");
        QFont font7;
        font7.setFamilies({QString::fromUtf8("Segoe UI")});
        font7.setBold(true);
        qLabel->setFont(font7);

        verticalLayout_11->addWidget(qLabel);

        lineEdit = new QLineEdit(pageCreareAngajat);
        lineEdit->setObjectName("lineEdit");

        verticalLayout_11->addWidget(lineEdit);

        lineEdit_2 = new QLineEdit(pageCreareAngajat);
        lineEdit_2->setObjectName("lineEdit_2");

        verticalLayout_11->addWidget(lineEdit_2);

        inputNumeAngajatNou = new QLineEdit(pageCreareAngajat);
        inputNumeAngajatNou->setObjectName("inputNumeAngajatNou");

        verticalLayout_11->addWidget(inputNumeAngajatNou);

        inputParolaAngajatNou = new QLineEdit(pageCreareAngajat);
        inputParolaAngajatNou->setObjectName("inputParolaAngajatNou");
        inputParolaAngajatNou->setEchoMode(QLineEdit::EchoMode::Password);

        verticalLayout_11->addWidget(inputParolaAngajatNou);

        btnSalveazaAngajat = new QPushButton(pageCreareAngajat);
        btnSalveazaAngajat->setObjectName("btnSalveazaAngajat");

        verticalLayout_11->addWidget(btnSalveazaAngajat);

        btnBackDinCreare = new QPushButton(pageCreareAngajat);
        btnBackDinCreare->setObjectName("btnBackDinCreare");

        verticalLayout_11->addWidget(btnBackDinCreare);

        stackedWidget->addWidget(pageCreareAngajat);
        pageRapoarte = new QWidget();
        pageRapoarte->setObjectName("pageRapoarte");
        pageRapoarte->setStyleSheet(QString::fromUtf8("\n"
"QWidget#pageRapoarte {\n"
"    background-color: #f5f7fa;\n"
"}\n"
"QListWidget#listAngajatiRapoarte {\n"
"    border: 1px solid #dfe6e9;\n"
"    border-radius: 8px;\n"
"    background: white;\n"
"    font-size: 13px;\n"
"}\n"
"QListWidget#listAngajatiRapoarte::item:selected {\n"
"    background-color: #8e44ad;\n"
"    color: white;\n"
"    border-radius: 4px;\n"
"}\n"
"QTableWidget#tableRapoarte {\n"
"    border: 1px solid #dfe6e9;\n"
"    border-radius: 8px;\n"
"    background: white;\n"
"    gridline-color: #f1f2f6;\n"
"}\n"
"QPushButton#btnBackDinRapoarte {\n"
"    background-color: #636e72;\n"
"    color: white;\n"
"    border-radius: 8px;\n"
"    padding: 10px;\n"
"    font-size: 13px;\n"
"}\n"
"QPushButton#btnBackDinRapoarte:hover {\n"
"    background-color: #2d3436;\n"
"}\n"
"        "));
        vLayoutRapoarte = new QVBoxLayout(pageRapoarte);
        vLayoutRapoarte->setSpacing(12);
        vLayoutRapoarte->setObjectName("vLayoutRapoarte");
        vLayoutRapoarte->setContentsMargins(25, 20, 25, 20);
        labelTitluRapoarte = new QLabel(pageRapoarte);
        labelTitluRapoarte->setObjectName("labelTitluRapoarte");
        labelTitluRapoarte->setFont(font6);

        vLayoutRapoarte->addWidget(labelTitluRapoarte);

        splitterRapoarte = new QSplitter(pageRapoarte);
        splitterRapoarte->setObjectName("splitterRapoarte");
        splitterRapoarte->setOrientation(Qt::Orientation::Horizontal);
        widgetStanga = new QWidget(splitterRapoarte);
        widgetStanga->setObjectName("widgetStanga");
        vLayoutStanga = new QVBoxLayout(widgetStanga);
        vLayoutStanga->setSpacing(8);
        vLayoutStanga->setObjectName("vLayoutStanga");
        vLayoutStanga->setContentsMargins(0, 0, 0, 0);
        labelAngajatiR = new QLabel(widgetStanga);
        labelAngajatiR->setObjectName("labelAngajatiR");
        labelAngajatiR->setFont(font7);

        vLayoutStanga->addWidget(labelAngajatiR);

        listAngajatiRapoarte = new QListWidget(widgetStanga);
        listAngajatiRapoarte->setObjectName("listAngajatiRapoarte");

        vLayoutStanga->addWidget(listAngajatiRapoarte);

        splitterRapoarte->addWidget(widgetStanga);
        widgetDreapta = new QWidget(splitterRapoarte);
        widgetDreapta->setObjectName("widgetDreapta");
        vLayoutDreapta = new QVBoxLayout(widgetDreapta);
        vLayoutDreapta->setSpacing(8);
        vLayoutDreapta->setObjectName("vLayoutDreapta");
        vLayoutDreapta->setContentsMargins(0, 0, 0, 0);
        labelRapoarteAngajat = new QLabel(widgetDreapta);
        labelRapoarteAngajat->setObjectName("labelRapoarteAngajat");
        labelRapoarteAngajat->setFont(font7);

        vLayoutDreapta->addWidget(labelRapoarteAngajat);

        tableRapoarte = new QTableWidget(widgetDreapta);
        if (tableRapoarte->columnCount() < 4)
            tableRapoarte->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableRapoarte->setHorizontalHeaderItem(0, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableRapoarte->setHorizontalHeaderItem(1, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableRapoarte->setHorizontalHeaderItem(2, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableRapoarte->setHorizontalHeaderItem(3, __qtablewidgetitem28);
        tableRapoarte->setObjectName("tableRapoarte");
        tableRapoarte->horizontalHeader()->setStretchLastSection(true);

        vLayoutDreapta->addWidget(tableRapoarte);

        splitterRapoarte->addWidget(widgetDreapta);

        vLayoutRapoarte->addWidget(splitterRapoarte);

        btnBackDinRapoarte = new QPushButton(pageRapoarte);
        btnBackDinRapoarte->setObjectName("btnBackDinRapoarte");

        vLayoutRapoarte->addWidget(btnBackDinRapoarte);

        stackedWidget->addWidget(pageRapoarte);

        verticalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);
        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Autentificare Personal", nullptr));
        roleCombo->setItemText(0, QCoreApplication::translate("MainWindow", "Administrator", nullptr));
        roleCombo->setItemText(1, QCoreApplication::translate("MainWindow", "Angajat", nullptr));

        userInput->setText(QString());
        userInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "Nume utilizator", nullptr));
        passInput->setText(QString());
        passInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "Parola...", nullptr));
        btnLogin->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        btnJoinGuest->setText(QCoreApplication::translate("MainWindow", "Join as Guest", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "PANOU CONTROL ADMINISTRATOR", nullptr));
        btnGoTasks->setText(QCoreApplication::translate("MainWindow", "Gestionare Sarcini \360\237\233\240\357\270\217", nullptr));
        btnGoEvents->setText(QCoreApplication::translate("MainWindow", "Organizare Evenimente \342\255\220", nullptr));
        btnGoSesizari->setText(QCoreApplication::translate("MainWindow", "Sesiz\304\203ri Primite \342\232\240\357\270\217", nullptr));
        btnGoIstoric->setText(QCoreApplication::translate("MainWindow", "Istoric Activitate \360\237\223\234", nullptr));
        btnGoInventar->setText(QCoreApplication::translate("MainWindow", "Gestiune Inventar \360\237\223\246", nullptr));
        btnGoRapoarte->setText(QCoreApplication::translate("MainWindow", "Rapoarte Angajati \360\237\223\213", nullptr));
        btnGoCreareCont->setText(QCoreApplication::translate("MainWindow", "Inregistrare Angajat Nou\360\237\221\267", nullptr));
        btnLogoutAdmin->setText(QCoreApplication::translate("MainWindow", "LogOut", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "SARCINI ALOCATE ECHIPEI", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableTaskuriAngajat->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableTaskuriAngajat->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Sarcina", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableTaskuriAngajat->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Locatie", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableTaskuriAngajat->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Resurse", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableTaskuriAngajat->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
        btnStartTask->setText(QCoreApplication::translate("MainWindow", " \303\216ncepe Lucrul\360\237\232\200", nullptr));
        btnFinishTask->setText(QCoreApplication::translate("MainWindow", " Finalizat\342\234\205", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Sarcini de Lucru \360\237\233\240\357\270\217", nullptr));
        groupRaport->setTitle(QCoreApplication::translate("MainWindow", "RAPORTARE FINALIZARE TASK\360\237\223\235", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Detalii lucrare:", nullptr));
        textDetaliiRaport->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: Am folosit...", nullptr));
        btnSendReport->setText(QCoreApplication::translate("MainWindow", " Trimite Raport\360\237\223\244", nullptr));
        groupSesizareTeren->setTitle(QCoreApplication::translate("MainWindow", "\360\237\223\242 SESIZARE PROBLEM\304\202 NOU\304\202", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Descrie problema g\304\203sit\304\203:", nullptr));
        inputSesizareTeren->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: Banc\304\203 rupt\304\203 l\303\242ng\304\203 lac...", nullptr));
        btnSendSesizareTeren->setText(QCoreApplication::translate("MainWindow", " Raporteaz\304\203 Problema\342\232\240\357\270\217", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Raportare & Sesiz\304\203ri \360\237\223\242", nullptr));
        btnLogoutAngajat->setText(QCoreApplication::translate("MainWindow", "LogOut", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Sesizare Cetateni", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Alege parcul: ", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Alege zona :", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Descrie problema :", nullptr));
        btnTrimiteSesizareaGuest->setText(QCoreApplication::translate("MainWindow", "Trimite sesizarea", nullptr));
        btnLogoutGuest->setText(QCoreApplication::translate("MainWindow", "LogOut", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\360\237\224\247 GESTIONARE SARCINI ACTIVE", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableTaskuriAdmin->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableTaskuriAdmin->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Sarcina", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableTaskuriAdmin->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Responsabil", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableTaskuriAdmin->horizontalHeaderItem(3);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
        inputTaskAdmin->setPlaceholderText(QCoreApplication::translate("MainWindow", "Descriere task nou...", nullptr));
        labelItemTask->setText(QCoreApplication::translate("MainWindow", "Item inventar:", nullptr));
        comboItemInventar->setItemText(0, QCoreApplication::translate("MainWindow", "(Selecteaza item...)", nullptr));

        labelCantTask->setText(QCoreApplication::translate("MainWindow", "Cant:", nullptr));
        btnAsociaItem->setText(QCoreApplication::translate("MainWindow", "Asociaza Item \360\237\224\227", nullptr));
        btnAdaugaTaskManual->setText(QCoreApplication::translate("MainWindow", "Adaug\304\203 Task\342\234\205", nullptr));
        btnBackToDash->setText(QCoreApplication::translate("MainWindow", "Go Back", nullptr));
        labelTitluEvenimente->setText(QCoreApplication::translate("MainWindow", "\342\255\220 ORGANIZARE EVENIMENTE ", nullptr));
        inputNumeEveniment->setPlaceholderText(QCoreApplication::translate("MainWindow", "Nume Eveniment...", nullptr));
        dateEveniment->setDisplayFormat(QCoreApplication::translate("MainWindow", "d/M/yyyy", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableEvenimenteAdmin->horizontalHeaderItem(0);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "Nume Eveniment", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableEvenimenteAdmin->horizontalHeaderItem(1);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "Data", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableEvenimenteAdmin->horizontalHeaderItem(2);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "Locatie", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableEvenimenteAdmin->horizontalHeaderItem(3);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
        btnAprobaEveniment->setText(QCoreApplication::translate("MainWindow", " Programeaz\304\203 Eveniment\360\237\223\205", nullptr));
        btnBackToDash_2->setText(QCoreApplication::translate("MainWindow", "Back to Menu", nullptr));
        label_31->setText(QCoreApplication::translate("MainWindow", "\342\232\240\357\270\217 SESIZ\304\202RI \310\230I RECLAMA\310\232II", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableSesizariAdmin->horizontalHeaderItem(0);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableSesizariAdmin->horizontalHeaderItem(1);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "Sursa", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableSesizariAdmin->horizontalHeaderItem(2);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "Locatie", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableSesizariAdmin->horizontalHeaderItem(3);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "Descriere", nullptr));
        btnIgnoraSesizarea->setText(QCoreApplication::translate("MainWindow", "\342\235\214 Ignor\304\203", nullptr));
        btnConvertTask->setText(QCoreApplication::translate("MainWindow", "\360\237\224\247 Transform\304\203 \303\256n Task", nullptr));
        btnBackToDash_3->setText(QCoreApplication::translate("MainWindow", "Go Back", nullptr));
        label_33->setText(QCoreApplication::translate("MainWindow", "\360\237\223\204 ISTORIC \310\230I ARHIV\304\202 ACTIVIT\304\202\310\232I", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableIstoric->horizontalHeaderItem(0);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "Data", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableIstoric->horizontalHeaderItem(1);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("MainWindow", "Tip", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableIstoric->horizontalHeaderItem(2);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("MainWindow", "Descriere", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableIstoric->horizontalHeaderItem(3);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("MainWindow", "Locatie", nullptr));
        btnBackToDash_4->setText(QCoreApplication::translate("MainWindow", "Go Back", nullptr));
        label_32->setText(QCoreApplication::translate("MainWindow", "\360\237\223\246 GESTIUNE INVENTAR \310\230I MATERIALE", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableInventar->horizontalHeaderItem(0);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableInventar->horizontalHeaderItem(1);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("MainWindow", "Nume", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = tableInventar->horizontalHeaderItem(2);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("MainWindow", "Cantitate", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = tableInventar->horizontalHeaderItem(3);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("MainWindow", "Locatie", nullptr));
        inputNumeMaterial->setPlaceholderText(QCoreApplication::translate("MainWindow", "Nume material nou...", nullptr));
        btnAddInventar->setText(QCoreApplication::translate("MainWindow", "\342\236\225 Adaug\304\203 \303\256n Stoc", nullptr));
        btnUseInventar->setText(QCoreApplication::translate("MainWindow", "\342\236\226 Scade din Stoc", nullptr));
        btnBackToDash_5->setText(QCoreApplication::translate("MainWindow", "Go Back", nullptr));
        qLabel->setText(QCoreApplication::translate("MainWindow", "Creare Angajat Nou", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Nume Angajat", nullptr));
        lineEdit_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "Prenume Angajat", nullptr));
        inputNumeAngajatNou->setPlaceholderText(QCoreApplication::translate("MainWindow", "Nume utilizator", nullptr));
        inputParolaAngajatNou->setPlaceholderText(QCoreApplication::translate("MainWindow", "Parola...", nullptr));
        btnSalveazaAngajat->setText(QCoreApplication::translate("MainWindow", "Creeaza Cont", nullptr));
        btnBackDinCreare->setText(QCoreApplication::translate("MainWindow", "Anuleaza", nullptr));
        labelTitluRapoarte->setText(QCoreApplication::translate("MainWindow", "RAPOARTE ANGAJATI", nullptr));
        labelAngajatiR->setText(QCoreApplication::translate("MainWindow", "Angajati", nullptr));
        labelRapoarteAngajat->setText(QCoreApplication::translate("MainWindow", "Selectati un angajat din stanga", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = tableRapoarte->horizontalHeaderItem(0);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("MainWindow", "Task", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = tableRapoarte->horizontalHeaderItem(1);
        ___qtablewidgetitem26->setText(QCoreApplication::translate("MainWindow", "Data", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = tableRapoarte->horizontalHeaderItem(2);
        ___qtablewidgetitem27->setText(QCoreApplication::translate("MainWindow", "Tip", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = tableRapoarte->horizontalHeaderItem(3);
        ___qtablewidgetitem28->setText(QCoreApplication::translate("MainWindow", "Descriere", nullptr));
        btnBackDinRapoarte->setText(QCoreApplication::translate("MainWindow", "Go Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
