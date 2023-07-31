#include "ttf_font.h"
#include "ttf.h"

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

zend_class_entry *ttf_font_ce = NULL;

php_sdl_ttf_font_object *php_sdl_ttf_font_object_from_zend_object(zend_object *zobj)
{
    return ((php_sdl_ttf_font_object *)(zobj + 1)) - 1;
}

inline void ttf_font_to_zval(TTF_Font *ttf_font, zval *zp)
{
    object_init_ex(zp, ttf_font_ce);
    php_sdl_ttf_font_object *php_sdl_ttf_font = php_sdl_ttf_font_object_from_zend_object(Z_OBJ_P(zp));
    php_sdl_ttf_font->internal = ttf_font;
}