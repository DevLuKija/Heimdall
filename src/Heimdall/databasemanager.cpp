#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager mgr;
    return mgr;
}

bool DatabaseManager::init()
{
    QString adminRole = "admin";

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dataPath);
    m_db.setDatabaseName(dataPath + "/heimdall.db");

    if (!m_db.open()) {
        qDebug() << "Ошибка открытия БД:" << m_db.lastError().text();
        return false;
    }

    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS users ( "
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "login TEXT UNIQUE NOT NULL, "
                      "password TEXT NOT NULL, "
                      "role TEXT NOT NULL DEFAULT 'user', "
                      "last_login TEXT, "
                      "records_count INTEGER DEFAULT 0"))
    {
        qDebug() << "Ошибка: не удалось создать базу данных";
        return false;
    }

    if (!checkAdmin(adminRole)) {
        qDebug() << "Запись админа не была найдена";
        if (!query.exec("INSERT OR IGNORE INTO users (login, password, role) "
                          "VALUES ('admin', 'admin', 'admin')"))
        {
            qDebug() << "Ошибка: не удалось создать запись админа";
            return false;
        }
    }

    return true;
}

bool DatabaseManager::checkAdmin(const QString& adminRole)
{
    QSqlQuery query;
    query.prepare("SELECT 1 FROM users WHERE role = :role LIMIT 1");
    query.bindValue(":role", adminRole);

    // if (query.exec())
    //     if (query.next())
    //         admID = query.value(0).toInt();

    // qDebug() << "Номер записи админа: " << admID;

    return query.exec() && query.next();
}

bool DatabaseManager::addUser(const QString& login, const QString& password)
{
    QSqlQuery query;
    query.prepare("INSERT INTO users (login, password) VALUES (:login, :pass)");
    query.bindValue(":login", login);
    query.bindValue(":pass", password);
    return query.exec();
}

bool DatabaseManager::checkUser(const QString& login, const QString& password)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM users WHERE login = :login AND password = :pass");
    query.bindValue(":login", login);
    query.bindValue(":pass", password);
    return query.exec() && query.next();
}

QString DatabaseManager::getUserRole(const QString& login)
{
    QSqlQuery query;
    query.prepare("SELECT role FROM users WHERE login = :login");
    query.bindValue(":login", login);
    if (query.exec() && query.next()) {
        return query.value("role").toString();
    }
    return QString();   // пользователь не найден
}

QStringList DatabaseManager::getAllLogins()
{
    QStringList logins;
    QSqlQuery query("SELECT login FROM users ORDER BY login");
    while (query.next()) {
        logins.append(query.value(0).toString());
    }
    return logins;
}