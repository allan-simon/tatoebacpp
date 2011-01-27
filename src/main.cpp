#include <tatoeba.h>

#include <iostream>

#include <cppcms/service.h>
#include <cppcms/applications_pool.h>
#include <cppdb/frontend.h>

#include "models/TatoDB.h"

using namespace std;
using namespace cppcms;

int main(int argc,char ** argv)
{
    try {

        service app(argc, argv);

        /** @TODO maybe it's not the better place 
         * but for the moment it's the only way I've found to initialize tatodb 
         * in order to have the pointer shared by every thread
         * @TODO remember to free tatoDB
         */
        string tatodbPath = app.settings().get<string>("tatoeba.tatodbxml");
        TatoDB::getInstance(tatodbPath);
        cout << "[NOTICE] database loaded" << endl;


        app.applications_pool().mount(applications_factory<apps::Tatoeba>());
        app.run();
    } catch(std::exception const &e) {
        cerr<<e.what()<<endl;
    }
}

