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
 * @package  Helpers
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */

#ifndef CONTENTS_HELPER_PAGINATIONS_H
#define CONTENTS_HELPER_PAGINATIONS_H

#include <cmath>
#include "helpers.h"
#include "results/pagination.h"

namespace contents {
namespace helpers {

/**
 * @struct Paginations
 * @brief content struct to be used in pagination helper (helper that is used
 *        to display content on several pages)
 *        This content is used to generate correctly the pagination header
 *        (with "go to first page"  "previous page" etc.)        
 *
 */
struct Paginations : public Helpers {

    /**
     * @brief The current page we're displaying
     */
    int currentPage;
    /**
     * @brief The maximun number of element we're supposed to display per page
     */
    int pageNormalSize;
    /**
     * @brief The overall number of elements to display along all these pages
     */
    int totalNbrElements; 
    /**
     * @brief The number of the previous page (well simply a currentPage -1)
     */
    int prevPage;
    /**
     * @brief The number of the next page (well simply a currentPage + 1)
     */
    int nextPage;
    /**
     * @brief The last page number (if we have 99 result and a page size of 10
     *        lastPage will be equal to 9)
     */
    int lastPage;

    /**
     * @brief first page number to be displayed in the pagination header
     *        which is like this[first][prev] X X X current-page X X X [next][last]
     *        (but as when we're near the end of near the beginning) "currentPage"
     *        is not neceserally in the middle, we need to keep trace of the first
     *        number to display (as it's not alway currentPage - 3
     */
    int firstDisplayedPage;
    /**
     * @brief same than firstDisplayedPage but for the last displayed page
     *        number
     *
     */
    int lastDisplayedPage;


    bool atBeginning;
    bool atEnd;

    public:
        /**
         * Constructor
         */
        Paginations(
            const results::Paginable &paginatedResult,
            std::string _baseUrl,
            std::string _lang
            
        ) :
            currentPage(paginatedResult.currentPage),
            pageNormalSize(paginatedResult.pageNormalSize),
            totalNbrElements(paginatedResult.totalNbrElements)
        {
            baseUrl = _baseUrl;
            lang = _lang;

            // typically this will arrive when I forget to set the 
            // page size in the model ...
            if (pageNormalSize <= 0) {
                // TODO replace this by a log
                std::cerr << "[ERROR]A page can't have a zero or less size ..." << std::endl;
                return ;
            }

            lastPage = ceil((double)totalNbrElements/(double)pageNormalSize) - 1;
            atEnd = currentPage >= lastPage;
            atBeginning = currentPage <= 0;

            // 6 = max number of page "number" we display in the pagination header
            // 
            //               __________6___________
            //              |                      |
            // [first][prev]  X X X currentPage X X [next][loast] 
    
            int paginationSize = std::min(6, lastPage ); // TODO magic number

            int maxPrevPages = std::min(paginationSize, currentPage );
            int maxNextPages = std::min(paginationSize, lastPage - currentPage);

            int minPrevPages = std::min(
                (int)ceil((double)paginationSize/2.0),
                maxPrevPages
            );

            int minNextPages = std::min(
                (int)floor((double)paginationSize/2.0),
                maxNextPages
            );

            int dispPrevPages;
            int dispNextPages;
            if (minPrevPages  <= minNextPages) {
                dispPrevPages = minPrevPages;
                dispNextPages = paginationSize - minPrevPages;
            } else {
                dispNextPages = minNextPages;
                dispPrevPages = paginationSize - minNextPages;
            }

            firstDisplayedPage = currentPage - dispPrevPages;
            lastDisplayedPage  = currentPage + dispNextPages;

            nextPage = currentPage +1 ;
            prevPage = currentPage -1 ;

            /* DEBUG BLOCK
            std::cout << "[DEBUG] pagination: " << std::endl
                << "\tcurrentPage : " << currentPage << std::endl
                << "\tpageNormalSize : " << pageNormalSize << std::endl
                << "\ttotalNbrElements  : " << totalNbrElements  << std::endl
                << "\tprevPage : " << prevPage << std::endl
                << "\tnextPage : " << nextPage << std::endl
                << "\tlastPage : " << lastPage << std::endl

                << "\tfirstDisplayedPage : " << firstDisplayedPage << std::endl
                << "\tlastDisplayedPage : " << lastDisplayedPage << std::endl


                 << "\tatBeginning : " << atBeginning << std::endl
                 << "\tatEnd : " << atEnd << std::endl;
            */
        }

};

} // end of namespace helpers
} // end of namespace contents

#endif

