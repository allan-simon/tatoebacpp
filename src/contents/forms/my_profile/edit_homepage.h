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


#ifndef TATOEBACPP_MY_PROFILE_EDIT_HOMEPAGE_FORM_H
#define TATOEBACPP_MY_PROFILE_EDIT_HOMEPAGE_FORM_H

#include <cppcms/form.h>
using namespace cppcms;

namespace forms {
namespace my_profile {

    /**
     * @struct EditHomepage
     * Form to edit homepage 
     *
     * @TODO: i18n it
     * @TODO: override the validate function to check the homepage is a
     *        correct webpage
     */
	struct EditHomepage : public cppcms::form {
        
        /**
         * @brief Will contain
         */
		widgets::text homepage;
        
        /**
         * @brief Permit to submit the new homepage
         */
		widgets::submit submit;
		

        /**
         * Default constructor, add all the fields to the form
         * define their names etc.
         */
		EditHomepage(const std::string &homepageText = "") {

			homepage.name("homepage");
			homepage.message("homepage: ");
            homepage.value(homepageText);

            

			submit.name("submit");
			submit.value("Submit");

			*this + homepage + submit;

		}
        
		
	};

} // end of namespace my_profile
} // end of namespace forms
#endif
