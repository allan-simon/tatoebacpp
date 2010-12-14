#ifndef CONTENTS_HOMEPAGE_H
#define CONTENTS_HOMEPAGE_H

#include "contents/content.h"
#include "contents/helpers/sentences.h"

namespace contents {

struct Homepage : public BaseContent {
    SentencesHelper shc;
    std::string text;
};

}

#endif
