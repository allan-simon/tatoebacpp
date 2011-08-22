#include "Controller.h"
#include "Searches.h"
#include "contents/searches.h"

#include "models/Searches.h"
#include "results/searches.h"

#include <cppcms/filters.h>


namespace controllers {
namespace apis {
/**
 *
 */
Searches::Searches(cppcms::service &serv) : Controller(serv) {
    // TODO have /  and /show directing to some "index" page 
    // as cburgmer pointed out, some people do navigate by crafting url
    cppcms::url_dispatcher* disp = &dispatcher();

  	disp->assign("/simple", &Searches::simple, this);
  	//disp->assign("/simple", &Searches::simple, this,1 ,2, 3, 4);
    searchesModel = new models::Searches();
}

/**
 *
 */
Searches::~Searches() {
    delete searchesModel;
}


/**
 *
 */
/*
void Searches::simple(
    std::string query,
    std::string lang
) {
    simple(query, lang, "1", "10");
}
*/
/**
 *
 */
void Searches::simple () {
    std::string fromLang = "und";
    std::string toLang = "und";
    std::string query = "";

    if (request().request_method() == "GET") {
        cppcms::http::request::form_type getData = request().get();
        cppcms::http::request::form_type::const_iterator it;
        
        GET_FIELD(fromLang, "from");
        GET_FIELD(toLang, "to");
        GET_FIELD(query, "query");
    }

    
    unsigned int currentPage = 0;//atoi(sizeStr.c_str());

	contents::SearchesShowResult c;
	contents::helpers::Sentences shc;

    init_content(c);

    shc.lang = c.lang;
    c.queryStr = query;
    c.queryLang = fromLang;
    c.paginationSize = 10; //TODO MAGIC NUMBER
    shc.currentUserHelper = c.usersHelper;

    std::cout << "[DEBUG]" <<  query <<
        " in " << fromLang <<
        " to " << toLang << std::endl; 

    shc.sentences = searchesModel->advance(
        query,
        fromLang,
        toLang,
        currentPage
    );
    
    c.shc = shc;

    render ("searches_simple_api", c);
}

} // End namespace apis
} // End namespace controllers
