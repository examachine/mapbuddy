//
//
// C++ Implementation file for application
//
// Description: map buddy server that runs on port 10000
//
// exa
//
//

#include "General.hxx"

#include "XmlRpc.h"
#include "InfoRPC.hxx"
#include "MapRPC.hxx"
#include "RouteRPC.hxx"
#include "PointRPCs.hxx"
#include "Store.hxx"

#include <iostream>
#include <stdlib.h>

using namespace XmlRpc;

// The server
XmlRpcServer s;

InfoRPC info_rpc(&s);
MapRPC map_rpc(&s);
RouteRPC route_rpc(&s);
GetPointRPC getPoint_rpc(&s);
InsertPointRPC insertPoint_rpc(&s);
DeletePointRPC deletePoint_rpc(&s);
NearestPointRPC nearestPoint_rpc(&s);

int main(int argc, char *argv[])
{
  if (argc != 2) {
    std::cerr << "Usage: mapbuddy-server serverport\n";
    return -1;
  }
  int port = atoi(argv[1]);

  std::cout << "mapbuddy server" << std::endl;
  std::cout << "authors: Eray Ozkural, Kartal Tabak" << std::endl;
  std::cout << "Copyright (C) 2003" << std::endl;

  // read database
  store.init();

  XmlRpc::setVerbosity(5);

  // Create the server socket on the specified port
  s.bindAndListen(port);
  
  // Enable introspection
  s.enableIntrospection(true);

  // Wait for requests indefinitely
  s.work(-1.0);

  return 0; // success
}
