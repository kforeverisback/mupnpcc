/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/Service.h>
#include <mupnp/Argument.h>
#include <uhttp/util/StringUtil.h>

using namespace std;
using namespace mUPnP;
using namespace uHTTP;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

const char *Argument::ELEM_NAME = "argument";

const char *Argument::IN_DIR = "in";
const char *Argument::OUT_DIR = "out";
const char *Argument::NAME = "name";
const char *Argument::DIRECTION = "direction";
const char *Argument::RELATED_STATE_VARIABLE = "relatedStateVariable";

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

Argument::Argument() {
  argumentNode = &defaultArgumentNode;
  serviceNode = &defaultServiceNode;
}
  
Argument::Argument(uXML::Node *servNode, uXML::Node *argNode) {
  argumentNode = argNode;
  serviceNode = servNode;
}

Argument::Argument(const std::string &name, const std::string &value) {
  argumentNode = &defaultArgumentNode;
  serviceNode = &defaultServiceNode;
  setName(name);
  setValue(value);
}

Argument::~Argument() {
}

////////////////////////////////////////////////
// setValue
////////////////////////////////////////////////

void Argument::setValue(int value) {
  string valueStr;
  Integer2String(value, valueStr);
  setValue(valueStr.c_str());
}

////////////////////////////////////////////////
// getService
////////////////////////////////////////////////

Service *Argument::getService() {
  uXML::Node *node = getServiceNode();
  ServiceData *data = dynamic_cast<ServiceData *>(node->getUserData());
  if (data == NULL)
    return NULL;
  return data->getService();
}

////////////////////////////////////////////////
// relatedStateVariable
////////////////////////////////////////////////

StateVariable *Argument::getRelatedStateVariable() {
  Service *service = getService();
  if (service == NULL)
    return NULL;
  const char *relatedStatVarName = getRelatedStateVariableName();
  return service->getStateVariable(relatedStatVarName);
}

