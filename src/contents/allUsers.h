#ifndef CONTENTS_ALLUSERS_H
#define CONTENTS_ALLUSERS_H

#include "contents/content.h"
#include "models/Users.h"
#include <vector>

namespace contents {
    struct AllUsers : public BaseContent {
        std::vector<models::UserResult> listOfMembers;
    };
}

#endif // CONTENTS_ALLUSERS_H
