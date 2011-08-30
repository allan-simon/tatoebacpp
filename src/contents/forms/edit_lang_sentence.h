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

#ifndef TATOEBACPP_EDIT_LANG_SENTENCE_FORM_H
#define TATOEBACPP_EDIT_LANG_SENTENCE_FORM_H

#include <cppcms/form.h>
#include "generics/Languages.h"

using namespace cppcms;

namespace forms {
    
    /**
     * @struct EditLangSentence
     * form to edit the language of a sentence
     */
    struct EditLangSentence : public cppcms::form {
        /**
         * hidden field to store the id of the sentence we're editing
         */
        widgets::hidden sentenceId;
        /**
         * Select to choose the new language
         */
        widgets::select newLang;
        
        widgets::submit submit;        
    
        // init of the form
        /**
         * Constructor
         */
        EditLangSentence(std::string id = "0", std::string lang = "und") {
            *this + sentenceId + newLang + submit;


            newLang.add("Unknown","und");
            Languages::get_instance()->fill_form_select(newLang);
            newLang.selected_id(lang);

            
            sentenceId.name("id");
            sentenceId.value(id);
            sentenceId.non_empty();


            submit.name("Edit language");
            submit.value("edit");

            newLang.non_empty();
        };

    };
}



#endif



