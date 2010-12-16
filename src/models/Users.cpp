#include "models/Users.h"
#include <iostream>

namespace models {

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  for(i=0; i<argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

Users::Users(sqlite3* sqliteDb) : SqliteModel(sqliteDb) {
    std::cout << "UsersModel sqliteDb : " << sqliteDb << std::endl;
}

void Users::test() {
    char *zErrMsg = 0;
    int rc;
    char* sql = (char*) "SELECT * FROM tbl1";
    
    rc = sqlite3_exec(sqliteDb, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cout << "SQL erro: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }
}

}
