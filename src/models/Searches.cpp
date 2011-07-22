#include "models/Searches.h"
#include "models/Sentences.h"

extern "C" {
#include "tato/fetcher.h"
#include "tato/item.h"
#include "tato/lang.h"
}

namespace models {

/**
 *
 */
Searches::Searches() :
    sphinxClient("127.0.0.1", 9312) 
{

}

/**
 *
 */
results::SentencesPagiVector Searches::advance(
    const std::string &query,
    const std::string &fromLang,
    const std::string &toLang 
) {
    return advance(
        query,
        fromLang,
        toLang,
        10,
        0
    );
}
results::SentencesPagiVector Searches::advance(
    const std::string &query,
    const std::string &fromLang,
    const std::string &toLang,
    const int size,
    const int offset
) {
    /*
    results::Searches resultIds = SearchEngine::get_instance()->search(
        query,
        lang,
        size,
        offset
    );
    */
    results::Searches resultIds = sphinxClient.search(
        query,
        fromLang,
        toLang,
        size,
        offset
    );
    
    
    results::SentencesPagiVector sentencesPagiVector(resultIds.size());

    models::Sentences sentencesModel;

    int resultSize = resultIds.size();
    for (int i = 0; i < resultSize; ++i) {
        sentencesPagiVector[i] = sentencesModel.get_by_id(
            resultIds[i],
            3 //TODO magic number: max depth for search results
        );
    }
    sentencesPagiVector.offset = offset;
    sentencesPagiVector.maxsize = resultIds.maxsize;
    return sentencesPagiVector;
}

} //end of namespace
