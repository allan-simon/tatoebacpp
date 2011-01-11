#include <iostream>
#include <sstream>
#include <cppcms/crypto.h>
#include <cppdb/frontend.h>
#include "models/Users.h"

namespace models {


/**
 *
 */
Users::Users(cppdb::session sqliteDb) : SqliteModel(sqliteDb) {
    // TODO ADD check for the username 
    check_passwd_state = sqliteDb.create_prepared_statement("SELECT 1 FROM users2 WHERE username = ? AND password = ?");
    add_user_state = sqliteDb.create_prepared_statement("INSERT INTO users2(username, password) VALUES(?,?)");
}

/**
 *
 */
bool Users::check_login(std::string login, std::string pass) {
    std::auto_ptr<cppcms::message_digest> d(cppcms::message_digest::md5());
    
    char buf[16];
    d->append(pass.c_str(), pass.size());
    d->readout(buf);

    std::stringstream in;
    in.write(buf, 16);
    

    check_passwd_state.bind(login);
    check_passwd_state.bind(in);
    cppdb::result res = check_passwd_state.row();
   
   
    int checkresult = 0;
    res.fetch(0,checkresult);

    // Don't forget to reset statement
    check_passwd_state.reset();

    if (checkresult == 1 ) {
        return true;
    }
    return false;
}

void Users::addUser(std::string login, std::string pass) {
    std::auto_ptr<cppcms::message_digest> d(cppcms::message_digest::md5());

    char buf[16];
    d->append(pass.c_str(), pass.size());
    d->readout(buf);

    std::stringstream in;
    in.write(buf, 16);
    
    add_user_state.bind(login);
    add_user_state.bind(in);

    add_user_state.exec();    
    add_user_state.reset();
}


}
