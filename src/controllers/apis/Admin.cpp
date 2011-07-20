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
 * @package  Controllers
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */

#include "Controller.h"
#include "controllers/apis/Admin.h"

#include "models/TatoDB.h"

namespace controllers {
namespace apis {

Admin::Admin(cppcms::service &serv) :
    controllers::apis::Controller(serv)
{
    cppcms::url_dispatcher* disp = &dispatcher();

  	disp->assign("/sphinx-dump/(.+)", &Admin::sphinx_dump, this, 1);

}


/**
 *
 */
void Admin::sphinx_dump(std::string path) {
    TatoDB::get_instance("")->sphinx_dump("sphinxdump.xml");
}




} // end of namespace apis
} // end of namespace controllers


