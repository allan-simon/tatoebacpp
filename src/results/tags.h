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
 * @package  Results
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */

#ifndef TATOEBACPP_RESULTS_TAGS_H
#define TATOEBACPP_RESULTS_TAGS_H


#ifndef BIGGER_FIRST_DEF
#define BIGGER_FIRST_DEF
struct BiggerFirstComp {
    bool operator()(int x,int y) {
        return x > y;
    }
};
#endif

#include <map>
namespace results {

    /**
     * @brief Structure to represent a tag
     *
     * @since 16 September 2011
     */
    struct Tag {
        std::string name;
        std::string standardName;
        std::string description;
    };

    /**
     * @brief Structure to represent a list of tags, ordered by number of
     *  sentences
     *
     * @since 16 September 2011
     */
    typedef std::multimap<int, Tag, BiggerFirstComp> TagsList;

} // end namespace results
#endif

