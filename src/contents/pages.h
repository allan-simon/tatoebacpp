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


#ifndef TATOEBACPP_CONTENTS_PAGES_H
#define TATOEBACPP_CONTENTS_PAGES_H

#include "contents/content.h"
#include "results/sentences_stats.h"
#include "contents/helpers/sentences.h"

namespace contents {

/**
 * Base content for every action of Pages controller
 *
 */
struct Pages : public BaseContent {
};

/**
 * @struct PagesHomepage
 * Content used by the homepage
 */
struct PagesHomepage : public Pages {
    helpers::Sentences shc;
    results::SentencesStats sentencesStats;
    /**
     * @brief store the total number of sentences in tatoeba
     *
     * @since 26 August 2011
     */
    unsigned int totalNbrSentences;
};

/**
 * @struct PagesContribute
 * Content used by page Contribute
 */
struct PagesContribute : public Pages {
};

/**
 * @struct PagesTermsOfUse
 * Content used by page Terms of use
 */
struct PagesTermsOfUse : public Pages {
};

/**
 * Content used by page Team and credits
 */
struct PagesTeamAndCredits : public Pages {

};

} //end of namespace

#endif
