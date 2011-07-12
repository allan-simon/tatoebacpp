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
 * @package  Apps
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */


#ifndef TATOEBA_H
#define TATOEBA_H

/**
 * @file tatoeba.h
 */
#include <map>

#include <cppcms/application.h>
#include <cppdb/frontend.h>
#include "controllers/webs/Sentences.h"
#include "controllers/apis/Sentences.h"
#include "controllers/webs/Users.h"
#include "controllers/webs/Pages.h"
#include "controllers/webs/Searches.h"


/** 
 * @namespace apps
 */
namespace apps {

/** 
 * @class Tatoeba
 * Application class representing the website
 * All http request will be dispatched by this class
 */
class Tatoeba : public cppcms::application {

private:
    controllers::webs::Sentences sentences;
    controllers::apis::Sentences sentencesApi;
    controllers::webs::Pages pages;
    controllers::webs::Users users;
    controllers::webs::Searches searches;
    /**
     * map containing aviable language of tatoeba
     * @TODO move this in Languages singleton
     */
    std::map<std::string,std::string> lang_map; 

public:
    /**
     * Constructor
     * Will connect every controllers to their respective paths
     * @param serv
     */
	Tatoeba(cppcms::service &serv);

    /**
     * Method who receive all web requests
     * get the user language of interface from url
     * @param url : url asked by user
     */
	void main(std::string url);
};
}
#endif
