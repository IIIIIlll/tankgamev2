#pragma once
#ifndef ROTATION_H
#define ROTATION_H

#include <SDL.h>
// overal rotation
class Rotation {
public:
	Rotation(SDL_Surface* surface, int centerX, int centerY, double angle);
	~Rotation();

	void setAngle(double angle);
	void setCenter(int centerX, int centerY);
	void rotate();

	SDL_Surface* getSurface() const;

private:
	SDL_Surface* surface;
	SDL_Surface* rotatedSurface;
	int centerX;
	int centerY;
	double angle;
};

#endif