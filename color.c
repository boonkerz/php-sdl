#include "php.h"
#include <zend_API.h>
#include <SDL3/SDL.h>
#include "color.h"
#include "zend_interfaces.h"
#include "zend_operators.h"

static zend_class_entry *php_sdl_color_ce;
static zend_object_handlers php_sdl_color_handlers;
struct php_sdl_color
{
	zend_object zo;
};

zend_class_entry *get_php_sdl_color_ce(void)
{
	return php_sdl_color_ce;
}

zend_bool sdl_color_to_zval(SDL_Color *color, zval *value)
{
	if (color)
	{
		object_init_ex(value, php_sdl_color_ce);
		zend_update_property_long(php_sdl_color_ce, Z_OBJ_P(value), "r", 1, color->r);
		zend_update_property_long(php_sdl_color_ce, Z_OBJ_P(value), "g", 1, color->g);
		zend_update_property_long(php_sdl_color_ce, Z_OBJ_P(value), "b", 1, color->b);
		zend_update_property_long(php_sdl_color_ce, Z_OBJ_P(value), "a", 1, color->a);

		return 1;
	}
	ZVAL_NULL(value);
	return 0;
}

zend_bool zval_to_sdl_color(zval *value, SDL_Color *color)
{
	if (Z_TYPE_P(value) == IS_OBJECT && Z_OBJCE_P(value) == php_sdl_color_ce)
	{
		zval *val, rv;

		val = zend_read_property(php_sdl_color_ce, Z_OBJ_P(value), "r", 1, 0, &rv);
		convert_to_long(val);
		Z_LVAL_P(val) = color->r = (Uint8)Z_LVAL_P(val);

		val = zend_read_property(php_sdl_color_ce, Z_OBJ_P(value), "g", 1, 0, &rv);
		convert_to_long(val);
		Z_LVAL_P(val) = color->g = (Uint8)Z_LVAL_P(val);

		val = zend_read_property(php_sdl_color_ce, Z_OBJ_P(value), "b", 1, 0, &rv);
		convert_to_long(val);
		Z_LVAL_P(val) = color->b = (Uint8)Z_LVAL_P(val);

		val = zend_read_property(php_sdl_color_ce, Z_OBJ_P(value), "a", 1, 0, &rv);
		convert_to_long(val);
		Z_LVAL_P(val) = color->a = (Uint8)Z_LVAL_P(val);

		return 1;
	}
	/* create an empty color */
	memset(color, 0, sizeof(SDL_Color));
	return 0;
}


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Color__construct, 0, 0, 4)
ZEND_ARG_INFO(0, r)
ZEND_ARG_INFO(0, g)
ZEND_ARG_INFO(0, b)
ZEND_ARG_INFO(0, a)
ZEND_END_ARG_INFO()

static PHP_METHOD(SDL_Color, __construct)
{
	zend_long r, g, b, a;
	zend_error_handling error_handling;

	zend_replace_error_handling(EH_THROW, NULL, &error_handling);
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "llll", &r, &g, &b, &a))
	{
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	zend_update_property_long(php_sdl_color_ce, Z_OBJ_P(getThis()), "r", 1, r & 255);
	zend_update_property_long(php_sdl_color_ce, Z_OBJ_P(getThis()), "g", 1, g & 255);
	zend_update_property_long(php_sdl_color_ce, Z_OBJ_P(getThis()), "b", 1, b & 255);
	zend_update_property_long(php_sdl_color_ce, Z_OBJ_P(getThis()), "a", 1, a & 255);
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_Color___toString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

static PHP_METHOD(SDL_Color, __toString)
{
	char *buf;
	SDL_Color color;

	if (zend_parse_parameters_none() == FAILURE)
	{
		return;
	}

	zval_to_sdl_color(getThis(), &color);
	spprintf(&buf, 100, "SDL_Color(%u,%u,%u,%u)", color.r, color.g, color.b, color.a);
	RETVAL_STRING(buf);
}

static const zend_function_entry php_sdl_color_methods[] = {
	PHP_ME(SDL_Color, __construct, arginfo_SDL_Color__construct, ZEND_ACC_CTOR | ZEND_ACC_PUBLIC)
	PHP_ME(SDL_Color, __toString, arginfo_class_SDL_Color___toString, ZEND_ACC_PUBLIC)

			PHP_FE_END};

#define REGISTER_COLOR_PROP(name) \
	zend_declare_property_long(php_sdl_color_ce, ZEND_STRL(name), 0, ZEND_ACC_PUBLIC)


/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_color)
{
	zend_class_entry ce_color, ce_palette, ce_pixelformat, ce_pixels;

	INIT_CLASS_ENTRY(ce_color, "SDL_Color", php_sdl_color_methods);
	php_sdl_color_ce = zend_register_internal_class(&ce_color);
	memcpy(&php_sdl_color_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	REGISTER_COLOR_PROP("r");
	REGISTER_COLOR_PROP("g");
	REGISTER_COLOR_PROP("b");
	REGISTER_COLOR_PROP("a");



	return SUCCESS;
}
/* }}} */
