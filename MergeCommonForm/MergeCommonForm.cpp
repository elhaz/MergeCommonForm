#include "MergeCommonForm.h"
namespace merge {
	MergeCommonForm::MergeCommonForm(char* recipe_path, char* src, char* dest) {
		_ReadRecipe(recipe_path);
		//MergeCommonForm::~MergeCommonForm();
	}
	MergeCommonForm::~MergeCommonForm() {
	}

	// Read Recipe file
	void MergeCommonForm::_ReadRecipe(char* recipe_path) {
	}

	void MergeCommonForm::_SaveCommonForm()
	{
	}
}
