#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Создаем два виджета
    // QWidget *loginPage = new QWidget;
    // QWidget *managerPage = new QWidget;

    // Настраиваем логин (QLineEdit, кнопки и т.д.)...
    // Настраиваем менеджер...

    // Сразу показываем страницу входа
    ui->stackedWidget->setCurrentIndex(eLoginPage);

    // Кнопки на экране авторизации
    connect(ui->pb_ConfAuth, &QPushButton::clicked, this, [this] () {
        clearStyleAuth();
        onAuthTriggered();
    });
    connect(ui->pb_GoSign, &QPushButton::clicked, this, [this]() {
        clearTextSign();
        clearStyleSign();

        ui->stackedWidget->setCurrentIndex(eSignPage);

        this->setMinimumSize(SIGN_WINDOW_WIDTH, SIGN_WINDOW_HEIGHT);
        this->setMaximumSize(SIGN_WINDOW_WIDTH, SIGN_WINDOW_HEIGHT);

        this->resize(SIGN_WINDOW_WIDTH, SIGN_WINDOW_HEIGHT);
    });

    // Кнопки на экране регистрации
    connect(ui->pb_confSign, &QPushButton::clicked, this, [this] () {
        clearStyleSign();
        onSignTriggered();
    });
    connect(ui->pb_GoAuth, &QPushButton::clicked, this, [this]() {
        clearTextAuth();
        clearStyleAuth();

        ui->le_login->clear();
        ui->le_password->clear();

        ui->stackedWidget->setCurrentIndex(eLoginPage);

        this->setMinimumSize(LOGIN_WINDOW_WIDTH, LOGIN_WINDOW_HEIGHT);
        this->setMaximumSize(LOGIN_WINDOW_WIDTH, LOGIN_WINDOW_HEIGHT);
        this->resize(LOGIN_WINDOW_WIDTH, LOGIN_WINDOW_HEIGHT);
    });

    // Настройки Enter'а на странице авторизации
    connect(ui->le_login, &QLineEdit::returnPressed, this, [this]() { ui->le_password->setFocus(); });
    connect(ui->le_password, &QLineEdit::returnPressed, this, [this] () {
        clearTextAuth();
        clearStyleAuth();
        onAuthTriggered();
    });

    this->setMinimumSize(LOGIN_WINDOW_WIDTH, LOGIN_WINDOW_HEIGHT);
    this->setMaximumSize(LOGIN_WINDOW_WIDTH, LOGIN_WINDOW_HEIGHT);
    this->resize(LOGIN_WINDOW_WIDTH, LOGIN_WINDOW_HEIGHT);

}

void MainWindow::onAuthTriggered() {

    QString validLogin = "admin";
    QString validPass = "admin";


    if (ui->le_login->text() != validLogin || (ui->le_password->text() != validPass)) {

        // Включаем статус ошибки для обоих полей
        ui->le_login->setProperty("hasError", true);
        ui->le_password->setProperty("hasError", true);

        // Важно! Заставляем Qt перерисовать стили виджетов
        ui->le_login->style()->unpolish(ui->le_login);
        ui->le_login->style()->polish(ui->le_login);
        ui->le_password->style()->unpolish(ui->le_password);
        ui->le_password->style()->polish(ui->le_password);

        // работа с фокусом
        ui->le_password->clear();
        ui->le_password->setFocus();

        return;
    }

    // Открываем основное окно программы
    ui->stackedWidget->setCurrentIndex(eManagerPage);

    // Делаем окно большим и разрешаем менять его размер
    this->setMinimumSize(0, 0);
    this->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);

    this->resize(1200, 800);

    ui->le_password->clear();
}

