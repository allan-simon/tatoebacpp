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



#ifndef CONTROLLERS_WEBS_OF_USER_H
#define CONTROLLERS_WEBS_OF_USER_H

#include <iostream>
#include "Controller.h"

namespace models {
    class OfUser;
}

namespace controllers {
namespace webs {

/**
 * @class OfUser
 *
 * @brief Controller that contain all the actions related to things a user can
 *        Own (sentences, comments etc.)
 *
 * @since 17 August 2011
 */
class OfUser : public Controller {

    private:

        /**
         * @brief Model for the controller
         *
         * @since 17 August 2011
         */
        models::OfUser *ofUsersModel;

    public:
        /**
         * @brief Constructor
         *
         * @since 17 August 2011
         */
        OfUser(cppcms::service &serv);
        
        /**
         * @brief Destructor
         *
         * @since 17 August 2011
         */
        ~OfUser();

        /**
         * @brief Will try to set the current user as the owner of the given
         *        sentence
         *
         * @param sentenceId Id of the sentence the user wants to adopt
         *
         * @since 17 August 2011
         */
        void adopt_sentence(
            std::string sentenceId
        );

        /**
         * @brief Will try to remove the ownership of the given sentence
         *
         * @param sentenceId Id of the sentence the user wants to abandon
         *
         * @since 20 August 2011
         */
        void abandon_sentence(
           std::string sentenceId
        );

        /**
         * @brief Get all the sentences owned by a given user
         *        (paginated, lang filtered), in a simple listing
         *        (no translation nor menu to translate etc.)
         *
         * @param username Name of the user we want the sentences of
         *
         * @since 17 August 2011
         */
        void sentences_of(
            std::string username
        );

        /**
         * @brief same as OfUser::sentences_of but only sentences in a
         *        specific language
         *
         * @param username   Name of the user we want the sentences of
         * @param inLanguage Will keep only the sentence in this language
         *                   (iso 639-3 code)
         *
         * @since 24 August 2011
         */
        void sentences_of_in(
            std::string username,
            std::string inLanguage
        );

        /**
         * @brief Display nothing, only treat the filter by language form
         *        and redirect to the correct page
         *
         * @param username Name of the user we're going to filter the
         *                 sentences of   
         *
         * @since 24 August 2011
         */
        void sentences_of_in_treat(
            std::string username
        );

        /**
         * @brief Get all the sentences owned by a given user
         *        (paginated, lang filtered), and their translations
         *
         * @param username Name of the user we want the sentences of
         -*
         * @since 21 August 2011
         */
        void translate_sentences_of(
            std::string username
        );

        /**
         * @brief same as OfUser::translate_sentences_of but only sentences in
         *        a specific language
         *
         * @param username   Name of the user we want to translate the sentences
         *                   of
         * @param inLanguage Will keep only the sentenc in this language
         *                   (iso 639-3 code)
         *
         * @since 24 August 2011
         */
        void translate_sentences_of_in(
            std::string username,
            std::string inLanguage
        );


        /**
         * @brief Display nothing, only treat the filter by language form
         *        and redirect to the correct page
         *
         * @param username Name of the user we're going to filter the
         *                 sentences of   
         *
         * @since 24 August 2011
         */
        void translate_sentences_of_in_treat(
            std::string username
        );



};


} // end of namespace webs
} // end of namespace controllers



#endif
