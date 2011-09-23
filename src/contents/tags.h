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

#ifndef TATOEBA_CONTENTS_TAGS_H
#define TATOEBA_CONTENTS_TAGS_H

#include "contents/content.h"
#include "results/tags.h"

#include "contents/helpers/sentences.h"
#include "contents/forms/generics/filter_lang.h"

namespace contents {
/**
 * @namespace contents::tags
 * @brief contains all the Content structure used by Tags pages
 * @since 16 September 2011
 */
namespace tags {



/**
 * @brief Content structure used by Tags::ViewAll page
 * 
 * @since 16 September 2011
 * 
 */
struct ViewAll : public BaseContent {
    /**
     * @brief List of all the tags supported by tatoeba
     *
     * @since 16 September 2011
     */
    results::TagsList tagsList;
};

/**
 * @brief Content structure used by Tags::sentences_with_tag page
 *
 * @since 23 September 2011
 */
struct SentencesWithTag : public BaseContent {

    /**
     * @brief content helper needed to display the group of sentences
     *
     * @since 23 September 2011
     */
    helpers::Sentences shc;
    
    /**
     * @brief Information about the tag itself
     *
     * @since 23 September 2011
     */
    results::Tag tag;
    
    /**
     * @brief Form to be able to display only sentences in a specific language
     *
     * @since 23 September 2011
     */
    forms::generics::FilterLang filterLang;

};



} // end of namespace tags
} // end of namespace contents

#endif

