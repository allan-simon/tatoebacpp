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

class SphinxClient {

    private:
        sphinx_client *client;

        void net_init();
    
    public:
        SphinxClient(std::string hostname, int port);
        ~SphinxClient();
        results::Searches search(
            const std::string &query,
            const std::string &from,
            const std::string &to,
            const int size,
            const int offset
        );
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
