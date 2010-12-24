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
    check_passwd_state = sqliteDb.create_prepared_statement("SELECT 1 FROM users2 WHERE password = ?");
}

/**
 *
 */
void Users::check_login(std::string login, std::string pass) {
    std::auto_ptr<cppcms::message_digest> d(cppcms::message_digest::md5());
    
    char buf[16];
    d->append(pass.c_str(), pass.size());
    d->readout(buf);

    std::stringstream in(buf);

    check_passwd_state.bind(login);
    check_passwd_state.bind(in);
    cppdb::res = check_passwd_state.row();
   
   
    // TODO replace me by a real piece of code 
    std::cout <<buf <<  std::endl;
    int checkresult = 0;
    res.fetch(0,checkresult);
    if (checkresult != 1 ) {
        std::cout << "wrong password" << std::endl; 
    } else {
        std::cout << "right one" << std::endl; 
    }


}


}
