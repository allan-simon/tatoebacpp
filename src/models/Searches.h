#ifndef MODELS_SEARCHES_H
#define MODELS_SEARCHES_H

#include <string>
#include <set>
#include <map>
#include <laputa.h>


#include "SphinxClient.h"
#include "results/sentences.h"
//TODO write doc
namespace models {

/**
* @class Searches
*/
class Searches {
    private:
        SphinxClient sphinxClient;

    public:
        Searches();


        /**
        * @brief 
        *
        * @param query
        * @param 
        *
        * @return 
        */

        results::PagiSentences advance(
            const std::string &query,
            const std::string &fromLang,
            const std::string &toLang
        );

        /**
        * @brief 
        *
        * @param query
        * @param lang
        * @param size
        * @param 
        *
        * @return 
        */
        results::PagiSentences advance(
            const std::string &query,
            const std::string &fromLang,
            const std::string &toLang,
            const int size,
            const int offset
        );


};

} // end namespace models
#endif 

