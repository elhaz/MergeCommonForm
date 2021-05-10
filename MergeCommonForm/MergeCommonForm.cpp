#include "MergeCommonForm.h"

namespace merge {
	MergeCommonForm::MergeCommonForm(char* recipe_path, char* src, char* dest) {
		//_ReadRecipe(recipe_path);
		//MergeCommonForm::~MergeCommonForm();
	}
	MergeCommonForm::~MergeCommonForm() {
	}

	// Read Recipe file
	void MergeCommonForm::_ReadRecipe(char* recipe_path) {
		char* content = __ReadOnce(recipe_path);
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
			length = ftell(f);
			fseek(f, 0, SEEK_SET);
			buffer = (char*)malloc(length);
			if (buffer) {
				fread(buffer, 1, length, f);
			}
			fclose(f);
		}
		return buffer;
	}
}
