#include "php.h"
#include <zend_API.h>
#include <SDL3/SDL.h>
#include "sdl.h"

PHP_FUNCTION(SDL_Init) {
	zend_long z_flags = (zend_long)SDL_INIT_VIDEO;

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(z_flags)
	ZEND_PARSE_PARAMETERS_END();

	Uint32 flags = (Uint32)z_flags;

	RETURN_LONG(SDL_Init(flags));
}

PHP_FUNCTION(SDL_InitSubSystem) {
	zend_long flags;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &flags) == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG(SDL_InitSubSystem((Uint32)flags));
}

PHP_FUNCTION(SDL_Quit)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}

	SDL_Quit();
}

PHP_FUNCTION(SDL_GetError)
{
	const char *error;

	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}

	error = SDL_GetError();
	if (error) {
		RETURN_STRING(error);
	}
}


PHP_FUNCTION(SDL_QuitSubSystem) {
	zend_long flags;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &flags) == FAILURE) {
		RETURN_FALSE;
	}

	SDL_QuitSubSystem((Uint32)flags);
}

PHP_FUNCTION(SDL_WasInit) {
	zend_long flags = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "|l", &flags) == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG(SDL_WasInit((Uint32)flags));
}

PHP_FUNCTION(SDL_SetHint) {
	char *hint;
	size_t hint_len;
	char *value;
	size_t value_len;

	ZEND_PARSE_PARAMETERS_START(2, 2)
	Z_PARAM_STRING(hint, hint_len)
	Z_PARAM_STRING(value, value_len)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG(SDL_SetHint(hint, value) == SDL_TRUE);
}

PHP_MINIT_FUNCTION(sdl_sdl)
{
	REGISTER_LONG_CONSTANT("SDL_INIT_TIMER",           SDL_INIT_TIMER,             CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_INIT_AUDIO",           SDL_INIT_AUDIO,             CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_INIT_VIDEO",           SDL_INIT_VIDEO,             CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_INIT_JOYSTICK",        SDL_INIT_JOYSTICK,          CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_INIT_HAPTIC",          SDL_INIT_HAPTIC,            CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_INIT_GAMEPAD",  	   SDL_INIT_GAMEPAD,           CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_INIT_EVENTS",          SDL_INIT_EVENTS,            CONST_CS | CONST_PERSISTENT);

	return SUCCESS;
}
