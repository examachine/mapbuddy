//
//
// C++ Implementation for module: Store
//
// Description: Persistent storage manager
//
//
// Author: exa
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "Store.hxx"

Store store;

void Store::init()
{
  global_map.read_database();
}

