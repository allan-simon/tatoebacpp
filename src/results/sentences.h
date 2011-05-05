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
 * @package  Results
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */

#ifndef TATOEBACPP_RESULTS_SENTENCES_H
#define TATOEBACPP_RESULTS_SENTENCES_H

#include <vector>
#include <map>

namespace results {
    struct Sentence;
}

typedef std::vector<results::Sentence> SentencesVector;
typedef std::vector<SentencesVector> TransVector; 


/**
 * @namespace results
 * contains everything which is needed to transit from the model
 * to the controller
 */
namespace results {

    typedef std::map<std::string, std::string> MetasMap;

    /**
     * @struct Sentence
     * Abstract representation of a sentence
     */
    struct Sentence {
        /**
         * Id of the sentence in tatodb
         */
        unsigned int id;
        /**
         * Text of the sentence
         */
        std::string text;
        /**
         * ISO code of the language in which the sentence is written
         */
        std::string lang;
        /**
         * List of binary flags store in a unsigned int
         */
        unsigned int flags; //TODO replace this by tatohyperdb type
        /**
         * Map containing the metas information on this sentence
         */
        MetasMap metas;
        /**
         * Vector of vector of Translation sentences of this sentence
         * organized the following way
         *
         *  0 =>  [translation1, translation2]
         *  1 =>  [indirect translation 1, indirect translation2, etc.]
         *
         *  the first index is used to know the distance between the main
         *  sentence and a translation
         *
         *  NOTE: this solution does not permit to view the "path" between
         *  one sentence and Nth indirect translation
         */
        TransVector translations;

        public:
            /**
             * Default constructor, will construct an empty sentence
             */
            Sentence(): id(0),text(""),lang(""),flags(0){};

            /**
             * Constructor that will create a sentence with the correct
             * id, text, lang and flags and no translations using std::string
             */
            Sentence(int id, std::string text, std::string lang, int flags):
                id(id),
                text(text),
                lang(lang),
                flags(flags) {
            };
            
            /**
             * Constructor that will create a sentence with the correct 
             * id, text, lang and flags and no translations using char*
             */
            Sentence(int id, char* text, char* lang, int flags):
                id(id),
                text(std::string(text)),
                lang(std::string(lang)),
                flags(flags) {
            };

            /*
            Sentence(TatoItem* sentenceItem) {
                if (sentenceItem == NULL) {
                    id = 0;
                    return;
                }
                id = sentenceItem->id;
                text = std::string(sentenceItem->str);
                lang = std::string(sentenceItem->lang->code);
                flags = sentenceItem->flags;

            };
            */

            /**
             * tell if the object represent an actual sentence
             */
            bool exists() {
                return id > 0;
            }

    };

    /**
     * Vector of sentences used when need to get only those in a given
     * window from  offset to min((offet + maxsize), totalnumberofsentences_
     * @TODO should be possible to template it
     *
     */
    struct SentencesPagiVector : public std::vector<Sentence> {
        /**
         * number of sentences that has been skip
         */
        int offset;
        /**
         * size of the window
         * if offset + maxsize > total number of sentences then the vector
         * will contain less sentences than maxsize
         */
        int maxsize;
        public:
            SentencesPagiVector(): offset(0), maxsize(0) {};
            SentencesPagiVector(int size) :
                std::vector<Sentence>(size),
                offset(0),
                maxsize(0) {};
    };
}

// We need this to be able to use results::Sentence has a key for map, set etc.
namespace std {
    template<> struct less<results::Sentence> {
        bool operator() (const results::Sentence& lhs, const results::Sentence& rhs) {
            return lhs.id < rhs.id;
        }
    };

};



#endif

