#include "txtRead.h"
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

txtRead::txtRead::txtRead() {
	_content = 0;
}
txtRead::txtRead::~txtRead() {
	if (_content) {
		free(_content);
	}
}

// discription	:	read file at once
// parameter	:	file path
// return		:	The entire contents of the file
void txtRead::txtRead::ReadAll(char* path) {
	char* buffer = 0;
	long length;
	FILE* f;
	fopen_s(&f, path, "rb");
	if (f) {
		fseek(f, 0, SEEK_END);
		length = ftell(f) + 1;
		fseek(f, 0, SEEK_SET);
		buffer = (char*)malloc(length);
		if (buffer) {
			fread(buffer, 1, length, f);
			buffer[length - 1] = '\0';
		}
		fclose(f);
	}
	_content = buffer;
}

void* txtRead::txtRead::GetContentPtr() {
	return _content;
}

std::vector<std::string> txtRead::txtRead::Split(char* content, char* delimeter)
{
	std::vector<std::string> answer;
	size_t str_begin = 0, str_end = 0;
	size_t file_size = strlen(content);
	size_t deli_size = strlen(delimeter);
	while (true) {
		// Find delimeter charecter position
		char* position = std::find(content + str_begin, content + file_size, *delimeter);
		if (position != content + file_size) {
			str_end = position - content;
			answer.push_back(std::string(content + str_begin, content + str_end));
			str_begin = str_end + deli_size;
		}
		else { // not any more delimeter charecter
			if (str_end < file_size) { // but str_end is not file end
				if (str_end + deli_size == file_size) {
					// append empty string
					answer.push_back(std::string());
				}
				else {
					answer.push_back(std::string(content + str_end + deli_size, content + file_size));
				}
			}

			break;
		}
	}
	return answer;
}

std::vector<std::string> txtRead::txtRead::File2Vector(char* path) {
	ReadAll(path);
	return Split((char*)_content, (char*)"\r\n\0");
}
