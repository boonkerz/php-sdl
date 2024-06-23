#ifndef PHP_SDL_VERSION_H
#define PHP_SDL_VERSION_H
#include "php.h"
#include <zend_API.h>
#include <SDL3/SDL_version.h>

zend_bool convert_sdl_version_to_php_array(SDL_Version *version, zval *version_array);

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetVersion, 0, 0, 1)
    ZEND_ARG_INFO(1, version)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_GetVersion);

PHP_MINIT_FUNCTION(sdl_version);
#endif

