
#include <iostream>
#include <cppcms/service.h>
#include <cppcms/applications_pool.h>
#include <cppdb/frontend.h>
#include <cppcms/json.h>

#include "models/SearchEngine.h"
#include "generics/Languages.h"
#include "contents/Config.h"

#include "models/TatoDB.h"
#include "models/SearchEngine.h"
using namespace std;
using namespace cppcms;

//the indexer will permit to create all the index needed by tatoebacpp
int main(int argc,char ** argv)
{

    service app(argc, argv);

    /*load some conf defined variables*/
    Config *conf = Config::get_instance();
    conf->indexesPath = app.settings().get<string>(
        "tatoeba.searchEngine.indexesPath"
    );
    /*start the graph database*/
    string dictPath = app.settings().get<string>("tatoeba.tatodbxml");
    TatoDB::get_instance(dictPath);
    cout << "[NOTICE] database loaded" << endl;

    /*load the languages*/
    Languages::get_instance();
    Languages::get_instance()->init(
        app.settings().at("tatoeba.languages").object()
    );       

    /*start the search engine*/
    SearchEngine::get_instance();
    SearchEngine::get_instance()->init_indexed_metas(
        app.settings().at("tatoeba.indexedMetas").object()
    );
    cout << "[NOTICE] search engine indexed" << endl;
    
    TatoDB::get_instance("")->feed_search_engine();
    cout << "[NOTICE] search engine indexed" << endl;

    /*time to destroy all the singletons*/
    SearchEngine::kill();
    TatoDB::kill();
    Languages::kill();

    return 0;
}   
