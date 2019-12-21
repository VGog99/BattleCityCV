#include "pch.h"
#include "CppUnitTest.h"
#include "../battlecity/Tank.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BCUnitTesting
{
	TEST_CLASS(BCUnitTesting)
	{
	public:
		
		TEST_METHOD(Constructor)
		{
			Tank tank;
			tank.setTankDirection('0');
			Assert::AreEqual(tank.getTankDirection(), '0');
		}
	};
}
