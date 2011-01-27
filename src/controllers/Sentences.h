#ifndef CONTROLLERS_SENTENCES_H
#define CONTROLLERS_SENTENCES_H

#include "Controller.h"
#include "models/Sentences.h"

extern "C" {
#include "tato/db.h"
#include "tato/item.h"
#include "tato/list.h"
#include "tato/fetcher_tree.h"
}


namespace controllers {

class Sentences : public Controller {
    private:
        models::Sentences sentenceModel;
	public:
		Sentences(apps::Tatoeba& tatoapp);
		void show(std::string sentence_id);
        void show_random();
};

} // End namespace

#endif
