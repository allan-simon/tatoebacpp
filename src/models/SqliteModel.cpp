#include "models/SqliteModel.h"

namespace models {

SqliteModel::SqliteModel(sqlite3* sqliteDb) : sqliteDb(sqliteDb) {
}

}
