#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QString>

class DatabaseManager
{
public:
    static DatabaseManager& instance();

    bool init();
    bool checkAdmin(const QString& adminRole);

    bool addUser(const QString& login, const QString& password);


    bool checkUser(const QString& login, const QString& password);

    QString getUserRole(const QString& login);
    QStringList getAllLogins();

private:
    DatabaseManager() = default;
    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_H