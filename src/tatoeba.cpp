/**
 * Tatoeba Project, free collaborative creation of multilingual corpuses project
 * Copyright (C) 2011 Allan SIMON <allan.simon@supinfo.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * @category Tatoebacpp
 * @package  Apps
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */


#include <cppcms/json.h>
#include <cppcms/application.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/http_response.h>
#include <cppcms/http_context.h>
#include <cppcms/session_interface.h>

#include <booster/regex.h>

#include <iostream>

#include "tatoeba.h"


namespace apps {

/**
 *
 */
Tatoeba::Tatoeba(cppcms::service &serv) :
    cppcms::application(serv),
    sentences(serv),
    sentencesApi(serv),
    pages(serv),
    users(serv),
    myProfile(serv),
    searches(serv),
    searchesApi(serv),
    languagesApi(serv),
    adminApi(serv)
{

    //TODO maybe move the matching string as a an attribute of the controller?
    add(sentencesApi, "^/api/sentences(.*)", 1);
    add(sentences, "^/sentences(.*)", 1);
    add(users, "^/users(.*)", 1);
    add(myProfile, "^/my-profile(.*)", 1);
    add(searchesApi, "^/api/searches(.*)", 1);
    add(searches, "^/searches(.*)", 1);
    add(languagesApi,"^/api/languages(.*)", 1);
    add(adminApi,"^/api/admin(.*)", 1);
    //NOTE important to add the page controller at the end
    //as its regexp is more global
    add(pages, "(.*)", 1);

    // TODO move this in Languages singleton
    cppcms::json::array langs = settings().at("tatoeba.interfacelangs").array();
    for (
        cppcms::json::array::const_iterator p=langs.begin();
        p!=langs.end();
        ++p
    ) {
        cppcms::json::array lang = p->array();
        lang_map[lang[0].str()]=lang[1].str();
    }
}

/**
 *
 */

static const booster::regex lang_regex("^/(\\w+)(/.*)?$");

void Tatoeba::main(std::string url) {
    /**
     * @todo Choose how we write the languague in the url and implement it
     * @todo implement the default language in order check the session, coockie
     * navigator
     */
    booster::smatch matches;
    booster::regex_match(url, matches, lang_regex);
    std::map<std::string,std::string>::const_iterator p = lang_map.find(
        std::string(matches[1])
    );
    session().load();
    // if we known the language
    if (p != lang_map.end()) {
        //TODO replace this by something more generic
        // This line permit to set in which format date, number etc. will be rendered
        context().locale("en_US.UTF-8");
        
        session()["lang"] = p->first;
        // if the other part of the url is random crap => 404
         
         
        if (!dispatcher().dispatch(matches[2])) {
            response().make_error_response(cppcms::http::response::not_found);
        }
    // if we don't know the lang / the lang is missing in the url
    } else {
        // we set it to english
        // TODO should be the lang provided by the web browser
        std::string defaultLang = "eng";
        session()["lang"] = defaultLang;
        std::string toDispatch = "/" + matches[1] + matches[2];

        if (url == "/") {
            response().set_redirect_header("/" + defaultLang) ;
            return;
        }
        //then it means that only the /lang/ was missing
        //we try to add the language before the previous url
        //TODO maybe we can avoid redirection if we know that
        //the produced url will lead to nowhere
        //but doing this :
        //if (dispatcher().dispatch(toDispatch)) {
        //   redirect
        //} else { 
        //  404
        //}
        //doesn't work  because dispatch actually fill the response
        //so the header can't be written anymore
        //so we need a function that check url without calling the handler
        response().set_redirect_header("/" + defaultLang + toDispatch);
    }
}



} // namespace apps
