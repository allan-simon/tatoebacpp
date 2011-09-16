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
UsersSpokenLangs::UsersSpokenLangs() :
    SqliteModel()
{
}

/**
 * @TODO throw exception if language has already been added for that
 *       user
 */
bool UsersSpokenLangs::add(
    const int userId,
    const std::string &langISO,
    const int proeficiencyLevel,
    const bool isNative
) {
    cppdb::statement addSpokenLang = sqliteDb.prepare(
        "INSERT INTO users_spoken_langs("
            "user_id, lang, proeficiency, is_native"
        ")"
        "VALUES(?,?,?,?)"
    );

    addSpokenLang.bind(userId);
    addSpokenLang.bind(langISO);
    addSpokenLang.bind(proeficiencyLevel);
    addSpokenLang.bind(isNative);
    try {
        addSpokenLang.exec();
    } catch (cppdb::cppdb_error const &e) {
        //TODO add something better to handle erros
        // at least log it
        std::cout << e.what() << std::endl;
        return false;
    }
    return true;
}

/**
 *
 */
results::SpokenLangsVector UsersSpokenLangs::get_from_user(
    const std::string &username
) {

    cppdb::statement getFromUser = sqliteDb.prepare(
        "SELECT * FROM users_spoken_langs "
        "WHERE user_id = ( "
        "   SELECT id FROM users WHERE username = ? "
        ")"
        "ORDER BY proeficiency;"
    );
    getFromUser.bind(username);

    // this function does the reset for us
    return get_spoken_langs_result(getFromUser);

}

/**
 *
 */
results::SpokenLangsVector UsersSpokenLangs::get_spoken_langs_result(
    cppdb::statement &getFromUser
) {

    results::SpokenLangsVector spokenLangs;

    cppdb::result res = getFromUser.query(); 

    while (res.next()) {
        results::SpokenLang tempSpokenLang;
        tempSpokenLang.langISO = res.get<std::string>("lang");
        tempSpokenLang.proeficiency = res.get<int>("proeficiency");
        tempSpokenLang.isNative = res.get<int>("is_native") == 1;

        spokenLangs.push_back(tempSpokenLang);
    
    }
    getFromUser.reset(); 
    return spokenLangs;


}

/**
 *
 */
results::SpokenLangsVector UsersSpokenLangs::get_from_user(
    const int userId
) {

    cppdb::statement getFromUser = sqliteDb.prepare(
        "SELECT * FROM users_spoken_langs WHERE user_id = ?"
        "ORDER BY proeficiency;"
    );
    getFromUser.bind(userId);

    // this function does the reset for us
    return get_spoken_langs_result(getFromUser);
}




/**
 * @TODO throw exception if language has already been added for that
 *       user
 */
bool UsersSpokenLangs::remove(
    const int userId,
    const std::string &langISO
) {
    cppdb::statement removeSpokenLang = sqliteDb.prepare(
        "DELETE FROM users_spoken_langs"
        "   WHERE user_id = ? AND lang = ?"
    );

    removeSpokenLang.bind(userId);
    removeSpokenLang.bind(langISO);
    try {
        removeSpokenLang.exec();
    } catch (cppdb::cppdb_error const &e) {
        //TODO add something better to handle erros
        std::cout << e.what() << std::endl;
        return false;
    }
    return true;
}

/**
 *
 */
results::SpokenLang UsersSpokenLangs::get_one(
    const int userId,
    const std::string &langISO
) {

    cppdb::statement getOne = sqliteDb.prepare(
        "SELECT * FROM users_spoken_langs "
        "WHERE user_id = ? AND lang = ?"
    );
    getOne.bind(userId);
    getOne.bind(langISO);


    results::SpokenLang spokenLang;
    cppdb::result res = getOne.row(); 

    spokenLang.langISO = res.get<std::string>("lang");
    spokenLang.proeficiency = res.get<int>("proeficiency");
    spokenLang.isNative = res.get<int>("is_native") == 1;

    
    getOne.reset(); 

    return spokenLang;
}


/**
 * @TODO throw exception if language was not existing for that user
 */
bool UsersSpokenLangs::edit(
    const int userId,
    const std::string &langISO,
    const int proeficiencyLevel,
    const bool isNative
) {
    cppdb::statement editSpokenLang = sqliteDb.prepare(
        "UPDATE users_spoken_langs SET "
        "    proeficiency = ?,"
        "    is_native = ? "
        "WHERE user_id = ? AND lang = ?"
    );

    editSpokenLang.bind(proeficiencyLevel);
    editSpokenLang.bind(isNative);
    editSpokenLang.bind(userId);
    editSpokenLang.bind(langISO);
    editSpokenLang.exec();

    return true;
}


std::vector<std::string> UsersSpokenLangs::get_iso_code_vector(
    std::string username
) {
    cppdb::statement getIsosFromUser = sqliteDb.prepare(
        "SELECT lang FROM users_spoken_langs "
        "WHERE user_id = ( "
        "   SELECT id FROM users WHERE username = ? "
        ")"
        "ORDER BY proeficiency;"
    );
    getIsosFromUser.bind(username);
    
    std::vector<std::string> isos;

    cppdb::result res = getIsosFromUser.query(); 
    while (res.next()) {
        isos.push_back(res.get<std::string>("lang"));
    }

    getIsosFromUser.reset();

    return isos;
}



} // end namespace models

