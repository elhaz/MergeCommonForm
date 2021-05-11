#pragma once
#include <vector>
#include <string>
namespace txtRead {
	class txtRead {
	public :
		txtRead();
		~txtRead();
		void ReadAll(const char* path);
		void* GetContentPtr();
		std::vector<std::string> Split(const char* content, const char* delimeter);
		std::vector<std::string> File2Vector(const char* path);
	protected:
		void* _content;
	};
}
