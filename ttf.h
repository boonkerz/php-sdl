#ifndef PHP_SRC_TTF_H
#define PHP_SRC_TTF_H
#include "php.h"
#include <zend_API.h>
#include "ttf_font.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "surface.h"
#include "color.h"

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_TTF_Init, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_TTF_OpenFont, 0, 2, TTF_Font, 0)
ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_ARG_TYPE_INFO(0, size, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_TTF_RenderText_Solid, 0, 3, SDL_Surface, 0)
    ZEND_ARG_OBJ_INFO(0, font, TTF_Font, 0)
    ZEND_ARG_TYPE_INFO(0, text, IS_STRING, 0)
    ZEND_ARG_OBJ_INFO(0, color, SDL_Color, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_TTF_SizeText, 0, 4, 0, 0)
ZEND_ARG_OBJ_INFO(0, font, TTF_Font, 0)
ZEND_ARG_TYPE_INFO(0, text, IS_STRING, 0)
ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_SDL_TTF_RenderText_Blended arginfo_SDL_TTF_RenderText_Solid

PHP_FUNCTION(SDL_TTF_Init);
PHP_FUNCTION(SDL_TTF_OpenFont);
PHP_FUNCTION(SDL_TTF_SizeText);
PHP_FUNCTION(SDL_TTF_RenderText_Blended);

PHP_MINIT_FUNCTION(sdl_ttf);
PHP_MSHUTDOWN_FUNCTION(sdl_ttf);

#endif //PHP_SRC_TTF_H
