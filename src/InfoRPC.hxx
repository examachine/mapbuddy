//
//
// C++ Interface for module: InfoRPC
//
// Description: 
//
//
// Author: exa
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef InfoRPC_Interface
#define InfoRPC_Interface

#include "General.hxx"
#include "XmlRpc.h"
using namespace XmlRpc;

// No arguments, result is server information
class InfoRPC : public XmlRpcServerMethod
{
public:
  InfoRPC(XmlRpcServer* s) : XmlRpcServerMethod("mapbuddy.info", s) {}

  void execute(XmlRpcValue& params, XmlRpcValue& result)
  {
    std::string info = "MapBuddy Server\n";

    std::ifstream infofile("data/info.txt");
    char buf[128];
    while (!infofile.eof()) {
      infofile.getline(buf, 127);
      info += buf + '\n';
    }
    result = info;
  }

  std::string help() { return std::string("Map server information"); }

};




#endif
