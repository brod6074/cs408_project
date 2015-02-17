#ifndef  SET_H
#define  SET_H

typedef unsigned long ItemType;

/*
===============================================================================
CLASS:   Set
PURPOSE: The Set class provides basic set functionality such as adding/removing
         values from a set.
===============================================================================
*/
class Set
{
friend void initializeSets(Set in[], Set out[], Set def[], Set use[], Set successor[]);

public:
         Set();
         Set(const Set& rhs);
         ~Set();
   bool  empty()  const;
   int   size()   const;
   bool  insert(const ItemType& value);
   bool  erase(const ItemType& value);
   bool  contains(const ItemType& value)  const;
   bool  get(int pos, ItemType& value)    const;
   void  swap(Set& other);
   void  dump() const;
   Set&  operator=(const Set& rhs);

private:
   struct Node {
      ItemType    item;
      Node*       next;
      Node*       prev;
   };

   int   m_size;
   Node* m_head;
   Node* m_tail;

   void  init(const Set& rhs);
   void  clear();
   Node* find(const ItemType& value) const;
};

void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);

#endif