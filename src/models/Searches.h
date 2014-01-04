#ifndef MODELS_SEARCHES_H
#define MODELS_SEARCHES_H

#include <string>
#include <set>
#include <map>


#include "SphinxClient.h"
#include "results/sentences.h"
//TODO write doc
namespace models {

/**
* @class Searches
*/
class Searches {
    private:
        /**
         * @brief permit to connect to a sphinx search server
         */
        SphinxClient sphinxClient;

    public:
        Searches();


        /**
        * @brief Perform a search using a query language that permit 
        *        advance request (i.e not only strict match search)
        *
        * @param query       The query to the search engine
        * @param fromLang    The lang in which we're searching ("und"
        *                    for every languages)
        *
        * @param toLang      To restrict the result to sentences which have
        *                    a translation in that language
        * @param langsTokeep The results sentences will keep only the
        *                    translations in one of these languages
        *
        * @return            The first page of sentences that match the query
        */

        results::PagiSentences advance(
            const std::string &query,
            const std::string &fromLang,
            const std::string &toLang,
            const std::vector<std::string> &langsToKeep = std::vector<std::string>()
        );


        /**
        * @brief Perform a search using a query language that permit 
        *        advance request (i.e not only strict match search)
        *        with pagination
        *
        * @param query       The query to the search engine
        * @param fromLang    The lang in which we're searching ("und"
        *                    for every languages)
        *
        * @param toLang      To restrict the result to sentences which have
        *                    a translation in that language
        * @param currentPage As the result are displayed on several page
                             this variable permits to know which page, we're
                             requesting 
        * @param langsTokeep The results sentences will keep only the
        *                    translations in one of these languages
        *
        * @return            A page of sentences that match the query
        */
        results::PagiSentences advance(
            const std::string &query,
            const std::string &fromLang,
            const std::string &toLang,
            const int currentPage,
            const std::vector<std::string> &langsToKeep =
                std::vector<std::string>()
        );


};

} // end namespace models
#endif 

