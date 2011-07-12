#include "Controller.h"
#include "Searches.h"
#include "contents/searches.h"

#include "models/Searches.h"

#include <cppcms/filters.h>

namespace controllers {
namespace webs {
/**
 *
 */
Searches::Searches(cppcms::service &serv) : Controller(serv) {
    // TODO have /  and /show directing to some "index" page 
    // as cburgmer pointed out, some people do navigate by crafting url
    cppcms::url_dispatcher* disp = &dispatcher();

  	disp->assign("/simple_treat$", &Searches::simple_treat, this);
  	disp->assign("/show-result/(.*)/([a-z]+)$", &Searches::show_result, this,1, 2);
  	disp->assign("/show-result/(.*)/([a-z]+)/(\\d+)/(\\d+)$", &Searches::show_result, this,1 ,2, 3, 4);

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
void Searches::simple_treat() {
    TREAT_PAGE();

    forms::SearchesSimple searchesSimple;
    searchesSimple.load(context());
    
    if (!searchesSimple.validate()) {
        go_back_to_previous_page();
        return;
    }

    std::ostringstream oss;
    oss << cppcms::filters::urlencode(searchesSimple.query.value());

    response().set_redirect_header(
        "/" + get_interface_lang() +"/searches/show-result"
        "/" + oss.str() +
        "/" + searchesSimple.sentencesLang.selected_id()
    );

}

/**
 *
 */
void Searches::show_result(std::string query, std::string lang) {
    show_result(query, lang, "1", "10");
}

/**
 *
 */
void Searches::show_result (
        std::string query,
        std::string lang,
        std::string offsetStr,
        std::string sizeStr
) {
    unsigned int size = atoi(sizeStr.c_str());
    unsigned int offset = atoi(offsetStr.c_str()) - 1;

	contents::SearchesShowResult c;
	contents::helpers::Sentences shc;
    init_content(c);
    // TODO filter this as otherwise it will produce strange result
    // if user search "../" etC.
    shc.baseUrl = "/searches/show-result/" + query + "/" + lang;
    shc.lang = c.lang;
    c.queryStr = query;
    c.queryLang = lang;
    c.paginationSize = size;
    shc.currentUserHelper = c.usersHelper;
    shc.sentences = searchesModel->advance(query, lang, size, offset);
    
    c.shc = shc;

    render ("searches_show_result", c);
}

} // End namespace webs
} // End namespace controllers
