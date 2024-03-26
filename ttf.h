#ifndef PHP_SRC_TTF_H
#define PHP_SRC_TTF_H
#include "php.h"
#include <zend_API.h>
#include <SDL3\SDL.h>
#include <SDL3_ttf\SDL_ttf.h>
#include "ttf_font.h"

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_TTF_Init, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_TTF_OpenFont, 0, 2, TTF_Font, 0)
ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_ARG_TYPE_INFO(0, size, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_TTF_Init);
PHP_FUNCTION(SDL_TTF_OpenFont);

PHP_MINIT_FUNCTION(sdl_ttf);
PHP_MSHUTDOWN_FUNCTION(sdl_rect);

#endif //PHP_SRC_TTF_H
