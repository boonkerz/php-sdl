#include "php.h"
#include <zend_API.h>
#include <SDL3\SDL.h>
#include <SDL3_ttf\SDL_ttf.h>
#include "ttf.h"
#include "ttf_font.h"

extern zend_class_entry *ttf_font_ce;

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

PHP_FUNCTION(SDL_TTF_RenderText_Blended)
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
    SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);

    sdl_surface_to_zval(surface, return_value);
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