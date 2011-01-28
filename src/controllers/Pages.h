#ifndef CONTROLLERS_PAGES_H
#define CONTROLLERS_PAGES_H

#include "Controller.h"

namespace controllers {

/**
 * @class Pages
 * contains all functions to generate all independant pages
 */
class Pages : public Controller {
    public:
        /**
         * Constructor
         */
        Pages(apps::Tatoeba& tatoapp);
        /**
         * generate home page
         */
        void homepage();
        /**
         * Main page to add sentences and so
         */
        void contribute();
        /**
         * Terms of use page
         */
        void termsOfUse();
        /**
         * Team and Credits page
         */
        void teamAndCredits();
};

} // End namespace

#endif
