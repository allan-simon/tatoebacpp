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
#include "contents/forms/my_profile/edit_homepage.h"
#include "contents/forms/my_profile/add_spoken_lang.h"
#include "contents/forms/my_profile/edit_spoken_lang.h"

#include "results/users.h"
#include "results/spoken_langs.h"

namespace contents {
namespace my_profile {

/**
 * @struct EditDescription
 * @brief  content used by the MyProfile::edit_description
 *         contain the info to edit one's description
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


/**
 * @struct EditHomepage
 * @brief  content used by the MyProfile::edit_homepage
 *         contain the info to edit one's homepage
 */
struct EditHomepage : public contents::BaseContent {
    forms::my_profile::EditHomepage form;
    std::string username;

    /**
    * @brief             Constructor
    *
    * @param username    name of the current user
    * @param description his homepage (empty if not precised)
    */
    EditHomepage(
        const std::string &username,
        const std::string &homepage = ""
    ) :
        form(homepage),
        username(username)
    {
    };
};


/**
 * @struct AddSpokenLang
 * @brief  content used the MyProfile::add_spoken_lang
 *         contain the info needed for a user to add a language he speaks
 */
struct AddSpokenLang : public contents::BaseContent {

    forms::my_profile::AddSpokenLang form;

};

/**
 * @struct EditSpokenLang
 * @brief  content used by MyProfile::edit_spoken_lang
 *         contain the info needed for a user to edit a language he speaks
 */
struct EditSpokenLang : public BaseContent {

    /**
     * @brief Form to edit a language a user told he can speaks
     */
    forms::my_profile::EditSpokenLang form;
    /**
     * @brief Localized name of the language to edit
     */
    std::string langName;

    EditSpokenLang(const results::SpokenLang &langToEdit) :
        form(langToEdit) 
    {
        langName = Languages::get_instance()->get_name_from_iso(
            langToEdit.langISO
        );
    }

};






} // end of namespace my_profile
} // end of namespace contents

#endif


