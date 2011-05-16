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


#ifndef TATOEBA_MODELS_SEARCH_ENGINE_H 
#define TATOEBA_MODELS_SEARCH_ENGINE_H  

#include <iostream>
#include <map>
#include <set>

#include <cppcms/json.h>
#include <booster/thread.h>
#include <dystopia.h>

#include "results/searches.h"
#include "generics/Singleton.h"

// TODO change the name, as we also use it to store the LANG_METANAME index
typedef std::map<std::string, TCIDB*> LangsDbsMap;
typedef std::vector<std::string> IndexedMetas;
typedef std::map<std::string, IndexedMetas> LangsIndexedMetasMap;

/**
 * @class SearchEngine
 * Singleton class that represents the search engine and permit 
 * access to the index files
 *
 */
class SearchEngine : public Singleton<SearchEngine>{
    friend class Singleton<SearchEngine>;

    private:
        /**
         * store the code of the last errors that occured on the database
         */
        int errorCode;
        /**
         * List of the indexes (every language and lang_meta)
         */
        LangsDbsMap langsDbs;
        /**
         * Map that associate a language code to all the name of the indexes
         * related to this language (e.g:  cmn => cmn_pinyin , cmn_traditional)
         */
        LangsIndexedMetasMap langsIndexedMetas;

        /**
         * Create a new index in the search engine with the name given
         * ass parameter
         * TODO: not sure what happened if the name is already taken
         */
        void add_index(std::string indexName);

        /**
         * execute the request on the index of name "lang"
         * skipping "offset" results, and at most retrieving "size"
         * results, and store them in "results"
         */
        results::Searches search_one_index(
            std::string request,
            std::string lang,
            int size,
            int offset,
            results::Searches &results,
            std::set<int> &uniqueResults
        );
        
        /**
         * Constructor
         */
        SearchEngine();
        /**
         * Destructor
         */
        ~SearchEngine();

    public:
        /**
         * Will init the meta that are indexed, based on the list
         * provided by the config.js file
         */
        void init_indexed_metas( 
            cppcms::json::object langsIndexedMetasJson
        );

        /**
         * index the sentence number "sentenceId" in the index "lang"
         */
        void add_sentence(
            int sentenceId,
            std::string text,
            std::string lang
        );

        /**
         * index the meta {key/value} of sentence "sentenceId"
         * in the index "lang_key"
         */
        void add_meta(
            int wordId, 
            std::string key,
            std::string value,
            std::string lang
        );

        /**
         * update the entry of the sentence "sentenceId" to fit the newText
         */
        void edit_text(
            int sentenceId,
            std::string oldText,
            std::string newText,
            std::string lang
        );

        /**
         * update the entry of meta {key/value} of the sentence "sentenceId"
         * with its new value
         */ 
        void edit_meta(
            int sentenceId, 
            std::string key,
            std::string value,
            std::string lang
        );

        /**
         * move the sentence "sentenceId" from the index "oldLang" to "newLang"
         */
        void edit_lang(
            int wordId,
            std::string text,
            std::string oldLang,
            std::string newLang
        );

        /**
         * Remove the sentence "sentenceId" from the index "lang"
         */
        void remove_sentence(
            int sentenceId,
            std::string lang
        );

        /**
         * Remove the meta {key/value} of sentence "sentenceId" from the index
         * lang_key
         */
        void remove_meta(
            int snetenceId, 
            std::string key,
            std::string value,
            std::string lang
        );


        /**
         * Execute the request to find all sentence of the lang "lang"
         * matching it,
         * It will skip the offset first results and return at most "size"
         * elements
         */
        results::Searches search(
            std::string request,
            std::string lang,
            int size,
            int offset
        );
        

};

#endif


