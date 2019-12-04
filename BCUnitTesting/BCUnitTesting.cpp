#include "pch.h"
#include "CppUnitTest.h"
#include "../battlecity/Enemy.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BCUnitTesting
{
	TEST_CLASS(BCUnitTesting)
	{
	public:
		
		TEST_METHOD(Constructor)
		{
			Enemy enemy(1, 1, 1, 1, 1);
			Assert::IsTrue(enemy.getDirection == 1);

		}
	};
}
