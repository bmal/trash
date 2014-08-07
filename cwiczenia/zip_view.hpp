#ifndef ZIP_VIEW_HPP
#define ZIP_VIEW_HPP

#include "boost/mpl/iterator_tags.hpp"
#include "boost/mpl/deref.hpp"
#include "boost/mpl/placeholders.hpp"
#include "boost/mpl/transform.hpp"
#include "boost/mpl/next.hpp"
#include "boost/mpl/iterator_range.hpp"
#include "boost/mpl/transform_view.hpp"

namespace mpl = boost::mpl;
using namespace mpl::placeholders;

template<class Iterator_seq>
struct zip_iterator;

template<class Iterator_seq>
struct zip_iterator
{
   typedef mpl::forward_iterator_tag category;
   typedef Iterator_seq base;

   typedef typename mpl::transform<
      Iterator_seq,
      mpl::deref<_1>
   >::type type;
};

template<class Sequences>
struct zip_view
 : mpl::iterator_range<
      zip_iterator<
         typename mpl::transform_view<
            Sequences, mpl::begin<_1>
         >::type
      >,
      zip_iterator<
         typename mpl::transform_view<
            Sequences, mpl::end<_1>
         >::type
      >
   >
{};

namespace boost
{
   namespace mpl
   {
      template<class Iterator_seq>
      struct next<::zip_iterator<Iterator_seq>>
      {
         typedef ::zip_iterator<
            typename transform<
               Iterator_seq,
               next<_1>
            >::type
         > type;
      };
   }
}

#endif
