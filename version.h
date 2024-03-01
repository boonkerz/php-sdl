#ifndef PHP_SDL_VERSION_H
#define PHP_SDL_VERSION_H
#include "php.h"
#include <zend_API.h>
#include <SDL3\SDL_version.h>

zend_bool convert_sdl_version_to_php_array(SDL_Version *version, zval *version_array);


#endif

