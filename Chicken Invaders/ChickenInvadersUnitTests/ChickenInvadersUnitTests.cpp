#include "pch.h"
#include "CppUnitTest.h"
#include "..\Chicken Invaders\ResourceLoader.h"
#include "..\Chicken Invaders\Boss.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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
	};
}
