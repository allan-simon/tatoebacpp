#ifndef TATOEBACPP_CUSTOMDB_H
#define TATOEBACPP_CUSTOMDB_H


/**
 * This template class is a singleton class
 * to encapsculate pointer on customdb such as tatodb etc.
 *
 */

template <typename T>
class CustomDB {

    public
        static T &instance();

    private:
        CustomDB();
        T db;


}


#endif
