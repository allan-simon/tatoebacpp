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


#ifndef TATOEBACPP_MY_PROFILE_ADD_SPOKEN_LANG_FORM_H
#define TATOEBACPP_MY_PROFILE_ADD_SPOKEN_LANG_FORM_H

#include <cppcms/form.h>
#include "generics/Languages.h"


namespace forms {
namespace my_profile {

    /**
     * @struct AddSpokenLang
     * @brief Form for the user to add a language he speaks 
     *
     * @TODO: i18n it
     */
	struct AddSpokenLang : public cppcms::form {
        
        /**
         * @brief 
         */
        cppcms::widgets::select spokenLang;

        /**
         * @brief 
         */
        cppcms::widgets::select proeficiencyLevel;

        /**
         * @brief 
         */
        cppcms::widgets::checkbox isNative;

        /**
         * @brief 
         */
        cppcms::widgets::submit submit;        
        /**
         * Default constructor, add all the fields to the form
         * define their names etc.
         */
		AddSpokenLang() {

            Languages::get_instance()->fill_form_select(spokenLang);
            
            
            proeficiencyLevel.add("1");
            proeficiencyLevel.add("2");
            proeficiencyLevel.add("3");
            proeficiencyLevel.add("4");
            proeficiencyLevel.name("proeflevel");
            proeficiencyLevel.message(
                "Grade your proeficiency in this language:"
            );

            isNative.name("isnative");
            isNative.message("Are you a native of this language ?");

			submit.name("submit");
			submit.value("Submit");

			*this + spokenLang + proeficiencyLevel + isNative + submit;

		}
        
		
	};

} // end of namespace my_profile
} // end of namespace forms
#endif
