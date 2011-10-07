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

#include <cstdlib>
#include <iostream>


#include <sstream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <exception>
#include <cstring>
#include "models/Sentences.h"
#include "models/OfUser.h"
#include "models/Tags.h"
#include "models/SphinxClient.h"
namespace models {

/**
 * 
 */
SentDupliException::SentDupliException(int originalId):
    originalId(originalId)
{

}

/**
 * 
 */
const char* SentDupliException::what() const throw() {
    return "The sentence already exists";
}

/**
 * 
 */
int SentDupliException::get_original_id() const throw() {
    return originalId;
}

/**
 *
 */
SentDupliException::~SentDupliException() throw() {}


/**
 *
 */
Sentences::Sentences():
    sphinxClient("127.0.0.1", 9312)
{

}

/**
 *
 */
results::Sentence Sentences::get_by_id(
    int id,
    int depth,
    const std::vector<std::string> &langsToKeep
) {
    TatoDb *tatoDb = GET_DB_POINTER();
    TatoItem *item = tato_db_item_find(tatoDb, id);

    if (item != NULL) { 
        return sentence_from_item(item, depth, langsToKeep);
    } else {
        return results::Sentence();
    }
}

/**
 *
 */
results::Sentence Sentences::simple_get_by_id(
    int id
) {
    TatoDb *tatoDb = GET_DB_POINTER();
    TatoItem *item = tato_db_item_find(tatoDb, id);

    if (item != NULL) { 
        return simple_sentence_from_item(item);
    } else {
        return results::Sentence();
    }
}


/**
 *
 */
int Sentences::get_random_id(
    const std::vector<std::string> &langsToKeep 
) {
    int id = 0;
    TatoDb *tatoDb = GET_DB_POINTER();
    TatoItem * item = NULL;
    if (langsToKeep.empty()) {
        item = tato_db_item_rand(tatoDb);
    } else {
        item = tato_db_item_rand_with_lang(
            tatoDb,
            langsToKeep[std::rand()%langsToKeep.size()].c_str()
        );
    } 

    if (item != NULL) {
        id = item->id;
    }

    return id;
}

/**
 *
 */
int Sentences::get_random_id(std::string isoCode) {

    int id = 0;

    TatoDb *tatoDb = GET_DB_POINTER();
    TatoItem *randSentence = tato_db_item_rand_with_lang(
        tatoDb,
        isoCode.c_str()
    );
    if (randSentence != NULL) {
        id = randSentence->id;
    }
    return id;
}


/**
 *
 */
results::Sentence Sentences::get_random(
    const int depthLimit,
    const std::vector<std::string> &langsToKeep 
) {
    TatoDb *tatoDb = GET_DB_POINTER();
    TatoItem *randItem = NULL;

    if (langsToKeep.empty()) {
        randItem = tato_db_item_rand(tatoDb);
    } else {
        randItem = tato_db_item_rand_with_lang(
            tatoDb,
            langsToKeep[std::rand()%langsToKeep.size()].c_str()
        );
    }
    if (randItem == NULL) {
        return results::Sentence();
    }
    
    return sentence_from_item(randItem, depthLimit, langsToKeep);

}
/**
 *
 */
bool Sentences::get_lang(
    const int id,
    std::string &sentenceLang
) {
    TatoDb *tatoDb = GET_DB_POINTER();
    TatoItem *item = tato_db_item_find(tatoDb, id);
    
    if (item != NULL) {
        sentenceLang = std::string(item->lang->code);
        return true;
    }
    return false;
}


/**
 *
 */
results::Sentence Sentences::get_random(
    const std::string &isoCode,
    const int depthLimit,
    const std::vector<std::string> &langsToKeep 
) {

    TatoDb *tatoDb = GET_DB_POINTER();
    TatoItem *randItem = tato_db_item_rand_with_lang(
        tatoDb,
        isoCode.c_str()
    );

    if (randItem == NULL) {
        return results::Sentence();
    }

    return sentence_from_item(randItem, depthLimit, langsToKeep);

}

/**
 *
 */
results::Sentence Sentences::add(
    const  std::string &lang,
    const  std::string &str,
    const  int userId
) throw(SentDupliException) {
    return add(lang, str, 0, userId);
}

results::Sentence Sentences::add(
    const std::string &lang,
    const std::string &str,
    const TatoItemFlags flags,
    const int userId
) throw(SentDupliException) {
    TatoDb *tatoDb = GET_DB_POINTER(); 
                                              
    TatoItem *item = tato_item_new(
        tato_tree_int_max(tatoDb->items) + 1,
        tato_db_lang_find_or_create(tatoDb, lang.c_str()),
        str.c_str(),
        flags
    );
    //TODO find a cleaner solution, we should not touch at the internal
    // indexes of tatodb here
    int originalId = tato_item_lang_item_can_add(item->lang, item->str);
    if (originalId >= 0) {
        tato_item_free(item);
        throw SentDupliException(originalId);         
    } 

    if (!tato_tree_int_insert_unique(
        tatoDb->items,
        item->id,
        (void *) item)
    ) {
        return results::Sentence();
    }

    tato_item_lang_item_add(item->lang, item);


 
    if (item != NULL) {
        
        OfUser().adopt_sentence(
            item->id,
            userId
        );
        /*
        logs.insert_add_word(
            newItem->id,
            lang,
            str,
            userId
        );
        */

        sphinxClient.add_sentence(
            item->id,
            str,
            lang
        );
    }
    return results::Sentence(
        item->id,
        item->str,
        item->lang->code,
        item->flags
    );
}

/**
 *
 */
void Sentences::link(
    int xId,
    int yId,
    int userId
) {

    TatoDb *tatoDb = GET_DB_POINTER(); 
    TatoRelation* relation = tato_db_relation_add(
        tatoDb,
        xId,
        yId,
        0,
        0
    );
    // TODO thrown an exception in that case
    if (relation == NULL) {
        return;
    }
    // TODO add it to the logs
}

/**
 *
 */
void Sentences::unlink(
    int xId,
    int yId,
    int userId
) {

    TatoDb *tatoDb = GET_DB_POINTER(); 
    TatoItem *item = tato_db_item_find(tatoDb, xId);
        
    TatoRelationsNode *it;
    TATO_RELATIONS_FOREACH(item->relations, it) {
        if (it->with->id == (unsigned int)yId) {
            bool deleted = tato_db_relation_delete(
                tatoDb,
                it->relation->id
            );
            if (deleted) {
                // TODO add it to the logs
            }
            return; 
        }
    }
}


/**
 *
 */
void Sentences::edit_text(
    int id,
    std::string newString,
    int userId
) throw(SentDupliException) {

    TatoDb *tatoDb = GET_DB_POINTER(); 
    TatoItem *item = tato_db_item_find(tatoDb, id);

    if (item == NULL) {
        return;
    }
    std::string oldString(item->str);

    int origId = tato_item_lang_item_can_add(
        item->lang,
        newString.c_str()
    ); 
	
    // if the new text was already present then we merge the sentence
    // with the already existing one
    if (origId >= 0 && origId != id) {
 
        merge(
            id,
            origId
        );
        throw SentDupliException(origId);         
    } 

	tato_item_lang_item_remove(item->lang, item);
	free(item->str);

	item->str = strdup(newString.c_str());
	tato_item_lang_item_add(item->lang, item);

    //TODO readd log and search engine update
    sphinxClient.edit_text(
        item->id,
        oldString,
        newString,
        std::string(item->lang->code)
    );


    return;

}



/**
 *
 */
void Sentences::merge(
    const int toMergeId,
    const int toKeepId
) {

    TatoDb *tatoDb = GET_DB_POINTER(); 
    TatoItem *toKeepItem = tato_db_item_find(tatoDb, toKeepId);
    tato_db_item_merge_into(
        tatoDb,
        toMergeId,
        toKeepItem
    );

    Tags tagModel;
    tagModel.merge(
        toMergeId,
        toKeepId
    );

    OfUser ofUser;
    ofUser.merge(
        toMergeId,
        toKeepId
    );
}

/**
 *
 */
void Sentences::edit_lang(
    int id,
    std::string newLang,
    int userId
) throw(SentDupliException) {

    TatoDb *tatoDb = GET_DB_POINTER(); 
    TatoItem *item = tato_db_item_find(tatoDb, id);

    if (item == NULL) {
        return;
    }
    std::string prevLang(item->lang->code);

    TatoItemLang* newTatoLang = tato_db_lang_find_or_create(
        tatoDb,
        newLang.c_str()
    );

    int origId = tato_item_lang_item_can_add(
        newTatoLang,
        item->str
    ); 
	
    // if the new text was already present then we merge the sentence
    // with the already existing one
    if (origId >= 0 && origId != id) {
        merge(
            id,
            origId
        );
        throw SentDupliException(origId);      
    } 

	tato_item_lang_item_remove(item->lang, item);
    item->lang = newTatoLang;

	tato_item_lang_item_add(newTatoLang, item);

    //TODO readd log update
    sphinxClient.edit_lang(
        item->id,
        std::string(item->str),
        prevLang,
        newLang
    );

    return;

}


/**
 *
 */
results::Sentence Sentences::simple_sentence_from_item(
    TatoItem* item
) {
    results::Sentence sentence(
        item->id,
        item->str,
        item->lang->code,
        item->flags
    );
    
    return sentence; 
}




/**
 *
 */
results::Sentence Sentences::sentence_from_item(
    TatoItem* item,
    const int depth,
    const std::vector<std::string> &langsToKeep 

) {
    results::Sentence sentence(
        item->id,
        item->str,
        item->lang->code,
        item->flags
    );
    if (!sentence.exists()) {
        return sentence;
    }
    
    sentence.set_owner_name(
        OfUser().get_owner_name_of_sentence(item->id)
    );


    //TODO reintroduce metas
    //models::Metas metasModel;
    //sentence.metas = metasModel.get_all_metas_of_sentence(item); 
    pack_translations(
        item,
        sentence.translations,
        depth,
        langsToKeep
    );
   
    return sentence; 
}

/**
 *
 */
void Sentences::pack_translations(
    TatoItem *item,
    TransVector &translations,
    const int maxDepth,
    const std::vector<std::string> &langsToKeep 
) {

    std::set<int> visiteds;
    std::queue<TatoItem*> itemsQueue;
    visiteds.insert(item->id);
    itemsQueue.push(item);

    TatoItem *pivot = NULL;
    int currentDepth = 0;
    TatoItem *lastItemForThisDistance = item;

    translations.push_back(SentencesVector());

    //
    // without language filtering
    // 
    if (langsToKeep.empty()) {
        while (!itemsQueue.empty() && currentDepth < maxDepth) {
            pivot = itemsQueue.front();
            itemsQueue.pop();
            
            TatoRelationsNode *it;
            TatoItem *tempChild = NULL;
            TATO_RELATIONS_FOREACH(pivot->relations, it) {

                tempChild = it->with;
                // if we haven't visited this sentence before
                if (visiteds.insert(tempChild->id).second) {
                    
                    itemsQueue.push(tempChild);
                    translations[currentDepth].push_back(
                        results::Sentence(
                            tempChild->id,
                            tempChild->str,
                            tempChild->lang->code,
                            tempChild->flags
                        )
                    );
                }

            }
            // if we have iterated over all the child of nodes of depth N-1
            // it means we have finished depth N and that the next node will be of
            // depth N + 1
            if (pivot == lastItemForThisDistance) {
                currentDepth++;
                translations.push_back(SentencesVector());
                lastItemForThisDistance = itemsQueue.back();

            }
        }
    //
    // with language filtering
    //
    } else { 
        while (!itemsQueue.empty() && currentDepth < maxDepth) {
            pivot = itemsQueue.front();
            itemsQueue.pop();
            
            TatoRelationsNode *it;
            TatoItem *tempChild = NULL;
            TATO_RELATIONS_FOREACH(pivot->relations, it) {

                tempChild = it->with;
                // if we haven't visited this sentence before
                if (visiteds.insert(tempChild->id).second) {
                    
                    itemsQueue.push(tempChild);
                    //TODO this if test is the only difference with the version
                    // without filtering, so it's highly possible to factorize it
                    if (
                        std::find(
                            langsToKeep.begin(),
                            langsToKeep.end(),
                            std::string(tempChild->lang->code)
                        ) != langsToKeep.end()    
                    ) {
                        translations[currentDepth].push_back(
                            results::Sentence(
                                tempChild->id,
                                tempChild->str,
                                tempChild->lang->code,
                                tempChild->flags
                            )
                        );
                    }
                }

            }
            // if we have iterated over all the child of nodes of depth N-1
            // it means we have finished depth N and that the next node will be of
            // depth N + 1
            if (pivot == lastItemForThisDistance) {
                currentDepth++;
                translations.push_back(SentencesVector());
                lastItemForThisDistance = itemsQueue.back();

            }
        }
    }



    //TODO workaround; need to find why we have one or two last extra
    // empty vectors in the results vectors
    for(int i = 0; i <currentDepth; i++) {
        if (translations.back().empty()) {
            translations.pop_back();
        }
    }

}

} //end of namespace
