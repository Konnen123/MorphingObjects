#include "Sound.hpp"
#include "Button.hpp"
#include "ColorSelector.hpp"
#include "Font.hpp"

namespace my
{
sf::SoundBuffer Sound::buffer = sf::SoundBuffer();
sf::Sound Sound::sound = sf::Sound();
bool Sound::isPlaying = false;

void Sound::playSound()
{
	buffer.loadFromFile("sound.ogg");
	sound.setBuffer(buffer);
	sound.play();
}

void Sound::stopSound()
{
	sound.stop();
}

void Sound::toggleSound()
{
	if (isPlaying)
	{
		stopSound();
		isPlaying = false;
	}
	else
	{
		playSound();
		isPlaying = true;
	}
}


}