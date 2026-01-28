#pragma once
#include <cstdint>
#include <array>
#include <string>
#include <deque>
#include <vector>
#include <ostream>


struct ip_info_s {
    std::string ip_str_repr;
    std::array<uint8_t, 4> ip_byte_repr;
    uint32_t ip_num_repr;

    ip_info_s(std::string str, std::array<uint8_t, 4> arr, uint32_t num)
        : ip_str_repr(std::move(str)), ip_byte_repr(arr), ip_num_repr(num) {}
};

class ip_storage {
public:
    void add_ip_addr(std::string ip_addr_str);
    void process_ip_addresses();
    void output_processed_ip(std::ostream& out) const;
private:
    std::deque<ip_info_s> ip_strg_;
    std::vector<const ip_info_s*> view_sorted_ip_;
};
