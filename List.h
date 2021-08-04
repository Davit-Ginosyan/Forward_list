#include <iostream>
#include <initializer_list>
using namespace std;

template <typename T>
class f_list //forward_list
{
public:
  f_list();                                //ctor
  f_list(initializer_list<T> il);          //initializer_list
  ~f_list();                               //dtor
  f_list(const f_list<T> &other);          //copy
  f_list(f_list<T> &&other);               //copy move
  f_list &operator=(const f_list<T> &lst); //operator=
  f_list &operator=(f_list<T> &&lst);      //move oper.=
  T operator[](int index);                 
  void push_front(T data);
  void pop_front();
  void remove(T key);
  void insert_after(int pos, T value);
  
  void print()
  {
    node* tmp = head;
    while(tmp)
    {
      cout << tmp->data <<endl;
      tmp = tmp->next;
    }
  }


  class node
  {
  public:
    node *next;
    T data;

    node(T data = T(), node *next = nullptr)
    {
      this->data = data;
      this->next = next;
    }
  };
 
private:
  node *head;
  int m_size;
};

template <typename T>
f_list<T>::f_list(): m_size{}, head{nullptr}{ }

template <typename T>
f_list<T>::f_list(initializer_list<T> il): m_size(), head(nullptr) 
{
  node *current = new node();
  node *ctor = current;
  typename initializer_list<T>::iterator it;
  for (it = il.begin(); it < il.end()-1; ++it)
  {
    current->data = *it;
    current->next = new node();
    current = current->next;
    
  }
  current->data = *it;
  current->next = nullptr;
  head = ctor;
  ++m_size = il.size();
}

template <typename T>
f_list<T>::~f_list()
{
  while (m_size)
  {
    f_list<T>::pop_front();
  }
}

template <typename T>
f_list<T>::f_list(const f_list<T> &other) : head(nullptr)
{
  this->m_size = other.m_size;

  node *current;
  node *count = new node();
  this->head = count;
  current = other.head;
  count->data = current->data;

  for (int i = 1; i < other.m_size; ++i)
  {
    current = current->next;
    node *rez = new node();
    count->next = rez;
    rez->data = current->data;
    count = count->next;
  }
  
}

template <typename T>
f_list<T>::f_list(f_list<T> &&other)
{
  this->m_size = other.m_size;
  this->head = other.head;
  other.m_size = 0;
  other.head = nullptr;
}

template <typename T>
f_list<T> &f_list<T>::operator=(const f_list<T> &other)
{

  if (this == &other)
  {
    return *this;
  }
  else
  {
    while (this->m_size > 0)
    {
      this->pop_front();
    }

    this->m_size = other.m_size;
    node *current = new node();
    node *count = new node();
    this->head = count;
    current = other.head;
    count->data = current->data;

    for (int i = 1; i < other.m_size; ++i)
    {
      current = current->next;
      node *rez = new node();
      count->next = rez;
      rez->data = current->data;
      count = count->next;
    }
    return *this;
  }
}

template <typename T>
f_list<T> &f_list<T>::operator=(f_list &&other)
{
  *this.~f_list();
  this->m_size = other.m_size;
  this->head = other.head;
  other.head = nullptr;
  return *this;
}

template <typename T>
T f_list<T>::operator[](int index)
{
  int count = 0;
  node *current = head;
  while (current != nullptr)
  {

    if (count == index)
    {
      return current->data;
    }
    current = current->next;
    ++count;
  }
  return T();
}

template <typename T>
void f_list<T>::push_front(T data)
{
  if (head == nullptr)
  {
    head = new node(data);
  }
  else
  {
    node *current = head;
    head = new node(data);
    head->next = current;
  }
  ++m_size;
}

template <typename T>
void f_list<T>::pop_front()
{
  node *current = head;
  head = head->next;
  delete current;
  --m_size;
}

template <typename T>
void f_list<T>::remove(T key)
{
  for (int i = 1; i < m_size; ++i)
  {
    if (head->data == key)
    {
      pop_front();
    }
  }
  node *current = head;
  node *tmp;
  tmp = current;
  current = current->next;

  while (tmp->next != nullptr)
  {
    if (tmp->data == key)
    {
      delete tmp;
      tmp = new node();
    }
    if (current->data == key)
    {
      if (current->next != nullptr)
      {
        tmp->next = current->next;
        delete current;
        --m_size;
        current = tmp->next;
      }
      else
      {
        delete current;
        --m_size;
        tmp->next = nullptr;
      }
    }
    else
    {

      if (current->next != nullptr)
      {
        tmp = current;
        current = current->next;
      }
      else
      {
        return;
      }
    }
  }
}

template <typename T>
void f_list<T>::insert_after(int pos, T value)
{
  //if(pos >= 0 && pos <= this->m_size)
  //{
  node *current = head;
  node *count;
  while (pos != 0)
  {
    current = current->next;
    --pos;
  }
  count = current->next;
  current->next = new node();
  current->next->data = value;
  current->next->next = count;

  //}
}

