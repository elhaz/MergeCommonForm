#pragma once
//#include <omp.h>
#include <vector>
#include <string>
namespace merge {
	class MergeCommonForm {
	public:
		MergeCommonForm(char* recipe_path, char* src, char* dest);
		~MergeCommonForm();
		
	//protected:
		void _ReadRecipe(char* recipe_path);

		void _SaveCommonForm();

		struct recipe {
			char* name;
			int turn;
			double corr;
		};
		//std::vector<struct recipe> mTurnTable;
	};
}