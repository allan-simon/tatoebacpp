/**
 * Tatoeba Project, free collaborative creation of multilingual corpuses project
 * Copyright (C) 2011 Allan SIMON <allan.simon@supinfo.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * @category Tatoebacpp
 * @package  Controllers
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */



#ifndef CONTROLLERS_SENTENCES_H
#define CONTROLLERS_SENTENCES_H

#include "Controller.h"

/*
extern "C" {
#include "tato/db.h"
#include "tato/item.h"
#include "tato/list.h"
#include "tato/fetcher_tree.h"
}
*/
namespace models {
    class Sentences;
}

namespace controllers {

/**
 * @class Controller class to handle pages related to sentences
 */
class Sentences : public Controller {
    private:
        /**
         * Model class for sentences
         */
        models::Sentences *sentencesModel;
	public:
        /**
         * Constructor, will attach the url to the dispatcher
         * and instantiate the model
         */
		Sentences(cppcms::service &serv);
        
        /**
         * Destructor
         */
        ~Sentences();

        /**
         * Display the sentence with the given id
         */
		void show(std::string sentence_id);

        /**
         * Display a random sentence
         */
        void show_random();

        /**
         * Display a random sentence in the language with the given iso code
         */
        void show_random_in(std::string isoCode);


        /**
         * Display a form to add a new sentence
         */
        void add();

        /**
         * Treat the result sent by a form to add a new sentence
         */
        void add_treat();

        /**
         * Display a form to change the text of the sentence with the
         * given id
         */
        void edit_text(std::string sentenceId);

        /**
         * Treat the result sent by a form to edit the text of a sentence
         */ 
        void edit_text_treat();

        /**
         * Display a form to change the lang of the sentence with the
         * given id
         */
        void edit_lang(std::string sentenceId);

        /**
         * Treat the result sent by a form to edit the lang of a sentence
         */ 
        void edit_lang_treat();

        /**
         * Display a form to add a translation to the sentence with the
         * given id
         */
        void translate(std::string sentenceId);

        /**
         * Treat the result sent by a form to translate a sentence
         */ 
        void translate_treat();

        /**
         * Link two sentences together
         */
        void link(std::string idOneStr, std::string idTwoStr);

        /**
         * Unlink two sentences 
         */
        void unlink(std::string idOneStr, std::string idTwoStr);

};

} // End namespace

#endif
