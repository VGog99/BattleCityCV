#include "pch.h"
#include "CppUnitTest.h"
#include "../battlecity/Tank.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BCUnitTesting
{
	TEST_CLASS(BCUnitTesting)
	{
	public:	

		TEST_METHOD(TestMethod1)
		{
			Tank tank;
			tank.setTankDirection('0');
			Assert::AreEqual(tank.getTankDirection(), '0');
		}

		TEST_METHOD(TestMethod2) {
			Tank tank;
			tank.setTankSpeed(15.f);
			Assert::AreEqual(tank.getTankSpeed(), 15.f);
		}

	};
}
