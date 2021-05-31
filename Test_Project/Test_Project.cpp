#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include "../SharpeNEAT/Mesh.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(TestProject)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Mesh m = Mesh(2, 10, 10, 10);
			//Assert::AreEqual(name, mc.GetName());
		}
	};
}
