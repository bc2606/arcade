/*
** EPITECH PROJECT, 2018
** DLLoader
** File description:
** Declaration of DLLoader
*/

#ifndef BOOT_DLLOADER_HPP
	#define BOOT_DLLOADER_HPP

#include <iostream>
#include <dlfcn.h>
#include <utility>

template <typename T>
class DLLoader {
public:
	typedef T *(*entryPoint)();
	explicit DLLoader(std::string path) {
		_path = path;
		_handler = dlopen(_path.c_str(), RTLD_LAZY);
	}
	T *getInstance() {
		if (!_handler) {
			std::cerr << dlerror() << std::endl;
			exit(84);
		}
		auto entry = (entryPoint)dlsym(_handler, "entryPoint");
		const char *error = dlerror();
		if (error) {
			std::cerr << error << std::endl;
			dlclose(_handler);
			exit(84);
		}
		return entry();
	}
	void close() {
		dlclose(_handler);
	};

private:
	std::string _path;
	void *_handler;
};

#endif /* BOOT_DLLOADER_HPP */
