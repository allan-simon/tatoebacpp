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
 * @package  Models
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */



#ifndef TATOEBACPP_MODELS_SENTENCES_H
#define TATOEBACPP_MODELS_SENTENCES_H

#include <exception>

#include "models/TatoDB.h"
#include "models/SphinxClient.h"
#include "results/sentences.h"

extern "C" {
#include "tato/fetcher.h"
#include "tato/item.h"
}

namespace models {

/**
 * @class SentDupliException
 * Exception class that is thrown when a duplicate is added
 * it will store the id of the original sentence
 */
class SentDupliException : public std::exception {
    public:
        SentDupliException(int originalId);

        virtual const char* what() const throw();

        /**
         * Return the id of the original sentence
         */
        int get_original_id() const throw();

        /**
         * Destructor
         */
        virtual ~SentDupliException() throw();

    private:
        /**
         * Store the id of the original sentence
         */
        int originalId;
};





/**
 * @class Sentences
 * class represente an abstract way to get the sentences stored in
 * the abstracted database (here tatodb)
 */
class Sentences {


    public:
        /**
         * Default constructor
         */
        Sentences();

        /**
         * get a sentence with a given ID and all its translations
         */
        results::Sentence get_by_id(
            const int id,
            const int depth,
            const std::vector<std::string> &langsToKeep = std::vector<std::string>()
        );

        /**
         * @brief Simply get the sentence with the given id, without extra
         *        information
         *
         * @param id The id of the sentence we want to retrieve
         *
         * @return The given sentence or an empty sentence if the given id is
         *         linked to no sentence
         *
         * @since  24 August 2011
         */
        results::Sentence simple_get_by_id(
            const int id
        );
        /**
         * Return the id of a random existing sentence
         */
        int get_random_id(
            const std::vector<std::string> &langsToKeep = std::vector<std::string>()
        );

        /**
         * Return the id of a random existing sentence in the language with
         * the given iso code
         */
        int get_random_id(std::string isoCode);


        /**
         * get a random sentence and all its translations
         */
        results::Sentence get_random(
            const int depthLimit = 20,
            const std::vector<std::string> &langsToKeep = std::vector<std::string>()
        );

        /**
         * get a random sentence in the language with the given iso code
         * and all its translations
         */
        results::Sentence get_random(
            const std::string &isoCode,
            const int depthLimit = 20,
            const std::vector<std::string> &langsToKeep = std::vector<std::string>()
        );


        /**
         * Will add the given sentence in the database
         * and return it or thrown an exception if duplicate
         */
        results::Sentence add(
            const std::string &lang,
            const std::string &str,
            const int userId
        ) throw(SentDupliException);

        /**
         * Will add the given sentence in the database
         * and return it or thrown an exception if duplicate
         */
        results::Sentence add(
            const std::string &lang,
            const std::string &str,
            const TatoItemFlags flags,
            const int userId
        ) throw(SentDupliException);

        /**
         * Will link the sentence X and Y together
         */
        void link(
            int xId,
            int yId,
            int userId
        );

        /**
         * Will unlink the sentence X and Y
         */
        void unlink(
            int xId,
            int yId,
            int userId
        );

        /**
         * @brief Write the code of the lang of a given sentence in a variable
         * 
         * @param sentenceId   The id of the sentence to get the lang of
         * @param sentenceLang The variable in which the code will be written
         *
         * @return True if something was written , false otherwise
         * @since  17 August 2011
         *
         * @todo:  use exception when the sentence id does not exist
         */
        static bool get_lang(
            int sentenceId,
            std::string &sentenceLang
        );

        /**
         * Change the text of the sentence with the given id
         * by the one send as parameter, if the pair (newText,lang) already
         * exists an exception is thrown
         */

        void edit_text(
            int id,
            std::string newString,
            int userId
        ) throw(SentDupliException);

        /**
         * Change the lang of the sentence with the given id
         * by the one send as parameter, if the pair (text,newLang) already
         * exists an exception is thrown
         */

        void edit_lang(
            int id,
            std::string newLang,
            int userId
        ) throw(SentDupliException);


        /*
        results::SentencesPagiVector get_all();
        results::SentencesPagiVector get_all(
            int offset,
            int windowsize
        );

        results::SentencesPagiVector get_all_in(std::string lang);
        results::SentencesPagiVector get_all_in(
            std::string lang,
            int offset,
            int windowsize
        );


        */

    private :
        /**
         * Client access to the sphinx server
         */
        SphinxClient sphinxClient;

        //TODO reintroduce logs
        /**
         * return the results::Sentence object constructed with a given
         * TatoItem struct
         */
        results::Sentence sentence_from_item(
            TatoItem* item,
            const int depth,
            const std::vector<std::string> &langsToKeep = std::vector<std::string>()
        );

        /**
         * @brief Return the results::Sentence object constructed with a given
         *        TatoItem struct, the object will have only the minimal set of
         *        information (text, sentences) (no translation/owner)
         *
         * @param Item The TatoItem to convert into a sentence object
         *
         * @return The sentence under the form of a results::Sentence object
         * 
         * @since 24 August 2011
         */
        results::Sentence simple_sentence_from_item(
            TatoItem* item
        );

        /**
         * Will traverse the graph of translations starting from
         * the node item until ,maxDepth and will pack linked item
         * in translations according to their distance from the start
         *
         */
        void pack_translations(
            TatoItem* item,
            TransVector &translations,
            const int maxDepth,
            const std::vector<std::string> &langsToKeep = std::vector<std::string>()
        );

};


}

#endif
