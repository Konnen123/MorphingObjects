#include "Timer.hpp"
#include <SFML/Graphics.hpp>

namespace my
{
void Timer::setTimer(float delay) //timer class to check the keyboard input once
{
	sf::Clock clock;
	sf::Time elapsed1 = clock.getElapsedTime();
	while (elapsed1.asMilliseconds() < delay)
		elapsed1 = clock.getElapsedTime();
}

}