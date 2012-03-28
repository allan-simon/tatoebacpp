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
 * @package  Forms
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */


#ifndef TATOEBACPP_MY_PROFILE_EDIT_DESCRIPTION_FORM_H
#define TATOEBACPP_MY_PROFILE_EDIT_DESCRIPTION_FORM_H

#include <cppcms/form.h>
using namespace cppcms;

namespace forms {
namespace my_profile {

    /**
     * @struct
     * Form to log in
     *
     * @todo i18n it
     */
    struct EditDescription : public cppcms::form {
        
        /**
         * @brief Will contain
         */
        widgets::textarea description;
        
        /**
         * @brief Permit to submit the new description
         */
        widgets::submit submit;
        

        /**
         * Default constructor add all the fields to the form
         * define their names etc.
         */
        EditDescription(const std::string &descriptionText = "") {

            description.name("description");
            description.message("Description : ");
            description.value(descriptionText);
            description.rows(10);
            description.cols(66);

            

            submit.name("submit");
            submit.value("Log in");

            add(description);
            add(submit);

        }
        
        
    };

} // end of namespace my_profile
} // end of namespace forms
#endif
