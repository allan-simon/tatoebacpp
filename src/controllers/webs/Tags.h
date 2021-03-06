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
 * @package  Controllers
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */

#ifndef CONTROLLERS_TAG_H
#define CONTROLLERS_TAG_H

#include "Controller.h"

#include "models/Tags.h"

namespace controllers {
namespace webs { 

/**
 * @brief Controller class to handle all the pages related to tags
 *
 * @since 16 September 2011
 */
class Tags : public Controller {

    private:
        /**
         * @brief Model class for tags, used to access the database
         *
         * @since 16 September 2011
         */
        models::Tags *tagsModel;

	public:
        /**
         * @brief Constructor, will attach the url to the dispatcher
         * and instantiate the model
         *
         * @param serv Server to which we will attach that controller
         *
         * @since 16 September 2011
         */
		Tags(cppcms::service &serv);
        /**
         * @brief Destructor
         *
         * @since 16 September 2011
         */
        ~Tags();


        /**
         * @brief Display a page containing all supported tags and number of
         * sentences tagged with each tag
         *
         * @since 16 September 2011
         */
        void view_all();


        /**
         * @brief Display a page containing all the sentences with a given
         *  tag and other extra information about this tag
         *
         * @param tagName Internal name of the tag
         *
         * @since 23 September 2011
         */
        void sentences_with_tag(std::string tagName);


        /**
         * @brief same as Tags::sentences_with_tag but only sentences in a
         *        specific language
         *
         * @param tagName    Internal name of the tag
         * @param inLanguage Will keep only the sentence in this language
         *                   (iso 639-3 code)
         *
         * @since 28 September 2011
         */
        void sentences_with_tag_in(
            std::string tagName,
            std::string inLanguage
        );

        /**
         * @brief Display nothing, only treat the filter by language form
         *        and redirect to the correct page
         *
         * @param tagName We will filter all the sentences which possess this
         *                tag
         *
         * @since 29 September 2011
         */
        void sentences_with_tag_in_treat(
            std::string tagName 
        );



        /**
         * @brief Display nothing, use to treat the form to add a tag on
         *        a sentence
         *
         * @since 23 September 2011
         */
        void add_treat();

        /**
         * @brief Display nothing, use to remove a tag on a sentence
         *
         * @param sentenceIdStr Id on the sentence we're going to remove a tag
         * @param tagIdStr      Id of the tag to remove on that sentence
         *
         * @since 28 September 2011
         */
        void remove_from_sentence(
            std::string sentenceIdStr,
            std::string tagIdStr
        );

        
};


} // End namespace webs 
} // End namespace controllers



#endif
