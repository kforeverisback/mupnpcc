/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/event/NotifyRequest.h>

#include <time.h>
#include <stdlib.h>
#include <string>

using namespace std;
using namespace mUPnP;
using namespace mUPnP;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

const char *NotifyRequest::XMLNS = "e";
const char *NotifyRequest::PROPERTY = "property";
const char *NotifyRequest::PROPERTYSET = "propertyset";

////////////////////////////////////////////////
// PropetySet
////////////////////////////////////////////////

bool NotifyRequest::setRequest(Subscriber *sub, const std::string &varName, const std::string &value) {
  //const char *callback = sub->getDeliveryURL();
  const char *sid = sub->getSID();
  long notifyCnt = sub->getNotifyCount();
  const char *host = sub->getDeliveryHost();
  const char *path = sub->getDeliveryPath();
  int port = sub->getDeliveryPort();

  setMethod(uHTTP::HTTP::NOTIFY);
  setURI(path);
  setHost(host, port);
  setNT(NT::EVENT);
  setNTS(NTS::PROPCHANGE);
  setSID(sid);
  setSEQ(notifyCnt);

  setContentType(uXML::XML::CONTENT_TYPE);
  uXML::Node *propSetNode = createPropertySetNode(varName, value);

  setContent(propSetNode);
  return true;
}


uXML::Node *NotifyRequest::createPropertySetNode(const std::string &varName, const std::string &value) {
  string propSetXmlNs;
  //propSetXmlNs.append(XMLNS)
  //propSetXmlNs.append(SOAP::DELIM)
  propSetXmlNs.append(PROPERTYSET);
  uXML::Node *propSetNode = new uXML::Node(propSetXmlNs.c_str());
  propSetNode->setNameSpace(XMLNS, Subscription::XMLNS);

  string propXmlNs;
  //propXmlNs.append(XMLNS)
  //propXmlNs.append(SOAP::DELIM)
  propXmlNs.append(PROPERTY);
  uXML::Node *propNode = new uXML::Node(propXmlNs.c_str());
  propSetNode->addNode(propNode);

  uXML::Node *varNameNode = new uXML::Node(varName);
  varNameNode->setValue(value);
  propNode->addNode(varNameNode);

  return propSetNode;
}

uXML::Node *NotifyRequest::getVariableNode() {
  uXML::Node *rootNode = getEnvelopeNode();
  if (rootNode == NULL)
    return NULL;
  if (rootNode->hasNodes() == false)
    return NULL;
  uXML::Node *propNode = rootNode->getNode(0);
  if (propNode->hasNodes() == false)
    return NULL;
  return propNode->getNode(0);
}

////////////////////////////////////////////////
// PropetySet
////////////////////////////////////////////////

// Thanks for Giordano Sassaroli <sassarol@cefriel.it> (09/08/03)
Property *NotifyRequest::getProperty(uXML::Node *varNode) {
  Property *prop = new Property();
  if (varNode == NULL) {
    prop->setName("");
    prop->setValue("");
    return prop;
  }
  // remove the event namespace
  std::string variableName = varNode->getName();
  size_t index = variableName.rfind(':');
  if (index != (int)std::string::npos)
    variableName = variableName.substr(index + 1);
  prop->setName(variableName.c_str());
  prop->setValue(varNode->getValue());
  return prop;
}

// Thanks for Giordano Sassaroli <sassarol@cefriel.it> (09/08/03)
PropertyList *NotifyRequest::getPropertyList()  {
  propList.clear();
  uXML::Node *propSetNode = getEnvelopeNode();
  for (int i = 0; i<propSetNode->getNNodes(); i++){
    uXML::Node *propNode = propSetNode->getNode(i);
    if (propNode == NULL)
      continue;
    Property *prop = getProperty(propNode->getNode(0));
    propList.add(prop);
  }
  return &propList;
}
  
