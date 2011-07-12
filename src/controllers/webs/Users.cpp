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
#include <cppcms/session_interface.h>

#include "Users.h"
#include "contents/users.h"
#include "models/Users.h"
#include "contents/Config.h"

namespace controllers {
namespace webs {
/**
 *
 */
Users::Users(cppcms::service &serv) : Controller(serv) {

    usersModel = new models::Users(cppdb::session(
        "sqlite3:db=" + Config::get_instance()->sqlite3Path
    ));
    cppcms::url_dispatcher* d = &dispatcher();
    d->assign("/register-new", &Users::register_new, this);
    d->assign("/register-new_treat", &Users::register_new_treat, this);
  	d->assign("/login", &Users::login, this);
  	d->assign("/login_treat", &Users::login_treat, this);
  	d->assign("/logout", &Users::logout, this);
    //tatoapp.dispatcher().assign("/users/all((/\\d+)?)", &Users::listMembers, this, 1);
}

/**
 *
 */
Users::~Users() {
    delete usersModel;
}

/**
 *
 */
void Users::register_new() {
    contents::UsersRegisterNew c;
    init_content(c);
    

    render("users_register_new", c);
}

/**
 *
 */
void Users::register_new_treat() {
    TREAT_PAGE();

    contents::UsersRegisterNew c;
    init_content(c);
    c.registerNewUser.load(context());

    if(c.registerNewUser.validate()) {
        if (
            usersModel->add(
                c.registerNewUser.username.value(),
                c.registerNewUser.password.value(),
                c.registerNewUser.email.value()
            )
        ) {
            response().set_redirect_header("/" + c.lang);
            session()["name"] = c.registerNewUser.username.value();
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
    contents::UsersLogin c;
    init_content(c);

    // we store in the hidden field the page we wanted to access
    // in order to be able to redirect on it after login

    std::string wantedPage = "/" + get_interface_lang();
    
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
/*
void Users::list_members(std::string page) {
    int intPage;

    // check if there is a page in argument
    if (page.compare("") == 0) {
        intPage = 1;
    }
    else {
        // convert page from string to integer
        std::string realPage = page.substr(1);  // remove the slash in "/pageNumber"
        intPage = atoi(realPage.c_str());
    }

    contents::AllUsers c;
    init_content(c);
    c.listOfMembers = userModel.getAllUsers();
    render("allusers", c);
}
*/
} // End namespace webs
} // End namespace controllers
