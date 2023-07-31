#ifndef PHP_SDL_TTF_H
#define PHP_SDL_TTF_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "php_sdl.h"
#include <SDL_ttf.h>

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_TTF_Init, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_SDL_TTF_WasInit arginfo_SDL_TTF_Init

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_TTF_Quit, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

/*

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_TTF_CloseFont, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, font, SDL_TTF_Font, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_TTF_RenderText_Solid, 0, 3, SDL_Surface, 0)
	ZEND_ARG_OBJ_INFO(0, font, SDL_TTF_Font, 0)
	ZEND_ARG_TYPE_INFO(0, text, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, color, SDL_Color, 0)
ZEND_END_ARG_INFO()

#define arginfo_SDL_TTF_RenderText_Blended arginfo_SDL_TTF_RenderText_Solid

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_TTF_RenderText_Shaded, 0, 4, SDL_Surface, 0)
	ZEND_ARG_OBJ_INFO(0, font, SDL_TTF_Font, 0)
	ZEND_ARG_TYPE_INFO(0, text, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, color, SDL_Color, 0)
	ZEND_ARG_OBJ_INFO(0, backgroundColor, SDL_Color, 0)
ZEND_END_ARG_INFO()
*/

ZEND_FUNCTION(SDL_TTF_Init);
ZEND_FUNCTION(SDL_TTF_WasInit);
ZEND_FUNCTION(SDL_TTF_Quit);

/*ZEND_FUNCTION(SDL_TTF_OpenFont);
ZEND_FUNCTION(SDL_TTF_CloseFont);
ZEND_FUNCTION(SDL_TTF_RenderText_Solid);
ZEND_FUNCTION(SDL_TTF_RenderText_Blended);
ZEND_FUNCTION(SDL_TTF_RenderText_Shaded);
*/


#ifdef  __cplusplus
} // extern "C" 
#endif

#endif /* PHP_SDL_TTF_H */