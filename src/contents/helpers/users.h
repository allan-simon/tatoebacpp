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
 * @package  Helpers
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */


#ifndef CONTENTS_HELPER_USERS_H
#define CONTENTS_HELPER_USERS_H

#include "helpers.h"

namespace contents {
    namespace helpers {
        /**
         * @struct Users
         * Used everywhere we need to send current user information
         * to the view
         */
        struct Users : public Helper {
    
            /**
             * Name of the user, empty for visitor
             */
            std::string username;

            public:
                /**
                 * To know if the current user is logged or not
                 */
                bool is_logged() {
                    return !username.empty();
                }
        };
    }
};
#endif

