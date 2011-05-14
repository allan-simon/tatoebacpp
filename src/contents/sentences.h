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

#ifndef TATOEBACPP_CONTENTS_SENTENCES_H
#define TATOEBACPP_CONTENTS_SENTENCES_H

#include "contents/content.h"
#include "contents/helpers/sentences.h"
#include "contents/forms/add_sentence.h"
#include "contents/forms/edit_text_sentence.h"
#include "contents/forms/edit_lang_sentence.h"
#include "contents/forms/translate_sentence.h"

namespace contents {
    
    /**
     * Base content for every action of the Sentences controller
     */
    struct Sentences : public BaseContent {
        helpers::Sentences shc;
    };

    /**
     * Content used by Sentences::show
     */
    struct SentencesShow : public Sentences {
        /**
         * Id of the sentence we want to show
         * we store it there because maybe the id refers to a non existing
         * sentence
         */
        int id;
    };

    /**
     * Content used by Sentences::add
     */
    struct SentencesAdd : public Sentences {
        /**
         * Form to add a sentence
         */
        forms::AddSentence addSentence;
    };

    /**
     * Content used by Sentences::edit_text
     */
    struct SentencesEditText : public Sentences {
        /**
         * Form to edit the text of a sentence
         */
        forms::EditTextSentence editText;
        /**
         * Id of the sentence we want to edit
         * we store it there because maybe the id refers to a non existing
         * sentence
         */
        int id;

        /**
         * Constructor
         */
        SentencesEditText(std::string idStr, std::string text) :
            editText(idStr, text)
        {
            id = atoi(idStr.c_str());

        }
    };

    /**
     * Content used by Sentences::edit_lang
     */
    struct SentencesEditLang : public Sentences {
        /**
         * Form to change the language of a sentence
         */
        forms::EditLangSentence editLang;
        /**
         * Id of the sentence we want to change the language of
         * we store it there because maybe the id refers to a non existing
         * sentence
         */
        int id;

        /**
         * Constructor
         */
        SentencesEditLang(std::string idStr, std::string lang) :
            editLang(idStr, lang)
        {
            id = atoi(idStr.c_str());

        }
    };

    /**
     * Content used by Sentences::translate
     */
    struct SentencesTrans : public Sentences {
        /**
         * Form to add a translation
         */
        forms::TransSentence transSentence;
        /**
         * Id of the sentence we want to translate
         * we store it there because maybe the id refers to a non existing
         * sentence
         */
        int id;

        /**
         * Constructor
         */
        SentencesTrans(std::string translatedId) :
            transSentence(translatedId)
        {
            id = atoi(translatedId.c_str());

        }
    };



}


#endif
