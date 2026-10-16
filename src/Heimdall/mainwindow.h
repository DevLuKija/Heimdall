#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "adminpage.h"
#include "managerpage.h"

#include <QMessageBox>
#include <QStackedWidget>
#include <QWidget>

#include <QPushButton>
#include <QLineEdit>

#include <QObject>
#include <QStyle>
#include <QPropertyAnimation>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <QDebug>

#define LOGIN_WINDOW_WIDTH 200
#define LOGIN_WINDOW_HEIGHT 300

#define SIGN_WINDOW_WIDTH 300
#define SIGN_WINDOW_HEIGHT 300

#define ADMIN_WINDOW_WIDTH 550
#define ADMIN_WINDOW_HEIGHT 10

enum PagesIndex {
    eLoginPage,
    eSignPage,
    eAdminPage,
    eManagerPage
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;

    // И в секцию private:
    QWidget *sidePanel;
    QPropertyAnimation *panelAnimation;
    bool isPanelExpanded = false; // Флаг состояния панели

    AdminPage *adminPage = nullptr;
    ManagerPage *managerPage = nullptr;

private slots:
    void onAuthTriggered();
    void onSignTriggered();

    // Сброс стилей полей
    void clearStyleAuth();
    void clearStyleSign();

    //Настрйока стилей
    void setStyleAuth();

    //Сброс текста полей
    void clearTextAuth();
    void clearTextSign();

};
#endif // MAINWINDOW_H
