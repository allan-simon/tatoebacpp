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
results::SentencesStats TatoDB::get_sentences_stats() {
    results::SentencesStats sentencesStats;
    TatoTreeStrNode *iter = NULL;
	TATO_TREE_STR_FOREACH(tatoDb->langs, iter) {
        TatoItemLang* lang = (TatoItemLang*)iter->value;
        std::string langCode(lang->code);
        sentencesStats.insert(
            std::pair<int, std::string>(
                tato_tree_str_size(lang->index),
                langCode
            ) 
        );
	}
    // TODO
    results::SentencesStats topFive;
    results::SentencesStats::iterator it = sentencesStats.begin();
    results::SentencesStats::const_iterator end = sentencesStats.end();

    for(int i = 5; it != end && i > 0; ++it, --i) {
        topFive.insert(
            std::pair<int, std::string>(
                it->first,
                it->second
            )
        );
    }


    return sentencesStats;
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

