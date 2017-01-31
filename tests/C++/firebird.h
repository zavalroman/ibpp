#ifndef FIREBIRD_H
#define FIREBIRD_H

#define IBPP_LINUX

#ifdef IBPP_WINDOWS //убедиться в необходимости
    #include "_ibpp_win.cpp"
#endif
#ifdef IBPP_LINUX
    #include "ibpp/core/ibpp.h"
#endif

#include <vector>
#include <string>

class Firebird
{
public:
    Firebird();
    ~Firebird();

    bool query( const char* );
    bool query( const char*, std::vector<int>* );
    bool query( const char*, std::vector<std::string>* );
    bool query( const char*, std::vector< std::vector<std::string> >* );

private:
    std::string host;
    std::string dbfile;
    std::string login;
    std::string password;

    IBPP::Database db;
    IBPP::Transaction tr;
    IBPP::Statement st;

    void showError( const char* );
    void showIbppException( IBPP::Exception& );

};

#endif // FIREBIRD_H
