//
// Created by info on 02.03.2024.
//

#ifndef GLCONTEXT_H
#define GLCONTEXT_H
#include "php.h"
#include <zend_API.h>
#include <SDL3/SDL.h>
zend_class_entry *get_php_sdl_glcontext_ce(void);
zend_bool  sdl_glcontext_to_zval(SDL_GLContext glcontext, zval *z_val, Uint32 flags);
SDL_GLContext zval_to_sdl_glcontext(zval *z_val);

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GLContext, 0, 0, 1)
       ZEND_ARG_OBJ_INFO(0, GLcontext, SDL_GLContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GL_DeleteContext, 0, 0, 1)
       ZEND_ARG_OBJ_INFO(0, GLcontext, SDL_GLContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GL_ExtensionSupported, 0, 0, 1)
       ZEND_ARG_INFO(0, extension)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GL_SetAttribute, 0, 0, 2)
       ZEND_ARG_INFO(0, attr)
       ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GL_GetAttribute, 0, 0, 2)
       ZEND_ARG_INFO(0, attr)
       ZEND_ARG_INFO(1, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GLContext__construct, 0, 0, 1)
       ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GL_MakeCurrent, 0, 0, 1)
       ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
       ZEND_ARG_OBJ_INFO(0, context, SDL_GLContext, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetWindowSizeInPixels, 0, 0, 3)
       ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
       ZEND_ARG_INFO(1, w)
       ZEND_ARG_INFO(1, h)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GL_SetSwapInterval, 0, 0, 1)
       ZEND_ARG_INFO(0, interval)
ZEND_END_ARG_INFO()

/* generic arginfo */

ZEND_BEGIN_ARG_INFO_EX(arginfo_none, 0, 0, 0)
ZEND_END_ARG_INFO()


PHP_FUNCTION(SDL_GL_CreateContext);
PHP_FUNCTION(SDL_GL_MakeCurrent);
PHP_FUNCTION(SDL_GL_GetCurrentWindow);
PHP_FUNCTION(SDL_GetWindowSizeInPixels);
PHP_FUNCTION(SDL_GL_SwapWindow);

PHP_FUNCTION(SDL_GL_ExtensionSupported);
PHP_FUNCTION(SDL_GL_SetAttribute);
PHP_FUNCTION(SDL_GL_GetAttribute);
PHP_FUNCTION(SDL_GL_DeleteContext);
PHP_FUNCTION(SDL_GL_GetCurrentContext);
PHP_FUNCTION(SDL_GL_SetSwapInterval);
PHP_FUNCTION(SDL_GL_GetSwapInterval);
PHP_MINIT_FUNCTION(sdl_glcontext);

#endif //GLCONTEXT_H
