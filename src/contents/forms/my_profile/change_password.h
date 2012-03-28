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


#ifndef TATOEBACPP_MY_PROFILE_CHANGE_PASSWORD_FORM_H
#define TATOEBACPP_MY_PROFILE_CHANGE_PASSWORD_FORM_H

#include <cppcms/form.h>

namespace forms {
namespace my_profile {

    /**
     * @struct ChangePassword
     * Form to change current user password 
     *
     * @TODO: i18n it
     */
    struct ChangePassword : public cppcms::form {
        
        /**
         * @brief Will contain the current password
         *        we need it to be sure someone is not hijacking the session
         */
        cppcms::widgets::password previous;
        /**
         * @brief Will contain the new password
         */
        cppcms::widgets::password newPassword;
        /**
         * @brief Will contain new password once again to be sure the user
         *        has made no typo
         */
        cppcms::widgets::password repeatNewPassword;
                     
        /**
         * @brief Permit to submit the new password
         */
        cppcms::widgets::submit submit;
        

        /**
         * @brief Default constructor, add all the fields to the form
         *        define their names etc.
         * 
         * @todo i18n it
         */

        ChangePassword() {
            previous.message("Previous password:");
            previous.name("previous");

            newPassword.message("New password:");
            newPassword.name("newpassword");

            repeatNewPassword.message("Repeat new password:");
            repeatNewPassword.name("repeatnewpassword");

            submit.name("Change");
            submit.value("Change");

            add(previous);
            add(newPassword);
            add(repeatNewPassword);
            add(submit);

        }
            
            
        /**
         * To be sure that everything is correct, nothing is missing etc.
         */
        virtual bool validate() {
            return form::validate() &&
                newPassword.value() == repeatNewPassword.value();
        }

    };

} // end of namespace my_profile
} // end of namespace forms
#endif

