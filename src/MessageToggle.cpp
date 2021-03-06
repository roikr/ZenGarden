/*
 *  Copyright 2009,2010 Reality Jockey, Ltd.
 *                 info@rjdj.me
 *                 http://rjdj.me/
 * 
 *  This file is part of ZenGarden.
 *
 *  ZenGarden is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  ZenGarden is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *  
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with ZenGarden.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "MessageToggle.h"

MessageToggle::MessageToggle(PdMessage *initString, PdGraph *graph) : MessageObject(1, 1, graph) {
  isOn = false;
}

MessageToggle::~MessageToggle() {
  // nothing to do
}

const char *MessageToggle::getObjectLabel() {
  return "toggle";
}

void MessageToggle::processMessage(int inletIndex, PdMessage *message) {
  MessageElement *messageElement = message->getElement(0);
  switch (messageElement->getType()) {
    case FLOAT: {
      isOn = (messageElement->getFloat() != 0.0f);
      PdMessage *outgoingMessage = getNextOutgoingMessage(0);
      outgoingMessage->setTimestamp(message->getTimestamp());
      outgoingMessage->getElement(0)->setFloat(isOn ? 1.0f : 0.0f);
      sendMessage(0, outgoingMessage);
      break;
    }
    case BANG: {
      isOn = !isOn;
      PdMessage *outgoingMessage = getNextOutgoingMessage(0);
      outgoingMessage->setTimestamp(message->getTimestamp());
      outgoingMessage->getElement(0)->setFloat(isOn ? 1.0f : 0.0f);
      sendMessage(0, outgoingMessage);
      break;
    }
    case SYMBOL: {
      if (strcmp(messageElement->getSymbol(), "set") == 0) {
        if (message->isFloat(1)) {
          isOn = (message->getFloat(1) != 0.0f);
        }
      }
    }
    default: {
      break;
    }
  }
}
