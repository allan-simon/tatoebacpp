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

#ifndef CONTROLLERS_USERS_H
#define CONTROLLERS_USERS_H

#include "Controller.h"

namespace models {
    class Users;
    class UsersSpokenLangs;
}
namespace controllers {
namespace webs { 
/**
 * @class Controller class to handle pages related to users
 */
class Users : public Controller {
    private:
        /**
         * Model class for user, used to access the database
         */
        models::Users *usersModel;
        /**
         *  @brief Model class for languages spoken by the current user
         */
        models::UsersSpokenLangs *usersSpokenLangsModel;
	public:
        /**
         * Constructor, will attach the url to the dispatcher
         * and instantiate the model
         */
		Users(cppcms::service &serv);
        /**
         * Destructor
         */
        ~Users();
        /**
         * Retrieve everything needed to 
         * display the page to create a new user
         */
        void register_new();
        
        /**
         * Will retrieve, check and validate data send by the form
         * to create a new user
         */
        void register_new_treat();
        
        /**
         * Retrieve everything to then display the page to login
         */
		void login();

        /**
         * Treat data send by the login form and will create session
         * if the login succed
         */
		void login_treat();

        /**
         * Logout the user and redirect to home page
         */
        void logout();

        /*
        void list_members();
        void list_members(std::string offset, std::string size);
        */
        /**
        * @brief list all users in a paginated way
        */
        void all();
        
        /**
         * @brief display the profile of a user
         * 
         * @param username Name of the user we want the profile of
         */
        void profile(std::string username);
};


} // End namespace webs 
} // End namespace controllers

#endif
