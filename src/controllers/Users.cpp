#include "Controller.h"
#include "controllers/Users.h"
#include "tatoeba.h"
#include <cppcms/session_interface.h>
#include "contents/register.h"
#include "contents/allUsers.h"
#include <vector>
#include "models/Users.h"

namespace controllers {

Users::Users(apps::Tatoeba& tatoapp) : Controller(tatoapp), userModel(cppdb::session("sqlite3:db=../doc/sqlite3.db")) {
    tatoapp.dispatcher().assign("/users/register", &Users::registerUser, this);
  	tatoapp.dispatcher().assign("/users/check_login", &Users::check_login, this);
  	tatoapp.dispatcher().assign("/users/logout", &Users::logout, this);
    tatoapp.dispatcher().assign("/users/all((/\\d+)?)", &Users::listMembers, this, 1);
}

void Users::registerUser() {
    contents::Register c;
    if (request().request_method() == "POST") {
        c.registerForm.load(context());
        if(c.registerForm.validate()) {
            userModel.addUser(
                c.registerForm.username.value(),
                c.registerForm.password.value()
            );
            response().set_redirect_header("/en");
        }
    }

    initContent(c);
    render("registeruser", c);
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

void Users::listMembers(std::string page) {
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
    initContent(c);
    c.listOfMembers = userModel.getAllUsers();
    render("allusers", c);
}

} // End namespace
