#ifndef CONTENTS_HELPER_HELPERS_H
#define CONTENTS_HELPER_HELPERS_H

#include <cppcms/view.h>

namespace contents {
    namespace helpers {
        /**
         * @struct contents::helpers::Helper
         * Base struct for sending data from the controller to the view
         * for data meant to be used in some reusable modules
         */
        struct Helper : public cppcms::base_content {
            /**
             * @TODO write this doc
             */
            std::string baseUrl;
            /**
             * @TODO write this doc
             */
            std::string lang;
        };
    }
}

#endif



