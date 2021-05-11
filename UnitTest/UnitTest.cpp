#include "CppUnitTest.h"
#include <string>
#include <vector>
#include "txtRead.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		std::string root_path = "E:\\source\\C\\MergeCommonForm\\UnitTest\\TestCase\\";
		//std::string root_path = "D:\\source\\Project\\MergeCommonForm\\UnitTest\\TestCase\\";
		TEST_METHOD(FileRead)
		{

			char* path1 = "E:\\source\\C\\MergeCommonForm\\UnitTest\\TestCase\\helloworld.txt";
			char* path2 = "D:\\source\\Project\\MergeCommonForm\\UnitTest\\TestCase\\helloworld.txt";
			txtRead::txtRead read;
			read.ReadAll(path2);
			
			Assert::AreEqual(std::string((char*)(read.GetContentPtr())), std::string("HelloWorld"));
		}
		TEST_METHOD(SPLIT) {
			char* path1 = "E:\\source\\C\\MergeCommonForm\\UnitTest\\TestCase\\split.txt";
			char* path2 = "D:\\source\\Project\\MergeCommonForm\\UnitTest\\TestCase\\split.txt";
			txtRead::txtRead read;
			auto l = read.File2Vector(path2);
			Assert::AreEqual((int)l.size(), 6);
		}
	};
}
