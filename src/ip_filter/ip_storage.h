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
    bool operator>(const ip_info_s& rhs) {
        return ip_num_repr > rhs.ip_num_repr;
    }
};

using sorted_ip_t = std::vector<const ip_info_s*>;
class ip_storage;

void output_processed_ip(std::ostream&, const sorted_ip_t&);
void process_ip_addresses(ip_storage&);
class ip_storage {
public:
    void add_ip_addr(std::string);
    
    const sorted_ip_t& sort_ip_addresses();
    const sorted_ip_t& get_sorted_ip() const {return view_sorted_ip_;}    
    sorted_ip_t get_addr_where_first_byte(const sorted_ip_t&, uint8_t);
    sorted_ip_t get_addr_with_first_two_bytes(const sorted_ip_t&, uint8_t, uint8_t);
    sorted_ip_t get_addr_where_any_of_byte_eq(const sorted_ip_t&, uint8_t);
private:
    std::deque<ip_info_s> ip_strg_;
    sorted_ip_t view_sorted_ip_;
};
