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


#ifndef TATOEBACPP_MODELS_TATODB_H
#define TATOEBACPP_MODELS_TATODB_H

#include <map>
#include "generics/Singleton.h"
#include "results/sentences_stats.h"

extern "C" {
#include "tato/db.h"
}

#define GET_DB_POINTER() TatoDB::get_instance("")->get_db_pointer()


/**
 * @class TatoDB
 * singleton representing the graph database of tatoeba
 */
class TatoDB : public Singleton<TatoDB>{
    friend class Singleton<TatoDB>;

    private:
        /**
         * Pointer on the graph database structure
         */
        TatoDb *tatoDb;
        /**
         * Constructor, will create a tatodb graph database
         * and fill it with the data at data_path
         */
        TatoDB(std::string data_path);
        /**
         * destructor
         */
        ~TatoDB();

    public:
        /**
         * Will return the pointer on the tatodb graph structure
         */
        TatoDb *get_db_pointer();

        /**
         * Will return a map of with the number of sentences for each languages
         */
        results::SentencesStats get_sentences_stats();

        /**
         * @brief Get the five languages that have the most sentences
         *
         * @return The five top languages and the number of sentences for
         *         each of them
         *
         * @sinceA 26 August 2011
         */
        results::SentencesStats get_top_five();

        /**
         * @brief Get the total number of sentences in tatoeba
         *
         * @return A number, the total number of sentences
         *
         * @since 26 August 2011
         */
        unsigned int get_total_nbr_sentences();
       
        /**
         * Will dump the database in the given following xml file
         */ 
        void dump(std::string path);

        /**
        * @brief Dump the database into a sphinx indexable format in the given file
        *
        * @param path Path of the file in which the dump will be written
        */
        void sphinx_dump(std::string path);

        /**
         * Will feed the search engine 
         */ 
        void feed_search_engine();
};


#endif