void MainWindow::onSignTriggered() {

    QString errString = "";
    QString forbidden = " '\"\\/<>;";

    ui->lb_signError->setText("");
    bool isContain = false;

    //LOGIN
    for (QChar c : forbidden) {
        if (ui->le_newLogin->text().contains(c)) {
            isContain = true;
            break;
        }
    }

    if (ui->le_newLogin->text().isEmpty()) {

        ui->le_newLogin->setProperty("hasError", true);

        ui->le_newLogin->style()->unpolish(ui->le_newLogin);
        ui->le_newLogin->style()->polish(ui->le_newLogin);

        errString += "Необходимо указать логин\n";
    }

    else if (isContain) {

        ui->le_newPass->setProperty("hasError", true);

        ui->le_newPass->style()->unpolish(ui->le_newPass);
        ui->le_newPass->style()->polish(ui->le_newPass);

        errString += QString("Пароль содержит не допустимые знаки %1\n").arg(forbidden);
    }

    //PASS
    for (QChar c : forbidden) {
        if (ui->le_newPass->text().contains(c)) {
            isContain = true;
            break;
        }
    }

    if (ui->le_newPass->text().isEmpty()) {

        ui->le_newPass->setProperty("hasError", true);

        ui->le_newPass->style()->unpolish(ui->le_newPass);
        ui->le_newPass->style()->polish(ui->le_newPass);

        errString += "Необходимо указать пароль\n";
    }

    else if (isContain) {

        ui->le_newPass->setProperty("hasError", true);

        ui->le_newPass->style()->unpolish(ui->le_newPass);
        ui->le_newPass->style()->polish(ui->le_newPass);

        errString += QString("Пароль содержит не допустимые знаки %1\n").arg(forbidden);
    }

    else if (ui->le_newPass->text() != ui->le_newPassConfrim->text()) {

        ui->le_newPassConfrim->setProperty("hasError", true);

        ui->le_newPassConfrim->style()->unpolish(ui->le_newPassConfrim);
        ui->le_newPassConfrim->style()->polish(ui->le_newPassConfrim);

        errString += "Пароли не совпадают\n";
    }

    if (!errString.isEmpty()) {
        ui->lb_signError->setText(errString);
        ui->lb_signError->setStyleSheet("color: red;");
        return;
    }


    // QString newLogin = ui->le_newLogin->text();
    // ui->le_login->setText(newLogin);

    ui->le_newLogin->clear();
    ui->le_newPass->clear();
    ui->le_newPassConfrim->clear();

    ui->lb_signError->setText("Аккаунт успешно создан");
    ui->lb_signError->setStyleSheet("color: green;");
}

// Сброс стилей полей
void MainWindow::clearStyleAuth() {

    // Включаем статус ошибки для обоих полей
    ui->le_login->setProperty("hasError", false);
    ui->le_password->setProperty("hasError", false);

    // Важно! Заставляем Qt перерисовать стили виджетов
    ui->le_login->style()->unpolish(ui->le_login);
    ui->le_login->style()->polish(ui->le_login);
    ui->le_password->style()->unpolish(ui->le_password);
    ui->le_password->style()->polish(ui->le_password);
}

void MainWindow::clearStyleSign() {

    ui->le_newLogin->setProperty("hasError", false);

    ui->le_newLogin->style()->unpolish(ui->le_newLogin);
    ui->le_newLogin->style()->polish(ui->le_newLogin);


    ui->le_newPass->setProperty("hasError", false);

    ui->le_newPass->style()->unpolish(ui->le_newPass);
    ui->le_newPass->style()->polish(ui->le_newPass);


    ui->le_newPassConfrim->setProperty("hasError", false);

    ui->le_newPassConfrim->style()->unpolish(ui->le_newPassConfrim);
    ui->le_newPassConfrim->style()->polish(ui->le_newPassConfrim);
}

//Сброс текста полей
void MainWindow::clearTextAuth() {

    ui->le_login->clear();
    ui->le_password->clear();

    ui->lb_logError->clear();
}

void MainWindow::clearTextSign() {

    ui->le_newLogin->clear();
    ui->le_newPass->clear();
    ui->le_newPassConfrim->clear();

    ui->lb_signError->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

