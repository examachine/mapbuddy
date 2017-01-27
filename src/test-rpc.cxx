//
//
// C++ Implementation for module: test-rpc
//
// Description: A program for testing mapbuddy rpcs
//
//
// Author: exa
//
// Copyright: See COPYING file that comes with this distribution
//
//


#include "XmlRpc.h"
#include <iostream>
using namespace XmlRpc;

int main(int argc, char* argv[])
{
  if (argc != 3) {
    std::cerr << "Usage: test-rpc serverHost serverPort\n";
    return -1;
  }
  int port = atoi(argv[2]);
  //XmlRpc::setVerbosity(5);

  // Use introspection API to look up the supported methods
  XmlRpcClient c(argv[1], port);
  XmlRpcValue noArgs, result;
  if (c.execute("system.listMethods", noArgs, result))
    std::cout << "\nMethods:\n " << result << "\n\n";
  else
    std::cout << "Error calling 'listMethods'\n\n";

  // Use introspection API to get the help string for the Hello method
  XmlRpcValue oneArg;
  oneArg[0] = "mapbuddy.info";
  if (c.execute("system.methodHelp", oneArg, result))
    std::cout << "Help for 'Info' method: " << result << "\n\n";
  else
    std::cout << "Error calling 'methodHelp'\n\n";

  // Call the info method
  if (c.execute("mapbuddy.info", noArgs, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error calling 'mapbuddy.info'\n\n";

  // Call the map method
  {
    XmlRpcValue args;
    args[0] = "kartal";
    args[1][0]["x"] = double(-10);
    args[1][0]["y"] = double(-10);
    args[1][1]["x"] = double(2);
    args[1][1]["y"] = double(11);
    args[2] = 3;
    std::cout << "calling mapbuddy.map with " << args << std::endl;
    if (c.execute("mapbuddy.map", args, result))
      std::cout << "result: " << result << "\n\n";
    else
      std::cout << "Error calling 'mapbuddy.map'\n\n"; 
  }

  // Call the route method
  {
    XmlRpcValue args;
//    args[0] = "kartal";
    args[0]["x"] = double(-10);
    args[0]["y"] = double(-10);
    args[1]["x"] = double(2);
    args[1]["y"] = double(11);
    std::cout << "calling mapbuddy.route with " << args << std::endl;
    if (c.execute("mapbuddy.route", args, result))
      std::cout << "result: " << result << "\n\n";
    else
      std::cout << "Error calling 'mapbuddy.route'\n\n"; 
  }

  // Call the nearestPoint method
  {
    XmlRpcValue args;
    args[0]["x"] = double(-10.4);
    args[0]["y"] = double(-9.5);
    std::cout << "calling mapbuddy.nearestPoint with " << args << std::endl;
    if (c.execute("mapbuddy.nearestPoint", args, result))
      std::cout << "result: " << result << "\n\n";
    else
      std::cout << "Error calling 'mapbuddy.nearestPoint'\n\n"; 
  }

  // Call the insertPoint method
  {
    XmlRpcValue args;
    args[0]["name"] = "test";
    args[0]["type"] = "P";
    args[0]["x"] = double(3.5);
    args[0]["y"] = double(6.2);
    args[0]["description"] = "test point";
    std::cout << "calling mapbuddy.insertPoint with " << args << std::endl;
    if (c.execute("mapbuddy.insertPoint", args, result)) {
      std::cout << "result: " << result << "\n\n";
      // now try to get info for it
      XmlRpcValue args;
      args[0] = true;
      args[1] = result[0];
      std::cout << "calling mapbuddy.getPoint with " << args << std::endl;
      if (c.execute("mapbuddy.getPoint", args, result)) {
	std::cout << "result: " << result << "\n\n";
	
      }
    }
    else
      std::cout << "Error calling 'mapbuddy.nearestPoint'\n\n"; 
  }
}
