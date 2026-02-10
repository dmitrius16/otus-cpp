#include <cassert>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <utility>
#include "ip_storage.h"
#include "string_utils.h"

void ip_storage::add_ip_addr(std::string ip_addr_str) {
    auto parts = str_utils::split(ip_addr_str, '.');
    if (parts.size() != 4) {
        throw std::invalid_argument("Invalid IP address format");
    }
    std::array<uint8_t, 4> ip_byte_repr;
    for (size_t i = 0; i < 4; ++i) {
        int val = std::stoi(parts[i]);
        if (val < 0 || val > 255) {
            throw std::invalid_argument("IP octet out of range");
        }
        ip_byte_repr[i] = static_cast<uint8_t>(val);
    }
    uint32_t ip_num_repr = (uint32_t(ip_byte_repr[0]) << 24) |
                           (uint32_t(ip_byte_repr[1]) << 16) |
                           (uint32_t(ip_byte_repr[2]) << 8) |
                           ip_byte_repr[3];
    auto& new_info = ip_strg_.emplace_back(std::move(ip_addr_str), ip_byte_repr, ip_num_repr);
    view_sorted_ip_.push_back(&new_info);
}

const sorted_ip_t& ip_storage::sort_ip_addresses() {
    std::sort(view_sorted_ip_.begin(), view_sorted_ip_.end(), [](const ip_info_s* a, const ip_info_s* b) {
        return a->ip_num_repr > b->ip_num_repr;
    });
    return view_sorted_ip_;
}

void process_ip_addresses(ip_storage& strg) {
    auto sorted_ip = strg.sort_ip_addresses();    
    auto ip_first_byte_eq_1 = strg.get_addr_where_first_byte(sorted_ip, 1);
    auto ip_two_bytes_46_70 = strg.get_addr_with_first_two_bytes(sorted_ip, 46, 70);
    auto ip_any_byte_46 = strg.get_addr_where_any_of_byte_eq(sorted_ip, 46);
    
    output_processed_ip(std::cout, sorted_ip);
    output_processed_ip(std::cout, ip_first_byte_eq_1);
    output_processed_ip(std::cout, ip_two_bytes_46_70);
    output_processed_ip(std::cout, ip_any_byte_46);
}

sorted_ip_t ip_storage::get_addr_where_first_byte(const sorted_ip_t& view_sorted_ip, uint8_t first_byte) {
    std::vector<const ip_info_s*> res;
    
    auto it_start = std::lower_bound(view_sorted_ip.begin(), view_sorted_ip.end(), first_byte,
        [](const ip_info_s* ptr, uint32_t val) { return ptr->ip_byte_repr[0] > val; });
    
    if (it_start != view_sorted_ip.end()) {
        auto it_end = std::upper_bound(view_sorted_ip.begin(), view_sorted_ip.end(), first_byte,
            [](uint32_t val, const ip_info_s* ptr) { return ptr->ip_byte_repr[0] < val; });
        res.assign(it_start, it_end);
    }
    return res;
}


sorted_ip_t ip_storage::get_addr_with_first_two_bytes(const sorted_ip_t& view_sorted_ip, uint8_t first_byte, 
                                                         uint8_t second_byte) {
    sorted_ip_t res;
    auto sorted_first_byte = get_addr_where_first_byte(view_sorted_ip, first_byte);
    auto it_start = std::lower_bound(sorted_first_byte.begin(), sorted_first_byte.end(), second_byte,
        [](const ip_info_s* ptr, uint32_t val) {return ptr->ip_byte_repr[1] > val;});
    if (it_start != view_sorted_ip_.end()) {
        auto it_end = std::upper_bound(sorted_first_byte.begin(), sorted_first_byte.end(), second_byte, 
            [](uint32_t val, const ip_info_s* ptr){return ptr->ip_byte_repr[1] < val;});
        res.assign(it_start, it_end);
    }
    return res; 
}

sorted_ip_t ip_storage::get_addr_where_any_of_byte_eq(const sorted_ip_t& view_sorted_ip, uint8_t byte_val) {
    auto st_it = view_sorted_ip.begin();
    auto end_it = view_sorted_ip.end();
    sorted_ip_t res;
    do {
        st_it = std::find_if(st_it, end_it, [byte_val](const ip_info_s* ip_addr) {
        return std::any_of(ip_addr->ip_byte_repr.begin(), 
                             ip_addr->ip_byte_repr.end(),
                             [byte_val](uint8_t val){return val == byte_val;});
        });
        
        if (st_it != end_it) {
            res.push_back(*st_it);
            ++st_it;
        }
    } while (st_it != end_it);
    return res;
}


void output_processed_ip(std::ostream& out, const sorted_ip_t &ip) {
    for (auto ip_info : ip) {
        out << ip_info->ip_str_repr << std::endl;
    }
}
