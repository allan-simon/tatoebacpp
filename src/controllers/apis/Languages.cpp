#include <cppcms/filters.h>
#include "Controller.h"
#include "Languages.h"
#include "contents/languages.h"

#include "generics/Languages.h"

namespace controllers {
namespace apis {
/**
 *
 */
Languages::Languages(cppcms::service &serv) : Controller(serv) {
    // TODO have /  and /show directing to some "index" page 
    // as cburgmer pointed out, some people do navigate by crafting url
    cppcms::url_dispatcher* disp = &dispatcher();

  	disp->assign("/get-langs", &Languages::getLangs, this);
}

/**
 *
 */
Languages::~Languages() {
}

/**
 *
 */
void Languages::getLangs() {
	contents::LanguagesGetLangs c;
    init_content(c);
    c.langs = ::Languages::get_instance()->get_iso_to_name_map();
    render("languages_get_langs_api",c);

}

} // End namespace apis
} // End namespace controllers

