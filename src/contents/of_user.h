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


#ifndef TATOEBA_CONTENTS_OF_USER_H
#define TATOEBA_CONTENTS_OF_USER_H

#include "contents/helpers/sentences.h"
#include "contents/content.h"


namespace contents {
namespace of_user {

/**
 * @brief Content used in OfUser::translate_sentences_of
 */
struct TranslateSentencesOf : public BaseContent {

    /**
     * @brief content helper needed to display the group of sentences
     */
    helpers::Sentences shc;
    
    /**
     * @brief Name of the user we're displaying the sentences of
     */
    std::string username;
    

};

/**
 * @brief Content used in OfUser::sentences_of
 */
struct SentencesOf : public TranslateSentencesOf {};


} // end of namespace of_user
} // end of namespace contents


#endif
