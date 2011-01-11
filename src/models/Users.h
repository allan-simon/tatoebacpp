#ifndef MODELS_USERS_H
#define MODELS_USERS_H

#include "models/SqliteModel.h"
#include <iostream>

namespace models {

static int callback(void *NotUsed, int argc, char **argv, char **azColName);
class Users : public SqliteModel {
    private:
        cppdb::statement check_passwd_state; 
        cppdb::statement add_user_state;

    public:
        Users(cppdb::session sqliteDb);
        bool check_login(std::string login, std::string pass);
        void addUser(std::string login, std::string pass);
};

}

#endif
