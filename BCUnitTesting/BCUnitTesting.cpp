#include "pch.h"
#include "CppUnitTest.h"
#include "../battlecity/Tank.h"
#include "../battlecity/PowerUps.h"
#include "../battlecity/WorldEntity.h"
#include "../battlecity/Menu.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BCUnitTesting
{
	TEST_CLASS(BCUnitTesting)
	{
	public:	

		TEST_METHOD(TankDirection)
		{
			Tank tank;
			tank.setTankDirection('0');
			Assert::AreEqual(tank.getTankDirection(), '0');
		}

		TEST_METHOD(TankSpeed) {
			Tank tank;
			tank.setTankSpeed(15.f);
			Assert::AreEqual(tank.getTankSpeed(), 15.f);
		}

		TEST_METHOD(TankConstructor){
		
			Tank tank(30, 30);
			Assert::IsTrue(tank.getPosition().first==30);
			Assert::IsTrue(tank.getPosition().second == 30);
		}

		TEST_METHOD(TestPowerUpsGetType){
			PowerUps PowerUp(BombPU,20,20);
			Assert::IsTrue(PowerUp.getType()==BombPU);
		}

		TEST_METHOD(TestWorldEntitiesGetType) {
			WorldEntity worldEntity(Steel, 20, 20);
			Assert::IsTrue(worldEntity.getType() == Steel);
		}

		TEST_METHOD(TestGetIsInMenu) {
			Menu menu;
			menu.setIsInMenu(1);
			Assert::IsTrue(menu.getIsInMenu());
		}

		TEST_METHOD(TestGetMenuOption) {
			Menu menu;
			menu.setMenuOption(1);
			Assert::IsTrue(menu.getMenuOption()==1);
		}
		TEST_METHOD(TestGetPaused) {
			Menu menu;
			menu.setPaused(1);
			Assert::IsTrue(menu.getPaused() == 1);
		}
		TEST_METHOD(TestGetStageChooser) {
			Menu menu;
			menu.setStageChooser(1);
			Assert::IsTrue(menu.getStageChooser() == 1);
		}
	};
}
