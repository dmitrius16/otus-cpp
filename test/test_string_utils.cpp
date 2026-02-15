#define BOOST_TEST_MODULE test_string_utils

#include "string_utils.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_string_utils)

BOOST_AUTO_TEST_CASE(test_split_empty) {
    auto result = str_utils::split("", '.');
    std::vector<std::string> expected = {""};
    BOOST_CHECK(result == expected);
}

BOOST_AUTO_TEST_CASE(test_split_single_token) {
    auto result = str_utils::split("11", '.');
    std::vector<std::string> expected = {"11"};
    BOOST_CHECK(result == expected);
}

BOOST_AUTO_TEST_CASE(test_split_multiple_separators) {
    auto result = str_utils::split("..", '.');
    std::vector<std::string> expected = {"", "", ""};
    BOOST_CHECK(result == expected);
}

BOOST_AUTO_TEST_CASE(test_split_with_trailing_separator) {
    auto result = str_utils::split("11.", '.');
    std::vector<std::string> expected = {"11", ""};
    BOOST_CHECK(result == expected);
}

BOOST_AUTO_TEST_CASE(test_split_with_leading_separator) {
    auto result = str_utils::split(".11", '.');
    std::vector<std::string> expected = {"", "11"};
    BOOST_CHECK(result == expected);
}

BOOST_AUTO_TEST_CASE(test_split_normal_case) {
    auto result = str_utils::split("11.22", '.');
    std::vector<std::string> expected = {"11", "22"};
    BOOST_CHECK(result == expected);
}

BOOST_AUTO_TEST_CASE(test_split_multiple_parts) {
    auto result = str_utils::split("192.168.1.1", '.');
    std::vector<std::string> expected = {"192", "168", "1", "1"};
    BOOST_CHECK(result == expected);
}

BOOST_AUTO_TEST_SUITE_END()
