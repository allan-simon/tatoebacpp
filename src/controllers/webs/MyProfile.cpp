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
#include <cstdio>

#include <sstream>
#include <string>



#include <cppcms/session_interface.h>
#include <cppcms/http_file.h>

#include "MyProfile.h"
#include "contents/my_profile.h"
#include "contents/users.h"

#include "models/Users.h"
#include "models/UsersSpokenLangs.h"
#include "contents/Config.h"

namespace controllers {
namespace webs {
/**
 *
 */
MyProfile::MyProfile(cppcms::service &serv) : Controller(serv) {

    usersModel = new models::Users(
        cppdb::session(
            "sqlite3:db=" + Config::get_instance()->sqlite3Path
        )
    );

    usersSpokenLangsModel= new models::UsersSpokenLangs(
        cppdb::session(
            "sqlite3:db=" + Config::get_instance()->sqlite3Path
        )
    );



    cppcms::url_dispatcher* d = &dispatcher();
    d->assign("/show$", &MyProfile::show, this);
    d->assign("/edit-description$", &MyProfile::edit_description, this);
    d->assign("/edit-description_treat$", &MyProfile::edit_description_treat, this);

    d->assign("/edit-homepage$", &MyProfile::edit_homepage, this);
    d->assign("/edit-homepage_treat$", &MyProfile::edit_homepage_treat, this);

    d->assign("/add-spoken-lang$", &MyProfile::add_spoken_lang, this);
    d->assign("/add-spoken-lang_treat$", &MyProfile::add_spoken_lang_treat, this);
    
    d->assign("/remove-spoken-lang/(\\w+)$", &MyProfile::remove_spoken_lang, this, 1);

    d->assign("/edit-spoken-lang/(\\w+)$", &MyProfile::edit_spoken_lang, this, 1);
    d->assign("/edit-spoken-lang_treat$", &MyProfile::edit_spoken_lang_treat, this);

    d->assign("/change-avatar$", &MyProfile::change_avatar, this);
    d->assign("/change-avatar_treat$", &MyProfile::change_avatar_treat, this);

    d->assign("/change-password$", &MyProfile::change_password, this);
    d->assign("/change-password_treat$", &MyProfile::change_password_treat, this);

    d->assign("/change-depth$", &MyProfile::change_depth, this);
    d->assign("/change-depth_treat$", &MyProfile::change_depth_treat, this);

}

/**
 *
 */
MyProfile::~MyProfile() {
    delete usersModel;
    delete usersSpokenLangsModel;
}


/**
 *
 */
void MyProfile::show() {
    
    CHECK_PERMISSION_OR_GO_TO_LOGIN(); 

    contents::users::Profile c;
    init_content(c);


    c.user = usersModel->get_user_from_username(
        session()["name"]
    );

    int userId = 0;
    std::istringstream(session()["userId"]) >> userId;

    c.user.spokenLangs =usersSpokenLangsModel->get_from_user(
        userId
    );

    render("my_profile_show", c);
}


/**
 *
 */
void MyProfile::edit_description() {
    CHECK_PERMISSION_OR_GO_TO_LOGIN(); 


    std::string username = session()["name"];
    contents::my_profile::EditDescription c (
        username,
        usersModel->get_description_from_username(
            username
        )
    );
    init_content(c);


    render("my_profile_edit_description", c);

}


/**
 *
 */
void MyProfile::edit_description_treat() {
    TREAT_PAGE();
    forms::my_profile::EditDescription form;
    form.load(context());

    if (form.validate()) {
        usersModel->update_description(
            session()["name"],
            form.description.value()
        );
    }

    go_to_profile_page();
}





/**
 *
 */
void MyProfile::edit_homepage() {
    CHECK_PERMISSION_OR_GO_TO_LOGIN(); 


    std::string username = session()["name"];
    contents::my_profile::EditHomepage c (
        username,
        usersModel->get_homepage_from_username(
            username
        )
    );
    init_content(c);


    render("my_profile_edit_homepage", c);

}


/**
 *
 */
void MyProfile::edit_homepage_treat() {
    TREAT_PAGE();
    forms::my_profile::EditHomepage form;
    form.load(context());

    if (form.validate()) {
        usersModel->update_homepage(
            session()["name"],
            form.homepage.value()
        );
    }

    go_to_profile_page();

}


/**
 *
 */
void MyProfile::add_spoken_lang() {
    CHECK_PERMISSION_OR_GO_TO_LOGIN(); 

    contents::my_profile::AddSpokenLang c;
    init_content(c);


    render("my_profile_add_spoken_lang", c);

}


/**
 *
 */
void MyProfile::add_spoken_lang_treat() {
    TREAT_PAGE();
    forms::my_profile::AddSpokenLang form;
    form.load(context());

    if (form.validate()) {

        int userId = 0;
        std::istringstream(session()["userId"]) >> userId;

        usersSpokenLangsModel->add(
            userId,
            form.spokenLang.selected_id(),
            form.proeficiencyLevel.selected(),
            form.isNative.value()
        );
    }

    go_to_profile_page();

}

/**
 *
 */
void MyProfile::remove_spoken_lang(std::string langISO) {
    CHECK_PERMISSION_OR_GO_TO_LOGIN(); 

    int userId = 0;
    std::istringstream(session()["userId"]) >> userId;

    usersSpokenLangsModel->remove(
        userId,
        langISO
    );

    go_to_profile_page();

}

/**
 *
 */
void MyProfile::edit_spoken_lang(std::string langISO) {
    CHECK_PERMISSION_OR_GO_TO_LOGIN(); 

    int userId = 0;
    std::istringstream(session()["userId"]) >> userId;

    //TODO redirect if lang does not exist for that user

    results::SpokenLang langToEdit = usersSpokenLangsModel->get_one(
        userId,
        langISO
    );

    contents::my_profile::EditSpokenLang c(langToEdit);

    init_content(c);

    render("my_profile_edit_spoken_lang", c);

}


/**
 *
 */
void MyProfile::edit_spoken_lang_treat() {
    TREAT_PAGE();
    forms::my_profile::EditSpokenLang form;
    form.load(context());

    if (form.validate()) {

        int userId = 0;
        std::istringstream(session()["userId"]) >> userId;

        usersSpokenLangsModel->edit(
            userId,
            form.spokenLang.value(),
            form.proeficiencyLevel.selected(),
            form.isNative.value()
        );
    }

    go_to_profile_page();

}


/**
 *
 */
void MyProfile::change_avatar() {
    CHECK_PERMISSION_OR_GO_TO_LOGIN(); 


    std::string username = session()["name"];
    contents::my_profile::ChangeAvatar c (
        usersModel->get_avatar(
            username
        )
    );
    init_content(c);


    render("my_profile_change_avatar", c);

}
/**
 *
 */
void MyProfile::change_avatar_treat() {
    TREAT_PAGE();
    forms::my_profile::ChangeAvatar form;
    form.load(context());
    if (form.validate()) {

        std::string filename = form.avatar.value()->filename(); 

        form.avatar.value()->save_to(
            filename
        );
        
        usersModel->update_avatar(
            session()["name"],
            filename
        );
       
        std::remove(filename.c_str());

    } else {
        //TODO implement something to be able to show it
        // on the html (session based ?)
        std::cout << "error" << std::endl;
    }

    go_to_profile_page();

}


/**
 *
 */
void MyProfile::change_password() {
    CHECK_PERMISSION_OR_GO_TO_LOGIN(); 

    contents::my_profile::ChangePassword c ;
    init_content(c);

    render("my_profile_change_password", c);

}


/**
 *
 */
void MyProfile::change_password_treat() {
    TREAT_PAGE();
    forms::my_profile::ChangePassword form;
    form.load(context());
    if (form.validate()) {
        
        bool updated = usersModel->update_password(
            session()["name"],
            form.previous.value(),
            form.newPassword.value()
        );

        //TODO replace this by something better
        // (old password wrong ? not typed two time the same pass? etc.)
        if (!updated) {
            std::cout << "[DEBUG]: update password faield" <<  std::endl;
        }

    }

    go_to_profile_page();

}


/**
 *
 */
void MyProfile::change_depth() {
    CHECK_PERMISSION_OR_GO_TO_LOGIN(); 


    std::string username = session()["name"];
    contents::my_profile::ChangeDepth c (
        usersModel->get_depth<int>(
            username
        )
    );
    init_content(c);


    render("my_profile_change_depth", c);

}


/**
 *
 */
void MyProfile::change_depth_treat() {
    TREAT_PAGE();
    forms::my_profile::ChangeDepth form;
    form.load(context());

    if (form.validate()) {
        int newDepth = form.newDepth.value();
        usersModel->update_depth(
            session()["name"],
            newDepth
        );
        std::ostringstream oss;
        oss << newDepth;
        session()["depth"] = oss.str();
    }

    go_to_profile_page();

}






/**
 *
 */
inline void MyProfile::go_to_profile_page() {
    response().set_redirect_header(
        "/" + get_interface_lang() +
        "/my-profile/show"
    );
}

} // End namespace webs 
} // End namespace controllers
