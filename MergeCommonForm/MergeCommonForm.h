#pragma once
#include <omp.h>
#include <vector>
#include <string>
namespace merge {
	const std::string CRLF = "\r\n";
	const std::string LF = "\n";
	const char comment_char = '#';
	const int _no_value_ = INT32_MAX;
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
		void _SaveCommonForm(const char* src, const char* dsst, bool srcHeaderExist = true, bool dstHeaderWrite = true);
		std::vector<std::pair<int, std::string>> __Parallel_line(std::vector<std::pair<int, std::string>>& srcBuffer);
		void __WriteDoneData(const char* dst, std::vector<std::pair<int, std::string>>& DoneData);
		
		std::vector<struct recipe> mTurnTable;
	};
}