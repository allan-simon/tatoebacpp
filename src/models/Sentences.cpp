#include <sstream>
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

int Sentences::getRandomSentenceId() {
    int id = 0;
    TatoDb *tatoDb = TatoDB::getInstance("")->getDatabasePointer();
    TatoItem *randSentence = tato_db_item_rand(tatoDb);

    std::stringstream ss;
    ss << randSentence->id;
    ss >> id;

    return id;
}

}
