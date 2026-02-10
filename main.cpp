#include "lib.h"
#include <exception>
#include <iostream>
#include <vector>
#include "string_utils.h"
#include "ip_storage.h"

ip_storage ip_strg;

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[]) {
	// read ip addresses
	try {
		std::vector<std::vector<std::string>> ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = str_utils::split(line, '\t');
			ip_strg.add_ip_addr(std::move(v.at(0)));
        }

		process_ip_addresses(ip_strg);
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
