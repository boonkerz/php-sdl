/* sdl_ttf extension for PHP */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "ttf.h"
#include <SDL_ttf.h>

extern zend_class_entry *ttf_font_ce;

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

PHP_FUNCTION(SDL_TTF_RenderText_Solid)
{
	char *text;
	size_t text_len;

	zval *z_font, *z_color;

	ZEND_PARSE_PARAMETERS_START(3, 3)
	Z_PARAM_OBJECT_OF_CLASS(z_font, ttf_font_ce)
	Z_PARAM_STRING(text, text_len)
	Z_PARAM_ZVAL(z_color)
	ZEND_PARSE_PARAMETERS_END();

	TTF_Font *font;
	font = php_ttf_font_from_zval_p(z_font);
	SDL_Color color;
	zval_to_sdl_color(z_color, &color);
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
		SDL_Surface *surface = SDLCALL TTF_RenderText_Solid(font, text, color);
	#else
		SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
	#endif

	sdl_surface_to_zval(surface, return_value);
}