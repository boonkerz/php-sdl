#include "php.h"
#include <zend_API.h>
#include "image.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

extern zend_bool sdl_surface_to_zval(SDL_Surface *surface, zval *z_val);

PHP_FUNCTION(SDL_IMG_Load)
{
    zend_string *file;
    SDL_Surface *surface = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STR(file)
    ZEND_PARSE_PARAMETERS_END();

    surface = IMG_Load(ZSTR_VAL(file));

    if (!surface) {
        RETURN_NULL();
    }

    sdl_surface_to_zval(surface, return_value);
}

PHP_MINIT_FUNCTION(sdl_image)
{

    return SUCCESS;
}


PHP_MSHUTDOWN_FUNCTION(sdl_image)
{
    return SUCCESS;
}
