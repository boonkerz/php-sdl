#include "php.h"
#include <zend_API.h>
#include <SDL3/SDL_version.h>
#include "version.h"

PHP_FUNCTION(SDL_GetVersion)
{
	RETURN_LONG(SDL_GetVersion());
}

PHP_MINIT_FUNCTION(sdl_version)
{
	return SUCCESS;
}

