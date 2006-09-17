/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#include <boost/detail/lightweight_test.hpp>
#include <boost/fusion/sequence/adapted/std_pair.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <boost/fusion/sequence/intrinsic/front.hpp>
#include <boost/fusion/sequence/intrinsic/back.hpp>
#include <boost/fusion/sequence/io/out.hpp>
#include <boost/fusion/sequence/container/vector/vector.hpp>
#include <boost/fusion/sequence/container/list/list.hpp>
#include <boost/fusion/sequence/generation/make_vector.hpp>
#include <boost/fusion/sequence/conversion/as_vector.hpp>
#include <boost/fusion/sequence/comparison/equal_to.hpp>
#include <boost/fusion/sequence/comparison/not_equal_to.hpp>
#include <boost/fusion/sequence/comparison/less.hpp>
#include <boost/fusion/sequence/comparison/less_equal.hpp>
#include <boost/fusion/sequence/comparison/greater.hpp>
#include <boost/fusion/sequence/comparison/greater_equal.hpp>
#include <boost/fusion/support/is_view.hpp>
#include <boost/mpl/assert.hpp>
#include <iostream>
#include <string>
#include <utility>

int
main()
{
    using namespace boost::fusion;
    using namespace boost;
    using namespace std;

    std::cout << tuple_open('[');
    std::cout << tuple_close(']');
    std::cout << tuple_delimiter(", ");

    {
        typedef std::pair<int, std::string> pair_type;
        BOOST_MPL_ASSERT_NOT((traits::is_view<pair_type>));
        pair_type p(123, "Hola!!!");

        std::cout << at_c<0>(p) << std::endl;
        std::cout << at_c<1>(p) << std::endl;
        std::cout << p << std::endl;
        BOOST_TEST(p == make_vector(123, "Hola!!!"));

        at_c<0>(p) = 6;
        at_c<1>(p) = "mama mia";
        BOOST_TEST(p == make_vector(6, "mama mia"));

        BOOST_STATIC_ASSERT(result_of::size<pair_type>::value == 2);
        BOOST_STATIC_ASSERT(!result_of::empty<pair_type>::value);

        BOOST_TEST(front(p) == 6);
        BOOST_TEST(back(p) == "mama mia");
    }
    
    {
        fusion::vector<int, float> v1(4, 3.3f);
        std::pair<short, float> v2(5, 3.3f);
        fusion::vector<long, double> v3(5, 4.4);
        BOOST_TEST(v1 < v2);
        BOOST_TEST(v1 <= v2);
        BOOST_TEST(v2 > v1);
        BOOST_TEST(v2 >= v1);
        BOOST_TEST(v2 < v3);
        BOOST_TEST(v2 <= v3);
        BOOST_TEST(v3 > v2);
        BOOST_TEST(v3 >= v2);
    }

    {
        // conversion from pair to vector
        fusion::vector<int, std::string> v(std::make_pair(123, "Hola!!!"));
        v = std::make_pair(123, "Hola!!!");
    }

    {
        // conversion from pair to list
        fusion::list<int, std::string> l(std::make_pair(123, "Hola!!!"));
        l = std::make_pair(123, "Hola!!!");
    }

    return boost::report_errors();
}
