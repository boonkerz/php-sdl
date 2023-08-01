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

	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
		TTF_Font *font = SDLCALL TTF_OpenFont(name, size);
	#else
		TTF_Font *font = TTF_OpenFont(name, size);
	#endif

	ttf_font_to_zval(font, return_value);
}

zend_class_entry *ttf_font_ce = NULL;
zend_object_handlers php_ttf_font_object_handlers;

php_sdl_ttf_font_object *php_sdl_ttf_font_object_from_zend_object(zend_object *zobj)
{
    return ((php_sdl_ttf_font_object *)(zobj + 1)) - 1;
}

zend_object *php_sdl_ttf_font_object_to_zend_object(php_sdl_ttf_font_object *obj)
{
    return ((zend_object *)(obj + 1)) - 1;
}

inline void ttf_font_to_zval(TTF_Font *ttf_font, zval *zp)
{
    object_init_ex(zp, ttf_font_ce);
    zend_update_property_long(ttf_font, Z_OBJ_P(zp), "height", 1, ttf_font->height);
    //php_sdl_ttf_font_object *php_sdl_ttf_font = php_sdl_ttf_font_object_from_zend_object(Z_OBJ_P(zp));
    //php_sdl_ttf_font->internal = ttf_font;
}

TTF_Font *php_ttf_font_from_zval_p(zval *zp)
{
    return php_sdl_ttf_font_object_from_zend_object(Z_OBJ_P(zp))->internal;
}

zend_object *php_ttf_font_object_create(zend_class_entry *ce)
{
    php_sdl_ttf_font_object *obj = zend_object_alloc(sizeof(php_sdl_ttf_font_object), ce);
    zend_object *zobj = php_sdl_ttf_font_object_to_zend_object(obj);

    obj->internal = NULL;
    zend_object_std_init(zobj, ce);
    object_properties_init(zobj, ce);
    zobj->handlers = &php_ttf_font_object_handlers;

    return zobj;
}

void php_sdl_ttf_font_object_free(zend_object *zobj)
{
    php_sdl_ttf_font_object *obj = php_sdl_ttf_font_object_from_zend_object(zobj);

    if (obj->internal)
    {
        // TTF_CloseFont(obj->internal);
        obj->internal = NULL;
    }

    zend_object_std_dtor(zobj);
}

zend_function *php_sdl_ttf_font_object_get_constructor(zend_object *object)
{
    zend_throw_error(NULL, "You cannot initialize a TTF_Font object except through helper functions");
    return NULL;
}


#define REGISTER_FONT_PROP(name) \
	zend_declare_property_long(ttf_font_ce, ZEND_STRL(name), 0, ZEND_ACC_PUBLIC)

void php_ttf_font_minit_helper(void)
{
    ttf_font_ce = register_class_TTF_Font();

    REGISTER_FONT_PROP("height");
    ttf_font_ce->create_object = php_ttf_font_object_create;

    memcpy(&php_ttf_font_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    php_ttf_font_object_handlers.clone_obj = NULL;
    php_ttf_font_object_handlers.free_obj = php_sdl_ttf_font_object_free;
    php_ttf_font_object_handlers.get_constructor = php_sdl_ttf_font_object_get_constructor;
    php_ttf_font_object_handlers.offset = XtOffsetOf(php_sdl_ttf_font_object, std);
}
