#include "UnitTest++.h"
#include "Block.h"

#include "Clock.h"
#include "SpeedCalculator.h"
#include "IntervalMove.h"
#include "Windows.h"


using namespace volt;


TEST(ObjectDistance) {
	float pixelsPerSecond = 20.0;
	float deltaTime = 1.0f;

	game::SpeedCalculator speedCalculator;
	speedCalculator.SetSpeedY(pixelsPerSecond);
	sf::Vector2f distance = speedCalculator.GetDistanceOverTime(deltaTime);
	
	CHECK_CLOSE(20.0, distance.y, 0.01);
}

TEST(HorizontalMoveExactlyOne) {
	IntervalMove move = IntervalMove(game::Direction::right, 1000);
	move.Start(0);
	int distance = move.DistanceUnitsSinceLastMove(1000);

	CHECK(distance == 1); 
}

TEST(VerticalMoveExactlyOne) {
	IntervalMove move = IntervalMove(game::Direction::top, 1000);
	move.Start(0);

	int distance = move.DistanceUnitsSinceLastMove(1000);
	CHECK(distance == 1);

	distance = move.DistanceUnitsSinceLastMove(1000);
	CHECK(distance == 0);

}

TEST(CheckMultipleMoves) {
	IntervalMove move = IntervalMove(game::Direction::top, 1000);
	move.Start(0);
	
	int distance = move.DistanceUnitsSinceLastMove(4400);
	CHECK(distance == 4);

	distance = move.DistanceUnitsSinceLastMove(5400);
	CHECK(distance == 1);

	distance = move.DistanceUnitsSinceLastMove(6000);
	CHECK(distance == 1);
}

TEST(CheckStartStop) {
	IntervalMove move = IntervalMove(game::Direction::top, 120);
	move.Start(200);

	int distance = move.DistanceUnitsSinceLastMove(800);
	CHECK(distance == 5);

	move.Stop();

	// currently stopped, should not move
	distance = move.DistanceUnitsSinceLastMove(1200);
	CHECK(distance == 0);

	move.Start(1500);

	distance = move.DistanceUnitsSinceLastMove(1750);
	CHECK(distance == 2);

	distance = move.DistanceUnitsSinceLastMove(2150);
	CHECK(distance == 3);

}