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

#ifndef MODELS_USERS_H
#define MODELS_USERS_H

#include <iostream>
#include <vector>
#include <booster/locale/date_time.h>

#include "models/SqliteModel.h"
#include "results/users.h"

namespace models {



class Users : public SqliteModel {
    private:
        /**
         * SQL statement to check if the password is correct
         */
        cppdb::statement checkPasswd; 
        /**
         * SQL statement to add a user in the database
         */
        cppdb::statement addUser;
        cppdb::statement getIdFromUsername;
        cppdb::statement getUserFromUsername;
        cppdb::statement getDescriptionFromUsername;
        cppdb::statement getHomepageFromUsername;
        cppdb::statement updateDescriptionFromUsername;
        cppdb::statement updateHomepageFromUsername;

    public:
        /**
         * constructor
         */
        Users(cppdb::session sqliteDb);

        /**
         * Return the id of the user having the given name
         */
        template <class T> T get_id_from_name(
            const std::string &username
        );

        /**
         * Test if the pair login/pass exists in the database
         */
        bool is_login_correct(
            const std::string &login,
            const std::string &pass
        );         
                   
        /**        
         * Add a new user with the given login/pass/mail
         * return false if the user can't be added (login already taken etc.)
         */        
        bool add(
            const std::string &login,
            const std::string &pass,
            const std::string &email
        );         
                   
        /**        
        * @brief Get a paginated list of users
        *          
        * @param page Used for pagination 
        *          
        * @return Paginated vector of users
        */
        results::PagiUsers get_all_users(
            const int page
        );


        /**
        * @brief Get the complete user information from his
        *        username
        *
        * @param username Name of the user for whom we want the information
        *
        * @return The user structure correctly filled
        */
        results::User get_user_from_username(
            const std::string &username
        );

        /**
        * @brief Get the user description from his
        *        username
        *
        * @param username Name of the user for whom we want the description
        *
        * @return The user description as a string
        */
        std::string get_description_from_username(
            const std::string &username
        );

        /**
        * @brief Get the user homepage from his
        *        username
        *
        * @param username Name of the user for whom we want the homepage
        *
        * @return The user homepage as a string
        */
        std::string get_homepage_from_username(
            const std::string &username
        );

        /**
        * @brief Update the description of the given user
        *
        * @param username Name of the user we want to update the description of
        * @param newDescription The new description
        *
        */
        void update_description(
            const std::string &username,
            const std::string &newDescription
        );

        /**
        * @brief Update the homepage of the given user
        *
        * @param username Name of the user we want to update the homepage of
        * @param newHomepage The new homepage
        *
        */
        void update_homepage(
            const std::string &username,
            const std::string &newHomepage
        );

        /**
        * @brief Get the avatar identifier of a user
        *
        * @param username Name of the user for whom we want the image of
        *
        * @return The user image name as a string
        */
        std::string get_avatar(
            const std::string &username
        );

        /**
        * @brief change the avatar (will save/resize/convert it) of the current
        *        user
        *
        * @param username Name of the user of whom the avatar will be changed
        * @param filename Temporary name of the file, to know which file open
        *
        * @todo Find a way to open from memory so that we don't need to first
        *       save to the disk
        * @todo Permit the user to go back to a "no avatar" state
        *
        * @return True if the avatar was successfuly updated, False otherwise
        */
        bool update_avatar(
            const std::string &username,
            const std::string &filename
        );

        /**
        * @brief Change the password of a user by a new one
        *
        * @param username     The user of which we're changing the password
        * @param oldpassword  The old password to check
        * @param newpassword  The new password to set
        *
        * @return True if the password was succefully update , false otherwise
        *         (wrong couple(username.oldpassword) for example)
        */
        bool update_password(
            const std::string &username,
            const std::string &oldpassword,
            const std::string &newpassword
        );

        /**
        * @brief Update the maximun depth of translation displayed for a user
        *
        * @param username The user of which we're changing the password
        * @param newDepth The new depth to set
        *
        * @return True if the new depth was succefully updated, false otherwise
        *
        */
        bool update_depth(
            const std::string &username,
            const int newDepth
        );

        /**
        * @brief Get the depth of translations configurated for a user
        *
        * @param username Name of the user for whom we want the depth of
        *
        * @return The defined depth of translations wanted
        */
        int get_depth(
            const std::string &username
        );

};



/**
* @brief          User to retrieve the identifier of a given user
* @TODO           Throw an exception when the user does not exists
*
* @tparam T       Type under which we want the id (int or std::string)
* @param username Name of the user want the id of
* 
*
* @return         The id in the requested type 
*/
template <class T> T models::Users::get_id_from_name(
    const std::string &username
) {
    getIdFromUsername.bind(username);
    cppdb::result res = getIdFromUsername.row();

    T userId;
    res.fetch(0, userId);
    getIdFromUsername.reset();
    
    return userId;

}


}
#endif
