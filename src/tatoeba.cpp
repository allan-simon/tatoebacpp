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


#include <iostream>

#include <cppcms/application.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/http_response.h>
#include <cppcms/http_request.h>
#include <cppcms/http_context.h>
#include <cppcms/session_interface.h>



#include "tatoeba.h"

#include "generics/Languages.h"

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
    ofUser(serv),
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
    add(ofUser, "^/of-user(.*)", 1);
    add(myProfile, "^/my-profile(.*)", 1);
    add(searchesApi, "^/api/searches(.*)", 1);
    add(searches, "^/searches(.*)", 1);
    add(languagesApi,"^/api/languages(.*)", 1);
    add(adminApi,"^/api/admin(.*)", 1);
    //NOTE important to add the page controller at the end
    //as its regexp is more global
    add(pages, "/(.*)", 1);


}

/**
 *
 */


void Tatoeba::main(std::string url) {
    /**
     * @todo Choose how we write the languague in the url and implement it
     * @todo implement the default language in order check the session, coockie
     * navigator
     */
    std::cout << "[DEBUG] url: " << url <<std::endl;
    if (request().server_port() == 4242 ) {
        std::cout << "[DEBUG] local version  " <<std::endl;
        context().locale("en_US.UTF-8");
        application::main(url);
        return;
    }
    std::string serverName = request().server_name();
    std::string subdomain = serverName.substr(
        0,
        serverName.find('.')
    );
    std::cout << std::endl;
    std::cout << "[DEBUG] serverName: " << serverName <<std::endl;
    std::cout << "[DEBUG] subdomain: " << subdomain <<std::endl;
    if (session().is_set("interfaceLang")) {
        std::cout << "[DEBUG] in session: " << session()["interfaceLang"] <<std::endl;
    } else {
        std::cout << "[DEBUG] no session lang yet"  <<std::endl;
    }


    // NextGen url "lang.tatoeba.org/url"
    if (Languages::get_instance()->is_interface_lang(subdomain)) {
        if (
            !session().is_set("interfaceLang") ||
            session()["interfaceLang"].empty()
        ) {
            session()["interfaceLang"] = subdomain;
        }
        if (subdomain == session()["interfaceLang"]) {
            context().locale(
                Languages::get_instance()->get_locale_from_lang(subdomain)
            );

            application::main(url);
        } else {

            response().set_redirect_header(
                "http://" + session()["interfaceLang"] + 
                serverName.substr(serverName.find('.')) +
                url
            );

        }
    // no lang inside the server name
    } else {
         
        // in a url tatoeba.org/A/B/C
        // try to see if A is an old style lang
        size_t firstFolderEndPos = url.find('/',1);
        std::string firstFolder = url.substr(
            1,
            firstFolderEndPos -1
        );

        std::cout << "[DEBUG] firstFolder: " << firstFolder <<std::endl;
        if (Languages::get_instance()->is_old_interface_lang(firstFolder)) {
            std::string newLang =Languages::get_instance()->
                get_new_lang_from_old(firstFolder);
            session()["interfaceLang"] = newLang;
            response().set_redirect_header(
                "http://" + newLang + "." +
                serverName +
                url.substr(firstFolderEndPos)
            );
            return;
        } else {
            session()["interfaceLang"] = "en";
            response().set_redirect_header(
                 "http://en." +
                serverName +
                url
            );
            return;
        }
         
    }
    
}



} // namespace apps
