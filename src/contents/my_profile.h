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

#ifndef TATOEBA_CONTENTS_MY_PROFILE_H
#define TATOEBA_CONTENTS_MY_PROFILE_H

#include "contents/content.h"
#include "contents/forms/my_profile/edit_description.h"

#include "results/users.h"

namespace contents {
namespace my_profile {

/**
 * @struct RegisterNew
 * @brief  content used by the Users::register_new
 *         contain the info for the register new user page
 */
struct EditDescription : public BaseContent {
    forms::my_profile::EditDescription form;
    std::string username;

    /**
    * @brief             Constructor
    *
    * @param username    name of the current user
    * @param description his description (empty if not precised)
    */
    EditDescription(
        const std::string &username,
        const std::string &description = ""
    ) :
        form(description),
        username(username)
    {
    };
};



} // end of namespace my_profile
} // end of namespace contents

#endif


