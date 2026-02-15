#define BOOST_TEST_MODULE test_ip_storage

#include "ip_storage.h"

#include <boost/test/unit_test.hpp>
#include <algorithm>
#include <random>
#include <vector>
#include <string>

BOOST_AUTO_TEST_SUITE(test_ip_storage)

BOOST_AUTO_TEST_CASE(test_sorting_consistency) {
    // already sorted addresses
    std::vector<std::string> sorted_ips = {
        "222.173.235.246",
        "222.173.235.245",
        "222.173.234.246",
        "222.172.235.246",
        "221.173.235.246",
        "192.168.0.10",
        "185.46.87.231",
        "10.10.0.1"
    };

    ip_storage etalon;
    for (const auto& ip : sorted_ips) {
        etalon.add_ip_addr(ip);
    }
    //etalon.sort_ip_addresses();  list of ip have been already sorted
    auto etalon_sorted = etalon.get_sorted_ip();

    // Shuffle the IPs
    auto shuffled_ips = sorted_ips;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(shuffled_ips.begin(), shuffled_ips.end(), g);

    // Create test storage with shuffled IPs
    ip_storage test_obj;
    for (const auto& ip : shuffled_ips) {
        test_obj.add_ip_addr(ip);
    }
    test_obj.sort_ip_addresses();
    auto test_sorted = test_obj.get_sorted_ip();

    // Extract IP strings for comparison
    std::vector<std::string> etalon_strs, test_strs;
    for (const auto* p : etalon_sorted) {
        etalon_strs.push_back(p->ip_str_repr);
    }
    for (const auto* p : test_sorted) {
        test_strs.push_back(p->ip_str_repr);
    }

    BOOST_CHECK(etalon_strs == test_strs);
}

BOOST_AUTO_TEST_CASE(test_get_addr_where_first_byte) {
    ip_storage storage;
    storage.add_ip_addr("1.2.3.4");
    storage.add_ip_addr("1.1.1.1");
    storage.add_ip_addr("2.1.1.1");
    storage.add_ip_addr("1.3.5.7");
    auto sorted = storage.sort_ip_addresses();

    auto result = storage.get_addr_where_first_byte(sorted, 1);

    std::vector<std::string> result_strs;
    for (const auto* p : result) {
        result_strs.push_back(p->ip_str_repr);
    }

    std::vector<std::string> expected = {"1.3.5.7", "1.2.3.4", "1.1.1.1"}; // descending order
    BOOST_CHECK(result_strs == expected);
}

BOOST_AUTO_TEST_CASE(test_get_addr_with_first_two_bytes) {
    ip_storage storage;
    storage.add_ip_addr("46.70.1.1");
    storage.add_ip_addr("46.70.2.2");
    storage.add_ip_addr("46.71.1.1");
    storage.add_ip_addr("47.70.1.1");
    auto sorted = storage.sort_ip_addresses();

    auto result = storage.get_addr_with_first_two_bytes(sorted, 46, 70);

    std::vector<std::string> result_strs;
    for (const auto* p : result) {
        result_strs.push_back(p->ip_str_repr);
    }

    std::vector<std::string> expected = {"46.70.2.2", "46.70.1.1"}; // descending order
    BOOST_CHECK(result_strs == expected);
}

BOOST_AUTO_TEST_CASE(test_get_addr_where_any_of_byte_eq) {
    ip_storage storage;
    storage.add_ip_addr("192.168.1.46");
    storage.add_ip_addr("46.1.1.1");
    storage.add_ip_addr("1.46.1.1");
    storage.add_ip_addr("1.1.46.1");
    storage.add_ip_addr("1.1.1.46");
    storage.add_ip_addr("2.2.2.2");
    auto sorted = storage.sort_ip_addresses();

    auto result = storage.get_addr_where_any_of_byte_eq(sorted, 46);

    std::vector<std::string> result_strs;
    for (const auto* p : result) {
        result_strs.push_back(p->ip_str_repr);
    }

    std::vector<std::string> expected = {"192.168.1.46", "46.1.1.1", "1.46.1.1", "1.1.46.1", "1.1.1.46"};
    BOOST_CHECK(result_strs == expected);
}

BOOST_AUTO_TEST_SUITE_END()