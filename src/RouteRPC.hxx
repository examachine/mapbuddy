//
//
// C++ Interface for module: RouteRPC
//
// Description: 
//
//
// Author: exa
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef RouteRPC_Interface
#define RouteRPC_Interface

#include "General.hxx"
#include "XmlRpc.h"
using namespace XmlRpc;

// Arguments are as follows:
// param 0, a point struct x,y for source location
// param 1, a point struct x,y for destination location
class RouteRPC : public XmlRpcServerMethod
{
public:
  RouteRPC(XmlRpcServer* s) : XmlRpcServerMethod("mapbuddy.route", s) {}

  void execute(XmlRpcValue& params, XmlRpcValue& result);
  std::string help();

};



#endif
