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

#include "cv.h"
#include "highgui.h"

#include <cppcms/util.h>
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
 * @brief will resize an already opened image to fit inside a squarre
 *        while keeping the ratio, and will save the reized image
 */
static void resize(
    const IplImage* source,
    const int maxSize,
    const std::string &resizedFileName
) {

    int destWidth = 0;
    int destHeight = 0;

    if (source->width > source->height) {
        destWidth = maxSize;
        destHeight = source->height * ((float)maxSize/(float)source->width);
    } else {
        destWidth = source->width * ((float)maxSize /(float)source->height);
        destHeight = maxSize;
    }

    // declare a destination IplImage object with correct size,
    //depth and channels
    IplImage *destination = cvCreateImage(
        cvSize(
            destWidth,
            destHeight
        ),
        source->depth,
        source->nChannels
    );

    cvResize(source, destination);

    cvSaveImage(
        resizedFileName.c_str(),
        destination
    );
    cvReleaseImage(&destination);
}





/**
 * @brief Will resize a given image into all the needed format/size
 *        and all these derivated images will follow the same naming
 *        pattern
 */
static void resize_all_format(
    const std::string &filename,
    const std::string &newFileName
) {
        IplImage *source = cvLoadImage(filename.c_str());
        

        //TODO the / is not windows friendly
        resize(
            source,
            128,
            "../ressources/img/avatars/128/" + newFileName + ".png"
        );
        resize(
            source,
            36,
            "../ressources/img/avatars/36/" + newFileName + ".png"
        );

        cvReleaseImage(&source);

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
        cppcms::util::md5hex(pass)
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
        cppcms::util::md5hex(pass)
    );
    addUser.bind(email);
    addUser.bind(
        booster::ptime::now().get_seconds()
    );
          
    try {
        addUser.exec();    
    } catch (cppdb::cppdb_error const &e) {
        //TODO log it
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
        "SELECT id, username, email, image "
        "FROM users LIMIT ? OFFSET ? "
    );

    cppdb::statement getUsersCount = sqliteDb.prepare(
        "SELECT count(*) as total FROM users "
    );

    pagiUsers.pageNormalSize = USERS_PER_PAGE;
    pagiUsers.currentPage = page;
    pagiUsers.totalNbrElements = getUsersCount.row().get<int>("total");

    getUsers.bind(USERS_PER_PAGE);
    getUsers.bind(page * USERS_PER_PAGE);
    cppdb::result res = getUsers.query();
    
    while (res.next()) {

        results::User user;
        user.id = res.get<int>("id");
        user.username = res.get<std::string>("username");
        user.email = res.get<std::string>("email");
        user.image = res.get<std::string>("image");
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
    user.depth = res.get<int>("depth");
    user.image = res.get<std::string>("image");
    user.since = res.get<long long>("since");

    // don't forget to reset the statement
    // NOTE: we put the reset at the end to avoid SQLITE to
    // to stay in a locked state
    getUserFromUsername.reset();

    return user;
}

          
/**       
 *        
 */       
std::string Users::get_avatar(
    const std::string &username
) {
    cppdb::statement getAvatar = sqliteDb.prepare(
        "SELECT image FROM users WHERE username = ? LIMIT 1;"
    );
    getAvatar.bind(username);

    std::string imageName = getAvatar.row().get<std::string>("image");

    getAvatar.reset();

    return imageName;
}



/**
 * @todo throw exception if user does not exist
 */
std::string Users::get_description_from_username(
    const std::string &username
) {
    getDescriptionFromUsername.reset();
    getDescriptionFromUsername.bind(username);
    return getDescriptionFromUsername.row().get<std::string>("description");
    
}

/**
 * @todo throw exception if user does not exist
 */
std::string Users::get_homepage_from_username(
    const std::string &username
) {
    getHomepageFromUsername.reset();
    getHomepageFromUsername.bind(username);
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


/**       
 *        
 */       
bool Users::update_password(
    const std::string &username,
    const std::string &oldPassword,
    const std::string &newPassword
) {
    cppdb::statement updatePassword = sqliteDb.prepare(
        "UPDATE users "
        "SET password = ? "
        "WHERE username = ? AND password = ?;"
    );
    updatePassword.bind(
        cppcms::util::md5hex(newPassword)
    );
    updatePassword.bind(username);
    updatePassword.bind(
        cppcms::util::md5hex(oldPassword)
    );

    updatePassword.exec();
    int affected = updatePassword.affected();
    updatePassword.reset();

    return affected == 1;
}

/**       
 *        
 */       
bool Users::update_avatar(
    const std::string &username,
    const std::string &filename
) { 
    cppdb::statement updatePassword = sqliteDb.prepare(
        "UPDATE users "
        "SET image = ? "
        "WHERE username = ? ;"
    );

    std::string usernameHashed = cppcms::util::md5hex(username);

    updatePassword.bind(usernameHashed);
    updatePassword.bind(username);
    updatePassword.exec();

    int affected = updatePassword.affected();
    updatePassword.reset();


    resize_all_format(
        filename,
        usernameHashed
    );

    return affected == 1;


}
    

/**       
 *        
 */       
bool Users::update_depth(
    const std::string &username,
    const int newDepth
) { 
    cppdb::statement updateDepth = sqliteDb.prepare(
        "UPDATE users "
        "SET depth = ? "
        "WHERE username = ? ;"
    );


    updateDepth.bind(newDepth);
    updateDepth.bind(username);
    updateDepth.exec();

    int affected = updateDepth.affected();
    updateDepth.reset();

    return affected == 1;

}


} // end of namespace models
