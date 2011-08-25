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

#include "OfUser.h"
#include "generics/Languages.h"
#include "models/Sentences.h"

#define PAGE_SIZE 10

namespace models {

/**
 *
 */
OfUser::OfUser(cppdb::session sqliteDb):
    SqliteModel(sqliteDb)
{

}

/**
 *
 */
OfUser::OfUser(): SqliteModel() {}

/**
 *
 */
OfUser::~OfUser() {
}


/**
 *
 */
/*
bool OfUser::adopt(
    const int sentenceId,
    const int userId,
    const std::string &isoCode
) {

    

}
*/

/**
 *
 */
bool OfUser::adopt_sentence(
    const int sentenceId,
    const int userId
) {
    std::string sentenceLang;
    if (!Sentences::get_lang(sentenceId,sentenceLang)) {
        return false;
    }


    cppdb::statement adopt = sqliteDb.prepare(
        "INSERT INTO sentence_users(sentence_id, user_id, lang_id) "
        "VALUES(?,?,?)"
    );
    adopt.bind(sentenceId);
    adopt.bind(userId);
    adopt.bind(
        Languages::get_instance()->get_id_from_iso(sentenceLang)
    );

    try {

        adopt.exec();        

    } catch (cppdb::cppdb_error const &e) {
        //TODO log it
        std::cerr << e.what() << std::endl;
        adopt.reset();
        return false;
    }

    int affected = adopt.affected();
    adopt.reset();
    return affected == 1;

}


/**
 *
 */
bool OfUser::abandon_sentence(
    const int sentenceId
) {
    cppdb::statement abandonSent = sqliteDb.prepare(
        "DELETE FROM sentence_users "
        "   WHERE sentence_id = ?"
    );

    abandonSent.bind(sentenceId);
    try {
        abandonSent.exec();
    } catch (cppdb::cppdb_error const &e) {
        //TODO add something better to handle erros
        std::cout << e.what() << std::endl;
        return false;
    }
    return true;
}

/**
 *
 */
std::string OfUser::get_owner_name_of_sentence(
    const int sentenceId
) {
    std::string ownerName("");

    cppdb::statement getOwnerName = sqliteDb.prepare(
        "SELECT username FROM users "
        "    INNER JOIN sentence_users ON id = user_id "
        "    WHERE sentence_id = ? "
        "    LIMIT 1;"
    );
    getOwnerName.bind(sentenceId);

    cppdb::result res = getOwnerName.row();
    if (!res.empty()) {
        ownerName = res.get<std::string>("username");
    }

    getOwnerName.reset();

    return ownerName;
}


/**
 *
 */
bool OfUser::is_sentence_owner(
    const int sentenceId,
    const int userId
) {

    cppdb::statement isSentOwnedBy = sqliteDb.prepare(
        "SELECT 1 FROM sentence_users "
        "    WHERE sentence_id = ? AND user_id = ? "
        "    LIMIT 1;"
    );
    isSentOwnedBy.bind(sentenceId);
    isSentOwnedBy.bind(userId);

    cppdb::result res = isSentOwnedBy.row();

    bool isOwned = !res.empty();
        
    isSentOwnedBy.reset();

    return isOwned;
}

/**
 *
 */
results::PagiSentences OfUser::sentences_of(
    const std::string &username,
    const int page,
    const bool simpleSentenceOnly
) {

    cppdb::statement getSentencesOfUserCount = sqliteDb.prepare(
        "SELECT count(*) AS total "
        "    FROM sentence_users INNER JOIN users ON id = user_id "
        "    WHERE username = ? "
    );
    getSentencesOfUserCount.bind(username);


    int maxsize = getSentencesOfUserCount.row().get<int>("total");
    results::PagiSentences pagiSentences;

    pagiSentences.currentPage = page;
    pagiSentences.totalNbrElements = maxsize;
    pagiSentences.pageNormalSize = PAGE_SIZE;

    cppdb::statement getSentencesOfUser = sqliteDb.prepare(
        "SELECT sentence_id "
        "    FROM sentence_users INNER JOIN users ON id = user_id "
        "    WHERE username = ? "
        "    LIMIT ? OFFSET ? "
    );


    getSentencesOfUser.bind(username);
    getSentencesOfUser.bind(PAGE_SIZE);
    getSentencesOfUser.bind(PAGE_SIZE * page);

    cppdb::result res = getSentencesOfUser.query();
    models::Sentences sentencesModel;
    
    int i = 0;

    if (simpleSentenceOnly) {
        while (res.next()) {

            pagiSentences.push_back(
                sentencesModel.simple_get_by_id(
                    res.get<int>("sentence_id")
                )
            );
            i++;
        }
    } else {
        while (res.next()) {

            pagiSentences.push_back(
                sentencesModel.get_by_id(
                    res.get<int>("sentence_id"),
                    3 //TODO magic number for depth of translation
                    //langsToKeep
                )
            );
            i++;
        }
    }
    getSentencesOfUser.reset();

    return pagiSentences;
}


/**
 *
 */
results::PagiSentences OfUser::sentences_of_in(
    const std::string &username,
    const int langId,
    const int page,
    const bool simpleSentenceOnly
) {

    cppdb::statement getSentencesOfUserCount = sqliteDb.prepare(
        "SELECT count(*) AS total "
        "    FROM sentence_users INNER JOIN users ON id = user_id "
        "    WHERE username = ? AND lang_id = ?"
    );
    getSentencesOfUserCount.bind(username);
    getSentencesOfUserCount.bind(langId);


    int maxsize = getSentencesOfUserCount.row().get<int>("total");
    results::PagiSentences pagiSentences;

    pagiSentences.currentPage = page;
    pagiSentences.totalNbrElements = maxsize;
    pagiSentences.pageNormalSize = PAGE_SIZE;

    cppdb::statement getSentencesOfUser = sqliteDb.prepare(
        "SELECT sentence_id "
        "    FROM sentence_users INNER JOIN users ON id = user_id "
        "    WHERE username = ? and lang_id = ? "
        "    LIMIT ? OFFSET ? "
    );


    getSentencesOfUser.bind(username);
    getSentencesOfUser.bind(langId);
    getSentencesOfUser.bind(PAGE_SIZE);
    getSentencesOfUser.bind(PAGE_SIZE * page);

    cppdb::result res = getSentencesOfUser.query();
    models::Sentences sentencesModel;
    
    int i = 0;

    if (simpleSentenceOnly) {
        while (res.next()) {

            pagiSentences.push_back(
                sentencesModel.simple_get_by_id(
                    res.get<int>("sentence_id")
                )
            );
            i++;
        }
    } else {
        while (res.next()) {

            pagiSentences.push_back(
                sentencesModel.get_by_id(
                    res.get<int>("sentence_id"),
                    3 //TODO magic number for depth of translation
                    //langsToKeep
                )
            );
            i++;
        }
    }
    getSentencesOfUser.reset();

    return pagiSentences;
}



}// end namespace models
