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
    cppcms::json::array langsJson
) {
    cppcms::json::array::const_iterator end = langsJson.end();

    // we iterate over the json array which is of the following form
    // "wuu" : ["Shanghainese", 61],
    // "eng" : ["English",      17],
    for (
        cppcms::json::array::const_iterator itr = langsJson.begin();
        itr != end;
        ++itr
    ) { 
        cppcms::json::array lang = itr->array();
        int langId = (int) lang[2].number();
        
        const std::string isoCode = lang[0].str();
        const std::string naturalName = lang[1].str();


        isoToName[isoCode] = naturalName;
        isoToId[isoCode] = langId; 
        nameToIso[naturalName] = isoCode;
        idToISO[langId] = isoCode;

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
std::string Languages::get_name_from_iso(std::string isoCode) {
    //TODO i18n this
    return isoToName[isoCode];
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


/**
 *
 */
void Languages::fill_form_select(cppcms::widgets::select &select) {
    ISOToNameMap::iterator itr;
    for(itr = nameToIso.begin(); itr != nameToIso.end(); ++itr){
        //TODO l10n the language name
        select.add(itr->first, itr->second);
    }

}

/**
 *
 */
void Languages::fill_form_select(
    cppcms::widgets::select &select,
    const std::vector<std::string> &userLangs
) {

    std::vector<std::string>::const_iterator itr;
    for(itr = userLangs.begin(); itr != userLangs.end(); ++itr){
        select.add(
            get_name_from_iso(*itr),
            *itr
        );
    }

}


