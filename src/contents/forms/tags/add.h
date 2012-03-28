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


#ifndef TATOEBACPP_TAGS_ADD_TAG_FORM_H
#define TATOEBACPP_TAGS_ADD_TAG_FORM_H

#include <cppcms/form.h>
using namespace cppcms;

namespace forms {
namespace tags {

    /**
     * @struct Add
     * Form to add a tag on a sentence
     *
     * @since 23 September 2011
     *
     * @TODO: i18n it
     */
    struct Add : public cppcms::form {
        
        /**
         * @brief Will contain the tag to add
         *
         * @since 23 September 2011
         */
        widgets::text tag;

        /**
         * @brief Hidden field that will contain the sentence id that we're
         * going to tag
         *
         * @since 23 September 2011
         */
       
        widgets::hidden sentenceId;
        
        /**
         * @brief Permit to submit the new tag
         *
         * @since 23 September 2011
         */
        widgets::submit submit;
        

        /**
         * @brief Default constructor, add all the fields to the form
         * define their names etc.
         *
         * @since 23 September 2011
         */
        Add(std::string sentenceIdStr = ""){

            sentenceId.value(sentenceIdStr);
            
            tag.name("addtag");
            

            submit.name("submit");
            submit.value("+");

            sentenceId.non_empty();
            tag.non_empty();
    
            add(tag);
            add(sentenceId);
            add(submit);

        }
        
        
    };

} // end of namespace tags
} // end of namespace forms
#endif
