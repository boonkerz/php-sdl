//
// Created by info on 03.03.2024.
//

#ifndef EVENT_H
#define EVENT_H
#include "php.h"
#include <zend_API.h>
#include <SDL3\SDL.h>
zend_class_entry *get_php_sdl_event_ce(void);
zend_bool sdl_event_to_zval(SDL_Event *event, zval *value);
zend_bool zval_to_sdl_event(zval *value, SDL_Event *event);

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_PollEvent, 0, 0, 1)
       ZEND_ARG_OBJ_INFO(1, event, SDL_Event, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_WaitEvent, 0, 0, 1)
       ZEND_ARG_OBJ_INFO(1, event, SDL_Event, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_PollEvent);
PHP_FUNCTION(SDL_WaitEvent);

PHP_MINIT_FUNCTION(sdl_event);

#endif //EVENT_H
