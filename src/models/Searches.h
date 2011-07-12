#ifndef MODELS_SEARCHES_H
#define MODELS_SEARCHES_H

#include <string>
#include <set>
#include <map>
#include <laputa.h>

#include "results/sentences.h"
//TODO write doc
namespace models {

class Searches {
    public:
        Searches();


        results::SentencesPagiVector advance(std::string query, std::string lang);
        results::SentencesPagiVector advance(
            std::string query,
            std::string lang,
            int size,
            int offset
        );


};

} // end namespace models
#endif 

