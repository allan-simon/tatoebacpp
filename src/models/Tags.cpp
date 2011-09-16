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


#include "models/Tags.h"

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

} // end of namespace models



