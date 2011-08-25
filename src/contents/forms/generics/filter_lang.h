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


#ifndef TATOEBACPP_FORM_GENERICS_FILTER_LANG_FORM_H
#define TATOEBACPP_FORM_GENERICS_FILTER_LANG_FORM_H


#include <cppcms/form.h>
#include "generics/Languages.h"

namespace forms{
namespace generics {

/**
 * @brief Generic form to use wherever we can filter by language
 */
struct FilterLang : public cppcms::form {

    /**
     * @brief Html select to choose the language to keep
     */
    cppcms::widgets::select filterLang;

    /**
     * @brief Button to submit the form
     */
    cppcms::widgets::submit submit;        


    /**
     * @brief Constructor
     *
     * @param lang Lang to be preselected, "mul" = "any" / no filtering
     */
    FilterLang(std::string lang = "mul") {

        Languages::get_instance()->fill_form_select(filterLang);
        //TODO i18n
        filterLang.add("Any","mul");
        filterLang.selected_id(lang);
        filterLang.non_empty();

        //TODO i18n
        submit.name("Filter");
        submit.value("Filter");

        *this + filterLang + submit;

    }

};



} // end of namespace generics
}// end of namespace forms


#endif


