/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/StateVariable.h>
#include <uhttp/util/Debug.h>
#include <mupnp/Service.h>
#include <mupnp/Service.h>
#include <mupnp/AllowedValue.h>
#include <mupnp/control/QueryListener.h>
#include <uhttp/util/StringUtil.h>

using namespace std;
using namespace uHTTP;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

const char *mUPnP::StateVariable::ELEM_NAME = "stateVariable";

const char *mUPnP::StateVariable::NAME = "name";
const char *mUPnP::StateVariable::DATATYPE = "dataType";
const char *mUPnP::StateVariable::SENDEVENTS = "sendEvents";
const char *mUPnP::StateVariable::SENDEVENTS_YES = "yes";
const char *mUPnP::StateVariable::SENDEVENTS_NO = "no";

////////////////////////////////////////////////
// StateVariable::StateVariable
////////////////////////////////////////////////

mUPnP::StateVariable::StateVariable() {
  this->serviceNode = NULL;
  this->stateVariableNode = &stateVarNode;

  initAllowedValueList();
  initAllowedValueRange();
}

mUPnP::StateVariable::StateVariable(uXML::Node *serviceNode, uXML::Node *stateVarNode) {
  this->serviceNode = serviceNode;
  this->stateVariableNode = stateVarNode;

  initAllowedValueList();
  initAllowedValueRange();
}

mUPnP::StateVariable::~StateVariable() {
}

////////////////////////////////////////////////
// AllowedallowedValueList
////////////////////////////////////////////////

void mUPnP::StateVariable::initAllowedValueList() {
  allowedValueList.clear();
  uXML::Node *allowedValueListNode = getStateVariableNode()->getNode(AllowedValueList::ELEM_NAME);
  if (allowedValueListNode == NULL)
    return;
  size_t nNode = allowedValueListNode->getNNodes();
  for (size_t n = 0; n < nNode; n++) {
    uXML::Node *node = allowedValueListNode->getNode(n);
    if (AllowedValue::isAllowedValueNode(node) == false)
      continue;
    AllowedValue *allowedVal = new AllowedValue(node);
    allowedValueList.add(allowedVal);
  }
}

////////////////////////////////////////////////
// AllowedValueRange
////////////////////////////////////////////////

void mUPnP::StateVariable::initAllowedValueRange() {
  uXML::Node *valueRangeNode = getStateVariableNode()->getNode(AllowedValueRange::ELEM_NAME);
  allowedValueRange.setAllowedValueRangeNode(valueRangeNode);
}

////////////////////////////////////////////////
// Value
////////////////////////////////////////////////

void mUPnP::StateVariable::setValue(const std::string &value) {
  // Thnaks for Tho Beisch (11/09/04)
  string currValue = getStateVariableData()->getValue();
  // Thnaks for Tho Rick Keiner (11/18/04)
  if (currValue.compare(value.c_str()) == 0)
      return;

  getStateVariableData()->setValue(value);

  // notify event
  Service *service = getService();
  if (service == NULL)
    return;
  if (isSendEvents() == false)
    return;
  service->notify(this);
}

void mUPnP::StateVariable::setValue(int value)  {
  string strValue;
  setValue(Integer2String(value, strValue));
}

void mUPnP::StateVariable::setValue(long value)  {
  string strValue;
  setValue(Long2String(value, strValue));
}

////////////////////////////////////////////////
// set
////////////////////////////////////////////////

void mUPnP::StateVariable::set(StateVariable *stateVar)  {
  setName(stateVar->getName());
  setValue(stateVar->getValue());
  setDataType(stateVar->getDataType());
  setSendEvents(stateVar->isSendEvents());
}

////////////////////////////////////////////////
// queryAction
////////////////////////////////////////////////

bool mUPnP::StateVariable::performQueryListener(QueryRequest *queryReq) {
  QueryListener *listener = getQueryListener();
  if (listener == NULL)
    return false;
  QueryResponse queryRes;
  StateVariable retVar;
  retVar.set(this);
  retVar.setValue("");
  retVar.setStatus(UPnP::INVALID_VAR);
  if (listener->queryControlReceived(&retVar) == true) {
    queryRes.setResponse(&retVar);
  }
  else {
    UPnPStatus *upnpStatus = retVar.getStatus();
    queryRes.setFaultResponse(upnpStatus->getCode(), upnpStatus->getDescription());
  }
  HTTPRequest *httpReq = queryReq;
  httpReq->post(&queryRes);
  return true;
}

////////////////////////////////////////////////
// ActionControl
////////////////////////////////////////////////

bool mUPnP::StateVariable::postQuerylAction() {
  QueryRequest queryReq;
  queryReq.setRequest(this);
  if (Debug::isOn() == true)
    queryReq.print();
  QueryResponse *querylRes = new QueryResponse();
  queryReq.post(querylRes);
  if (Debug::isOn() == true)
    querylRes->print();
  setQueryResponse(querylRes);
  // Thanks for Dimas <cyberrate@users.sourceforge.net> and Stefano Lenzi <kismet-sl@users.sourceforge.net> (07/09/04)
  int statCode = querylRes->getStatusCode();
  setStatus(statCode);
  if (querylRes->isSuccessful() == false) {
    setValue(querylRes->getReturnValue());
    return false;
  }
  setValue(querylRes->getReturnValue());
  return true;
}
