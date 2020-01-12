#include "pch.h"
#include "CppUnitTest.h"
#include"../Chicken Invaders/Player.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IsImmortalTest
{
	TEST_CLASS(IsImmortalTest)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Player player;
			player.IsDead();
			Assert::AreEqual(player.IsImmortal(), true);
		}
		TEST_METHOD(TestMethod1)
		{
			Player player;
			player.IsDead();
			Assert::AreEqual(player.IsImmortal(), false);
		}

	};
}
