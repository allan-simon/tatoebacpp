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

#include "models/SqliteModel.h"
#include <iostream>
#include <vector>
#include <booster/locale/date_time.h>


namespace models {

    // TODO improve this
    // TODO move this in results
    struct UserResult {
        int id;
        std::string username;
        std::string email;
        std::string lang;
        std::string since;
        int last_time_active;
        bool send_notifications;
        std::string name;
        int birthday;
        std::string description;
        std::string homepage;
        std::string image;
        std::string country_id;
        bool is_public;
    };
    typedef std::vector<UserResult> ListOfUsers;

static int callback(void *NotUsed, int argc, char **argv, char **azColName);

class Users : public SqliteModel {
    private:
        /**
         * SQL statement to check if the password is correct
         */
        cppdb::statement checkPasswdState; 
        /**
         * SQL statement to add a user in the database
         */
        cppdb::statement addState;
        cppdb::statement getAllState;
        cppdb::statement getIdFromName;

    public:
        /**
         * constructor
         */
        Users(cppdb::session sqliteDb);

        /**
         * Return the id of the user having the given name
         */
        template <class T> T get_id_from_name(std::string username);

        /**
         * Test if the pair login/pass exists in the database
         */
        bool is_login_correct(
            std::string login,
            std::string pass
        );

        /**
         * Add a new user with the given login/pass/mail
         * return false if the user can't be added (login already taken etc.)
         */
        bool add(
            std::string login,
            std::string pass,
            std::string email
        );
        std::vector<UserResult> get_all_users();
};
/**
 *
 */
template <class T> T Users::get_id_from_name(std::string username) {
    getIdFromName.bind(username);
    cppdb::result res = getIdFromName.row();

    T userId;
    res.fetch(0, userId);
    getIdFromName.reset();
    
    return userId;

}


}
#endif
