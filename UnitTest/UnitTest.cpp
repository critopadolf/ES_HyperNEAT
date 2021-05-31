#include "pch.h"
#include "CppUnitTest.h"
#include "../SharpeNEAT/global_id.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			global_id gid(5, 1);
			//semaphore S;
			Assert::AreEqual(4, 4);
		}
	};
}
