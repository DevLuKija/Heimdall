#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Создаем два виджета
    QWidget *loginPage = new QWidget;
    QWidget *managerPage = new QWidget;

    // Настраиваем логин (QLineEdit, кнопки и т.д.)...
    // Настраиваем менеджер...

    // Сразу показываем страницу входа
    ui->stackedWidget->setCurrentIndex(0);

    // Привязываем кнопку входа к переключению
    connect(ui->pb_LogBut, &QPushButton::clicked, this, MainWindow::auth);
}

bool MainWindow::auth() {

    QString validLogin = "admin";
    QString validPass = "admin";

    if (!(ui->le_login->text() == validLogin))
        return false;

    if (!(ui->le_password->text() == validPass))
        return false;

    ui->stackedWidget->setCurrentIndex(1);

    this->setMinimumSize(0, 0);
    this->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);

    this->resize(500, 400);

    return true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

