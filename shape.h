//
// Created by info on 02.03.2024.
//

#ifndef SHAPE_H
#define SHAPE_H
#include "php.h"
#include <zend_API.h>
#include <SDL3\SDL.h>

zend_class_entry *get_php_sdl_windowshapemode_ce(void);
zend_bool sdl_windowshapemode_to_zval(SDL_WindowShapeMode *mode, zval *z_val);
SDL_WindowShapeMode *zval_to_sdl_windowshapemode(zval *z_val);


PHP_MINIT_FUNCTION(sdl_shape);

#endif //SHAPE_H
