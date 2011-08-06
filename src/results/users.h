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

#ifndef TATOEBACPP_RESULTS_USERS_H
#define TATOEBACPP_RESULTS_USERS_H

#include "results/pagination.h"
#include "results/spoken_langs.h"

namespace results {
    struct User {
        int id;
        std::string username;
        std::string email;
        //std::string lang;
        long long since;
        //int last_time_active;
        //bool send_notifications;
        std::string name;
        //int birthday;
        std::string description;
        std::string homepage;
        //std::string image;
        //std::string country_id;
        //bool is_public;
        SpokenLangsVector spokenLangs;
    };

typedef PagiVector<User> PagiUsers;

}

#endif


