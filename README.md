#Tatoeba (cpp version)

In order to compile you need


  * libtatodb  (you can find it as an other repository of this github)
  * cppcms-skeleton (same)
  * cppcms
  * cppdb  (both are dependency of cppcms-skeleton)
  * libsphinxclient (for the search engine)

  * cmake
  * a compiler recent enough to support basic c++11

after that you simply need to

     mkdir build ;  cd build ;  cmake .. ;  make

and to run it (from the build directory

     ./tatoeba -c ../config.js


and then you can open at this address `127.0.0.1:4242` (port etc.
can be changed from the config.js)
