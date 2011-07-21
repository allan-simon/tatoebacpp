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


#ifndef CONTROLLERS_WEBS_SEARCHES_H
#define CONTROLLERS_WEBS_SEARCHES_H

#include "Controller.h"

namespace models {
    class Searches;
}


namespace controllers {
namespace webs {

/**
 * @class Searches
 * Class that will controll all the page request related to the 
 * search engine
 */
class Searches : public Controller {
    private:
        /**
         * Model class for the search engine
         */
        models::Searches *searchesModel;
	public:
        /**
         * Constructor, will attach the url to the dispatcher
         * and instantiate the model
         */
		Searches(cppcms::service &serv);
        
        /**
         * Destructor
         */
        ~Searches();

        /**
         * Will treat the request send by the search bar
         */
        void simple_treat();

        /**
         * Display the sentences matching the query
         */
        void show_result(std::string query, std::string lang);
        /**
         * Display the sentences matching the query (with pagination)
         */
        void show_result(
            std::string query,
            std::string fromLang,
            std::string toLang
        );

};

} // End namespace webs
} // End namespace generics

#endif

