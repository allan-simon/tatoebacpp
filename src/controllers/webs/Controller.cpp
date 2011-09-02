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
 * @package  Controllers
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */


#include "Controller.h"
#include <cppcms/serialization_classes.h>
#include <cppcms/archive_traits.h>
#include <cppcms/session_interface.h>
#include <cppcms/filters.h>

#include "contents/content.h"

#include "models/UsersSpokenLangs.h"
#include "contents/Config.h"

namespace controllers {
namespace webs {

/**
 *
 */
Controller::Controller(cppcms::service &serv) :
    controllers::generics::Controller(serv)
{


}

/**
 *
 */
void Controller::init_content(contents::BaseContent& content) {
    
    response().content_encoding("UTF-8");
    response().set_content_header("text/html; charset=UTF-8");

    content.searchesSimple.set_langs(
        get_current_user_spoken_langs()
    );

    content.interfaceLang.set_langs();
    //std::cout << "user name: " << session()["name"] << std::endl;
    if (session().is_set("name")) {
        content.usersHelper.username = session()["name"];
    }

    if (session().is_set("message")) {
        content.message = session()["message"];
        session().erase("message");
    }
}


/**
 *
 */
inline bool Controller::is_logged() {
    return !session()["name"].empty();
}


void Controller::go_to_sentence(int sentenceId) {
    std::ostringstream oss;
    oss << sentenceId;

    response().set_redirect_header(
        "/sentences/show"
        "/" + oss.str()
    );
}

/**
 *
 */
void Controller::go_to_sentence(std::string sentenceId) {

    response().set_redirect_header(
        "/sentences/show"
        "/" + sentenceId
    );
}




/**
 *
 */
void Controller::go_back_to_previous_page() {
    //std::cout << "referer : " << request().http_referer() << std::endl;
    
    //TODO we do not handle the case where the referer is not a valid page
    // "*_treat" page, or page that require a priviledge that the user does
    // not have anymore (if session has expired etc.)
    response().set_redirect_header(
        request().http_referer()
    );
}


/**
 *
 */
bool Controller::check_permission() {

    //TODO for the moment we do not handle case
    // when you're logged but you're current group has not
    // enough priviledges
    if (!is_logged()) {
        std::ostringstream oss;
        
        oss << cppcms::filters::urlencode(
           request().path_info()
        );

        response().set_redirect_header(
            "/users/login"
            "?from=" + oss.str()
        );
        return false;
    }
    return true;
}

/**
 *
 */
int Controller::get_current_user_id() {
    //std::cout << "[NOTICE] current id:" << session()["userId"] << std::endl;
    return atoi(session()["userId"].c_str());
}


/**
 *
 */
std::vector<std::string> Controller::get_current_user_spoken_langs() {

    // will contain the iso codes of the languages to keep
    std::vector<std::string> isos;

    std::string username = session()["name"];
    std::string key = "langs_" + username;

    // if not logged => no filtering
    if (username.empty()) {
        return isos;
    }
    
    // if not "no_langs_filter" set as get parameter
    // => no filtering
    if (request().get().find("no_langs_filter") !=  request().get().end()) {
        return isos; 
    }

    std::string data;
    // we first check if we have this vector in cache
    cache().fetch_frame(
        key,
        data,
        true
    );
    // if not we regenerate it
    if (data.empty()) {
        models::UsersSpokenLangs usersSpokenLangsModel =  models::UsersSpokenLangs(
            cppdb::session(
                "sqlite3:db=" + Config::get_instance()->sqlite3Path
            )
        );

        isos = usersSpokenLangsModel.get_iso_code_vector(
                username
        );
        
        // we serliazed and save it for later use
        cppcms::archive a;
        a & isos;
        std::set<std::string> tags;
        tags.insert(key);
        cache().store_frame(
            key,
            a.str(),
            tags,
            -1,
            true
        );


    // otherwise we just read the seriliazed data
    } else {
        cppcms::archive a; 
        a.mode(cppcms::archive::load_from_archive);
        a.str(data);
        a >> isos;
    }
    return isos;

}



/**
 *
 */
int Controller::get_depth() {
    if (is_logged()) {
        int depth = 0;
        std::istringstream(session()["depth"]) >> depth;
        return depth; 
    }

    return DEFAULT_DEPTH; 
}


/**
 *
 */
unsigned int Controller::get_page() {
    int page = 0;
    if (request().request_method() == "GET") {
        cppcms::http::request::form_type getData = request().get();
        cppcms::http::request::form_type::const_iterator it;
       
        GET_INT_FIELD(page, "page");
    }
    return page;
}

/**
 *
 */

void Controller::set_message(std::string message) {

    session()["message"] = message;
}



} // End namespace webs
} // End namespace controllers
