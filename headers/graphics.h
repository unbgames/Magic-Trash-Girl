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
#include "camera.h"


struct SDL_Window;
struct SDL_Renderer;
/*
 *	Classe Graphics:
 *
 * 	Utilizada para a criação da janela e renderer
 *
 *	\ _spriteSheets é o map que guarda os spritesheets já carregados
 *
 */
class Graphics{

public:

	Graphics();

	~Graphics();

	SDL_Surface* loadImage(const std::string &filepath);

	SDL_Texture* loadTexture(const std::string &filePath);

	void blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle, double angle = 0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void flip();

	void clear();

	SDL_Renderer* getRenderer() const;

	Camera camera;

private:

	SDL_Window* _window;
	SDL_Renderer* _renderer;

	std::map<std::string, SDL_Surface*> _spriteSheetsSurfaces;
	std::map<std::string, SDL_Texture*> _spriteSheetsTextures;

};



#endif /* SOURCE_HEADERS_GRAPHICS_H_ */
