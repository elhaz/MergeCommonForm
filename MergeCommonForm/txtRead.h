#pragma once
#include <vector>
#include <string>
namespace txtRead {
	class txtRead {
	public :
		txtRead();
		~txtRead();
		void ReadAll(char* path);
		void* GetContentPtr();
		std::vector<std::string> Split(char* content, char* delimeter);
		std::vector<std::string> File2Vector(char* path);
	protected:
		void* _content;
	};
}
