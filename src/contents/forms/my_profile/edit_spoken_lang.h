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


#ifndef TATOEBACPP_MY_PROFILE_EDIT_SPOKEN_LANG_FORM_H
#define TATOEBACPP_MY_PROFILE_EDIT_SPOKEN_LANG_FORM_H

#include <cppcms/form.h>
#include "results/spoken_langs.h"


namespace forms {
namespace my_profile {

    /**
     * @struct AddSpokenLang
     * @brief Form for the user to edit a language he speaks 
     *
     * @TODO: i18n it
     */
	struct EditSpokenLang : public cppcms::form {
        /**
         * @brief Hidden field to store the code of the language to edit
         */
        cppcms::widgets::hidden spokenLang;
        
        /**
         * @brief Select to change the level of that user in this language
         */
        cppcms::widgets::select proeficiencyLevel;

        /**
         * @brief To select if the user is or not a native in that language
         */
        cppcms::widgets::checkbox isNative;

        /**
         * @brief Button to submit the form
         */
        cppcms::widgets::submit submit;        

    
        /**
         * @brief Default constructor
         */
        EditSpokenLang() {
            init();
        }
        /**
         * @ brief Constructor, add all the fields to the form
         * define their names etc.
         *
         * @param langToEdit Structure used to init the form with
         *        the right value
         */
        EditSpokenLang(const results::SpokenLang &langToEdit) {
            init();
            // put the default values
            spokenLang.value(langToEdit.langISO);
            proeficiencyLevel.selected(langToEdit.proeficiency);
            isNative.value(langToEdit.isNative);


		}
        
        private:
            /**
             * @brief Create the widgets of the form
             */
            void init() {
                spokenLang.name("spokenlang");

                proeficiencyLevel.add("C2");
                proeficiencyLevel.add("C1");
                proeficiencyLevel.add("B2");
                proeficiencyLevel.add("B1");
                proeficiencyLevel.add("A2");
                proeficiencyLevel.add("A1");

                proeficiencyLevel.name("proefiency");
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



} // end namespace my_profile
} // end namespace forms

#endif
