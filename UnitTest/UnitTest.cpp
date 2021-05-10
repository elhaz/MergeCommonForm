#include "CppUnitTest.h"
#include "MergeCommonForm.h"
#include <string>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(FileRead)
		{
			char* path = "E:\\source\\C\\MergeCommonForm\\UnitTest\\TestCase\\helloworld.txt";
			merge::MergeCommonForm mcf(path, "", "");
			std::string content = std::string((char*)mcf._p_recipe);
			Assert::AreEqual(content, std::string("HelloWorld"));
		}
	};
}
