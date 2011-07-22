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


#ifndef TATOEBA_MODELS_SPHINX_CLIENT_H 
#define TATOEBA_MODELS_SPHINX_CLIENT_H  

#include <vector>

#if _WIN32
#include <winsock2.h>
#endif

#include "sphinxclient.h"
#include "results/searches.h"




namespace models {

/**
 * @class Class used to communicate with the sphinx server,
 *        to make query, update indexes etc.
 */
class SphinxClient {

    private:
            
        /**
        * @brief Structure used by the C API of sphinx
        */
        sphinx_client *client;

        void net_init();
    
    public:
            
        /**
        * @brief Consructor for the sphinx client
        *
        * @param hostname Ip on which the sphinx deamon is running
        * @param port     Port on which the deamon is listening
        */
        SphinxClient(std::string hostname, int port);

        ~SphinxClient();

                
        /**
        * @brief 
        *
        * @param query  Query to send to sphinx
        * @param from   Language in which we're searching ("und" to search
        *               in every language
        * @param to     Filter only having result in that language ("und" for
        *               no filter)
        * @param size   Number of max results wanted
        * @param offset Offset (used for pagination)
        *
        * @return       List of sentences group that match the query
        */
        results::Searches search(
            const std::string &query,
            const std::string &from,
            const std::string &to,
            const int size,
            const int offset
        );

        
        /**
         * index the sentence number "sentenceId" in the index "lang"
         */
        void add_sentence(
            const int sentenceId,
            const std::string &text,
            const std::string &lang
        );

        /**
         * update the entry of the sentence "sentenceId" to fit the newText
         */
        void edit_text(
            const int sentenceId,
            const std::string &oldText,
            const std::string &newText,
            const std::string &lang
        );    
              
        /**   
         * move the sentence "sentenceId" from the index "oldLang" to "newLang"
         */   
        void edit_lang(
            const int sentenceId,
            const std::string &text,
            const std::string &oldLang,
            const std::string &newLang
        );    
              
              
        /**   
         * Remove the sentence "sentenceId" from the index "lang"
         */   
        void remove_sentence(
            const int sentenceId,
            const std::string &lang
        );    
              
              
        /**   
         *    
         */   
        /*
        void add_link(
            const int sentenceId,
            const std::string &lang,
            const std::string &linkedToLang
        );
        */

        /**
         *
         */
        /*
        void remove_link(
            const int sentenceId,
            const std::string lang,
            const std::string removeLinkToLang
        );
        */

        /*
        ::results::Searches search(
            std::string query,
            std::string from,
            std::string to
        );
        */
};

} // end namespace models 

#endif
