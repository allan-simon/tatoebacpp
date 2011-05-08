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
         * Display a form to add a new sentence
         */
        void add();

        /**
         * Treat the result sent by a form to add a new sentence
         */
        void add_treat();
};

} // End namespace

#endif
