#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

enum PagesIndex {
    eLoginPage,
    eManagerPage,
    eSignPage
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

private slots:
    void onAuthTriggered();
    void onSignTriggered();

    // Сброс стилей полей
    void clearStyleAuth();
    void clearStyleSign();

    //Сброс текста полей
    void clearTextAuth();
    void clearTextSign();

};
#endif // MAINWINDOW_H
