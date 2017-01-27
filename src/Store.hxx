//
//
// C++ Interface for module: Store
//
// Description: Persistent storage manager
//
//
// Author: exa
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef Store_Interface
#define Store_Interface

#include "General.hxx"
#include "Map.hxx"

class Store {
public:
  Store() {}
  
  void init();
  Map global_map;
  Map user_map;
};

extern Store store;

#endif
