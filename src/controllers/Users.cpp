#include "Controller.h"
#include "controllers/Users.h"
#include "tatoeba.h"
#include <cppcms/session_interface.h>

namespace controllers {

Users::Users(apps::tatoeba& tatoapp) : Controller(tatoapp), userModel(cppdb::session("sqlite3:db=../doc/sqlite3.db")) {
  	tatoapp.dispatcher().assign("/users/check_login", &Users::check_login, this);
  	tatoapp.dispatcher().assign("/users/logout", &Users::logout, this);
}

void Users::check_login() {
    contents::BaseContent c;
    c.login.load(context());

    std::cout << "Hello " << c.login.username.value() << std::endl;
    std::cout << "password : " << c.login.password.value() << std::endl;

    if (userModel.check_login(c.login.username.value(), c.login.password.value())) {
        session()["name"] = "toto";
        response().set_redirect_header("/en");
    }
    else {
        response().set_redirect_header("/fr");
    }
    
}

void Users::logout() {
    session().clear();
    response().set_redirect_header("/en");
}

} // End namespace
