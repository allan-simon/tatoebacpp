#ifndef CONTENTS_BASE_CONTENT_H
#define CONTENTS_BASE_CONTENT_H

#include <cppcms/view.h>
#include "login_form.h"


namespace contents {

struct ConfigContent {
    std::string css_path;
    std::string img_path;
};

struct BaseContent : public cppcms::base_content {
    struct ConfigContent config;
    std::string lang;
    bool isAuthenticated;
    login_form login;
};

}

#endif
