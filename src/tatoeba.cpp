#include <tatoeba.h>
#include <contents/content.h>

#include <cppcms/json.h>
#include <cppcms/application.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/http_response.h>

#include <booster/regex.h>

#include <iostream>
namespace apps {


Tatoeba::Tatoeba(cppcms::service &w) : 
	cppcms::application(w),

	pagesController(*this),
	sentencesController(*this),
	usersController(*this)
{

	add(pagesController);
	add(sentencesController);
	add(usersController);

    cppcms::json::object langs = settings().at("tatoeba.languages").object();
    for(cppcms::json::object::const_iterator p=langs.begin();p!=langs.end();++p) {
        lang_map[p->first]=p->second.str();
    }
}
static const booster::regex lang_regex("^/(\\w+)(/.*)?$");

void Tatoeba::main(std::string url) {
	booster::smatch res;
	booster::regex_match(url, res, lang_regex);
    std::map<std::string,std::string>::const_iterator p = lang_map.find(std::string(res[1]));
    if (p == lang_map.end()) {
        response().set_redirect_header("/en");
    }
    else {
	    context().locale(p->second);
	    if (!dispatcher().dispatch(res[2])) {
		    response().make_error_response(cppcms::http::response::not_found);
	    }
    }
}



} // namespace apps
