/* sdl_ttf extension for PHP */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "ttf.h"
#include <SDL_ttf.h>

PHP_FUNCTION(SDL_TTF_Init)
{
	ZEND_PARSE_PARAMETERS_NONE();

	RETURN_LONG(TTF_Init());
}

PHP_FUNCTION(SDL_TTF_WasInit)
{
	ZEND_PARSE_PARAMETERS_NONE();

	RETURN_LONG(TTF_WasInit());
}

PHP_FUNCTION(SDL_TTF_Quit)
{
	ZEND_PARSE_PARAMETERS_NONE();

	TTF_Quit();
}