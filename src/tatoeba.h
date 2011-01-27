#ifndef TATOEBA_H
#define TATOEBA_H

/**
 * @file tatoeba.h
 */

#include <cppcms/application.h>
#include <cppdb/frontend.h>

#include "controllers/Pages.h"
#include "controllers/Sentences.h"
#include "controllers/Users.h"



/** @namespace apps
 *
 */
namespace apps {

/** @class Tatoeba
 *
 */
class Tatoeba : public cppcms::application {

private:
	controllers::Pages pagesController; /**< Pages controller */
	controllers::Sentences sentencesController; /**< Sentences controller */
	controllers::Users usersController; /**< Users controller */
    std::map<std::string,std::string> lang_map; /**< map containing aviable language of tatoeba */

public:
    /**
     * Contuctor
     * @param w
     */
	Tatoeba(cppcms::service &w);
    /**
     * Method who receive all web requests
     * get the user language of interface from url
     * @param url : url asked by user
     */
	void main(std::string url);
};
}
#endif
