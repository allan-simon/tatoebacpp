#ifndef TATOEBACPP_MODELS_TATODB_H
#define TATOEBACPP_MODELS_TATODB_H

#include <iostream>
#include "generics/Singleton.h"

extern "C" {
#include "tato/db.h"
}


class TatoDB : public Singleton<TatoDB>{
    friend class Singleton<TatoDB>;

    private:
        TatoDb *tatoDb;
        TatoDB(std::string data_path);
        ~TatoDB();

    public:
        TatoDb *getDatabasePointer();
        

};


#endif
