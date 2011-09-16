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
 * @package  Models
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */ 

#ifndef MODELS_TAGS_H
#define MODELS_TAGS_H

#include "models/SqliteModel.h"
#include "results/tags.h"

namespace models {


/**
 * @brief Model class used to do all the database requests
 *  related to tags
 *
 * @since 9 September 2011
 */
class Tags : public SqliteModel {
    private:
    public:
        /**
         * @brief Constructor
         *
         * @since 9 September 2011
         */
        Tags(cppdb::session sqliteDb);

        Tags();

        /**
         * @brief Destructor
         *
         * @since 9 September 2011
         */
        ~Tags();

        /*
        void add_requested(
            std::string name,
            std::string description,
            int userId            
        );
        */

        /**
         * @brief Retrieve all the tags supported by tatoeba
         *
         * @return The complete list of tags
         *
         * @since 9 September 2011
         */
        results::TagsList get_all();
};


} // end of namespace models
#endif
