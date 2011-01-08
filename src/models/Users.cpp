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
}

/**
 *
 */
void Users::check_login(std::string login, std::string pass) {
    try {
    std::auto_ptr<cppcms::message_digest> d(cppcms::message_digest::md5());
    
    char buf[16];
    d->append(pass.c_str(), pass.size());
    d->readout(buf);

    std::stringstream in(buf);
    
    /*
    TEST add user plop

    cppdb::session sql("sqlite3:db=../doc/sqlite3.db");

    cppdb::statement stat;
    stat = sql << 
            "INSERT INTO users2(id, username, password) "
            "VALUES(?,?,?)";
            //<< 100 << "plop" << in;
    stat.bind(100);
    stat.bind("plop");
    stat.bind(in);
    stat.exec();
    */

    check_passwd_state.bind(login);
    check_passwd_state.bind(in);
    cppdb::result res = check_passwd_state.row();
   
   
    // TODO replace me by a real piece of code 
    std::cout << in.str() <<  std::endl;
    int checkresult = 0;
    bool tip = false;
    tip = res.fetch(0,checkresult);
    std::cout << res.empty();
    if (checkresult != 1 ) {
        std::cout << "wrong password" << std::endl; 
    } else {
        std::cout << "right one" << std::endl;
    }
    // Don't forget to reset
    check_passwd_state.reset();
    } catch (std::exception const &e)
    {std::cerr << "ERROR: " << e.what() << std::endl;}

}


}
