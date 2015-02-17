#include "Set.h"
#include <iostream>
using namespace std;

/*
===============================================================================
FUNCTION: CONSTRUCTOR (DEFAULT)
===============================================================================
*/
Set::Set() : m_size(0), m_head(nullptr), m_tail(nullptr) {}

/*
===============================================================================
FUNCTION: CONSTRUCTOR (COPY)
===============================================================================
*/
Set::Set(const Set& rhs) :
   m_head(nullptr), m_tail(nullptr), m_size(0) {
   init(rhs);
}

/*
===============================================================================
FUNCTION: DESTRUCTOR
===============================================================================
*/
Set::~Set() {
   Node* next = nullptr;
   while (m_head != nullptr) {
      next = m_head->next;
      delete m_head;
      m_head = next;
      m_size--;
   }
}

/*
===============================================================================
FUNCTION: EMPTY
===============================================================================
*/
bool Set::empty() const { return m_size == 0; }

/*
===============================================================================
FUNCTION: SIZE
===============================================================================
*/
int Set::size() const { return m_size; }

/*
===============================================================================
FUNCTION: INSERT
===============================================================================
*/
bool Set::insert(const ItemType& value) {
   if (contains(value))
      return false;

   Node* newNode = new Node();
   newNode->item = value;

   if (m_size == 0) {
      newNode->next = newNode->prev = nullptr;
      m_head = m_tail = newNode;
   } else {
      newNode->prev = nullptr;
      newNode->next = m_head;
      m_head->prev = newNode;
      m_head = newNode;
   }
   m_size++;
   return true;
}

/*
===============================================================================
FUNCTION: ERASE
===============================================================================
*/
bool Set::erase(const ItemType& value) 
{
   Node* target = find(value);
   if (target == nullptr) 
   {
      return false;
   } 
   else 
   {
      if (m_size == 1)
      {
         m_head = m_tail = nullptr;
      }
      else if ((target == m_head) && (target != m_tail))
      {
         m_head->next->prev = nullptr;
         m_head = m_head->next;
      }
      else if ((target != m_head) && (target == m_tail))
      {
         m_tail->prev->next = nullptr;
         m_tail = m_tail->prev;
      }
      else// if ((target != m_head) && (target != m_tail)) 
      {
         target->prev->next = target->next;
         target->next->prev = target->prev;
      }
   }
   delete target;
   m_size--;
   return true;
}

/*
===============================================================================
FUNCTION: CONTAINS
===============================================================================
*/
bool Set::contains(const ItemType& value) const {
   return (find(value) != nullptr);
}

/*
===============================================================================
FUNCTION: GET
===============================================================================
*/
bool Set::get(int i, ItemType& value) const {
   if ((m_size == 0 ) || (i < 0) || (i >= m_size))
      return false;

   Node* curr = m_head;
   while (i > 0) {
      curr = curr->next;
      i--;
   }

   value = curr->item;
   return true;
}

/*
===============================================================================
FUNCTION: SWAP
===============================================================================
*/
void Set::swap(Set& other) {
   int tempInt = m_size;
   m_size = other.m_size;
   other.m_size = tempInt;

   Node* tempNode = m_head;
   m_head = other.m_head;
   other.m_head = tempNode;

   tempNode = m_tail;
   m_tail = other.m_tail;
   other.m_tail = tempNode;
}

/*
===============================================================================
FUNCTION: DUMP
===============================================================================
*/
void Set::dump() const {
   cout << "SET_SIZE = " << m_size << endl;
   cout << "HEAD" << endl;
   Node* curr = m_head;
   while (curr != nullptr)
   {
      cout << " |" << endl << " " << curr->item << endl;
      curr = curr->next;
   }
   cout << " | " << endl << "TAIL" << endl;
}

/*
===============================================================================
FUNCTION: OPERATOR=
===============================================================================
*/
Set& Set::operator=(const Set& rhs) {
   // check for assignment to self
   if (this == &rhs)
      return *this;

   clear();
   init(rhs);
}

/*
===============================================================================
FUNCTION: FIND
===============================================================================
*/
Set::Node* Set::find(const ItemType& value) const {
   Node* curr = m_head;
   while ((curr != nullptr) && (curr->item != value))
      curr = curr->next;
   return curr;
}

/*
===============================================================================
FUNCTION:   INIT
===============================================================================
*/
void  Set::init(const Set& rhs) {
   m_size = rhs.m_size;

   if (m_size != 0) {
      m_head = new Node;
      m_head->item = rhs.m_head->item;
      m_head->prev = nullptr;
      
      Node* rhsIter = rhs.m_head;   // iterates through rhs linked list
      Node* newIter = m_head;       // iterates through new linked list

      while (rhsIter != nullptr) {
         if (rhsIter->next == nullptr) {
            break;
         }
         rhsIter = rhsIter->next;
         Node* newNode = new Node;
         newNode->item = rhsIter->item;
         newNode->prev = newIter;
         newIter->next = newNode;
         newIter = newIter->next;
      }
      newIter->next = nullptr;
      m_tail = newIter;
   }
}

/*
===============================================================================
FUNCTION: CLEAR
===============================================================================
*/
void  Set::clear() {
   if (m_size != 0) {
      while (m_head != nullptr) {
         Node* iter = m_head->next;
         delete m_head;
         m_head = iter;
      }
      m_tail = nullptr;
   }
}

/*
===============================================================================
FUNCTION: UNITE
===============================================================================
*/
void unite(const Set& s1, const Set& s2, Set& result) {
   ItemType temp;
   Set blank;

   for (int i = 0; i < s1.size(); i++) {
      s1.get(i, temp);
      blank.insert(temp);
   }

   for (int i = 0; i < s2.size(); i++) {
      s2.get(i, temp);
      blank.insert(temp);
   }

   blank.swap(result);
}

/*
===============================================================================
FUNCTION: SUBTRACT
===============================================================================
*/
void subtract(const Set& s1, const Set& s2, Set& result) {
   ItemType temp;
   Set blank;

   for (int i = 0; i < s1.size(); i++) {
      s1.get(i, temp);
      blank.insert(temp);
   }

   for (int i = 0; i < s2.size(); i++) {
      s2.get(i, temp);
      blank.erase(temp);
   }

   blank.swap(result);
}