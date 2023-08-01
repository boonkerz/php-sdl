#ifndef PHP_SDL_TFT_FONT_H
#define PHP_SDL_TFT_FONT_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "php.h"
#include <SDL_ttf.h>

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_SDL_TTF_OpenFont, 0, 2, TTF_Font, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, size, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(SDL_TTF_OpenFont);

typedef struct TTF_Font
{
	uint height;
    TTF_Font *internal;
    zend_object std;
} php_sdl_ttf_font_object;

php_sdl_ttf_font_object *php_sdl_ttf_font_object_from_zend_object(zend_object *zobj);
zend_object *php_sdl_ttf_font_object_to_zend_object(php_sdl_ttf_font_object *obj);

zend_object *php_ttf_font_object_create(zend_class_entry *ce);

zend_function *php_sdl_ttf_font_object_get_constructor(zend_object *object);
void php_sdl_ttf_font_object_free(zend_object *zobj);

void ttf_font_to_zval(TTF_Font *ttf_font, zval *zp);
TTF_Font *php_ttf_font_from_zval_p(zval *zp);
void php_ttf_font_minit_helper(void);



static const zend_function_entry class_TTF_Font_methods[] = {
	ZEND_FE_END
};



static zend_class_entry *register_class_TTF_Font(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "TTF_Font", class_TTF_Font_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);

	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}



#ifdef  __cplusplus
} // extern "C" 
#endif

#endif /* PHP_SDL_WINDOW_H */
