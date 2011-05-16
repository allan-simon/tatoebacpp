#include "TatoDB.h"
#include "SearchEngine.h"

/**
 *
 */
TatoDb *TatoDB::get_db_pointer() {
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
void TatoDB::dump(std::string path) {
    tato_db_dump(tatoDb, path.c_str());
}
 
/**
 *
 */
void TatoDB::feed_search_engine() {
	TatoTreeIntNode *it = NULL;
    TatoItem *item = NULL;
	RB_FOREACH(it, TatoTreeInt_, tatoDb->items) {
        item = (TatoItem*) it->value;
        SearchEngine::get_instance()->add_sentence(
            item->id,
            std::string(item->str),
            std::string(item->lang->code)
        );

        TatoKvListNode *itkv;
        TATO_KVLIST_FOREACH(item->metas, itkv) {
            SearchEngine::get_instance()->add_meta(
                item->id,
                std::string(itkv->key),
                std::string(itkv->value),
                std::string(item->lang->code)
            );
        }
	}
}


 

/**
 *
 */
TatoDB::~TatoDB() {
    tato_db_free(tatoDb);
}

