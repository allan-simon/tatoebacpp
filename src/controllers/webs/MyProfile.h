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

#ifndef CONTROLLERS_MY_PROFILE_H
#define CONTROLLERS_MY_PROFILE_H

#include "Controller.h"

namespace models {
    class Users;
    class UsersSpokenLangs;
}
namespace controllers {
namespace webs { 
/**
 * @class Controller class to handle pages related to the current user
 *        (the one we're logged with)
 */
class MyProfile : public Controller {
    private:
        /**
         *  @brief Model class for user, used to access the database
         */
        models::Users *usersModel;
        /**
         *  @brief Model class for languages spoken by the current user
         */
        models::UsersSpokenLangs *usersSpokenLangsModel;

        /**
         * @brief set the http header to redirect the current user's profile
         */
        void go_to_profile_page();
	public:
        /**
         * @brief Constructor, will attach the url to the dispatcher
         * and instantiate the model
         */
		MyProfile(cppcms::service &serv);
        /**
         * @brief Destructor
         */
        ~MyProfile();

        /**
         * @brief display the profile of the user we're logged with
         * 
         */
        void show();

        /**
        * @brief Display a form to edit current user's description
        */
        void edit_description();

        /**
        * @brief Will treat the data send to change current's users
        *        description
        */
        void edit_description_treat();


        /**
        * @brief Display a form to edit current user's homepage
        */
        void edit_homepage();

        /**
        * @brief Will treat the data send to change current's users
        *        homepage
        */
        void edit_homepage_treat();

        /**
        * @brief Display a form for the user to add a language he speaks 
        */
        void add_spoken_lang();

        /**
        * @brief Will treat the data send to add a language the user speaks 
        *        in his profile
        */
        void add_spoken_lang_treat();


};


} // End namespace webs 
} // End namespace controllers

#endif

