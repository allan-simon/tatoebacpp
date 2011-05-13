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



#include <sstream>
#include <queue>
#include <set>
#include <exception>
#include <cstring>
#include "models/Sentences.h"
namespace models {

/**
 * 
 */
SentDupliException::SentDupliException(int originalId)
    : originalId(originalId) {};

/**
 * 
 */
const char* SentDupliException::what() const throw() {
    return "The sentnece already exists";
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
SentDupliException::~SentDupliException() throw() {};


/**
 *
 */
Sentences::Sentences() {
}

/**
 *
 */
results::Sentence Sentences::get_by_id(int id) {
    TatoDb *tatoDb = GET_DB_POINTER();
    TatoItem *item = tato_db_item_find(tatoDb, id);

    if (item != NULL) { 
        return sentence_from_item(item);
    } else {
        return results::Sentence();
    }
}
/**
 *
 */
int Sentences::get_random_id() {
    int id = 0;
    TatoDb *tatoDb = GET_DB_POINTER();
    TatoItem *randSentence = tato_db_item_rand(tatoDb);

    std::stringstream ss;
    ss << randSentence->id;
    ss >> id;

    return id;
}

/**
 *
 */
results::Sentence Sentences::get_random() {

    TatoDb *tatoDb = GET_DB_POINTER();
    TatoItem *randItem = tato_db_item_rand(tatoDb);

    return sentence_from_item(randItem);

}

/**
 *
 */
results::Sentence Sentences::add(
    std::string lang,
    std::string str,
    int userId
) throw(SentDupliException) {
    return add(lang, str, 0, userId);
}

results::Sentence Sentences::add(
    std::string lang,
    std::string str,
    TatoItemFlags flags,
    int userId
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
        /*
        logs.insert_add_word(
            newItem->id,
            lang,
            str,
            userId
        );

        SearchEngine::get_instance()->add_word(
            newItem->id,
            str,
            lang
        );
        */
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

    int origId = tato_item_lang_item_can_add(
        item->lang,
        newString.c_str()
    ); 
	
    // if the new text was already present then we merge the sentence
    // with the already existing one
    if (origId >= 0) {
        TatoItem *origItem = tato_db_item_find(tatoDb, origId);
        tato_db_item_merge_into(
            tatoDb,
            id,
            origItem
        );
        throw SentDupliException(origItem->id);         
    } 

	tato_item_lang_item_remove(item->lang, item);
	free(item->str);

	item->str = strdup(newString.c_str());
	tato_item_lang_item_add(item->lang, item);

    //TODO readd log and search engine update
    return;

}

/**
 *
 */
results::Sentence Sentences::sentence_from_item(TatoItem* item) {
    results::Sentence sentence(
        item->id,
        item->str,
        item->lang->code,
        item->flags
    );

    if (!sentence.exists()) {
        return sentence;
    }
    //TODO reintroduce metas
    //models::Metas metasModel;
    //sentence.metas = metasModel.get_all_metas_of_sentence(item); 
    pack_translations(item, sentence.translations, 20);
   
    return sentence; 
}

/**
 *
 */
void Sentences::pack_translations(
    TatoItem *item,
    TransVector &translations,
    int maxDepth
) {

    std::set<int> visiteds;
    std::queue<TatoItem*> itemsQueue;
    visiteds.insert(item->id);
    itemsQueue.push(item);

    TatoItem *pivot = NULL;
    int currentDepth = 0;
    TatoItem *lastItemForThisDistance = item;

    translations.push_back(SentencesVector());
    

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
        // if we have iterated over all the cild of nodes of depth N-1
        // it means we have finished depth N and that the next node will be of
        // depth N + 1
        if (pivot == lastItemForThisDistance) {
            currentDepth++;
            translations.push_back(SentencesVector());
            lastItemForThisDistance = tempChild;

        }
    }

}

} //end of namespace
