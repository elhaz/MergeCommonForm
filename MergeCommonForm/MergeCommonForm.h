#pragma once
//#include <omp.h>
#include <vector>
#include <string>
namespace merge {
	struct recipe {
		std::string name;
		int turn;
		double corr;
	};

	class MergeCommonForm {
	public:
		MergeCommonForm(const char* recipe_path, const char* src, const char* dest);
		~MergeCommonForm();
		int get_recipe_count();
	protected:
		void _ReadRecipe(const char* recipe_path);
		void _SaveCommonForm();

		const char comment_char = '#';
		const int _no_value_ = INT32_MAX;
		std::vector<struct recipe> mTurnTable;
	};
}