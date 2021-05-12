#include "MergeCommonForm.h"
#include "txtRead.h"
#include <fstream>
#include <algorithm>


namespace merge {
	MergeCommonForm::MergeCommonForm(const char* recipe_path, const char* src, const char* dest) {
		_ReadRecipe(recipe_path);
		_SaveCommonForm(src, dest);
		MergeCommonForm::~MergeCommonForm();
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

	void MergeCommonForm::_SaveCommonForm(const char* src, const char* dst, bool srcHeaderExist, bool dstHeaderWrite) {
		txtRead::txtRead srcRead;
		auto srcFile = srcRead.File2Vector(src);
		if (srcFile.size()) {
			// Write Header in dstFile ==================================
			if (dstHeaderWrite) {
				std::ofstream dstFile;
				dstFile.open(dst, std::ios_base::out);
				if (dstFile.is_open()) {
					std::string dstHeader = "";
					for (auto t : mTurnTable) {
						dstHeader += (t.name + ",");
					}
					dstHeader = dstHeader.substr(0, dstHeader.size() - 1) + LF;
					dstFile.write(dstHeader.c_str(), dstHeader.size());
					dstFile.close();
				}
			}
			// ==========================================================

			std::vector<std::pair<int, std::string>> srcBuffer;
			// assign a number to line. 
			for (int i = 0; i < srcFile.size(); i++) {
				// srcFile Header is present
				if (srcHeaderExist && i==0)
					continue;
				
				srcBuffer.push_back(std::make_pair(i, srcFile[i]));
			}

			// process the data in parallel for the line.
			if (srcBuffer.size()) {
				auto result = __Parallel_line(srcBuffer);
				__WriteDoneData(dst, result);
			}
		}
	}

	// process the data in parallel for the line.
	std::vector<std::pair<int, std::string>> 
		MergeCommonForm::__Parallel_line (std::vector<std::pair<int, std::string>>& srcBuffer)	{
		std::vector<std::pair<int, std::string>> DoneList;
		DoneList.resize(srcBuffer.size());

		size_t* prefix;
		#pragma omp parallel
		{
			int ithread = omp_get_thread_num();
			int nthreads = omp_get_num_threads();
			#pragma omp single
			{
				prefix = new size_t[nthreads + 1];
				prefix[0] = 0;
			}
			// buffer for each thread
			std::vector<std::pair<int, std::string>> private_done;
			#pragma omp for schedule(dynamic) nowait
			for (int i = 0; i < srcBuffer.size(); i++) {
				// sorted within one line
				std::vector<std::string> private_SingleCell;
				private_SingleCell.resize(mTurnTable.size());
				txtRead::txtRead tok;
				auto cells = tok.Split(srcBuffer[i].second.c_str(), ",\0");

				for (int j = 0; j < mTurnTable.size(); j++) {
					if (mTurnTable[j].turn != _no_value_) {
						if (mTurnTable[j].corr == 0) {
							private_SingleCell[j] = cells[mTurnTable[j].turn];
						}
						else {
							private_SingleCell[j] = std::to_string(stod(cells[mTurnTable[j].turn]) * mTurnTable[j].corr);
						}
					}
				}
				std::string makeLine = "";
				for (auto str : private_SingleCell) {
					makeLine+=(str+",");
				}
				private_done.push_back(std::make_pair(i, makeLine.substr(0, makeLine.size() - 1)));
			}
			prefix[ithread + 1] = private_done.size();
			#pragma omp barrier
			#pragma omp single 
			{
				for (int i = 1; i < (nthreads + 1); i++) prefix[i] += prefix[i - 1];
			}
			// Upon completion, copy private_done to DoneList
			std::copy(private_done.begin(), private_done.end(), DoneList.begin() + prefix[ithread]);
		}
		delete[] prefix;
		// sort DoneList by line number
		std::sort(DoneList.begin(), DoneList.end(), [](auto& left, auto& right) {
			return left.first < right.first;
		});
		return DoneList;
	}

	void MergeCommonForm::__WriteDoneData
	(const char* dst, std::vector<std::pair<int, std::string>>& DoneData) 	{
		std::ofstream dstFile;
		dstFile.open(dst, std::ios_base::out|std::ios_base::app);
		if (dstFile.is_open()) {
			for (auto line : DoneData) {
				dstFile.write((line.second + LF).c_str(), (line.second + LF).size());
			}
			dstFile.close();
		}
	}
}
