#ifndef PHP_SRC_TTF_FONT_H
#define PHP_SRC_TTF_FONT_H
#include "php.h"
#include <zend_API.h>
#include <SDL3\SDL.h>
#include <SDL3_ttf\SDL_ttf.h>

typedef struct _php_tff_font_object
{
    TTF_Font *internal;
    zend_object std;
} php_ttf_font_object;

php_ttf_font_object *php_ttf_font_object_from_zend_object(zend_object *zobj);
zend_object *php_ttf_font_object_to_zend_object(php_ttf_font_object *obj);

TTF_Font *php_ttf_font_from_zval_p(zval *zp);
void ttf_font_to_zval(TTF_Font *ttf_font, zval *zp);
zend_object *php_ttf_font_object_create(zend_class_entry *ce);

void php_ttf_font_object_free(zend_object *zobj);
zend_function *php_ttf_font_object_get_constructor(zend_object *object);

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

#endif //PHP_SRC_TTF_FONT_H
