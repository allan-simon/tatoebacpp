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

#ifndef TATOEBA_REGISTER_FORM_H
#define TATOEBA_REGISTER_FORM_H

#include <cppcms/form.h>
#include "contents/content.h"

namespace forms {

/**
 * @struct RegisterNewUser
 * Form to register a new user
 */
struct RegisterNewUser : public cppcms::form {
    /**
     * name of the user
     */
    cppcms::widgets::text username;
    /**
     * his password
     */
    cppcms::widgets::password password;
    /**
     * his email address
     */
    cppcms::widgets::email email;
    /**
     * The answer to a question to check he's not a bot
     */
    cppcms::widgets::text quiz;
    /**
     * Checkbox to say you've read and agreed the terms of use
     */
    cppcms::widgets::checkbox termsOfUse;
    /**
     * html submit button
     */
    cppcms::widgets::submit submit;

    /**
     * Default constructor add all the fields to the form
     * define their names etc.
     */
    RegisterNewUser() {
        *this + username + password + email + quiz + termsOfUse + submit;
        
        username.name("username");
        password.name("password");
        email.name("email");
        quiz.name("quiz");
        termsOfUse.name("termsofuse");


        submit.value("Register");
        submit.id("registerButton");

        username.non_empty();
        password.non_empty();

    }

    /**
     * To be sure that everything is correct, nothing is missing etc.
     */
    virtual bool validate() {
        return form::validate() &&
            termsOfUse.value() && //should have check the terms of use
            // the "captcha" test is to input the first five letters of 
            // the email so we test if it's correct
            email.value().substr(0,5).compare(quiz.value()) == 0; 
    }
};

}

#endif

