/*
 * graphics.h
 *
 *  Created on: Mar 29, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_GRAPHICS_H_
#define SOURCE_HEADERS_GRAPHICS_H_

#include <map>
#include <string>


struct SDL_Window;
struct SDL_Renderer;

class Graphics{

public:

	Graphics();
	~Graphics();

	SDL_Surface* loadImage(const std::string &filepath);

	void blitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);

	void flip();

	void clear();

	SDL_Renderer* getRenderer() const;

private:

	SDL_Window* _window;
	SDL_Renderer* _renderer;

	std::map<std::string, SDL_Surface*> _spriteSheets;
};



#endif /* SOURCE_HEADERS_GRAPHICS_H_ */
