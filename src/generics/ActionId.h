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
 * @package  Singletons
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */
#ifndef YADICT_GENERICS_ACTIONID_H
#define YADICT_GENERICS_ACTIONID_H

#include "Singleton.h"

namespace singletons {
/**
 * Singleton class used to centralise the action id (used for logs)
 */
class ActionId : public Singleton<ActionId> {
    friend class Singleton<ActionId>;
    private:

        /**
         * Defaut constructor, will init the value of lastActionId
         * for the moment it is stored in a sqlite3 database
         */
        ActionId();

        /**
         * last action id, will be incremented each time a logged action
         * occurs 
         */
        unsigned int lastActionId;
    public:
        /**
         * The destructor will save the value of lastActionid
         * inside a database so that we can retrieve it even if
         * we restart the server
         */
        ~ActionId();
        /**
         * return the last action id + 1
         * and update lastactionId accordingly
         * so several consecutiv calls will not give the same result 
         */
        unsigned int get_action_id();


};

} //end namespace singletons
#endif
