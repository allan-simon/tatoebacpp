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
};


} // End namespace webs 
} // End namespace controllers

#endif

