namespace my
{
class Sound
{
private:
	static sf::SoundBuffer buffer;
	static sf::Sound sound;
	static bool isPlaying;

public:
	static void playSound();
	static void stopSound();
	static void toggleSound();
};
}