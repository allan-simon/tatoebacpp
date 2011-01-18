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

    shc.tree = sentenceModel.getSentenceWithId(id);

    c.shc = shc;
    //test_ouput(tree->root);	
    render ("sentences_show", c);
}


/**
 * Display a random sentence
 */

void Sentences::show_random() {
    std::ostringstream oss;
    oss << sentenceModel.getRandomSentenceId();

    response().set_redirect_header("/en/sentences/show/" + oss.str() );

}


} // End namespace
