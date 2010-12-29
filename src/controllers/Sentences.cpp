#include "Controller.h"
#include "controllers/Sentences.h"
#include "tatoeba.h"
#include "contents/homepage.h"

#include "models/TatoDB.h"

namespace controllers {

Sentences::Sentences(apps::tatoeba& tatoapp) : Controller(tatoapp) {
	std::cout << "i dans sentences vaut " << this->i << std::endl;
  	tatoapp.dispatcher().assign("/sentences/show/(\\d+)", &Sentences::show, this, 1);
  	tatoapp.dispatcher().assign("/sentences/show/random", &Sentences::show_random, this);
}

/**
 * Display all the information about a specific sentence
 */

void Sentences::show(std::string sentence_id) {
	int id = atoi(sentence_id.c_str());

	contents::Homepage c;
	contents::SentencesHelper shc;
    initContent(c);
    // TODO it's only for the proof of concept 
    // it should be moved in the model
    //
    TatoDb *tatoDb = TatoDB::getInstance("")->getDatabasePointer(); 
    TatoItem *sentence = tato_db_item_find(tatoDb, id);
    shc.tree = NULL;
    if (sentence != NULL) {
        TatoFetcherTree *tree = tato_fetcher_tree_new();
        tato_fetcher_tree_bfs(tree, sentence, 20, NULL);
        shc.tree = tree;

    }

    c.shc = shc;
    //test_ouput(tree->root);	
    render ("sentences_show", c);
}


/**
 * Display a random sentence
 */

void Sentences::show_random() {
    TatoDb *tatoDb = TatoDB::getInstance("")->getDatabasePointer(); 
    TatoItem *randSentence = tato_db_item_rand(tatoDb);

    std::ostringstream oss;
    oss << randSentence->id;

    response().set_redirect_header("/en/sentences/show/" + oss.str() );

}


} // End namespace
