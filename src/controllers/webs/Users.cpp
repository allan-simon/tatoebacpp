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

#include <set>

#include <cppcms/archive_traits.h>
#include <cppcms/serialization_classes.h>
#include <cppcms/session_interface.h>

#include "Users.h"
#include "contents/users.h"
#include "models/Users.h"
#include "models/UsersSpokenLangs.h"
#include "contents/Config.h"

namespace controllers {
namespace webs {
/**
 *
 */
Users::Users(cppcms::service &serv) : Controller(serv) {

    usersModel = new models::Users();

    usersSpokenLangsModel= new models::UsersSpokenLangs();


    cppcms::url_dispatcher* d = &dispatcher();
    d->assign("/register-new", &Users::register_new, this);
    d->assign("/register-new_treat", &Users::register_new_treat, this);
  	d->assign("/login", &Users::login, this);
  	d->assign("/login_treat", &Users::login_treat, this);
  	d->assign("/logout", &Users::logout, this);
    d->assign("/all", &Users::all, this);
    d->assign("/profile/(.*)", &Users::profile, this, 1);
}

/**
 *
 */
Users::~Users() {
    delete usersModel;
    delete usersSpokenLangsModel;
}

/**
 *
 */
void Users::register_new() {
    contents::users::RegisterNew c;
    init_content(c);
    

    render("users_register_new", c);
}

/**
 *
 */
void Users::register_new_treat() {
    TREAT_PAGE();

    // TODO directly use the form
    forms::users::RegisterNew form;
    form.load(context());

    if(form.validate()) {
        if (
            usersModel->add(
                form.username.value(),
                form.password.value(),
                form.email.value()
            )
        ) {
            response().set_redirect_header("/");
            session()["name"] = form.username.value();
            session().save();
            //std::cout << "user name: " << session()["name"] << std::endl;
            return;
        }
    }
    
    go_back_to_previous_page();
}

/**
 *
 */
void Users::login() {
    contents::users::Login c;
    init_content(c);

    // we store in the hidden field the page we wanted to access
    // in order to be able to redirect on it after login

    std::string wantedPage = "/" ;
    
    cppcms::http::request::form_type::const_iterator p = request().get().find("from");
    cppcms::http::request::form_type::const_iterator end = request().get().end();

    if (p != end) {
        wantedPage = p->second;
    }

    c.loginUser.previousUrl.value(
        wantedPage
    );

    render("users_login", c);
}

/**
 *
 */
void Users::login_treat() {
    TREAT_PAGE();
    forms::LoginUser loginUser;
    loginUser.load(context());

    std::string username = loginUser.username.value();

    if (
        // TODO move that in the validate function of the form

        usersModel->is_login_correct(
            username,
            loginUser.password.value()
        )
    ) {
        session()["name"] = username;
        session()["userId"] = usersModel->get_id_from_name<std::string>(username);
        session()["depth"] = usersModel->get_depth<std::string>(username);
        session().save();
        

        // we redirect to the page the user was before going
        // on the login page
        response().set_redirect_header(
            loginUser.previousUrl.value()
        );

    } else {
        go_back_to_previous_page();
    }
}

/**
 *
 */
void Users::logout() {
    session().clear();
    response().set_redirect_header(
        request().http_referer()
    );
}


/**
 *
 */
void Users::all() {
    contents::users::All c;
    init_content(c);

    unsigned int page = 0;

    if (request().request_method() == "GET") {
        cppcms::http::request::form_type getData = request().get();
        cppcms::http::request::form_type::const_iterator it;
       
        GET_INT_FIELD(page, "page");
    }



    c.users = usersModel->get_all_users(
        page
    );
    std::cout << "[debug] nbr users: " <<  c.users.size() << std::endl;
    c.baseUrl = "/users/all";

    render("users_all", c);

}

/**
 *
 */
void Users::profile(std::string userName) {
    contents::users::Profile c;
    init_content(c);

    c.user = usersModel->get_user_from_username(
        userName
    );

    c.user.spokenLangs = usersSpokenLangsModel->get_from_user(
        userName
    );

    render("users_profile", c);
}




} // End namespace webs
} // End namespace controllers
