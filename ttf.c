/* sdl_ttf extension for PHP */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "ttf.h"
#include <SDL_ttf.h>

PHP_FUNCTION(SDL_TTF_Init)
{
	ZEND_PARSE_PARAMETERS_NONE();
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
		RETURN_LONG(SDLCALL TTF_Init());
	#else
		RETURN_LONG(TTF_Init());
	#endif
	
}

PHP_FUNCTION(SDL_TTF_WasInit)
{
	ZEND_PARSE_PARAMETERS_NONE();

	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
		RETURN_LONG(SDLCALL TTF_WasInit());
	#else
		RETURN_LONG(TTF_WasInit());
	#endif
}

PHP_FUNCTION(SDL_TTF_Quit)
{
	ZEND_PARSE_PARAMETERS_NONE();

	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
		SDLCALL TTF_Init();
	#else
		TTF_Quit();
	#endif
}