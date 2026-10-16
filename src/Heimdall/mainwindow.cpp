#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasemanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Создание БД
    DatabaseManager::instance().init();

    // Создание необходимых страниц
    adminPage = new AdminPage();
    managerPage = new ManagerPage();

    // Работа со stackWidget
    ui->stackedWidget->addWidget(adminPage);
    ui->stackedWidget->addWidget(managerPage);

    // Заполнение выпадающего списка из режима админа
    connect(adminPage, AdminPage::reqUserList, this, [this] () {
        QStringList users = DatabaseManager::instance().getAllLogins();
        adminPage->setUsersList(users);
    });

    // Обработка возвращения из режима админа
    connect(adminPage, AdminPage::handleReturn, this, [this] () {
        clearTextAuth();
        clearStyleAuth();

        ui->le_login->clear();
        ui->le_password->clear();

        ui->stackedWidget->setCurrentIndex(eLoginPage);

        this->setMinimumSize(LOGIN_WINDOW_WIDTH, LOGIN_WINDOW_HEIGHT);
        this->setMaximumSize(LOGIN_WINDOW_WIDTH, LOGIN_WINDOW_HEIGHT);
        this->resize(LOGIN_WINDOW_WIDTH, LOGIN_WINDOW_HEIGHT);
    });

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
        clearStyleAuth();
        onAuthTriggered();
        clearTextAuth();
    });

    ui->stackedWidget->setCurrentIndex(0);

    this->setMinimumSize(LOGIN_WINDOW_WIDTH, LOGIN_WINDOW_HEIGHT);
    this->setMaximumSize(LOGIN_WINDOW_WIDTH, LOGIN_WINDOW_HEIGHT);
    this->resize(LOGIN_WINDOW_WIDTH, LOGIN_WINDOW_HEIGHT);

}

void MainWindow::onAuthTriggered() {

    // Проверка на существование пользователя
    if (!DatabaseManager::instance().checkUser(ui->le_login->text(), ui->le_password->text())) {
        setStyleAuth();
        return;
    }

    QString role = DatabaseManager::instance().getUserRole(ui->le_login->text());

    if (role == "admin") {
        ui->stackedWidget->setCurrentIndex(eAdminPage);  // Открываем админку

        adminPage->refresh();

        this->setMaximumSize(ADMIN_WINDOW_WIDTH, ADMIN_WINDOW_HEIGHT);
        this->setMaximumSize(ADMIN_WINDOW_WIDTH, ADMIN_WINDOW_HEIGHT);

        this->resize(ADMIN_WINDOW_WIDTH, ADMIN_WINDOW_HEIGHT);
    }
    else {
        ui->stackedWidget->setCurrentIndex(eManagerPage); // Открываем основное окно программы

        // Делаем окно большим и разрешаем менять его размер
        this->setMinimumSize(0, 0);
        this->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);

        this->resize(1200, 800);
    }

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

    if (!DatabaseManager::instance().addUser(ui->le_newLogin->text(), ui->le_newPass->text())) {
        ui->lb_signError->setText("Пользователь уже существует");
        return;
    }

    if (!errString.isEmpty()) {
        ui->lb_signError->setText(errString);
        ui->lb_signError->setStyleSheet("color: red;");
        return;
    }

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

//Настрйока стилей
void MainWindow::setStyleAuth() {

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

