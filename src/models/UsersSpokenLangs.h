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

#include "models/SqliteModel.h"
#include "results/spoken_langs.h"

namespace models {


/**
 * @class UsersSpokenLangs
 * 
 * @brief This class permit access to the languages users speak and related
 *        information (who is native in what etc.)
 *
 */
class UsersSpokenLangs : public SqliteModel {
    public:
        /**
         * @brief Constructor
         */
        UsersSpokenLangs(cppdb::session sqliteDb);
        /**
        * @brief Add a language to the list of languages spoken by a user
        *
        * @param userId            Id of the user 
        * @param langISO           ISO code of the language to add
        * @param proeficiencyLevel Integer representing the proeficiency,
        *                          the lower, the better
        * @param isNative          If the user is a native of that language
        *
        * @TODO  Should throw an exception if we try to add language that is
        *        already present
        */
        bool add(
            const int userId,
            const std::string &langISO,
            const int proeficiency,
            const bool isNative
        );
         
        /**
        * @brief Get all the languages a user entered he can speaks
        *
        * @param userId Id of the user we want the languages of
        *
        * @return The list of spoken languages
        */
        ::results::SpokenLangsVector get_from_user_id(const int userId);


        /**
        * @brief Remove the given language from the list of languages
        *        the given user speaks
        * @param userId  Id of the user we want to remove the language from the
        *                list of 
        * @param langISO ISO code of the language we want to remove
        *
        * @return True if no problems, false otherwise
        */
        bool remove(
            const int userId,
            const std::string &langISO
        );

        /**
        * @brief Retrieve all the information about a given user toward
        *        a given language
        *
        * @param userId  The user want to get the info about
        * @param langISO ISO of the language we want the information of
        *
        * @return The information about how good the user can speak
        *         that lang, if he's a native etc.
        */

        SpokenLang get_one(
            const int userId,
            const std::string &langISO
        );

        /**
        * @brief Permit to change the information a given user as entered about
        *        a given language
        *        
        *
        * @param userId       User we want to edit the info about one of the
        *                     language he speaks
        * @param langISO      ISO code of the language to change the infos of
        * @param proeficiency The new proeficiency to set
        * @param isNative     The new "is native or not"
        *
        * @return             If there was no problem or some 
        */
        bool edit(
            const int userId,
            const std::string &langISO,
            const int proeficiency,
            const bool isNative
        );
};

} // end namespace models 
