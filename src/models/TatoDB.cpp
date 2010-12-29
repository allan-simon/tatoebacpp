#include "TatoDB.h"


/**
 *
 */
TatoDb *TatoDB::getDatabasePointer() {
    return tatoDb;
}


/**
 *
 *
 */

TatoDB::TatoDB(std::string data_path) {
    tatoDb = tato_db_new();
    tato_db_load(tatoDb, data_path.c_str());
}

 

/**
 *
 */
TatoDB::~TatoDB() {
    tato_db_free(tatoDb);
}

