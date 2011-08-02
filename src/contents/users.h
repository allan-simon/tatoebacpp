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
 * @package  Contents
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */

#ifndef TATOEBA_CONTENTS_USERS_H
#define TATOEBA_CONTENTS_USERS_H

#include "contents/content.h"
#include "contents/forms/register.h"
#include "contents/forms/login.h"

#include "results/users.h"

namespace contents {
namespace users {

/**
 * @struct RegisterNew
 * @brief  content used by the Users::register_new
 *         contain the info for the register new user page
 */
struct RegisterNew : public BaseContent {
    forms::users::RegisterNew registerNew;
};

/**
 * @struct Login
 * @brief  content used by Users::login
 *         contain the info for the login page
 */
struct Login : public BaseContent {
    forms::LoginUser loginUser;
};

/**
 * @struct All
 * @brief content used by Users::all
 *        contain the list of tatoeba's users
 */
struct All : public BaseContent {
    results::PagiUsers users;     
    std::string baseUrl;
};


/**
 * @struct Profile
 * @brief content used by Users::profile
 *        contain the information about the requested user
 */
struct Profile : public BaseContent {
    results::User user;     
};




} // end of namespace users
} // end of namespace contents

#endif

