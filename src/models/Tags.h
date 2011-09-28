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
 * @package  Models
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */ 

#ifndef MODELS_TAGS_H
#define MODELS_TAGS_H

#include "models/SqliteModel.h"
#include "results/tags.h"
#include "results/sentences.h"

namespace models {


/**
 * @brief Model class used to do all the database requests
 *  related to tags
 *
 * @since 9 September 2011
 */
class Tags : public SqliteModel {
    private:
    public:
        /**
         * @brief Constructor
         *
         * @since 9 September 2011
         */
        Tags(cppdb::session sqliteDb);

        Tags();

        /**
         * @brief Destructor
         *
         * @since 9 September 2011
         */
        ~Tags();

        /*
        void add_requested(
            std::string name,
            std::string description,
            int userId            
        );
        */

        /**
         * @brief Retrieve all the tags supported by tatoeba
         *
         * @return The complete list of tags
         *
         * @since 9 September 2011
         */
        results::TagsList get_all();


        /**
         * @brief Retrieve all the sentences with a given tag
         *
         * @param tagName Internal name of the tag
         * @param page    Number of the page requested, as results are
         *                paginated
         *
         * @return Paginated list of sentences
         *
         * @since 23 September 2011
         */
        results::PagiSentences sentences_with_tag(
            const std::string &tagName,
            const int page
        );

        /**
         * @brief Get all the information about a given tag 
         *
         * @param standardName Internal name of the tag
         *
         * @return The tag and all its infos
         *
         * @since 23 September 2011
         */
        results::Tag get(const std::string &standardName);

        /**
         * @brief Get the id of a given tag
         *
         * @param realName Human readable name of a tag
         *
         * @return The id of this tag, 0 if this tag does not exist
         *
         * @since 26 September 2011
         */
        int get_id(const std::string &realName);


        /**
         * @brief Apply a tag on a sentence
         *
         * @param sentenceId Id of the sentence on which to apply the tag 
         * @param tagId      Id of the tag to apply
         * @param userId     Id of the user who applies this tag
         *
         * @return True if the tag is successfly apply, false otherwise
         *
         * @since 26 September 2011
         */
        bool tag_sentence(
            const int sentenceId,
            const int tagId,
            const int userId
        );


        /**
         * @brief Retrieve all the tags on a given sentence
         *
         * @param sentenceId Id of the sentence we want the tags of
         *
         * @return Return the list of tags on this sentence, and by who and
         *         when they have been added
         *
         * @since 27 September 2011
         */
        results::TagsList on_sentence(const int sentenceId);

        /**
         * @brief Remove a tag from a sentence
         *
         * @param sentenceId Id of the sentence on which to remove the tag
         * @param tagId      Id of the tag to remove
         *
         * @return True if the tag was correctly removed, false otherwise
         *
         * @since 28 September 2011
         */
        bool remove_from_sentence(
            const int sentenceId,
            const int tagId
        );
};


} // end of namespace models
#endif
