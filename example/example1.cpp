/*
First example of typedconfig
requirements: C++20
*/

#include "typedconfig/number_types.h"
#include "typedconfig/string_types.h"
#include "typedconfig/formatter.h"
#include "typedconfig/var_manager.h"
#include "typedconfig/config.h"

#include <iostream>

int main() try {
	auto& vm = typedconfig::var_manager::instance();
	using namespace typedconfig::types;
	vm.import<boolean>();
	vm.import<i8>();
	vm.import<i16>();
	vm.import<i32>();
	vm.import<i64>();
	vm.import<u8>();
	vm.import<u16>();
	vm.import<u32>();
	vm.import<u64>();
	vm.import<f32>();
	vm.import<f64>();
	vm.import<f96>();
	vm.import<str>();

	typedconfig::config config;
	config.parse("str:hello=world");
	config.append<boolean>("test");
	config.append<f32>("f32_var", 14.15926585f);
	config.append<u64>("very long number", 100000000000000);

	std::cout << config.dump('\n');
}
catch (std::exception& e) {
	std::cout << std::format("e.what(): {}\n\n", e.what());
}