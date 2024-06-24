#ifndef PHP_SDL_VERSION_H
#define PHP_SDL_VERSION_H
#include "php.h"
#include <zend_API.h>
#include <SDL3/SDL_version.h>

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetVersion, 0, 0, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_GetVersion);

PHP_MINIT_FUNCTION(sdl_version);
#endif

