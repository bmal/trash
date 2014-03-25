#include <iostream>

using namespace std;

template<class T>
class New_creator
{
   public:
       static T* create() { return new T(10); }
};

class New_creator1
{
   public:
      template<class T>
      static T* create()
      {
         return new T(10);
      }
};

template<class Creator>
class Factory : public Creator
{
};

template<template<class> class Creator>
class Factory1 : public Creator<int>
{
};

template<typename Creator>
class Factory2 : public Creator
{
};

int main()
{
   Factory<New_creator<int> > fac;
   cout << *fac.create() << endl;

   Factory1<New_creator> fac1;
   cout << *fac1.create() << endl;

   Factory2<New_creator1> fac2;
   cout << *fac2.create<int>() << endl;
}
