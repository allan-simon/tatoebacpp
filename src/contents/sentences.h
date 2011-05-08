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
         * Form to add a sentece
         */
        forms::AddSentence addSentence;
    };
}


#endif
