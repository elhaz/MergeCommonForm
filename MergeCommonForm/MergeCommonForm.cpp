#include "MergeCommonForm.h"
#include "txtRead.h"
namespace merge {
	MergeCommonForm::MergeCommonForm(const char* recipe_path, const char* src, const char* dest) {
		_ReadRecipe(recipe_path);
		//MergeCommonForm::~MergeCommonForm();
	}
	MergeCommonForm::~MergeCommonForm() {
		if (mTurnTable.size()) {
			std::vector<struct recipe>().swap(mTurnTable);
		}
	}

	int MergeCommonForm::get_recipe_count() {
		return mTurnTable.size();
	}



	// Read Recipe file
	void MergeCommonForm::_ReadRecipe(const char* recipe_path) {

		txtRead::txtRead read;
		auto file = read.File2Vector(recipe_path);
		if (file.size()) {
			std::vector<struct merge::recipe> TurnTable;
			for (size_t i = 0; i < file.size(); ++i) {

				// ignore comment line
				if (file[i][0] == comment_char)
					continue;

				auto line = read.Split((char*)file[i].c_str(), ",");

				// IDX, CommonName, Turn, corr
				if (line.size() == 4) {
					TurnTable.push_back(
						struct merge::recipe() = { 
							line[1],
							line[2].empty() ? _no_value_ : stoi(line[2]), 
							stod(line[3]) 
						} 
					);
				}
			}

			// exist result
			if (TurnTable.size()) {
				mTurnTable.swap(TurnTable);
			}
		}
	}

	void MergeCommonForm::_SaveCommonForm()
	{
	}
}
