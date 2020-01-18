#include "pch.h"
#include "CppUnitTest.h"
#include "../battlecity/Tank.h"
#include "../battlecity/PowerUps.h"
#include "../battlecity/WorldEntity.h"
#include "../battlecity/Menu.h"
#include "../battlecity/Bullet.h"
#include "../battlecity/Animation.hpp"
#include "../battlecity/Engine.h"

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
		TEST_METHOD(TestPowerUpsGetType) {
			PowerUps PowerUp(ShovelPU, 50, 50);
			Assert::IsTrue(PowerUp.getType() == ShovelPU);
		}

		TEST_METHOD(TestsetTankDirection) {
			Tank tank;
			tank.setTankDirection('2');
			Assert::AreEqual(tank.getTankDirection(),'2');
		}

		TEST_METHOD(TestsetTankDirection) {
			Tank tank;
			tank.setTankSpeed(10.5f);
			Assert::AreEqual(tank.getTankSpeed(), 10.5f);
		}

		TEST_METHOD(TestisEnemy) {
			Tank tank;
			Assert::IsTrue(tank.isEnemy(), 0);
		}

		TEST_METHOD(TestisInMenu) {
			Menu menu;
			menu.setIsInMenu(1);
			Assert::IsTrue(menu.getIsInMenu() == 1);
		}

		TEST_METHOD(TestGetLocalPlayerKills) {
			Engine engine;
			engine.setlocalPlayerKills(100);
			Assert::IsTrue(engine.getLocalPlayerKills() == 100);
		}

		TEST_METHOD(TestGetLocalPlayerScore) {
			Menu menu;
			Engine engine;
			engine.setLocalPlayerScore(10000);
			Assert::IsTrue(engine.getLocalPlayerScore() == 10000);
		}

		TEST_METHOD(TestGetLocalPlayerKills) {
			Engine engine;
			engine.setlocalPlayerKills(2);
			Assert::IsFalse(engine.getLocalPlayerKills() == 4);
		}

		TEST_METHOD(TestPowerUpsGetType) {
			PowerUps PowerUp(ClockPU, 35, 35);
			Assert::IsTrue(PowerUp.getType() == ClockPU);
		}

		TEST_METHOD(TestGetLocalPlayerScore) {
			Menu menu;
			Engine engine;
			engine.setLocalPlayerScore(100);
			Assert::IsFalse(engine.getLocalPlayerScore()==10);
		}

		TEST_METHOD(TestPowerUpsGetType) {
			PowerUps PowerUp(StarPU, 20, 20);
			Assert::IsTrue(PowerUp.getType() == StarPU);
		}
	};
}
