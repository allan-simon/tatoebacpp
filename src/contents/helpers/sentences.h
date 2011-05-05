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
 * @package  Helpers
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */
#ifndef CONTENTS_HELPER_SENTENCES_H
#define CONTENTS_HELPER_SENTENCES_H

#include "helpers.h"
#include "results/sentences.h"

namespace contents {
    namespace helpers {
        /**
         * @struct Sentences
         * Used everywhere we need to send sentence(s) to the view
         */
        struct Sentences : public Helper {
            /**
             * Collection of Sentences
             */
            results::SentencesPagiVector sentences;
            public:
                /**
                 * Defaut constructor will create an empty helper
                 */
                Sentences() {};
                /**
                 * Constructor, will init the helper with one sentence
                 */
                Sentences(results::Sentence sentence) {
                    if (sentence.exists()) {
                        sentences.push_back(sentence);
                    }

                }
                /**
                 * To know if the helper is empty
                 */
                bool empty() {
                    return sentences.empty();
                }
        };
    }
}

#endif
