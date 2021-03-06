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

#ifndef _ZG_LINKED_LIST_H_
#define _ZG_LINKED_LIST_H_

#include <stdlib.h>

struct LinkedListNode {
  void *data;
  LinkedListNode *previous;
  LinkedListNode *next;
};

class ZGLinkedList {
  public:
    ZGLinkedList();
    ~ZGLinkedList();

    /** Adds a new node to the list. Returns a pointer to the data pointer of the new node.*/
    void **add();

    /** Removes the given element from the list. */
    void remove(void *element);

    void *remove(int index);

    virtual bool isDataEqualTo(void *dataA, void *dataB) { return (dataA == dataB); }

    /** Returns the number of elements in the list. */
    int size();

    /** Returns the data at the given index. <code>NULL</code> if out-of-bounds. */
    void *get(int index);

  protected:
    LinkedListNode *getEmptyNode();

    /** Inserts node A after node B. */
    void insertAfter(LinkedListNode *nodeA, LinkedListNode *nodeB);

    /** Inserts node A before node B. */
    void insertBefore(LinkedListNode *nodeA, LinkedListNode *nodeB);

    void *remove(LinkedListNode *node);

    virtual void *newDataHolder() { return NULL; }

    virtual void deleteDataHolder(void *data) { /* nothing to do */ }

    LinkedListNode *head;
    LinkedListNode *tail;
    int numElements;

    LinkedListNode *emptyHead;
    LinkedListNode *emptyTail;
    int numEmptyElements;
};

#endif // _ZG_LINKED_LIST_H_
