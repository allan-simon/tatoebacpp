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

#ifndef TATOEBACPP_TRANSLATE_SENTENCE_FORM_H
#define TATOEBACPP_TRANSLATE_SENTENCE_FORM_H

#include <cppcms/form.h>
#include "generics/Languages.h"

using namespace cppcms;

namespace forms {
    
    /**
     * @struct TransSentence
     * form to translate a sentence in the database
     */
    struct TransSentence : public cppcms::form {
        /**
         * hidden field to store the id of the sentence we're translating
         */
        widgets::hidden translatedId;
        /**
         * The text of the translation
         */
        widgets::text transString;
        /**
         * Select to choose the language in which the translation
         * is written
         */
        widgets::select transLang;
        widgets::submit submit;        
    
        // init of the form
        /**
         * Constructor
         * id : id of the sentence to be translated
         */
        TransSentence(std::string id = "0") {
            *this + transString + transLang +  translatedId + submit;
            
            translatedId.value(id);

            transString.name("str");

            transLang.add("Unknown","und");

            submit.name("Translate sentence");
            submit.value("translate");

            translatedId.non_empty();
            transString.non_empty();
            // TODO for select I'm sure there's something more specific for
            // selects to say "value must one the possible values of the select"
            transLang.non_empty();
        };
        //TODO factorize this
        void set_langs(
            const std::vector<std::string> &userLangs =
                std::vector<std::string>()
        ) {
            if (!userLangs.empty()) {
                Languages::get_instance()->fill_form_select(
                    transLang,
                    userLangs
                );
            } else {
                Languages::get_instance()->fill_form_select(transLang);
            }
        }
    };
}



#endif



