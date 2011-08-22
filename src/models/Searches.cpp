#include "models/Searches.h"
#include "models/Sentences.h"


#define SEARCH_PAGE_SIZE 10

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
    const std::string &toLang,
    const std::vector<std::string> &langsToKeep 
) {
    return advance(
        query,
        fromLang,
        toLang,
        0,
        langsToKeep
    );
}
results::PagiSentences Searches::advance(
    const std::string &query,
    const std::string &fromLang,
    const std::string &toLang,
    const int currentPage,
    const std::vector<std::string> &langsToKeep
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
        currentPage,
        SEARCH_PAGE_SIZE
    );
    
    
    results::PagiSentences pagiSentences(resultIds.size());

    models::Sentences sentencesModel;

    int resultSize = resultIds.size();
    for (int i = 0; i < resultSize; ++i) {
        pagiSentences[i] = sentencesModel.get_by_id(
            resultIds[i],
            3, //TODO magic number: max depth for search results
            langsToKeep
        );
    }
    pagiSentences.pageNormalSize = SEARCH_PAGE_SIZE;
    pagiSentences.currentPage = currentPage;
    pagiSentences.totalNbrElements = resultIds.totalNbrElements;
    return pagiSentences;
}

} //end of namespace
