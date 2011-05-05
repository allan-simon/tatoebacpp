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

#include "ActionId.h"
#include <cppdb/frontend.h>

namespace singletons {

/**
 *
 */
ActionId::ActionId() {
    //TODO replace the hardcodedpath by something in config.js
    cppdb::session sqliteDb("sqlite3:db=../doc/sqlite3.db");
    sqliteDb << "SELECT last_id FROM action_id LIMIT 1;" <<
        cppdb::row >> lastActionId;
}

/**
 *
 */
unsigned int ActionId::get_action_id() {
    unsigned int tempId = lastActionId;
    lastActionId++;
    return tempId;
}


/**
 *
 */
ActionId::~ActionId() {
    cppdb::session sqliteDb("sqlite3:db=../doc/sqlite3.db");
    sqliteDb << "UPDATE action_id SET last_id = ?;" << lastActionId << cppdb::exec;
}

};//end namespace singletons

