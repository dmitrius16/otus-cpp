#pragma once
#include <cstdint>
#include <array>
#include <algorithm>
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
    
    template<typename...Args>
    sorted_ip_t get_addr(const sorted_ip_t&, Args...args) const;
    sorted_ip_t get_addr_with_byte(const sorted_ip_t&, uint8_t) const;
private:
    template<int N, typename T>
    sorted_ip_t get_addr_impl(const sorted_ip_t&, T val) const;
    template<int N, typename T, typename...Args>
    sorted_ip_t get_addr_impl(const sorted_ip_t&, T val, Args... args) const;
    template<int N, typename T>
    sorted_ip_t get_addr_impl_aux(const sorted_ip_t&, T val) const;
private:
    std::deque<ip_info_s> ip_strg_;
    sorted_ip_t view_sorted_ip_;
};

template<typename...Args>
sorted_ip_t ip_storage::get_addr(const sorted_ip_t& view_sorted_ip, Args...args) const {
    return get_addr_impl<0>(view_sorted_ip, args...);
}

template<int N, typename T, typename... Args>
sorted_ip_t ip_storage::get_addr_impl(const sorted_ip_t& view_sorted_ip, T val, Args... args) const {
    static_assert(N < 4);
    
    auto res = get_addr_impl_aux<N>(view_sorted_ip, val);
    res =  get_addr_impl<N+1>(res, args...);

    return res;
}

template<int N, typename T>
sorted_ip_t ip_storage::get_addr_impl(const sorted_ip_t& view_sorted_ip, T byte_val) const {
    static_assert(N < 4);
    return get_addr_impl_aux<N>(view_sorted_ip, byte_val);
}

template<int N, typename T>
sorted_ip_t ip_storage::get_addr_impl_aux(const sorted_ip_t& view_sorted_ip, T byte_val) const {
    static_assert(N < 4);
    sorted_ip_t res;
    
    auto it_start = std::lower_bound(view_sorted_ip.begin(), view_sorted_ip.end(), byte_val,
        [](const ip_info_s* ptr, uint32_t val) { return ptr->ip_byte_repr[N] > val; });
    
    if (it_start != view_sorted_ip.end()) {
        auto it_end = std::upper_bound(view_sorted_ip.begin(), view_sorted_ip.end(), byte_val,
            [](uint32_t val, const ip_info_s* ptr) { return ptr->ip_byte_repr[N] < val; });
        res.assign(it_start, it_end);
    }
    return res;
    
}
