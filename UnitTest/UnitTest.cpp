#include "CppUnitTest.h"
#include "txtRead.h"
#include "MergeCommonForm.h"
#include <string>
#include <vector>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		//std::string root_path = "E:\\source\\C\\MergeCommonForm\\UnitTest\\TestCase\\";
		std::string root_path = "D:\\source\\Project\\MergeCommonForm\\UnitTest\\TestCase\\";
		TEST_METHOD(TEST1_FileRead)
		{
			std::string path = root_path + "helloworld.txt";
			txtRead::txtRead read;
			read.ReadAll(path.c_str());
			Assert::AreEqual(std::string((char*)(read.GetContentPtr())), std::string("HelloWorld"));
		}
		TEST_METHOD(TEST2_SPLIT) {
			std::string path = root_path + "split.txt";
			txtRead::txtRead read;
			auto l = read.File2Vector(path.c_str());
			Assert::AreEqual((int)l.size(), 6);
		}

		//TEST_METHOD(TEST3_RECIPE_CHECK) {
		//	std::string path = root_path + "recipe_exam.csv";
		//	merge::MergeCommonForm mcf(path.c_str(), "", "");
		//	Assert::AreEqual(mcf.get_recipe_count(), 4);
		//}

		TEST_METHOD(TEST4_substr) {
			std::string substrTest = "";
			for (int i = 0; i < 10; i++) {
				substrTest += ("Name,");
			}
			substrTest = substrTest.substr(0, substrTest.size() - 1);
			Assert::IsTrue(true);
		}

		TEST_METHOD(TEST5_MakeCommonForm) {
			std::string recipe = root_path + "recipe_exam.csv";
			std::string src = root_path + "src.csv";
			std::string dst = root_path + "dst.csv";
			merge::MergeCommonForm mcf(recipe.c_str(), src.c_str(), dst.c_str());
			Assert::IsTrue(true);
		}
	};
}
