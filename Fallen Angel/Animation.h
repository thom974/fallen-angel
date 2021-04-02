#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H
#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>

class Animation
{
private:
	int currentFrame;
	std::string currentDirection;
	std::string currentAnimation;
	sf::Texture currentTexture;
	std::unordered_map<std::string, sf::Texture>  frameLibrary;
	std::unordered_map<std::string, std::vector<std::string>> frameCycles;
public:
	Animation();
	int getCurrentFrame();
	void incrementFrame();
	void loadFrames(std::string, std::string, std::vector<int>);
	std::string getTexture();
	void setAnimation(std::string);
	void changeAnimation(std::string);

	void setCurrentFrame(int n)
	{ currentFrame = n; }

	std::string getAnimation()
	{ return currentAnimation; }

	std::unordered_map<std::string, sf::Texture> getLib()
	{ return frameLibrary; }

	std::unordered_map<std::string, std::vector<std::string>> getCyc()
	{ return frameCycles; }
};

#endif