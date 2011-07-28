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

#include <iostream>
#include "generics/Languages.h"
#include "SphinxClient.h"

namespace models {

/**
 *
 */
SphinxClient::SphinxClient(std::string hostname, int port) {
	net_init();

	client = sphinx_create (SPH_TRUE);
	if (!client)
		std::cerr << "failed to create client" ;

	if (port) {
		sphinx_set_server ( client, "127.0.0.1", port );
    }

	sphinx_set_match_mode ( client, SPH_MATCH_EXTENDED2 );
	sphinx_set_sort_mode ( client, SPH_SORT_RELEVANCE, NULL );
    sphinx_set_limits(
        client,
        0, // default offset
        10, // display 10 results per page 
        500, // we don't need to go as far as 1000 results 
        0 // default value for so called cutoff (i don't know what it does)
    );


}

/**
 *
 */
SphinxClient::~SphinxClient() {
	sphinx_close (client);
	sphinx_destroy (client);
}

/**
 *
 */
void SphinxClient::net_init () {
#if _WIN32
	// init WSA on Windows
	WSADATA wsa_data;
	int wsa_startup_err;

	wsa_startup_err = WSAStartup ( WINSOCK_VERSION, &wsa_data );
	//if ( wsa_startup_err )
	//	die ( "failed to initialize WinSock2: error %d", wsa_startup_err );
#endif
}


/**
 *
 */
results::Searches SphinxClient::search(
    const std::string &query,
    const std::string &from,
    const std::string &to,
    const int size = 10,
    const int offset = 0
) {
    sphinx_set_limits(
        client,
        offset, 
        size, 
        500, // we don't need to go as far as 1000 results 
        0 // default value for so called cutoff (i don't know what it does)
    );

    sphinx_reset_filters(client);
    if (to.compare("und") != 0) {
        
        const sphinx_int64_t translatedInFilter[1] ={Languages::get_instance()->get_id_from_iso(to)};
        sphinx_add_filter(
            client,
            "translatedin",
            1,
            translatedInFilter, 
            SPH_FALSE
        );
            
    }


	sphinx_result* res = sphinx_query(
        client,
        query.c_str(),
        from.c_str(),
        NULL
    );

    results::Searches matchedIds;
    if (res == NULL) {
        return matchedIds;
    }

	for (int i=0; i< res->num_matches; i++ ) {
		matchedIds.push_back(
            (int)sphinx_get_id (res, i)
        );
    }
    matchedIds.maxsize = res->total;

    return matchedIds;
}


/**
 *
 */
void SphinxClient::add_sentence(
    const int sentenceId,
    const std::string &text,
    const std::string &lang
) {

    //TODO write here the code to update in realtime
    // the index when the API will be ready
}

/**
 *
 */
void SphinxClient::edit_text(
    const int sentenceId,
    const std::string &oldText,
    const std::string &newText,
    const std::string &lang
) {
    //TODO waiting the sphinx api to be ready
}

/**
 *
 */
void SphinxClient::edit_lang(
    const int sentenceId,
    const std::string &text,
    const std::string &oldLang,
    const std::string &newLang
) {
    //TODO waiting the sphinx api to be ready

}

/**
 *
 */
void remove_sentence(
    const int sentenceId,
    const std::string &lang
) {
    //TODO waiting the sphinx api to be ready
}

} // end namespace models

