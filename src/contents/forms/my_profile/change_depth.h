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


#ifndef TATOEBACPP_MY_PROFILE_CHANGE_DEPTH_FORM_H
#define TATOEBACPP_MY_PROFILE_CHANGE_DEPTH_FORM_H

//TODO replace me by something which depend on the user
//     grade
#define MAX_DEPTH 5 


#include <cppcms/form.h>
using namespace cppcms;

namespace forms {
namespace my_profile {

    /**
     * @struct ChangeDepth
     * Form to change the depth of translations for current user 
     *
     * @TODO: i18n it
     * @TODO: override 
     */
	struct ChangeDepth : public cppcms::form {
        
        /**
         * @brief Will contain the new depth
         */
		widgets::numeric<int> newDepth;
        
        /**
         * @brief Permit to submit the new depth
         */
		widgets::submit submit;
		

        /**
         * Default constructor, add all the fields to the form
         * define their names etc.
         */
		ChangeDepth(const int currentDepth = 0) {

            newDepth.message(
                cppcms::locale::translate("New depth:")
            );
            newDepth.name("newdepth");
            newDepth.range(0,MAX_DEPTH);
            newDepth.value(currentDepth);

			submit.name("Change");
			submit.value(
                cppcms::locale::translate("Change")
            );

			*this + newDepth + submit;

		}
        
		
	};

} // end of namespace my_profile
} // end of namespace forms
#endif

