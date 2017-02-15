/*
*
* firebird.cpp
*
*/

#include <iostream>

#include "firebird.h"

Firebird::Firebird()
{
    host = "localhost";
    dbfile = "/var/db/firebird/mokou.fdb";
    login = "SYSDBA";
    password = "masterkey";

    try {
        db = IBPP::DatabaseFactory(host, dbfile, login, password);
        db->Connect();
    } catch (IBPP::Exception& e) { showIbppException(e); }

    //tr = IBPP::TransactionFactory(db);
}

Firebird::~Firebird()
{
    if ( db->Connected() )
        db->Disconnect();
}

void Firebird::showError( const char* errorText)
{
    std::cout << errorText << std::endl;
}

void Firebird::showIbppException(IBPP::Exception& e)
{
    std::cout << e.ErrorMessage();
}

bool Firebird::query( const char* statement)
{
    if ( !db->Connected() ) {
        showError( "ERROR: db disconnected" );
        return false;
    }

    tr = IBPP::TransactionFactory( db );
    tr->Start();

    st = IBPP::StatementFactory( db, tr );

    try {
        st->Execute( statement );
        tr->Commit();
    } catch (IBPP::Exception& e) { showIbppException(e); return false; }

    return true;
}

bool Firebird::query( const char* statement, std::vector<int>* container )
{
    if ( !db->Connected() ) {
        showError( "ERROR: db disconnected" );
        return false;
    }

    tr = IBPP::TransactionFactory( db );
    tr->Start();

    st = IBPP::StatementFactory( db, tr );

    try {
		int cell;
        container->clear();       
        st->Execute( statement );
        while ( st->Fetch() ) {
           st->Get( 1, cell );
           container->push_back( cell );
        }
        tr->Commit();
    } catch (IBPP::Exception& e) { showIbppException(e); return false; }

    return true;
}

bool Firebird::query( const char* statement, std::vector<std::string>* container)
{
    if ( !db->Connected() ) {
        showError( "ERROR: db disconnected" );
        return false;
    }

    tr = IBPP::TransactionFactory( db );
    tr->Start();

    st = IBPP::StatementFactory( db, tr );

    try {
        std::string cell;
        container->clear();
        st->Execute( statement );
        while ( st->Fetch() ) {
           st->Get( 1, cell );
           container->push_back( cell );
        }
        tr->Commit();
    } catch (IBPP::Exception& e) { showIbppException(e); return false; }

    return true;
}

bool Firebird::query( const char* statement, std::vector< std::vector<std::string> >* container)
{
    if ( !db->Connected() ) {
        showError( "ERROR: db disconnected" );
        return false;
    }

    tr= IBPP::TransactionFactory( db );
    tr->Start();

    st = IBPP::StatementFactory( db, tr );

    try
    {
        std::vector<std::string> list;
        std::string cell;
        int n;

        st->Execute( statement );

        n = st->Columns();
        container->clear();

        while (st->Fetch())
        {
            list.clear();
            for ( int i = 1; i<=n; i++) {
                st->Get(i, cell);
                list.push_back( cell );
            }
            container->push_back( list );
        }
        tr->Commit();
    } catch (IBPP::Exception& e) { showIbppException(e); return false; }

    return true;
}
