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


#include <booster/posix_time.h>
#include "models/Tags.h"
#include "generics/Languages.h"
#include "models/Sentences.h"

#define PAGE_SIZE 10

namespace models {
/**
 *
 */
Tags::Tags():
    SqliteModel()
{

}

/**
 *
 */
Tags::~Tags() {}



/**
 *
 */
results::TagsList Tags::get_all() {

    results::TagsList tagsList;

    cppdb::statement getAllTags = sqliteDb.prepare(
        "SELECT internal_name, name, nbrOfSentences"
        "   FROM tags"
        "   ORDER BY nbrOfSentences;"
    );

    cppdb::result res = getAllTags.query();

    while (res.next()) {
        results::Tag tempTag;
        tempTag.name = res.get<std::string>("name");
        tempTag.standardName = res.get<std::string>("internal_name");

        tagsList.insert(
            std::pair<int, results::Tag>(
                res.get<int>("nbrOfSentences"),
                tempTag
            )
        );
    }
    getAllTags.reset();

    return tagsList;
}


/**
 *
 */
int Tags::get_id(std::string realName) {

    cppdb::statement getId = sqliteDb.prepare(
        "SELECT id"
        "   FROM tags"
        "   WHERE name = ?"
        "   LIMIT 1;"
    );

    getId.bind(realName);

    cppdb::result res = getId.row();
    int id = 0;
    if (!res.empty()) {
        id = res.get<int>("id");
    }
    getId.reset();
    return id;
}

/**
 *
 */
results::Tag Tags::get(std::string standardName) {

    //TODO exception if tag does not exist
    results::Tag tag;

    cppdb::statement getTag = sqliteDb.prepare(
        "SELECT internal_name, name, description"
        "   FROM tags"
        "   WHERE internal_name = ? "
        "   LIMIT 1;"
    );
    getTag.bind(standardName);

    cppdb::result res = getTag.row();

    tag.standardName = res.get<std::string>("internal_name");
    tag.name = res.get<std::string>("name");
    tag.description = res.get<std::string>("description");

    getTag.reset();

    return tag;

}


/**
 *
 */
// TODO maybe factorize this
results::PagiSentences Tags::sentences_with_tag(
    const std::string &tagName,
    const int page
) {

    cppdb::statement getSentencesWithTagCount = sqliteDb.prepare(
        "SELECT count(*) AS total "
        "    FROM tags_sentences INNER JOIN tags ON id = tag_id "
        "    WHERE internal_name = ? "
    );
    getSentencesWithTagCount.bind(tagName);


    int maxsize = getSentencesWithTagCount.row().get<int>("total");
    results::PagiSentences pagiSentences;

    pagiSentences.currentPage = page;
    pagiSentences.totalNbrElements = maxsize;
    pagiSentences.pageNormalSize = PAGE_SIZE;

    cppdb::statement getSentencesWithTag = sqliteDb.prepare(
        "SELECT sentence_id "
        "    FROM tags_sentences INNER JOIN tags ON id = tag_id "
        "    WHERE internal_name = ? "
        "    LIMIT ? OFFSET ? "
    );


    getSentencesWithTag.bind(tagName);
    getSentencesWithTag.bind(PAGE_SIZE);
    getSentencesWithTag.bind(PAGE_SIZE * page);

    cppdb::result res = getSentencesWithTag.query();
    models::Sentences sentencesModel;

    while (res.next()) {

        pagiSentences.push_back(
            sentencesModel.get_by_id(
                res.get<int>("sentence_id"),
                3 //TODO magic number for depth of translation
                //langsToKeep
            )
        );
    }
    getSentencesWithTag.reset();

    return pagiSentences;
}

/**
 *
 */ 
bool Tags::tag_sentence(
    int sentenceId,
    int tagId,
    int userId
) {

    models::Sentences sentencesModel;
    std::string sentenceLang;
    if (!sentencesModel.get_lang(sentenceId,sentenceLang)) {
        return false;
    }

    cppdb::statement tagSentence = sqliteDb.prepare(
        "INSERT INTO tags_sentences("
        "   tag_id, sentence_id, user_id, lang_id, added_time"
        ") VALUES("
        "   ?,?,?,?,?"
        ")"
    );

    tagSentence.bind(tagId);
    tagSentence.bind(sentenceId);
    tagSentence.bind(userId);

    tagSentence.bind(
        Languages::get_instance()->get_id_from_iso(sentenceLang)
    );

    tagSentence.bind(
        booster::ptime::now().get_seconds()
    );

          
    try {
        tagSentence.exec();    
    } catch (cppdb::cppdb_error const &e) {
        //TODO log it
        tagSentence.reset();
        return false;
    }


    cppdb::statement incrementTagCount = sqliteDb.prepare(
        "UPDATE tags "
        "   SET nbrOfSentences = nbrOfSentences + 1 "
        "   WHERE id = ?;"
    );
    incrementTagCount.bind(tagId);
    incrementTagCount.exec();


    incrementTagCount.reset();
    tagSentence.reset();

    return true;
}

} // end of namespace models



