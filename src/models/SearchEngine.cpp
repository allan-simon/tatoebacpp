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

#include <cmath>
#include "SearchEngine.h"
#include "generics/Languages.h"
#include "contents/Config.h"

/**
 *
 */
SearchEngine::SearchEngine() {

    indexesPath = Config::get_instance()->indexesPath; 
    /*
    ISOToNameMap isoToName = Languages::get_instance()->get_iso_to_name_map();
    ISOToNameMap::const_iterator itr;
    for (itr = isoToName.begin(); itr != isoToName.end(); ++itr) {
        add_index(itr->first);
    }
    */


    // create the object
}

/**
 *
 */
SearchEngine::~SearchEngine() {
    // close the databases
    //

    /*
    LangsDbsMap::const_iterator end = langsDbs.end();
    for (LangsDbsMap::const_iterator it = langsDbs.begin(); it != end; ++it) {
        if (!tcidbclose(it->second)) {
            errorCode = tcidbecode(it->second);
            std::cerr << "close error: "<< tcidberrmsg(errorCode) << std::endl;
        }
        // delete the object
        tcidbdel(it->second);
    }
    */
}

/**
 *
 */
TCIDB* SearchEngine::get_index(std::string indexName) {
    TCIDB *tempIDB = tcidbnew();
    std::string indexPath = indexesPath + indexName;
    if (!tcidbopen(tempIDB, indexPath.c_str(), IDBOWRITER | IDBOCREAT | IDBOLCKNB )) {
        errorCode = tcidbecode(tempIDB);
        std::cerr << "open error: "<< tcidberrmsg(errorCode) << std::endl;
        // TODO throw an exception instead
        return NULL;
    }
    return  tempIDB;

}

/**
 *
 */
void SearchEngine::close_index(TCIDB* index) {
    if (index == NULL) {
        return;
    }

    if (!tcidbclose(index)) {
        errorCode = tcidbecode(index);
        std::cerr << "close error: "<< tcidberrmsg(errorCode) << std::endl;
    }
    // delete the object
    tcidbdel(index);
}


/**
 *
 */
void SearchEngine::init_indexed_metas(
    cppcms::json::object langsIndexedMetasJson
) {

    ISOToNameMap isoToName = Languages::get_instance()->get_iso_to_name_map();
    ISOToNameMap::const_iterator itr;
    for (itr = isoToName.begin(); itr != isoToName.end(); ++itr) {
        
        std::string tempLang = itr->first;
        if (langsIndexedMetasJson[tempLang].is_null()) {
            continue;
        }
        cppcms::json::array indexedMetas = langsIndexedMetasJson[tempLang].array();
        for (
            cppcms::json::array::const_iterator jsonItr = indexedMetas.begin();
            jsonItr != indexedMetas.end();
            ++jsonItr
        ) {
            std::string meta = (*jsonItr).str();
            langsIndexedMetas[tempLang].push_back(meta);
            //add_index(tempLang + "_" + meta);
        }
    }
}

/**
 *
 */
void SearchEngine::add_index(std::string indexName) {

    TCIDB *tempIDB = tcidbnew();
    //tcidbsetcache(tempIDB,1,1);
    // open the database
    std::string indexPath = indexesPath + indexName;
    if (!tcidbopen(tempIDB, indexPath.c_str(), IDBOWRITER | IDBOCREAT | IDBOLCKNB )) {
        errorCode = tcidbecode(tempIDB);
        std::cerr << "open error: "<< tcidberrmsg(errorCode) << std::endl;
    }
    langsDbs[indexName] = tempIDB;
}

/**
 *
 */
void SearchEngine::add_sentence(
    int sentenceId,
    std::string text,
    std::string lang
) {
    TCIDB *langIDB = get_index(lang); //langsDbs[lang];
    if (!tcidbput(langIDB, sentenceId, text.c_str())) {
        errorCode = tcidbecode(langIDB);
        std::cerr << "add error: "<< tcidberrmsg(errorCode) << std::endl;
    }
    close_index(langIDB);
}

