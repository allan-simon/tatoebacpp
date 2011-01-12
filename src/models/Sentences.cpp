#include "models/Sentences.h"

namespace models {

Sentences::Sentences() {
}

TatoFetcherTree* Sentences::getSentenceWithId(int id) {
    TatoDb *tatoDb = TatoDB::getInstance("")->getDatabasePointer();
    TatoItem *sentence = tato_db_item_find(tatoDb, id);

    if (sentence != NULL) {
        TatoFetcherTree *tree = tato_fetcher_tree_new();
        tato_fetcher_tree_bfs(tree, sentence, 20, NULL);
        return tree;
    }

    return NULL;
}

}
