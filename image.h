#ifndef PHP_SDL_IMAGE_H
#define PHP_SDL_IMAGE_H
#include "php.h"
#include <zend_API.h>
#include "surface.h"
#include <SDL3/SDL_version.h>

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_IMG_Load, 0, 1, 0)
ZEND_ARG_TYPE_INFO(0, file, IS_STRING, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_IMG_Load);

PHP_MINIT_FUNCTION(sdl_image);
PHP_MSHUTDOWN_FUNCTION(sdl_image);
#endif

