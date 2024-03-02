//
// Created by info on 02.03.2024.
//

#ifndef MOUSE_H
#define MOUSE_H
#include "php.h"
#include <zend_API.h>
#include <SDL3\SDL.h>

zend_class_entry *get_php_sdl_cursor_ce(void);
zend_bool sdl_cursor_to_zval(SDL_Cursor *cursor, zval *z_val, Uint32 flags);
SDL_GLContext zval_to_sdl_cursor(zval *z_val);

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_CreateSystemCursor, 0, 0, 1)
       ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_CreateColorCursor, 0, 0, 3)
       ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
       ZEND_ARG_INFO(0, hot_x)
       ZEND_ARG_INFO(0, hot_y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_ShowCursor, 0, 0, 1)
       ZEND_ARG_INFO(0, toggle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetMouseState, 0, 0, 0)
       ZEND_ARG_INFO(1, x)
       ZEND_ARG_INFO(1, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_WarpMouseInWindow, 0, 0, 3)
       ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
       ZEND_ARG_INFO(0, x)
       ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetRelativeMouseMode, 0, 0, 1)
       ZEND_ARG_INFO(0, enabled)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Cursor, 0, 0, 1)
       ZEND_ARG_OBJ_INFO(0, cursor, SDL_Cursor, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Cursor__construct, 0, 0, 6)
       ZEND_ARG_INFO(0, data)
       ZEND_ARG_INFO(0, mask)
       ZEND_ARG_INFO(0, w)
       ZEND_ARG_INFO(0, h)
       ZEND_ARG_INFO(0, hot_x)
       ZEND_ARG_INFO(0, hot_y)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_CreateCursor);
PHP_FUNCTION(SDL_CreateSystemCursor);
PHP_FUNCTION(SDL_CreateColorCursor);
PHP_FUNCTION(SDL_FreeCursor);
PHP_FUNCTION(SDL_SetCursor);
PHP_FUNCTION(SDL_GetCursor);
PHP_FUNCTION(SDL_GetDefaultCursor);
PHP_FUNCTION(SDL_ShowCursor);
PHP_FUNCTION(SDL_GetMouseFocus);
PHP_FUNCTION(SDL_GetMouseState);
PHP_FUNCTION(SDL_GetRelativeMouseState);
PHP_FUNCTION(SDL_WarpMouseInWindow);
PHP_FUNCTION(SDL_SetRelativeMouseMode);
PHP_FUNCTION(SDL_GetRelativeMouseMode);

PHP_MINIT_FUNCTION(sdl_mouse);


#endif //MOUSE_H
