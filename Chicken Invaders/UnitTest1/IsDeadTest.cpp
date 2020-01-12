#include "pch.h"
#include "CppUnitTest.h"
#include"../Chicken Invaders/Player.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IsDeadTest
{
	TEST_CLASS(IsDeadTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Player player;
			player.IsDead();
			Assert::AreEqual(player.IsDead(), true);
		}
		TEST_METHOD(TestMethod1)
		{
			Player player;
			player.IsDead();
			Assert::AreEqual(player.IsDead(), false);
		}
		
	};
}
