#include <tatoeba.h>

#include <iostream>

#include <cppcms/service.h>
#include <cppcms/applications_pool.h>
#include <cppdb/frontend.h>



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
        string tatodbPath = app.settings().get<string>("tatoeba.tatodbxml");
        tato_db_load(tatoDb, tatodbPath.c_str());
        cout << "[NOTICE] database loaded" << endl;

        // Base sqlite3
        // TODO: replace this by a path set in the configuration settings
        //sqlite3_close(sqliteDb);

        app.applications_pool().mount(applications_factory<apps::tatoeba>(tatoDb));
        app.run();
    } catch(std::exception const &e) {
        cerr<<e.what()<<endl;
    }
}

