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
#include "contents/forms/generics/filter_lang.h"

namespace contents {
namespace of_user {


/**
 * @brief Base structure used for the pages which display sentences
 *        of a specific user
 *
 * @since 24 August 2011
 */
struct SentencesOfBase : public BaseContent {

    /**
     * @brief content helper needed to display the group of sentences
     *
     * @since 24 August 2011
     */
    helpers::Sentences shc;
    
    /**
     * @brief Name of the user we're displaying the sentences of
     *
     * @since 24 August 2011
     */
    std::string username;
    
    /**
     * @brief Form to be able to display only sentences in a specific language
     *
     * @since 24 August 2011
     */
    forms::generics::FilterLang filterLang;

    /**
     * @brief Constructor
     * 
     * @param selectedLang The default language selected for the filtering
     *
     * @since 24 August 2011
     */
    SentencesOfBase(const std::string& selectedLang = "mul"):
        filterLang(selectedLang)
    {};
};

/**
 * @brief Base structure used for the pages which display sentences
 *        of a specific user and filtered in a specific language
 *
 * @since 24 August 2011
 */
struct SentencesOfInBase : public SentencesOfBase {
    std::string inLanguage;
    SentencesOfInBase(const std::string& selectedLang = "mul"):
        SentencesOfBase(selectedLang)
    {};

};


/**
 * @brief Content used in OfUser::translate_sentences_of
 *
 * @since 24 August 2011
 */
struct TranslateSentencesOf : public SentencesOfBase {};

/**
 * @brief Content used in OfUser::sentences_of
 *
 * @since 24 August 2011
 */
struct SentencesOf : public SentencesOfBase {};

/**
 * @brief Content used in OfUser::translate_sentences_of_in
 *
 * @since 24 August 2011
 */
struct TranslateSentencesOfIn : public SentencesOfInBase {

    /**
     * @brief Constructor
     * 
     * @param selectedLang The default language selected for the filtering
     *
     * @since 24 August 2011
     */
    TranslateSentencesOfIn(const std::string& selectedLang = "mul"):
        SentencesOfInBase(selectedLang)
    {};
};

/**
 * @brief Content used in OfUser::sentences_of_in
 *
 * @since 24 August 2011
 */
struct SentencesOfIn : public SentencesOfInBase {

    /**
     * @brief Constructor
     * 
     * @param selectedLang The default language selected for the filtering
     *
     * @since 24 August 2011
     */
    SentencesOfIn(const std::string& selectedLang = "mul"):
        SentencesOfInBase(selectedLang)
    {};
};


} // end of namespace of_user
} // end of namespace contents


#endif
