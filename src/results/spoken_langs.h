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

#ifndef TATOEBACPP_RESULTS_SPOKEN_LANGS_H
#define TATOEBACPP_RESULTS_SPOKEN_LANGS_H

#include <string>
#include <vector>

namespace results {
    
    /**
     * @struct Represent a lang spoken by a user
     */
    struct SpokenLang {
        /**
         * @brief ISO code of that language
         *        We don't need the human readable name, as it's better
         *        to localized it only in the view
         */
        std::string langISO;
        /**
         * @brief Level of the user in that language (for the moment the lower)
         *        The better
         */
        int proeficiency;
        /**
         * @brief If the user is a native of that language
         *        Note: this field is needed because even native are more
         *        or less good in their own language, and some non-native
         *        may have a better letter than some natives.
         */
        bool isNative;
    };
    /**
     * @brief Vector of spoken lang, can represent the set of languages a user
     *        speaks
     */
    typedef std::vector<SpokenLang> SpokenLangsVector;
} // end namespace results

#endif
