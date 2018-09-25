/*
 * textcaches.h
 *
 *  Created on: Jun 12, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_TEXTCACHES_H_
#define SOURCE_HEADERS_TEXTCACHES_H_

#include "globals.h"
#include <map>

class Graphics;

class TextCaches{

public:

	TextCaches();

	TextCaches(Graphics &graphics);

	~TextCaches();

	SDL_Texture* getFpsTexture(std::string textToPrint);

private:

	Graphics* _graphicsAssociated;
	TTF_Font* _fpsFont;
	std::map<std::string, SDL_Texture*> _fpsTextures;

};



#endif /* SOURCE_HEADERS_TEXTCACHES_H_ */
