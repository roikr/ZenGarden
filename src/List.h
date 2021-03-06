/*
 *  Copyright 2009 Reality Jockey, Ltd.
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

#ifndef _LIST_H_
#define _LIST_H_

/**
 * Implements an ArrayList.
 */
class List {
  
  public:
    List();
  
    /** The contents of the list are not destroyed. */
    virtual ~List();
  
    /** The number of elements currently in the list. */
    inline int size() { return numElements; }
  
    /** Add the element onto the end of the list */
    List *add(void *element);
  
    /**
     * Adds another List to the end of this List, in place.
     * The original List (i.e., this) is returned.
     */
    List *add(List *list);
  
    void *toArray();
  
    /** Returns the indexed element in the list. */
    inline void *get(int index) { return arrayList[index]; }
  
    void *remove(int index);
  
    void *replace(int index, void *newElement);
  
    /** Returns <code>true</code> if the given element exists in the list. <code>false</code> otherwise. */
    bool exists(void *element);

    /**
     * Resets the number of elements to zero.
     */
    void clear();
  
    /**
     * The list is returned to the same state as if it had just been created.
     */
    void revertToNewState();
  
  private:
    void growArrayList();
  
    const static int DEFAULT_LENGTH = 1;
    int maxLength;
    void **arrayList;
    int numElements;
};

#endif // _LIST_H_
