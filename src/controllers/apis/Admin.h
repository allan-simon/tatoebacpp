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



#ifndef CONTROLLERS_APIS_ADMIN_H
#define CONTROLLERS_APIS_ADMIN_H

#include "Controller.h"

namespace models {
    class Sentences;
}

namespace controllers {
namespace apis {
/**
 * @class Controller class to provide an API to admin task (dump of
 *        the database etc.)
 */
class Admin :
    public controllers::apis::Controller
{
	public:
        /**
         * Constructor, will attach the url to the dispatcher
         */
	    Admin(cppcms::service &serv);
        
        /**
        * @brief dump the database in a sphinx readable XML in a file
        *        at the given path
        *
        * @param path Full path where to dump the database
        */
        void sphinx_dump(std::string path);

};

} // End namespace apis
} // End namespace controllers

#endif

