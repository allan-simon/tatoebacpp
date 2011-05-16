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

namespace results {

/**
 * @struct Searches
 * Used to store the ids of the sentence that match a search query
 */
struct Searches : public std::vector<int> {
    /**
     * offset, mainly used in pagination, if we want to skip the offset th
     * results
     */
    int offset;
    /**
     * used with pagination, we will retrieve at most maxsize elements
     */
    int maxsize;
    public:
        /**
         * Constructor
         */
        Searches(): offset(0), maxsize(0) {};
        /**
         * Constructor with a preallocated size
         */
        Searches(int size) :
            std::vector<int>(size),
            offset(0),
            maxsize(0)
            {};
};

} // end of namespace
