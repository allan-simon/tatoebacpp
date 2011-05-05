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
 * @package  Forms
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */


#ifndef TATOEBACPP_USERS_LOGIN_FORM_H
#define TATOEBACPP_USERS_LOGIN_FORM_H

#include <cppcms/form.h>
using namespace cppcms;

namespace forms {

    /**
     * @struct LoginUser
     * Form to log in
     */
	struct LoginUser : public cppcms::form {
        /**
         * To keep trace of the url we were in before
         * landing on the login page
         */
        widgets::hidden previousUrl;
        
        /**
         * TODO write the doc
         */
		widgets::text username;
        
        /**
         * TODO write the doc
         */
		widgets::password password;
        
        /**
         * TODO write the doc
         */
		widgets::checkbox rememberMe;
        
        /**
         * TODO write the doc
         */
		widgets::submit submit;
		

        /**
         * Default constructor add all the fields to the form
         * define their names etc.
         */
		LoginUser() {
            previousUrl.name("previousurl");
            previousUrl.value("");

			username.name("username");
			username.message("Username : ");
			username.attributes_string("class=\"input text\"");

			password.name("password");
			password.message("Password : ");

			rememberMe.name("rememberMe");
			rememberMe.message("Remember Me");

            

			submit.name("submit");
			submit.value("Log in");

			*this + previousUrl + username + password + rememberMe + submit;

			username.non_empty();
			password.non_empty();
		}
		
        /**
         * To be sure that everything is correct, nothing is missing etc.
         */
		virtual bool validate() {
			if (! form::validate()) {
                // TODO complete this
				return false;
			}
			return true;
		}
		
	};

}
#endif
