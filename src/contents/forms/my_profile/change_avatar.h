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


#ifndef TATOEBACPP_MY_PROFILE_CHANGE_AVATAR_FORM_H
#define TATOEBACPP_MY_PROFILE_CHANGE_AVATAR_FORM_H
#include <booster/regex.h>
#include <cppcms/form.h>
using namespace cppcms;

namespace forms {
namespace my_profile {

    /**
     * @struct ChangeAvatar
     * Form to upload a new image to be used as avatar 
     *
     * @TODO: i18n it
     */
    struct ChangeAvatar : public cppcms::form {
        
        /**
         * @brief Will contain the uploaded file
         */
        widgets::file avatar;
        
        /**
         * @brief Permit to submit the new avatar 
         */
        widgets::submit submit;
        

        /**
         * Default constructor, add all the fields to the form
         * define their names etc.
         */
        ChangeAvatar() {

            avatar.filename(
                booster::regex(".*\\.(jpg|jpeg|png|JPG|PNG)")
            );
            // magic for JPEG
            avatar.add_valid_magic("\xFF\xD8");
            // magic for PNG
            avatar.add_valid_magic("\x89\x50\x4E\x47\x0D\x0A\x1A\x0A");

            avatar.limits(0, 1024*1024);
            avatar.non_empty();
            submit.name("Upload");
            submit.value("Upload");

            add(avatar); 
            add(submit);

        }
        
        
    };

} // end of namespace my_profile
} // end of namespace forms
#endif

