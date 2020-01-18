#include "pch.h"
#include "CppUnitTest.h"
#include "..\Chicken Invaders\Bullet.h"
#include "..\Chicken Invaders\Missile.h"
#include "..\Chicken Invaders\Egg.h"
#include "..\Chicken Invaders\ResourceLoader.h"
#include "..\Chicken Invaders\Boss.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework
		{
			template<> inline std::wstring ToString<Bullet>(const class Bullet& t)
			{
				return L"Bullet";
			}
			template<> inline std::wstring ToString<Missile>(const class Missile& t)
			{
				return L"Missile";
			}
			template<> inline std::wstring ToString<Egg>(const class Egg& t)
			{
				return L"Egg";
			}
			template<> inline std::wstring ToString<Boss>(const class Boss& t)
			{
				return L"Boss";
			}
			template<> inline std::wstring ToString<ResourceLoader>(const class ResourceLoader& t)
			{
				return L"ResourceLoader";
			}
		}
	}
}

namespace ChickenInvadersUnitTests
{
	TEST_CLASS(ChickenInvadersUnitTests)
	{
	public:
		
		TEST_METHOD(GetLifeBossTest)
		{
			ResourceLoader resourceLoader;
			resourceLoader.Init1();
			resourceLoader.Init2();

			Boss boss(resourceLoader.GetTexture(ResourceLoader::TextureType::Boss), 10, 50, 50);

			Assert::IsTrue(boss.GetLife() != 0);
		}

		TEST_METHOD(EggFallDown)
		{
			ResourceLoader resourceLoader;
			resourceLoader.Init1();
			resourceLoader.Init2();

			sf::Vector2f initPos(0, 0);

			Egg egg(initPos, resourceLoader.GetTexture(ResourceLoader::TextureType::Egg));

			egg.FallDown(1080);
			Assert::AreNotEqual(initPos, egg.GetPosition());
		}

		TEST_METHOD(MissileMovement)
		{
			ResourceLoader resourceLoader;
			resourceLoader.Init1();
			resourceLoader.Init2();

			sf::Vector2f shipPos(0, 0);

			Missile missile(shipPos.x, shipPos.y, resourceLoader.GetTexture(ResourceLoader::TextureType::Rocket));
			missile.UpdatePosition(shipPos.x);

			Assert::AreNotEqual(missile.GetPosition(), shipPos);
		}

		TEST_METHOD(MissileExplode)
		{
			ResourceLoader resourceLoader;
			resourceLoader.Init1();
			resourceLoader.Init2();

			sf::Vector2f shipPos(960, 540);

			Missile missile(shipPos.x, shipPos.y, resourceLoader.GetTexture(ResourceLoader::TextureType::Rocket));
			missile.UpdatePosition(shipPos.x);

			Assert::IsTrue(missile.ItIsTimeForExplosion());
		}

		TEST_METHOD(BulletPresentCollected)
		{
			ResourceLoader resourceLoader;
			resourceLoader.Init1();
			resourceLoader.Init2();

			sf::Vector2f shipPos(0, 0);

			Bullet bullet(0, 0, resourceLoader.GetTexture(ResourceLoader::TextureType::Bullet));
			bullet.Present_Collected();
			std::vector<std::tuple<int, int, bool>> bullets = bullet.GetBulletsPositionAndState();

			Assert::IsTrue(std::get<2>(bullets[1]));
		}

		TEST_METHOD(BulletResetLevel)
		{
			ResourceLoader resourceLoader;
			resourceLoader.Init1();
			resourceLoader.Init2();

			sf::Vector2f shipPos(0, 0);

			Bullet bullet(0, 0, resourceLoader.GetTexture(ResourceLoader::TextureType::Bullet));
			bullet.Present_Collected();
			bullet.ResetBulletLevel();
			std::vector<std::tuple<int, int, bool>> bullets = bullet.GetBulletsPositionAndState();

			Assert::IsFalse(std::get<2>(bullets[1]));
		}
	};
}
