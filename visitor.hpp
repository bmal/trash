#ifndef VISITOR_HPP
#   define VISITOR_HPP

class Base_Visitor
{
   public:
      virtual ~Base_Visitor()
      {}
};

template<class T, typename Result = void>
class Visitor
{
   public:
      typedef Result result_type;

      virtual result_type visit(T&) = 0;
};

template<class Result = void>
class Base_Visitable
{
   public:
      typedef Result result_type;

      virtual result_type accept(Base_Visitor&) = 0;

      virtual ~Base_Visitable()
      {}

   protected:
      template<class T>
      static result_type Accept_Impl(T& visited, Base_Visitor& guest)
      {
         if(Visitor<T>* p = dynamic_cast<Visitor<T>*>(&guest))
            return p->visit(visited);
         return result_type();
      }
};

#define DEFINE_VISITABLE()                              \
   virtual result_type accept(Base_Visitor& guest)      \
   {                                                    \
      return Accept_Impl(*this, guest);                 \
   }

/*EXAMPLE
class Doc_Element
  : public Base_Visitable<>
{
   public:
      DEFINE_VISITABLE()
};

class Paragraph
   : public Doc_Element
{
   public:
      DEFINE_VISITABLE()
};

class My_Concrete_Visitor
   : public Base_Visitor,
     public Visitor<Doc_Element>,
     public Visitor<Paragraph>
{
   public:
      void visit(Doc_Element&)
      {
         std::cout << "visit(Doc_Element&)\n";
      }

      void visit(Paragraph&)
      {
         std::cout << "visit(Paragraph&)\n";
      }
};

int main()
{
   My_Concrete_Visitor visitor;
   Paragraph par;
   Doc_Element* d = &par;
   d->accept(visitor);
}
*/

#endif
