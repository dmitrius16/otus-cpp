#include <cassert>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <iostream>
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

void ip_storage::process_ip_addresses() {
    std::sort(view_sorted_ip_.begin(), view_sorted_ip_.end(), [](const ip_info_s* a, const ip_info_s* b) {
        return a->ip_num_repr > b->ip_num_repr;
    });
}

void ip_storage::output_processed_ip(std::ostream& out) const {
    for (auto ip_info : view_sorted_ip_) {
        out << ip_info->ip_str_repr << std::endl;
    }
}
