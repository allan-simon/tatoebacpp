#include <tatoeba.h>

#include <iostream>

#include <cppcms/service.h>
#include <cppcms/applications_pool.h>


using namespace std;
using namespace cppcms;

int main(int argc,char ** argv)
{
    try {

        service app(argc,argv);

        // TODO maybe it's not the better place 
        // but for the moment it's the only way I've found to initialize tatodb 
        // in order to have the pointer shared by every thread
        TatoDb *tatoDb = tato_db_new();
        std::string tatodbPath = app.settings().get<std::string>("tatoeba.tatodbxml");
        tato_db_load(tatoDb, tatodbPath.c_str());
        std::cout << "[NOTICE] database loaded" << std::endl;

        app.applications_pool().mount(applications_factory<apps::tatoeba>(tatoDb));
        app.run();
    } catch(std::exception const &e) {
        cerr<<e.what()<<endl;
    }
}

