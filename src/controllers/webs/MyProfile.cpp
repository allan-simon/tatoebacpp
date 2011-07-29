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

#include "MyProfile.h"
#include "contents/users.h"
#include "models/Users.h"
#include "contents/Config.h"

namespace controllers {
namespace webs {
/**
 *
 */
MyProfile::MyProfile(cppcms::service &serv) : Controller(serv) {

    usersModel = new models::Users(cppdb::session(
        "sqlite3:db=" + Config::get_instance()->sqlite3Path
    ));
    cppcms::url_dispatcher* d = &dispatcher();
    d->assign("/show", &MyProfile::show, this);
}

/**
 *
 */
MyProfile::~MyProfile() {
    delete usersModel;
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

    render("my_profile_show", c);
}

} // End namespace webs 
} // End namespace controllers
