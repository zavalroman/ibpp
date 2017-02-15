#ifndef FIREBIRD_H
#define FIREBIRD_H

#define IBPP_LINUX

#ifdef IBPP_WINDOWS //убедиться в необходимости
    #include "../../core/_ibpp_win.cpp"
#endif
#ifdef IBPP_LINUX
    #include "../../core/ibpp.h"
#endif

#include <QString>

class Firebird
{
public:
    Firebird();
    ~Firebird();

    bool query(QString &);
    bool query(QString &, QList<int>*);
    bool query(QString &, QStringList*);
    bool query(QString &, QList<QStringList>*);

private:
    std::string host;
    std::string dbfile;
    std::string login;
    std::string password;

    IBPP::Database db;
    IBPP::Transaction tr;
    IBPP::Statement st;

    void showError(QString);
    void showIbppException(IBPP::Exception&);

};

#endif // FIREBIRD_H
