#ifndef PHP_SDL_TTF_FONT_H
#define PHP_SDL_TTF_FONT_H

#include "php.h"
#include <SDL_ttf.h>

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_TTF_OpenFont, 0, 2, TTF_Font, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, size, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(SDL_TTF_OpenFont);

typedef struct
{
    TTF_Font *internal;
    zend_object std;
} php_sdl_ttf_font_object;


php_sdl_ttf_font_object *php_sdl_ttf_font_object_from_zend_object(zend_object *zobj);

void ttf_font_to_zval(TTF_Font *ttf_font, zval *zp);

#endif