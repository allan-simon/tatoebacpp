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
#include <sstream>
#include <vector>
#include <cppcms/crypto.h>
#include <cppdb/frontend.h>
#include "models/Users.h"

using namespace cppcms::crypto;
namespace models {

/**
 *
 */
Users::Users(cppdb::session sqliteDb) : SqliteModel(sqliteDb) {
    // TODO ADD check for the username 
    checkPasswdState = sqliteDb.create_prepared_statement(
        "SELECT 1 FROM users "
        "WHERE username = ? AND password = ? LIMIT 1"
    );
    addState = sqliteDb.create_prepared_statement(
        "INSERT INTO users(username, password, email)"
        "VALUES(?,?,?)"
    );
    getAllState = sqliteDb.create_prepared_statement(
        "SELECT * FROM users"
    );

    getIdFromName = sqliteDb.create_prepared_statement(
        "SELECT id FROM users WHERE username = ? LIMIT 1"
    );
}


/**
 *
 */
bool Users::is_login_correct(
    std::string login,
    std::string pass
) {
    
    // we generate the md5 of the password
    std::auto_ptr<message_digest> d(message_digest::md5());

    char buf[16];
    d->append(pass.c_str(), pass.size());
    d->readout(buf);

    std::stringstream in;
    in.write(buf, 16);
    
    checkPasswdState.bind(login);
    checkPasswdState.bind(in);
    cppdb::result res = checkPasswdState.row();
   
   
    int checkresult = 0;
    res.fetch(0,checkresult);

    // Don't forget to reset statement
    checkPasswdState.reset();

    if (checkresult == 1 ) {
        return true;
    }
    return false;
}

/**
 *
 */
bool Users::add(
    std::string login,
    std::string pass,
    std::string email
) {

    std::auto_ptr<message_digest> d(message_digest::md5());

    // we generate the md5 of the password
    char buf[16];
    d->append(pass.c_str(), pass.size());
    d->readout(buf);
    std::stringstream binaryHash;
    binaryHash.write(buf, 16);
    
    addState.bind(login);
    addState.bind(binaryHash);
    addState.bind(email);

    try {
        addState.exec();    
    } catch (cppdb::cppdb_error const &e) {
        addState.reset();
        return false;
    }
    addState.reset();
    return true;
}

/**
 *
 */
ListOfUsers Users::get_all_users() {
    cppdb::result res = getAllState.query();

    ListOfUsers listOfUsers;

    while (res.next()) {
        UserResult user;
        user.id = res.get<int>("id");
        user.username = res.get<std::string>("username");
        user.email = res.get<std::string>("email");
        std::tm sinceTime = res.get<std::tm>("since");
        user.since = asctime(&sinceTime);
        listOfUsers.push_back(user);
    }

    getAllState.reset();

    return listOfUsers;
}


}
