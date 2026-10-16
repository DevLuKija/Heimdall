#ifndef MANAGERPAGE_H
#define MANAGERPAGE_H

#include <QWidget>

namespace Ui {
class ManagerPage;
}

class ManagerPage : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerPage(QWidget *parent = nullptr);
    ~ManagerPage();

private:
    Ui::ManagerPage *ui;
};

#endif // MANAGERPAGE_H
