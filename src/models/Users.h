#ifndef MODELS_USERS_H
#define MODELS_USERS_H

#include "models/SqliteModel.h"

namespace models {

static int callback(void *NotUsed, int argc, char **argv, char **azColName);
class Users : public SqliteModel {
    public:
        Users(sqlite3* sqliteDb);
        void test();
};

}

#endif
