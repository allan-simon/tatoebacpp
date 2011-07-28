#include "models/Searches.h"
#include "models/Sentences.h"


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
results::PagiSentences Searches::advance(
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
results::PagiSentences Searches::advance(
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
    
    
    results::PagiSentences pagiSentences(resultIds.size());

    models::Sentences sentencesModel;

    int resultSize = resultIds.size();
    for (int i = 0; i < resultSize; ++i) {
        pagiSentences[i] = sentencesModel.get_by_id(
            resultIds[i],
            3 //TODO magic number: max depth for search results
        );
    }
    pagiSentences.offset = offset;
    pagiSentences.maxsize = resultIds.maxsize;
    return pagiSentences;
}

} //end of namespace
