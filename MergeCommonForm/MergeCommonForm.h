#pragma once
#include <omp.h>
#include <vector>
namespace merge {
	class MergeCommonForm {
	public:
		MergeCommonForm(); // test
		MergeCommonForm(char* recipe_path, char* src, char* dest);
		~MergeCommonForm();
		
	//protected:
		void _ReadRecipe(char* recipe_path);
		void _SaveCommonForm();
		char* __ReadOnce(char* path);

		struct recipe {
			char* name;
			int turn;
			double corr;
		};
		std::vector<struct recipe> mTurnTable;
	};
}