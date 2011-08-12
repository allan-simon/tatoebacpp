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



#ifndef SHDICT_GENERICS_LANGUAGES_H
#define SHDICT_GENERICS_LANGUAGES_H

#include <map>
#include "Singleton.h"
#include <cppcms/json.h>
#include <cppcms/form.h>

//TODO maybe replace all these maps by something smarter
typedef std::map<std::string, std::string> ISOToNameMap;
typedef std::map<std::string, std::string> NameToISOMap;
typedef std::map<int, std::string> IdToISOMap;
typedef std::map<std::string, int> ISOToIdMap;


//TODO try to view how it deals with i18n (especially for language name sorting)
/**
 * Singleton class used to store the information about the
 * languages supported in Tatoeba, and their related info
 * ISO code, name, id in the database 
 */
class Languages : public Singleton<Languages> {
    friend class Singleton<Languages>;

    private:
        /**
         * Map associating ISO code to the English name
         **/
        ISOToNameMap isoToName;

        /**
         * Map associating  English name of a language to its ISO code
         **/
        NameToISOMap nameToIso;



        /**
         * Map associating internal ID in the database to ISO code
         */
        IdToISOMap idToISO;

        /**
         * Map associating the ISO code to internal ID
         */
        ISOToIdMap isoToId;
        Languages();

    public:
        /**
         * return the map ISO code => English name
         */
        ISOToNameMap get_iso_to_name_map();

         /**
         * return the map English name => ISO code
         */
        ISOToNameMap get_name_to_iso_map();
        


        /**
         * Initialize the singleton with the data stored in config.js 
         */
        void init(cppcms::json::array langsJson);

        /**
         * Return the internal id associated to the ISO code of a given language
         */
        int get_id_from_iso(std::string isoCode);

        /**
         * Return the ISO code associated to the internal ID of a given language
         */
        std::string get_iso_from_id(int id);

        /**
         * Test if an ISO code exists/is supported or not
         */
        bool iso_exists(const std::string &isoCode);

        /**
         * @brief Fill a html form's select and fill it with all the supported
         *        languages
         *
         * @param select The cppcms select to fill
         */
        void fill_form_select(cppcms::widgets::select &select);

        /**
         * @brief Fill a html form's select and fill it with all the supported
         *        languages the user can speak
         *
         * @param select The cppcms select to fill
         * @param userLangs the languages this user can speak
         */

        void fill_form_select(
            cppcms::widgets::select &select,
            const std::vector<std::string> &userLangs
        );


        /**
        * @brief Return the localized name of the language with the given iso
        *        code
        *
        * @param isoCode ISO code of the language of which we want the name
        *
        * @todo i18n it
        *
        * @return The localized name of the language
        */
        std::string get_name_from_iso(std::string isoCode);
};

#endif