/**
 *
 */
void SearchEngine::add_sentence(
    int sentenceId,
    std::string text,
    std::string lang,
    TCIDB * langIDB
) {
    if (!tcidbput(langIDB, sentenceId, text.c_str())) {
        errorCode = tcidbecode(langIDB);
        std::cerr << "add error: "<< tcidberrmsg(errorCode) << std::endl;
    }
}



/**
 *
 */
void SearchEngine::add_meta(
    int sentenceId, 
    std::string key,
    std::string value,
    std::string lang
) {
    add_sentence(
        sentenceId,
        value,
        lang + "_" + key
    );
}



/**
 *
 */
void SearchEngine::edit_text(
    int sentenceId,
    std::string oldText,
    std::string newText,
    std::string lang
) {

    TCIDB *langIDB = get_index(lang);//langsDbs[lang];
    if (!tcidbout(langIDB, sentenceId)) {
        errorCode = tcidbecode(langIDB);
        std::cerr << "remove error: "<< tcidberrmsg(errorCode) << std::endl;
        close_index(langIDB);
        return;
    }


    if (!tcidbput(langIDB, sentenceId, newText.c_str())) {
        errorCode = tcidbecode(langIDB);
        std::cerr << "add error: "<< tcidberrmsg(errorCode) << std::endl;
        close_index(langIDB);
        return;
    }
    close_index(langIDB);
}

/**
 *
 */
void SearchEngine::edit_lang(
    int sentenceId,
    std::string text,
    std::string oldLang,
    std::string newLang
) {
    TCIDB *oldIDB = get_index(oldLang);
    TCIDB *newIDB = get_index(newLang);


    if (!tcidbout(oldIDB, sentenceId)) {
        errorCode = tcidbecode(oldIDB);
        std::cerr << "remove error: "<< tcidberrmsg(errorCode) << std::endl;
        close_index(oldIDB);
        return;
    }

    if (!tcidbput(newIDB, sentenceId, text.c_str())) {
        errorCode = tcidbecode(newIDB);
        std::cerr << "add error: "<< tcidberrmsg(errorCode) << std::endl;
        close_index(oldIDB);
        close_index(newIDB);
        return;
    }
   
    close_index(oldIDB);
    close_index(newIDB);
}

/**
 *
 */
void SearchEngine::edit_meta(
    int sentenceId, 
    std::string key,
    std::string value,
    std::string lang
) {
    std::string indexName(lang + "_" + key);
    TCIDB *langIDB = get_index(indexName);

    if (!tcidbout(langIDB, sentenceId)) {
        errorCode = tcidbecode(langIDB);
        std::cerr << "remove error: "<< tcidberrmsg(errorCode) << std::endl;
        close_index(langIDB);
        return;
    }


    if (!tcidbput(langIDB, sentenceId, value.c_str())) {
        errorCode = tcidbecode(langIDB);
        std::cerr << "add error: "<< tcidberrmsg(errorCode) << std::endl;
        close_index(langIDB);
        return;
    }
    close_index(langIDB);

}



/**
 *
 */
void SearchEngine::remove_sentence(
    int sentenceId,
    std::string lang
) {

    TCIDB *langIDB = get_index(lang);//langsDbs[lang];
    if (!tcidbout(langIDB, sentenceId)) {
        errorCode = tcidbecode(langIDB);
        std::cerr << "remove error: "<< tcidberrmsg(errorCode) << std::endl;
    }
    close_index(langIDB);

    // remove also the metas from the indexes
    IndexedMetas::const_iterator end = langsIndexedMetas[lang].end();
    for (
        IndexedMetas::const_iterator itr = langsIndexedMetas[lang].begin();
        itr != end;
        ++itr
    ) {
        std::string indexName(lang + "_" + *itr);
        TCIDB *metaIDB = get_index(indexName);

        if (!tcidbout(metaIDB, sentenceId)) {
            errorCode = tcidbecode(metaIDB);
            std::cerr << "remove error: "<< tcidberrmsg(errorCode) << std::endl;
        }
        close_index(metaIDB);
       
    }

}


