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

namespace models {


/**
 * @class UsersSpokenLangs
 * 
 * @brief This class permit access to the languages users speak and related
 *        information (who is native in what etc.)
 *
 */
class UsersSpokenLangs : public SqliteModel {
    private:
        /**
         * @brief Statement to add a new language in the list of language a
         *        user speaks
         */
        cppdb::statement addSpokenLang; 
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
        void add(
            const int userId,
            const std::string &langISO,
            const int proeficiencyLevel,
            const bool isNative
        );
 

};

} // end namespace models 
