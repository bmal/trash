#include "boost/mpl/equal.hpp"
#include "boost/mpl/vector_c.hpp"
#include "boost/mpl/transform.hpp"
#include "boost/mpl/erase.hpp"
#include "boost/mpl/divides.hpp"
#include "boost/mpl/insert_range.hpp"
#include "boost/mpl/begin_end.hpp"
#include "boost/mpl/advance.hpp"
#include "boost/mpl/size.hpp"
#include "boost/mpl/plus.hpp"
#include "boost/mpl/int.hpp"
#include "boost/mpl/placeholders.hpp"
#include "boost/static_assert.hpp"

using namespace boost::mpl;

template<class T>
struct double_first_half
{
   private:
      typedef typename advance<
         typename begin<T>::type,
         typename divides<
            typename size<T>::type,
            int_<2>
         >::type
      >::type iterator_middle;

      typedef typename begin<T>::type iterator_begin;
      typedef typename end<T>::type iterator_end;

      typedef typename transform<
            typename erase<T, iterator_middle, iterator_end>::type, 
            plus<
               _1, 
               _1>
         >::type doubled_first_half;

   public:
      typedef typename insert_range<
         doubled_first_half,
         typename end<doubled_first_half>::type,
         typename erase<T, iterator_begin, iterator_middle>::type
      >::type type;
};

BOOST_STATIC_ASSERT((
         equal<
            double_first_half<vector_c<int, 1, 2, 3, 4>>::type,
            vector_c<int, 2, 4, 3, 4>
         >::type::value));
