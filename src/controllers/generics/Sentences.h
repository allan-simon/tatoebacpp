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
namespace generics {
/**
 * @class Controller class to handle pages related to sentences
 */
class Sentences {
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
		Sentences();
        
        /**
         * Destructor
         */
        virtual ~Sentences();

        /**
         * Display the sentence with the given id
         */
		virtual void show(std::string sentence_id) = 0;

        /**
         * Display a random sentence
         */
        virtual void show_random() = 0;

        /**
         * Display a random sentence in the language with the given iso code
         */
        virtual void show_random_in(std::string isoCode) = 0;


        /**
         * Display a form to add a new sentence
         */
        virtual void add() = 0;

        /**
         * Treat the result sent by a form to add a new sentence
         */
        virtual void add_treat() = 0;

        /**
         * Display a form to change the text of the sentence with the
         * given id
         */
        virtual void edit_text(std::string sentenceId) = 0;

        /**
         * Treat the result sent by a form to edit the text of a sentence
         */ 
        virtual void edit_text_treat() = 0;

        /**
         * Display a form to change the lang of the sentence with the
         * given id
         */
        virtual void edit_lang(std::string sentenceId) = 0;

        /**
         * Treat the result sent by a form to edit the lang of a sentence
         */ 
        virtual void edit_lang_treat() = 0;

        /**
         * Display a form to add a translation to the sentence with the
         * given id
         */
        virtual void translate(std::string sentenceId) = 0;

        /**
         * Treat the result sent by a form to translate a sentence
         */ 
        virtual void translate_treat() = 0;

        /**
         * Link two sentences together
         */
        virtual void link(std::string idOneStr, std::string idTwoStr) = 0;

        /**
         * Unlink two sentences 
         */
        virtual void unlink(std::string idOneStr, std::string idTwoStr) = 0;

};

} // End namespace generics
} // End namespace controllers

#endif
