//
// Created by info on 02.03.2024.
//

#ifndef PIXELS_H
#define PIXELS_H
#include "php.h"
#include <zend_API.h>
#include <SDL3/SDL.h>
#include <zend_exceptions.h>
#include "php_sdl.h"
/* PHP specific struct to manage memory access */
typedef struct SDL_Pixels
{
    Uint8 *pixels;
} SDL_Pixels;

zend_class_entry *get_php_sdl_color_ce(void);
zend_bool sdl_color_to_zval(SDL_Color *color, zval *value);
zend_bool zval_to_sdl_color(zval *value, SDL_Color *color);

PHP_MINIT_FUNCTION(sdl_color);

#endif //PIXELS_H
