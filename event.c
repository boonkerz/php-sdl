//
// Created by info on 03.03.2024.
//
#include "php.h"
#include <zend_API.h>
#include <SDL3/SDL.h>
#include "event.h"
static zend_class_entry *php_sdl_event_ce;
static zend_object_handlers php_sdl_event_handlers;

struct php_sdl_event
{
	zend_object zo;
};

zend_class_entry *get_php_sdl_event_ce(void)
{
	return php_sdl_event_ce;
}

zend_bool sdl_event_to_zval(SDL_Event *event, zval *value)
{
	if (NULL == event)
	{
		ZVAL_NULL(value);
		return 0;
	}
	if (value != NULL)
	{
		zval_ptr_dtor(value);
	}

	object_init_ex(value, php_sdl_event_ce);

	zend_update_property_long(php_sdl_event_ce, Z_OBJ_P(value), ZEND_STRL("type"), event->type);

	switch (event->type)
	{
	case SDL_EVENT_MOUSE_MOTION:
	{
		zval motion;
		object_init(&motion);
		add_property_long(&motion, "state", event->motion.state);
		add_property_long(&motion, "x", event->motion.x);
		add_property_long(&motion, "y", event->motion.y);
		add_property_zval(value, "motion", &motion);
		zval_ptr_dtor(&motion);
	}
	break;
	case SDL_EVENT_MOUSE_BUTTON_DOWN:
	{
		zval button;
		object_init(&button);
		add_property_long(&button, "button", event->button.button);
		add_property_long(&button, "x", event->button.x);
		add_property_long(&button, "y", event->button.y);
		add_property_zval(value, "button", &button);
		zval_ptr_dtor(&button);
	}
	break;
	case SDL_EVENT_KEY_DOWN:
	case SDL_EVENT_KEY_UP:
	{
		zval keysym;
		object_init(&keysym);
		add_property_long(&keysym, "sym", event->key.key);

		zval key;
		object_init(&key);
		add_property_zval(&key, "keysym", &keysym);

		add_property_zval(value, "key", &key);
		zval_ptr_dtor(&key);
		zval_ptr_dtor(&keysym);
	}
	break;
	case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
	{
		zval window;
		object_init(&window);
		//add_property_long(&window, "event", event->window.event);
		add_property_long(&window, "timestamp", event->window.timestamp);
		add_property_long(&window, "windowID", event->window.windowID);
		add_property_long(&window, "data1", event->window.data1);
		add_property_long(&window, "data2", event->window.data2);
		add_property_zval(value, "window", &window);
		zval_ptr_dtor(&window);
	}
	break;
	case SDL_EVENT_JOYSTICK_BUTTON_DOWN:
	case SDL_EVENT_JOYSTICK_BUTTON_UP:
	{
		zval joybutton;
		object_init(&joybutton);
		add_property_long(&joybutton, "type", event->jbutton.type);
		add_property_long(&joybutton, "timestamp", event->jbutton.timestamp);
		add_property_long(&joybutton, "which", event->jbutton.which);
		add_property_long(&joybutton, "button", event->jbutton.button);
		add_property_long(&joybutton, "state", event->jbutton.state);
		add_property_zval(value, "jbutton", &joybutton);
		zval_ptr_dtor(&joybutton);
	}
	break;
	case SDL_EVENT_JOYSTICK_AXIS_MOTION:
	{
		zval jaxis;
		object_init(&jaxis);
		add_property_long(&jaxis, "type", event->jaxis.type);
		add_property_long(&jaxis, "timestamp", event->jaxis.timestamp);
		add_property_long(&jaxis, "which", event->jaxis.which);
		add_property_long(&jaxis, "axis", event->jaxis.axis);
		add_property_long(&jaxis, "value", event->jaxis.value);
		add_property_zval(value, "jaxis", &jaxis);
		zval_ptr_dtor(&jaxis);
	}
	break;
	}

	return 1;
}

zend_bool zval_to_sdl_event(zval *value, SDL_Event *event)
{
	zval *val, rv;

	if (Z_TYPE_P(value) == IS_OBJECT && Z_OBJCE_P(value) == php_sdl_event_ce)
	{
		val = zend_read_property(php_sdl_event_ce, Z_OBJ_P(value), ZEND_STRL("type"), 0, &rv);
		convert_to_long(val);
		Z_LVAL_P(val) = event->type = (int)Z_LVAL_P(val);

		return 1;
	}
	/* creupdate an empty rect */
	memset(event, 0, sizeof(SDL_Event));
	return 0;
}

static PHP_METHOD(SDL_Event, __construct)
{
	zend_error_handling error_handling;

	zend_replace_error_handling(EH_THROW, NULL, &error_handling);
	if (FAILURE == zend_parse_parameters_none())
	{
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);
}

/* {{{ proto SDL_Event::__toString() */
static PHP_METHOD(SDL_Event, __toString)
{
	char *buf;
	size_t buf_len;
	SDL_Event event;

	if (zend_parse_parameters_none() == FAILURE)
	{
		return;
	}

	zval_to_sdl_event(getThis(), &event);
	buf_len = spprintf(&buf, 100, "SDL_Event(type=%d)", event.type);
	RETVAL_STRINGL(buf, buf_len);
	efree(buf);
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_Event___toString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

static HashTable *sdl_event_get_properties(zend_object *object)
{
	HashTable *props;
	props = zend_std_get_properties(object);

	return props;
}

PHP_FUNCTION(SDL_PollEvent)
{
	zval *object;
	SDL_Event event;
	int ret;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "O/", &object, get_php_sdl_event_ce()) == FAILURE)
	{
		return;
	}

	ret = SDL_PollEvent(&event);

	sdl_event_to_zval(&event, object);
	RETURN_LONG(ret);
}

