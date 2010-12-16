#ifndef MODELS_SQLITE_H
#define MODELS_SQLITE_H

#include <sqlite3.h>

namespace models {

class SqliteModel {
    protected:
        sqlite3* sqliteDb;
    public:
        SqliteModel(sqlite3* sqliteDb);
};

}

#endif
