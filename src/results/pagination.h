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

#ifndef TATOEBACPP_RESULTS_PAGINATION_H
#define TATOEBACPP_RESULTS_PAGINATION_H

#include <vector>
namespace results { 


    /**
     * @brief Class a collection of result is supposed to inherit from
     *        to be used with pagination
     */
    class Paginable {
        public: 
            int currentPage;
            int pageNormalSize;
            int totalNbrElements;
     
            Paginable():
                currentPage(0),
                pageNormalSize(0),
                totalNbrElements(0)
            {};
    };


    /**
     * @brief A generic vector class that implements paginable
     */
    template <class T> class PagiVector :
        public std::vector<T>,
        public Paginable
    {

        public: 
            PagiVector<T>(): std::vector<T>(), Paginable(){};

            PagiVector<T>(int size) :
                std::vector<T>(size),
                Paginable()
            {};
    };

}

#endif