PHP_FUNCTION(SDL_WaitEvent)
{
	zval *object = NULL;
	SDL_Event event;
	int ret;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "O/", &object, get_php_sdl_event_ce()) == FAILURE)
	{
		return;
	}

	ret = SDL_WaitEvent(&event);
	sdl_event_to_zval(&event, object);

	RETURN_LONG(ret);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_none, 0, 0, 0)
ZEND_END_ARG_INFO()

static const zend_function_entry php_sdl_event_methods[] = {
	PHP_ME(SDL_Event, __construct, arginfo_none, ZEND_ACC_CTOR | ZEND_ACC_PUBLIC)
		PHP_ME(SDL_Event, __toString, arginfo_class_SDL_Event___toString, ZEND_ACC_PUBLIC)
			PHP_FE_END};

/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_event)
{
	zend_class_entry ce_event;

	REGISTER_LONG_CONSTANT("SDL_EVENT_QUIT", SDL_EVENT_QUIT, CONST_CS | CONST_PERSISTENT);

	REGISTER_LONG_CONSTANT("SDL_EVENT_TERMINATING", SDL_EVENT_TERMINATING, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_LOW_MEMORY", SDL_EVENT_LOW_MEMORY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WILL_ENTER_BACKGROUND", SDL_EVENT_WILL_ENTER_BACKGROUND, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_DID_ENTER_BACKGROUND", SDL_EVENT_DID_ENTER_BACKGROUND, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WILL_ENTER_FOREGROUND", SDL_EVENT_WILL_ENTER_FOREGROUND, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_DID_ENTER_FOREGROUND", SDL_EVENT_DID_ENTER_FOREGROUND, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_KEY_DOWN", SDL_EVENT_KEY_DOWN, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_KEY_UP", SDL_EVENT_KEY_UP, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_TEXT_EDITING", SDL_EVENT_TEXT_EDITING, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_TEXT_INPUT", SDL_EVENT_TEXT_INPUT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_MOUSE_MOTION", SDL_EVENT_MOUSE_MOTION, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_MOUSE_BUTTON_DOWN", SDL_EVENT_MOUSE_BUTTON_DOWN, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_MOUSE_BUTTON_UP", SDL_EVENT_MOUSE_BUTTON_UP, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_MOUSE_WHEEL", SDL_EVENT_MOUSE_WHEEL, CONST_CS | CONST_PERSISTENT);

	// Joystick
	REGISTER_LONG_CONSTANT("SDL_EVENT_JOYSTICK_AXIS_MOTION", SDL_EVENT_JOYSTICK_AXIS_MOTION, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_JOYSTICK_BUTTON_DOWN", SDL_EVENT_JOYSTICK_BUTTON_DOWN, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_JOYSTICK_BUTTON_UP", SDL_EVENT_JOYSTICK_BUTTON_UP, CONST_CS | CONST_PERSISTENT);

	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_SHOWN", SDL_EVENT_WINDOW_SHOWN, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_HIDDEN", SDL_EVENT_WINDOW_HIDDEN, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_EXPOSED", SDL_EVENT_WINDOW_EXPOSED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_MOVED", SDL_EVENT_WINDOW_MOVED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_RESIZED", SDL_EVENT_WINDOW_RESIZED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED", SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_MINIMIZED", SDL_EVENT_WINDOW_MINIMIZED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_MAXIMIZED", SDL_EVENT_WINDOW_MAXIMIZED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_RESTORED", SDL_EVENT_WINDOW_RESTORED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_ENTER_FULLSCREEN", SDL_EVENT_WINDOW_ENTER_FULLSCREEN, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_LEAVE_FULLSCREEN", SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_FOCUS_GAINED", SDL_EVENT_WINDOW_FOCUS_GAINED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_FOCUS_LOST", SDL_EVENT_WINDOW_FOCUS_LOST, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_CLOSE_REQUESTED", SDL_EVENT_WINDOW_CLOSE_REQUESTED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_EVENT_WINDOW_HIT_TEST", SDL_EVENT_WINDOW_HIT_TEST, CONST_CS | CONST_PERSISTENT);

	INIT_CLASS_ENTRY(ce_event, "SDL_Event", php_sdl_event_methods);
	php_sdl_event_ce = zend_register_internal_class(&ce_event);
	memcpy(&php_sdl_event_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	php_sdl_event_handlers.get_properties = sdl_event_get_properties;
	php_sdl_event_handlers.offset = XtOffsetOf(struct php_sdl_event, zo);

	zend_declare_property_null(php_sdl_event_ce, ZEND_STRL("type"), ZEND_ACC_PUBLIC);
	zend_declare_property_null(php_sdl_event_ce, ZEND_STRL("key"), ZEND_ACC_PUBLIC);
	zend_declare_property_null(php_sdl_event_ce, ZEND_STRL("motion"), ZEND_ACC_PUBLIC);
	zend_declare_property_null(php_sdl_event_ce, ZEND_STRL("window"), ZEND_ACC_PUBLIC);
	zend_declare_property_null(php_sdl_event_ce, ZEND_STRL("button"), ZEND_ACC_PUBLIC);

	return SUCCESS;
}
/* }}} */
