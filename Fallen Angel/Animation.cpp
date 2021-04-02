#include "Animation.h"

// CONSTRUCTOR
Animation::Animation()
{
	currentFrame = 0;
	currentAnimation = "idle";
}

// MEMBER FUNCTIONS 
void Animation::loadFrames(std::string path, std::string aniName, std::vector<int> frameOrder)
{
	for (int i = 0; i < frameOrder.size(); i++)
	{
		// load in frame Textures into unordered map
		std::string frameName = aniName + std::to_string(i);
		sf::Texture frameTexture;
		frameTexture.loadFromFile(path + "/" + frameName + ".png");
		frameLibrary[frameName] = frameTexture;

		// load in the frame cycle, which only contains strings.
		for (int j = 0; j < frameOrder[i]; j++)
		{
			frameCycles[aniName].push_back(aniName + std::to_string(i));
		}
	}
}

void Animation::incrementFrame()
{
	// increment the animation's frame.
	if (currentFrame >= frameCycles[currentAnimation].size() - 1)
	{
		currentFrame = 0;
	}
	else
	{
		currentFrame++;
	}
}

std::string Animation::getTexture()
{
	// get the Texture at which the animation is currently at, corresponding to currentFrame member.
	std::string aniName = frameCycles[currentAnimation][currentFrame];
	return aniName;
}

void Animation::setAnimation(std::string animationType)
{
	currentAnimation = animationType;
}

void Animation::changeAnimation(std::string newAnim)
{
	if (currentAnimation != newAnim)
	{
		currentAnimation = newAnim;
		currentFrame = 0;
	}
}

int Animation::getCurrentFrame()
{ return currentFrame; }