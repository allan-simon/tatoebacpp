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


#ifndef TATOEBACPP_MODELS_OF_USERS_H
#define TATOEBACPP_MODELS_OF_USERS_H

#include "models/SqliteModel.h"
#include "results/sentences.h"

namespace models {

class Sentences;

/**
 * @class OfUser
 *
 * @brief Model that contain all the actions to modify/add/get the relation
 *        between a user and the things he can Own (sentences, comments etc.)
 *
 * @since 17 August 2011
 */
class OfUser : public SqliteModel {

    public:
        /**
         * @brief Constructor
         *
         * @since 17 August 2011
         */
        OfUser(cppdb::session sqliteDb);

        OfUser();

        /**
         * @brief Destructor
         *
         * @since 17 August 2011
         */
        ~OfUser();


        /**
         * @brief Set the owner of a sentence
         *
         * @param sentenceId Id of the sentence to adopt
         * @param userId     Id of the owner
         *
         * @return True if the ownership is correctly set, false otherwise
         *
         * @since 17 August 2011
         */
        bool adopt_sentence(
            const int sentenceId,
            const int userId
        );
        
        /**
         * @brief Remove the ownership of a sentence
         *
         * @param sentenceId Id of the sentence to abandon
         *
         * @return True if the sentence is correctly abandonned
         *
         * @since 17 August 2011
         */
        bool abandon_sentence(
            const int sentenceId
        );
    
        /**
         * @brief Permits to know if the given sentence is owned by the given
         *        user
         *
         * @param sentenceId Id of the sentence to check ownership of
         * @param userId     Id of the user we want to check if he owns the
         *                   given sentence
         *
         * @since 20 August 2011
         *
         * @return True if the sentence is owned by that user, false otherwise
         *         or if an error happens
         */
        bool is_sentence_owner(
            const int sentenceId,
            const int userId
        );


        /**
         * @brief Get the owner of a given sentence
         *
         * @param sentenceId Id of the sentence we want to know the owner of
         *
         * @since 20 August 2011
         *
         * @return The name of the user or an empty string if the sentence is
         *         owned by no one
         *
         */
        std::string get_owner_name_of_sentence(
            const int sentenceId
        );

        /**
         * @brief Return a paginated list of sentences owned by a given user
         *
         * @param username Name of the user we want the sentences of
         * @param page     Page number requested (0 = first one)
         *
         * @return A paginated vector of sentences and their translations
         */
        results::PagiSentences sentences_of(
            const std::string &username,
            const int page
        );
};

} // end of namespace models

#endif

