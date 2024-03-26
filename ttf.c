#include "php.h"
#include <zend_API.h>
#include <SDL3\SDL.h>
#include <SDL3_ttf\SDL_ttf.h>
#include "ttf.h"
#include "ttf_font.h"

PHP_FUNCTION(SDL_TTF_Init)
{
    ZEND_PARSE_PARAMETERS_NONE();

    RETURN_LONG(TTF_Init());
}

PHP_FUNCTION(SDL_TTF_OpenFont)
{
        char *name;
        size_t name_len;
        zend_long size;

        ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STRING(name, name_len)
        Z_PARAM_LONG(size)
        ZEND_PARSE_PARAMETERS_END();

        TTF_Font *font = TTF_OpenFont(name, size);

        ttf_font_to_zval(font, return_value);
}

PHP_MINIT_FUNCTION(sdl_ttf)
{
    php_ttf_font_minit_helper();
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(sdl_ttf)
{
    return SUCCESS;
}