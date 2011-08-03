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
 * @package  Models
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */

#include <iostream>
#include <string>
#include <cppdb/frontend.h>

#include "models/UsersSpokenLangs.h"


#define USERS_PER_PAGE 20

namespace models {

/**
 *
 */
UsersSpokenLangs::UsersSpokenLangs(cppdb::session sqliteDb) :
    SqliteModel(sqliteDb)
{
    addSpokenLang = sqliteDb.prepare(
        "INSERT INTO users_spoken_langs("
            "user_id, lang, proeficiency, is_native"
        ")"
        "VALUES(?,?,?,?)"
    );

}
/**
 * @TODO throw exception if language has already been added for that
 *       user
 */
void UsersSpokenLangs::add(
    const int userId,
    const std::string &langISO,
    const int proeficiencyLevel,
    const bool isNative
) {
    // don't forget to reset the statement
    addSpokenLang.reset();
    addSpokenLang.bind(userId);
    addSpokenLang.bind(langISO);
    addSpokenLang.bind(proeficiencyLevel);
    addSpokenLang.bind(isNative);
    addSpokenLang.exec();
}

} // end namespace models

