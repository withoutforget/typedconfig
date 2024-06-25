#include "Config.h"
#include "VarManager.h"

using namespace TypedConfig;


#include <iostream>
#include <sstream>

int main() try {
    auto s = "f64:i32=14.000000\nf64:i32=42.000000";
    std::stringstream ss;
    ss << s;
    Config config{};
    config.from_stream(ss);
    config.dump_to(std::cout);
}
catch (std::exception& e) {
    std::cout << "what(): " << e.what() << std::endl;
}