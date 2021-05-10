#include "pch.h"
#include "CppUnitTest.h"
#include "MergeCommonForm.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(FileRead)
		{
			merge::MergeCommonForm mcf;
			char* content = mcf.__ReadOnce("TestCase\\helloworld.txt");
			Assert::AreEqual(content, "HelloWorld");
		}
	};
}
