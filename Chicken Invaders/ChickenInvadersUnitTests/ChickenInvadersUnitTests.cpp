#include "pch.h"
#include "CppUnitTest.h"
#include "..\Chicken Invaders\ResourceLoader.h"
#include "..\Chicken Invaders\Boss.h"
#include"..\Chicken Invaders\Player.h"
#include"..\Chicken Invaders\Chicken.h"
#include"..\Chicken Invaders\Asteroid.h"
#include"..\Chicken Invaders\Present.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChickenInvadersUnitTests
{
	TEST_CLASS(ChickenInvadersUnitTests)
	{
	public:
		TEST_METHOD(isDeadTest)
		{
			Player player;
			Assert::AreEqual(false, player.IsDead());
		}
		TEST_METHOD(isImmortalTest)
		{
			Player player;
			Assert::AreEqual(true, player.IsImmortal());
		}
		TEST_METHOD(getNumberMissiletest)
		{
			Player player;
			Assert::AreEqual(player.GetNrMissiles(), 3);

		}
		TEST_METHOD(chickenIsMovingTest)
		{
			ResourceLoader resourceLoader;
			Chicken chicken(Vector2f(40,40),resourceLoader.GetTexture(ResourceLoader::TextureType::Chicken),1);
			chicken.moveChicken(1,1);
			Assert::AreNotEqual(sf::Vector2f(40,40), chicken.getPosition());

		}
		TEST_METHOD(isOnScreenTest)
		{
			ResourceLoader resourceLoader;
			Chicken chicken(Vector2f(40, 40), resourceLoader.GetTexture(ResourceLoader::TextureType::Chicken), 1);
			Assert::AreNotSame(chicken.getPosition(), sf::Vector2f(0, 1920));
			
		}
		
		TEST_METHOD(isAliveChickenTest)
		{
			ResourceLoader resourceLoader;
			Chicken chicken(Vector2f(40, 40), resourceLoader.GetTexture(ResourceLoader::TextureType::Chicken), 1);
			Assert::AreNotEqual(chicken.GetLife(), 0);

		}
		TEST_METHOD(asteroidIsOnScreen)
		{
			ResourceLoader resourceLoader;
			Asteroid asteroid(Vector2f(40, 40), resourceLoader.GetTexture(ResourceLoader::TextureType::Asteroid), 3);
	
			Assert::IsTrue(asteroid.IsOnTheScreen());
		}
		TEST_METHOD(asteroidFallDowanTest)
		{
			ResourceLoader resourceLoader;
			Asteroid asteroid(Vector2f(40, 40), resourceLoader.GetTexture(ResourceLoader::TextureType::Asteroid), 3);
			Assert::IsTrue(asteroid.Falldown(1080, 2, 2));

		}
		TEST_METHOD(asteroidGetPositionTest)
		{
			ResourceLoader resourceLoader;
			Asteroid asteroid(Vector2f(40, 40), resourceLoader.GetTexture(ResourceLoader::TextureType::Asteroid), 3);
			Assert::AreEqual(sf::Vector2f(40, 40), asteroid.GetPosition());
		}
		TEST_METHOD(presentSpriteTest)
		{
			ResourceLoader resourceLoader;
			Present present(Vector2f(40, 40), resourceLoader.GetTexture(ResourceLoader::TextureType::Gift));
			 sf::Texture presentTexture = present.GetSprite().getTexture();
			Assert::AreEqual(present.GetSprite().getTexture(),presentTexture);
		}
		TEST_METHOD(GetLifeBossTest)
		{
			ResourceLoader resourceLoader;
			resourceLoader.Init1();
			resourceLoader.Init2();

			Boss boss(resourceLoader.GetTexture(ResourceLoader::TextureType::Boss), 10, 50, 50);

			Assert::IsTrue(boss.GetLife() != 0);
		}
	};
}
