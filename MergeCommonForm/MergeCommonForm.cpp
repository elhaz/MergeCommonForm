#include "MergeCommonForm.h"
#include <stdio.h>
#include <stdlib.h>
namespace merge {
	MergeCommonForm::MergeCommonForm(char* recipe_path, char* src, char* dest) {
		_ReadRecipe(recipe_path);
		//MergeCommonForm::~MergeCommonForm();
	}
	MergeCommonForm::~MergeCommonForm() {
		if (_p_recipe != nullptr) {
			free(_p_recipe);
		}
	}

	// Read Recipe file
	void MergeCommonForm::_ReadRecipe(char* recipe_path) {
		_p_recipe = __ReadOnce(recipe_path);
	}

	void MergeCommonForm::_SaveCommonForm()
	{
	}

	char* MergeCommonForm::__ReadOnce(char* path)
	{
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
				buffer[length-1] = '\0';
			}
			fclose(f);
		}
		return buffer;
	}
}
