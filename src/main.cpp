#include <tatoeba.h>

#include <iostream>

#include <cppcms/service.h>
#include <cppcms/applications_pool.h>

#include <sqlite3.h>

using namespace std;
using namespace cppcms;

int main(int argc,char ** argv)
{
    try {

        service app(argc,argv);

        // :TODO: maybe it's not the better place 
        // but for the moment it's the only way I've found to initialize tatodb 
        // in order to have the pointer shared by every thread
        // :TODO: remember to free tatoDB
        TatoDb *tatoDb = tato_db_new();
        std::string tatodbPath = app.settings().get<std::string>("tatoeba.tatodbxml");
        tato_db_load(tatoDb, tatodbPath.c_str());
        std::cout << "[NOTICE] database loaded" << std::endl;

        // Base sqlite3
        int rc;
        sqlite3* sqliteDb;
        rc = sqlite3_open("../doc/sqlite3.db", &sqliteDb);
        if (rc) {
            std::cout << "Can't open database: " << sqlite3_errmsg(sqliteDb) << std::endl;
            sqlite3_close(sqliteDb);
        }
        //sqlite3_close(sqliteDb);

        app.applications_pool().mount(applications_factory<apps::tatoeba>(tatoDb, sqliteDb));
        app.run();
    } catch(std::exception const &e) {
        cerr<<e.what()<<endl;
    }
}