/**
 *
 */
void SearchEngine::remove_meta(
    int sentenceId,
    std::string key,
    std::string value,
    std::string lang
) {
    std::string indexName(lang + "_" + key);
    TCIDB *metaIDB = get_index(indexName);

    if (!tcidbout(metaIDB, sentenceId)) {
        errorCode = tcidbecode(metaIDB);
        std::cerr << "remove error: "<< tcidberrmsg(errorCode) << std::endl;
    }
    close_index(metaIDB);


}
/**
 *
 */
results::Searches SearchEngine::search(
    std::string request,
    std::string lang,
    unsigned int size,
    int offset
) {
    std::set<int> uniqueResults;
    results::Searches results;


    search_one_index(
        request,
        lang,
        size,
        offset,
        results,
        uniqueResults
    );

    IndexedMetas::const_iterator end = langsIndexedMetas[lang].end();
    for (
        IndexedMetas::const_iterator it = langsIndexedMetas[lang].begin();
        it != end && (size - results.size()) > 0; 
        ++it
    ) {
        search_one_index(
            request,
            lang + "_" + *it,
            size - results.size(),
            std::max(0, offset- (int)uniqueResults.size()),
            results,
            uniqueResults
        );
        results::Searches::iterator insertIt = results.end();
    }
    results.offset = offset;
    results.maxsize = uniqueResults.size();
    return results;
}
/**
 *
 */

results::Searches SearchEngine::search_one_index(
    std::string request,
    std::string indexName,
    unsigned int size,
    int offset,
    results::Searches& results,
    std::set<int>& uniqueResults
) {
    TCIDB *langIDB = get_index(indexName); //langsDbs[lang];
    if (langIDB == NULL) {
        return results::Searches();
    }
    /* search records */

    int rnum = 0;

    //we first search for words beginning with the
    //request, so that they will appear first
    uint64_t *beginWithResult = tcidbsearch(
        langIDB,
        request.c_str(),
        IDBSPREFIX,
        &rnum
    );

    int max = std::min(rnum,(int)size+offset);

    if (beginWithResult) {

        int sentenceId = 0;
        for (int i = 0; i < rnum; i++) {
            sentenceId = (int)beginWithResult[i];
            uniqueResults.insert(sentenceId);
        }
        for (int i = offset; i < max; i++) {
            sentenceId = (int)beginWithResult[i];
            results.push_back(sentenceId);
        }
        
        offset = std::max(0, offset- rnum);
        free(beginWithResult);
    } else {
        errorCode = tcidbecode(langIDB);
        std::cerr << "search error: "<< tcidberrmsg(errorCode) << std::endl;
    }

    // and then we make a more generic search
    uint64_t *dystopiaResult = tcidbsearch2(
        langIDB,
        request.c_str(),
        &rnum
    );


    if (dystopiaResult) {
        for (
            int i = 0;
            results.size() < size && i < rnum;
            i++
        ) {
            int sentenceId = (int)dystopiaResult[i];
            // we add it only if it has not been found in the "start with"
            // search ....
            if (uniqueResults.find(sentenceId) == uniqueResults.end()) {
                if (i >= offset) {
                    results.push_back(sentenceId);
                }
            } else {
                // otherwise we increment the offset size (as the already match
                // found shoudn't be again in the search result
                // so we compensate that by starting one element after
                if (i < offset) {
                    offset++;
                }
            }
        }

        for (int i = 0; i < rnum; i++) {
            int sentenceId = (int)dystopiaResult[i];
            uniqueResults.insert(sentenceId);
        }
        free(dystopiaResult);
    } else {
        errorCode = tcidbecode(langIDB);
        std::cerr << "search error: "<< tcidberrmsg(errorCode) << std::endl;
    }
    close_index(langIDB);
    return results;
}
