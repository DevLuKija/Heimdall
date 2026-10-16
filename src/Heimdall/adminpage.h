#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QWidget>

namespace Ui {
class AdminPage;
}

class AdminPage : public QWidget
{
    Q_OBJECT

public:
    explicit AdminPage(QWidget *parent = nullptr);
    ~AdminPage();

    void refresh();
    void setUsersList(const QStringList& users);

private:
    Ui::AdminPage *ui;

signals:
    void handleReturn();
    void reqUserList();
};

#endif // ADMINPAGE_H
