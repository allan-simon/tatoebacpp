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
#include <booster/posix_time.h>

#include "models/Users.h"


#define USERS_PER_PAGE 20

using namespace cppcms::crypto;
namespace models {

/**
 *
 */
Users::Users(cppdb::session sqliteDb) : SqliteModel(sqliteDb) {
    // TODO ADD check for the username 

    // create all the prepated statement
    checkPasswd = sqliteDb.prepare(
        "SELECT 1 FROM users "
        "WHERE username = ? AND password = ? LIMIT 1"
    );
    addUser = sqliteDb.prepare(
        "INSERT INTO users(username, password, email, since)"
        "VALUES(?,?,?,?)"
    );

    
    updateDescriptionFromUsername = sqliteDb.prepare(
        "UPDATE users SET description = ?"
        "WHERE username = ? "
    );

    updateHomepageFromUsername = sqliteDb.prepare(
        "UPDATE users SET homepage = ?"
        "WHERE username = ? "
    );




    getIdFromUsername = sqliteDb.prepare(
        "SELECT id FROM users WHERE username = ? LIMIT 1"
    );
    
    getUserFromUsername = sqliteDb.prepare(
        "SELECT * FROM users WHERE username = ? LIMIT 1 "
    );

    getDescriptionFromUsername = sqliteDb.prepare(
        "SELECT description FROM users WHERE username = ? LIMIT 1 "
    );

    getHomepageFromUsername = sqliteDb.prepare(
        "SELECT homepage FROM users WHERE username = ? LIMIT 1 "
    );


    
}


/**
 *
 */
static std::string binary_md5(
    const std::string toHash
) {
    // we generate the md5 of the password
    std::auto_ptr<message_digest> d(message_digest::md5());

    char buf[16];
    d->append(toHash.c_str(), toHash.size());
    d->readout(buf);

    std::stringstream in;
    in.write(buf, 16);
 
    return in.str();
}

/**
 *
 */
bool Users::is_login_correct(
    const std::string &login,
    const std::string &pass
) {
    
   
    checkPasswd.bind(login);
    checkPasswd.bind(
        binary_md5(pass)
    );
    cppdb::result res = checkPasswd.row();
   
   
    int checkresult = 0;
    res.fetch(0,checkresult);

    // Don't forget to reset statement
    checkPasswd.reset();

    if (checkresult == 1 ) {
        return true;
    }
    return false;
}

/**
 *
 */
bool Users::add(
    const std::string &login,
    const std::string &pass,
    const std::string &email
) {       
          
    addUser.bind(login);
    addUser.bind(
        binary_md5(pass)
    );
    addUser.bind(email);
    addUser.bind(
        booster::ptime::now().get_seconds()
    );
          
    try {
        addUser.exec();    
    } catch (cppdb::cppdb_error const &e) {
        addUser.reset();
        return false;
    }
    addUser.reset();
    return true;
}         
          
/**       
 *        
 */       
results::PagiUsers Users::get_all_users(
    const int page
) {
    results::PagiUsers pagiUsers;
    cppdb::statement getUsers = sqliteDb.prepare(
        "SELECT * FROM users LIMIT 20 OFFSET ? "
    );

    cppdb::statement getUsersCount = sqliteDb.prepare(
        "SELECT count(*) as total FROM users "
    );

    pagiUsers.maxsize = getUsersCount.row().get<int>("total");

    getUsers.bind(page * USERS_PER_PAGE);
    cppdb::result res = getUsers.query();
    
    while (res.next()) {

        results::User user;
        user.id = res.get<int>("id");
        user.username = res.get<std::string>("username");
        user.email = res.get<std::string>("email");
        //std::tm sinceTime = res.get<std::tm>("since");
        //user.since = asctime(&sinceTime);
        pagiUsers.push_back(user);
    }

    getUsers.reset();
    getUsersCount.reset();

    return pagiUsers;
}

/**
 * @TODO must throw exception if the user does not exist
 */
results::User Users::get_user_from_username(
    const std::string &username
) {

    results::User user; 

    // attach the username to the sql statement
    getUserFromUsername.bind(username);   
 
    cppdb::result res = getUserFromUsername.row();

    // fill the user structure with the data retrieve from the database
    user.id = res.get<int>("id");
    user.username = res.get<std::string>("username");
    user.description = res.get<std::string>("description");
    user.email = res.get<std::string>("email");
    user.homepage = res.get<std::string>("homepage");
    user.since = res.get<long long>("since");

    // don't forget to reset the statement
    // NOTE: we put the reset at the end to avoid SQLITE to
    // to stay in a locked state
    getUserFromUsername.reset();

    return user;
}

/**
 * @todo throw exception if user does not exist
 */
std::string Users::get_description_from_username(
    const std::string &username
) {
    getDescriptionFromUsername.bind(username);
    getDescriptionFromUsername.reset();
    return getDescriptionFromUsername.row().get<std::string>("description");
    
}

/**
 * @todo throw exception if user does not exist
 */
std::string Users::get_homepage_from_username(
    const std::string &username
) {
    getHomepageFromUsername.bind(username);
    getHomepageFromUsername.reset();
    return getHomepageFromUsername.row().get<std::string>("homepage");
    
}



/**
 * @todo throw exception if user does not exist
 */
void Users::update_description(
    const std::string &username,
    const std::string &newDescription
) {
    std::cout << "[DEBUG] username :" << username << " description :" << newDescription << std::endl;

    // don't forget to reset the statement
    updateDescriptionFromUsername.bind(newDescription);
    updateDescriptionFromUsername.bind(username);
    updateDescriptionFromUsername.exec();
    updateDescriptionFromUsername.reset();
    
}


/**
 * @TODO throw exception if user does not exist
 */
void Users::update_homepage(
    const std::string &username,
    const std::string &newHomepage
) {
    // don't forget to reset the statement
    updateHomepageFromUsername.bind(newHomepage);
    updateHomepageFromUsername.bind(username);
    updateHomepageFromUsername.exec();
    updateHomepageFromUsername.reset();
}

} // end of namespace models
