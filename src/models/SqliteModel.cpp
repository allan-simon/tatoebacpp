#include "models/SqliteModel.h"

namespace models {

SqliteModel::SqliteModel(cppdb::session sqliteDb) : sqliteDb(sqliteDb) {
}

}
