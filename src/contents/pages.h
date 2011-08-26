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
#include "contents/forms/generics/filter_lang.h"

namespace contents {
namespace pages {

/**
 * Base content for every action of Pages controller
 *
 */
struct Pages : public BaseContent {
};

/**
 * @struct Homepage
 * Content used by the homepage
 */
struct Homepage : public Pages {
    helpers::Sentences shc;
    results::SentencesStats sentencesStats;
    /**
     * @brief store the total number of sentences in tatoeba
     *
     * @since 26 August 2011
     */
    unsigned int totalNbrSentences;
    
    /**
     * @brief Form to be able to display an other random sentence in
     *        a specific language
     *
     * @since 26 August 2011
     */
    forms::generics::FilterLang anotherRandomInLang;

    Homepage() {
        //TODO i18n
        anotherRandomInLang.submit.value("Show another");
    }

};

/**
 * @struct Contribute
 * Content used by page Contribute
 */
struct Contribute : public Pages {
};

/**
 * @struct TermsOfUse
 * Content used by page Terms of use
 */
struct TermsOfUse : public Pages {
};

/**
 * Content used by page Team and credits
 */
struct TeamAndCredits : public Pages {

};

} // end of namespace pages
} //end of namespace contents

#endif
