#include "managerpage.h"
#include "ui_managerpage.h"

ManagerPage::ManagerPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerPage)
{
    ui->setupUi(this);
}

ManagerPage::~ManagerPage()
{
    delete ui;
}
