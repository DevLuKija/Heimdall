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
    connect(ui->pb_ConfAuth, &QPushButton::clicked, this, MainWindow::onAuthTriggered);
    connect(ui->pb_GoSign, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(eSignPage);

        this->setMinimumSize(SIGN_WINDOW_WIDTH, SIGN_WINDOW_HEIGHT);
        this->setMaximumSize(SIGN_WINDOW_WIDTH, SIGN_WINDOW_HEIGHT);

        this->resize(SIGN_WINDOW_WIDTH, SIGN_WINDOW_HEIGHT);
    });

    // Кнопки на экране регистрации
    connect(ui->pb_confSign, &QPushButton::clicked, this, MainWindow::onSignTriggered);


    // Настройки Enter'а
    connect(ui->le_login, &QLineEdit::returnPressed, this, [this]() { ui->le_password->setFocus(); });
    connect(ui->le_password, &QLineEdit::returnPressed, this, MainWindow::onAuthTriggerd);

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
    \
    // Делаем окно большим и разрешаем менять его размер
    this->setMinimumSize(0, 0);
    this->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);

    this->resize(1200, 800);
}

void MainWindow::onSignTriggered() {

    if (ui->le_newLogin->text().isEmpty()) {

        ui->le_newLogin
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

