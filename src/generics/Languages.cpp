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
 * @package  Singletons
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */

#include "Languages.h"

/**
 *
 */
Languages::Languages() {}

/**
 *
 */
void Languages::init(
    cppcms::json::object langsJson
) {
    cppcms::json::object::const_iterator end = langsJson.end();

    // we iterate over the json array which is of the following form
    // "wuu" : ["Shanghainese", 61],
    // "eng" : ["English",      17],
    for (
        cppcms::json::object::const_iterator itr = langsJson.begin();
        itr != end;
        ++itr
    ) { 
        cppcms::json::array lang = itr->second.array();
        int langId = (int) lang[1].number();

        isoToName[itr->first] = lang[0].str(); 
        isoToId[itr->first] = langId; 
        nameToIso[lang[0].str()] = itr->first;
        idToISO[langId] = itr->first;

    }
}


/**
 *
 */
ISOToNameMap Languages::get_iso_to_name_map() {
    return isoToName;
}

/**
 *
 */
NameToISOMap Languages::get_name_to_iso_map() {
    return nameToIso;
}



/**
 *
 */
int Languages::get_id_from_iso(std::string isoCode) {
    // TODO handle if the isoCode is a wrong one
    return isoToId[isoCode];
}


/**
 *
 */
std::string Languages::get_iso_from_id(int id) {
    // TODO handle if the isoCode is a wrong one
    return idToISO[id];
}

/**
 *
 */
bool Languages::iso_exists(const std::string &isoCode) {
    return isoToId.find(isoCode) != isoToId.end();
}

