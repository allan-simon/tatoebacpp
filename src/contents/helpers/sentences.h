#ifndef CONTENTS_HELPER_SENTENCES_H
#define CONTENTS_HELPER_SENTENCES_H

#include <cppcms/view.h>
extern "C" {
    #include "tato/fetcher_tree.h"
}


namespace contents {

struct SentencesHelper : public cppcms::base_content {
    TatoFetcherTree *tree;
};

}

#endif
