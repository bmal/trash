#ifndef FACTORY_HPP
#   define FACTORY_HPP

#include <map>
#include <exception>
#include <string>
#include <functional>

template<typename Identifier_Type, class Abstract_Product>
class Default_Factory_Error
{
   public:
      class Exception
         : public std::exception
      {
         public:
            Exception(const Identifier_Type& unknown_id)
               : unknown_id_(unknown_id)
            {}

            virtual const char* what() const noexcept
            {
               return "Nieznany typ obiektu!";
            }

            const Identifier_Type& get_id()
            {
               return unknown_id_;
            }

         private:
            Identifier_Type unknown_id_;
      };

   protected:
      static Abstract_Product* on_unknown_type(const Identifier_Type& id)
      {
         throw Exception(id);
      }

      ~Default_Factory_Error()
      {}
};

template<
   class Abstract_Product,
   typename Identifier_Type = std::string,
   typename Product_Creator = std::function<Abstract_Product*()>,
   template<typename, class>
      class Factory_Error_Policy = Default_Factory_Error
>
class Factory
   : public Factory_Error_Policy<Identifier_Type, Abstract_Product>
{               
   public:
      bool register_creator(const Identifier_Type& id, Product_Creator creator)
      {
         return associations_.insert(
            typename assoc_map::value_type(id, creator)).second;
      }

      bool unregister_creator(const Identifier_Type& id)
      {
         return associations_.erase(id) == true;
      }

      Abstract_Product* create_object(const Identifier_Type& id)
      {
         auto i = associations_.find(id);
         if(i != associations_.end())
            return (i->second)();
         return this->on_unknown_type(id);
      }

   private:
      typedef std::map<Identifier_Type, Product_Creator> assoc_map;
      assoc_map associations_;
};

#endif
