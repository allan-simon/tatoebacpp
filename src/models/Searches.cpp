#include "models/Searches.h"
#include "models/SearchEngine.h"
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
Searches::Searches() {
    
}

/**
 *
 */
results::SentencesPagiVector Searches::advance(
    std::string query,
    std::string lang
) {
    return advance(query, lang, 10, 0);
}
results::SentencesPagiVector Searches::advance(
    std::string query,
    std::string lang,
    int size,
    int offset
) {
    results::Searches resultIds = SearchEngine::get_instance()->search(
        query,
        lang,
        size,
        offset
    );
    
    results::SentencesPagiVector sentencesPagiVector(resultIds.size());

    models::Sentences sentencesModel;

    int resultSize = resultIds.size();
    for (int i = 0; i < resultSize; ++i) {
        sentencesPagiVector[i] = sentencesModel.get_by_id(
            resultIds[i]
        );
    }
    sentencesPagiVector.offset = offset;
    sentencesPagiVector.maxsize = resultIds.maxsize;
    return sentencesPagiVector;
}

}; //end of namespace
