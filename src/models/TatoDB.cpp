#include "TatoDB.h"
//#include "SearchEngine.h"

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
void TatoDB::sphinx_dump(std::string path) {
    tato_db_sphinx_dump(tatoDb, path.c_str());
}

/**
 *
 */
unsigned int TatoDB::get_total_nbr_sentences() {

    return tato_tree_int_size(tatoDb->items);
}

/**
 *
 */
results::SentencesStats TatoDB::get_top_five() {
    results::SentencesStats sentencesStats;

    TatoTreeStrNode *iter = NULL;
	TATO_TREE_STR_FOREACH(tatoDb->langs, iter) {
        TatoItemLang* lang = (TatoItemLang*)iter->value;

        std::string langCode(lang->code);

        sentencesStats.insert(
            std::pair<int, std::string>(
                // number of sentences
                tato_tree_str_size(lang->index),
                // in which language
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

    return topFive;
}




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

    return sentencesStats;
}

/**
 *
 */
/*
void TatoDB::feed_search_engine() {
	TatoTreeStrNode *iterLang = NULL;
	TatoTreeStrNode *iterItem = NULL;
    TatoItem *item = NULL;

	
    TATO_TREE_STR_FOREACH(tatoDb->langs, iterLang) {

        TatoItemLang* lang = (TatoItemLang*)iterLang->value;
        std::string langCode(lang->code);

        TCIDB* index = SearchEngine::get_instance()->get_index(langCode);

	    TATO_TREE_STR_FOREACH(lang->index, iterItem) {

            item = (TatoItem*) iterItem->value;
            SearchEngine::get_instance()->add_sentence(
                item->id,
                std::string(item->str),
                std::string(item->lang->code),
                index
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

        SearchEngine::get_instance()->close_index(index);
    }

}
*/
/**
 *
 */
/*
void TatoDB::feed_search_engine_indirect() {
	TatoTreeStrNode *iterLang = NULL;
	TatoTreeStrNode *iterLang2 = NULL;
	TatoTreeStrNode *iterItem = NULL;
    TatoItem *item = NULL;

	
    TATO_TREE_STR_FOREACH(tatoDb->langs, iterLang) {
        
        TatoItemLang* lang = (TatoItemLang*)iterLang->value;
        std::string langCode(lang->code);

        TATO_TREE_STR_FOREACH(tatoDb->langs, iterLang2) {

            // we're indexing only the sentence having a direct or indirect translation
            // (distance <= 2) in the following language
            TatoItemLang* transInLang = (TatoItemLang*)iterLang2->value;
            std::string transInLangCode(transInLang->code);

            TCIDB* index = SearchEngine::get_instance()->get_index(
                "indirect/" + langCode + transInLangCode
            );

            TATO_TREE_STR_FOREACH(lang->index, iterItem) {

                item = (TatoItem*) iterItem->value;

                //TODO if has translation in 
                SearchEngine::get_instance()->add_sentence(
                    item->id,
                    std::string(item->str),
                    std::string(item->lang->code),
                    index
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

            SearchEngine::get_instance()->close_index(index);
        }
    }

}
*/


 

/**
 *
 */
TatoDB::~TatoDB() {
    tato_db_free(tatoDb);
}

