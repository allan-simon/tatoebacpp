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
  	disp->assign("/show-result/(.*)/([a-z]+)/([a-z]+)$", &Searches::show_result, this,1, 2, 3);

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
        "/" + searchesSimple.sentencesLang.selected_id() +
        "/" + searchesSimple.translatedInLang.selected_id()
    );

}

/**
 *
 */
void Searches::show_result(
    std::string query,
    std::string fromLang,
    std::string toLang
) {
    // TODO replace by page instead of offset/size
    unsigned int offset = 1;
    unsigned int size = 10;

    if (request().request_method() == "GET") {
        cppcms::http::request::form_type getData = request().get();
        cppcms::http::request::form_type::const_iterator it;
       
        GET_INT_FIELD(offset, "offset");
        GET_INT_FIELD(size, "size");
    }
    offset -= 1;


	contents::SearchesShowResult c;
	contents::helpers::Sentences shc;
    init_content(c);
    // TODO filter this as otherwise it will produce strange result
    // if user search "../" etC.
    shc.baseUrl = "/searches/show-result/" + query + "/" + fromLang + "/" + toLang;
    shc.lang = c.lang;
    c.queryStr = query;
    c.queryLang = fromLang;
    c.paginationSize = size;

    shc.currentUserHelper = c.usersHelper;

    shc.sentences = searchesModel->advance(
        query,
        fromLang,
        toLang,
        size,
        offset,
        get_current_user_spoken_langs()
    );
    
    c.shc = shc;

    render ("searches_show_result", c);
}

} // End namespace webs
} // End namespace controllers
