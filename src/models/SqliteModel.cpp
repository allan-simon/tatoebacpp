#include "models/SqliteModel.h"
#include "contents/Config.h"

namespace models {
SqliteModel::SqliteModel():
    sqliteDb(
        cppdb::session(
            "sqlite3:db=" + Config::get_instance()->sqlite3Path
        )
    )
{
}


SqliteModel::SqliteModel(cppdb::session sqliteDb) : sqliteDb(sqliteDb) {

}

} // end of namespace models
