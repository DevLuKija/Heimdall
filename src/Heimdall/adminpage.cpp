#include "adminpage.h"
#include "ui_adminpage.h"

AdminPage::AdminPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminPage)
{
    ui->setupUi(this);

    // Переход обратно на авторизацию со всех вкладок
    connect(ui->pb_retAuthAdmin, QPushButton::clicked, this, AdminPage::handleReturn);
    connect(ui->pb_retAuthUsers, QPushButton::clicked, this, AdminPage::handleReturn);

    refresh();
}

void AdminPage::refresh()
{
    emit reqUserList();
}

void AdminPage::setUsersList(const QStringList& users)
{
    ui->cb_usersList->clear();
    if (users.isEmpty()) {
        ui->cb_usersList->addItem("Пусто");
        return;
    }
    ui->cb_usersList->addItems(users);
}

AdminPage::~AdminPage()
{
    delete ui;
}