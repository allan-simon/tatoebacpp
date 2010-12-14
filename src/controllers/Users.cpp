#include "Controller.h"
#include "controllers/Users.h"
#include "tatoeba.h"
#include <cppcms/session_interface.h>

namespace controllers {

Users::Users(apps::tatoeba& tatoapp) : Controller(tatoapp) {
  	tatoapp.dispatcher().assign("/users/check_login", &Users::check_login, this);
  	tatoapp.dispatcher().assign("/users/logout", &Users::logout, this);
}

void Users::check_login() {
	std::cout << "=> login checking..." << std::endl;
	
    contents::BaseContent c;
    c.login.load(context());
    std::cout << "Hello " << c.login.username.value() << std::endl;
	// test for the login form
	/*if (request().request_method() == "POST") {
		std::cout <<request().post() << std::endl;
	}*/

    session()["name"] = "toto";
    response().set_redirect_header("/en");
}

void Users::logout() {
    session().clear();
    response().set_redirect_header("/en");
}

} // End namespace
