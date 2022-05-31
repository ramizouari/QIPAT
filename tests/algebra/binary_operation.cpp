//
// Created by ramizouari on 11/04/2022.
//
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include "boost/mp11.hpp"
#include "algebra/binary_operation.h"

using namespace algebra;
constexpr real err=1e-6;

static std::vector<integer> A={5,8,9,15,13,17,19,25,66,100},B={3,4,27,30,-13,-1,18,-500,99,102};

using additive_types=boost::mp11::mp_list<std::int32_t,std::int64_t>;
using string_types=boost::mp11::mp_list<std::string,std::wstring,std::u8string,std::u16string,std::u32string>;
using multiplicative_types=boost::mp11::mp_list<std::int32_t,std::int64_t>;
using comparable_types=boost::mp11::mp_list<std::int16_t,std::int32_t,std::int64_t>;
using bitwise_types= boost::mp11::mp_list<std::uint8_t,std::uint16_t,std::uint32_t,std::uint64_t>;


BOOST_AUTO_TEST_SUITE(test_binary_operation)

    BOOST_AUTO_TEST_CASE_TEMPLATE(plus,T,additive_types)
    {
        plus_t<T> F;
        BOOST_CHECK_EQUAL(F(47,12),59);
        BOOST_CHECK_EQUAL(F(1,2,3,4,5,6,7,8,9,10),55);
    }

    BOOST_AUTO_TEST_CASE(plus_string)
    {
        monoid_plus_t<std::string> F;
        BOOST_CHECK_EQUAL(F("ABC","DEF"),"ABCDEF");
        BOOST_CHECK_EQUAL(F("HELLO"," ","WORLD"," ","I"," ","PRESENT"," ","MYSELF","."),"HELLO WORLD I PRESENT MYSELF.");
    }

    BOOST_AUTO_TEST_CASE(plus_u8string)
    {
        monoid_plus_t<std::u8string> F;
        BOOST_CHECK(F(u8"ABC",u8"DEF")==u8"ABCDEF");
        BOOST_CHECK(F(u8"HELLO",u8" ",u8"WORLD",u8" ",u8"I",u8" ",u8"PRESENT",u8" ",u8"MYSELF",u8".")==u8"HELLO WORLD I PRESENT MYSELF.");
    }

    BOOST_AUTO_TEST_CASE_TEMPLATE(multiplies,T,additive_types)
    {
        multiplies_t<T> F;
        BOOST_CHECK_EQUAL(F(47,12),564);
        BOOST_CHECK_EQUAL(F(1,2,3,4,5,6,7,8,9,10),3628800);
    }

    BOOST_AUTO_TEST_CASE_TEMPLATE(max,T,comparable_types)
    {
        max_t<T> F;
        BOOST_CHECK_EQUAL(F(47,12),47);
        BOOST_CHECK_EQUAL(F(1,2,3,4,5,6,7,8,9,10),10);
    }

    BOOST_AUTO_TEST_CASE_TEMPLATE(min,T,comparable_types)
    {
        min_t<T> F;
        min_t<T>::neutral=std::numeric_limits<T>::max();
        BOOST_CHECK_EQUAL(F(47,12),12);
        BOOST_CHECK_EQUAL(F(1,2,3,4,5,6,7,8,9,10),1);
    }

    BOOST_AUTO_TEST_CASE(max_string)
    {
        max_t<std::string> F;
        BOOST_CHECK_EQUAL(F("Competitive","Maths"),"Maths");
        BOOST_CHECK_EQUAL(F("Adam","Bob","Cunningham","Dick","Emily","Fox","Ginger","Harold","Isaac","Jee Shen"),"Jee Shen");
    }

    BOOST_AUTO_TEST_CASE(min_string)
    {
        min_t<std::string> F;
        min_t<std::string>::neutral="~";
        BOOST_CHECK_EQUAL(F("Competitive","Maths"),"Competitive");
        BOOST_CHECK_EQUAL(F("Adam","Bob","Cunningham","Dick","Emily","Fox","Ginger","Harold","Isaac","Jee Shen"),"Adam");
    }

    BOOST_AUTO_TEST_CASE(max_u32string)
    {
        max_t<std::u32string> F;
        BOOST_CHECK(F(U"Competitive",U"Maths")==U"Maths");
        BOOST_CHECK(F(U"Adam",U"Bob",U"Cunningham",U"Dick",U"Emily",U"Fox",U"Ginger",U"Harold",U"Isaac",U"Jee Shen")==U"Jee Shen");
    }

    BOOST_AUTO_TEST_CASE_TEMPLATE(min_u16string,T,comparable_types)
    {
        min_t<std::u16string> F;
        min_t<std::u16string>::neutral=u"~";
        BOOST_CHECK(F(u"Competitive",u"Maths")==u"Competitive");
        BOOST_CHECK(F(u"Adam",u"Bob",u"Cunningham",u"Dick",u"Emily",u"Fox",u"Ginger",u"Harold",u"Isaac",u"Jee Shen")==u"Adam");
    }

    BOOST_AUTO_TEST_CASE_TEMPLATE(bitwise_and,T,bitwise_types)
    {
        and_t<T> F;
        BOOST_CHECK_EQUAL(F(0x11,0x12),0x10);
        BOOST_CHECK_EQUAL(F(0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A),0x00);
    }

    BOOST_AUTO_TEST_CASE_TEMPLATE(bitwise_or,T,bitwise_types)
    {
        or_t<T> F;
        BOOST_CHECK_EQUAL(F(0x11,0x12),0x13);
        BOOST_CHECK_EQUAL(F(0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A),0x0F);
    }

    BOOST_AUTO_TEST_CASE_TEMPLATE(bitwise_xor_t,T,bitwise_types)
    {
        xor_t<T> F;
        BOOST_CHECK_EQUAL(F(0x11,0x12),0x03);
        BOOST_CHECK_EQUAL(F(0b0001,0b010,0b0011,0b0100,0b0101,0b0110,0b0111,0b1000,0b1001,0b1010),0b1011);
    }

    BOOST_AUTO_TEST_CASE(bitwise_xor_byte)
    {
        using B=std::byte;
        xor_t<std::byte> F;
        BOOST_CHECK(F(B{0x11},B{0x12})==B{0x03});
        BOOST_CHECK(F(B{0b0001},B{0b010},B{0b0011},B{0b0100},B{0b0101},B{0b0110},B{0b0111},B{0b1000},B{0b1001},B{0b1010})==B{0b1011});
    }

BOOST_AUTO_TEST_SUITE_END()
