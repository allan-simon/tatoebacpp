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
 * @package  Contents
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */
#ifndef CONTENTS_SEARCHES_H
#define CONTENTS_SEARCHES_H

#include "contents/content.h"
#include "contents/forms/search.h"
#include "contents/helpers/sentences.h"

namespace contents {

/**
 * @struct SearchesSimple
 * TODO write doc
 */
struct SearchesSimple : public BaseContent {
    helpers::Sentences shc;
    std::string queryStr;
    std::string queryLang;
};

/**
 * @struct SearchesShowResult
 * content use to diplsay the results of request on the search engine
 */
struct SearchesShowResult : public SearchesSimple {
    int paginationSize;
};



};

#endif

