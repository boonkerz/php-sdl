#include "php.h"
#include <zend_API.h>
#include <SDL3/SDL.h>
#include "iostream.h"

static zend_class_entry *php_sdl_iostream_ce;
static zend_object_handlers php_sdl_iostream_handlers;

struct php_sdl_iostream {
    zend_object   zo;
    SDL_IOStream    *iostream;
    Uint32        flags;
    char         *buf;
};


/* {{{ get_php_sdl_iostream_ce */
zend_class_entry *get_php_sdl_iostream_ce(void)
{
    return php_sdl_iostream_ce;
}
/* }}} */


#define FETCH_IOSTREAM(__ptr, __id, __check) \
{ \
        intern = (struct php_sdl_iostream *)Z_OBJ_P(__id);\
        __ptr = intern->iostream; \
        if (__check && !__ptr) {\
                php_error_docref(NULL, E_WARNING, "Invalid %s object", ZSTR_VAL(intern->zo.ce->name));\
                RETURN_FALSE;\
        }\
}

/* {{{ sdl_rwops_to_zval */
zend_bool sdl_iostream_to_zval(SDL_IOStream *iostream, zval *z_val, Uint32 flags, char *buf)
{
    if (iostream) {
        struct php_sdl_iostream *intern;

        object_init_ex(z_val, php_sdl_iostream_ce);
        intern = (struct php_sdl_iostream *)Z_OBJ_P(z_val);
        intern->iostream = iostream;
        intern->flags = flags;
        intern->buf   = buf;

        return 1;
    }
    ZVAL_NULL(z_val);
    return 0;
}
/* }}} */


/* {{{ zval_to_sdl_iostream */
SDL_IOStream *zval_to_sdl_iostream(zval *z_val)
{
    struct php_sdl_iostream *intern;

    if (Z_TYPE_P(z_val) == IS_OBJECT && Z_OBJCE_P(z_val) == php_sdl_iostream_ce) {
        intern = (struct php_sdl_iostream *)Z_OBJ_P(z_val);
        return intern->iostream;
    }
    return NULL;
}
/* }}} */


/* {{{ php_sdl_iostream_free
	 */
static void php_sdl_iostream_free(zend_object *object)
{
    struct php_sdl_iostream *intern = (struct php_sdl_iostream *) object;

    if (intern->iostream) {
        SDL_CloseIO(intern->iostream);
        if (intern->buf) {
            efree(intern->buf);
        }
    }

    zend_object_std_dtor(&intern->zo);
}
/* }}} */


/* {{{ php_sdl_iostream_new
 */
static zend_object* php_sdl_iostream_new(zend_class_entry *class_type)
{
    struct php_sdl_iostream *intern = NULL;

    intern = ecalloc(1, sizeof(struct php_sdl_iostream) + zend_object_properties_size(class_type));

    zend_object_std_init(&intern->zo, class_type);
    object_properties_init(&intern->zo, class_type);

    intern->iostream = NULL;
    intern->zo.handlers = (zend_object_handlers *) &php_sdl_iostream_handlers;

    return &intern->zo;
}
/* }}} */

/* {{{ php_stream_to_zval_iostream */
void php_stream_to_zval_iostream(php_stream *stream, zval *return_value, int autoclose )
{
    SDL_IOStream *iostream;
    FILE * fp = NULL;

    if (stream == NULL) {
        RETURN_NULL();
    }
    if (autoclose) {
        php_error_docref(NULL, E_NOTICE, "autoclose can raise unsupported error with PHP stream");
    }

    /* Can we get a FILE * */
    if (php_stream_is(stream, PHP_STREAM_IS_STDIO))	{
        if (FAILURE == php_stream_cast(stream, PHP_STREAM_AS_STDIO, (void**)&fp, REPORT_ERRORS)) {
            RETURN_NULL();
        }
        sdl_iostream_to_zval(iostream, return_value, 0, NULL);
    }
}
/* }}} */


/* {{{ sdl_iostream_methods[] */
static const zend_function_entry php_sdl_iostream_methods[] = {

        PHP_FE_END
};
/* }}} */

/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_iostream)
{
        zend_class_entry ce_iostream;

        INIT_CLASS_ENTRY(ce_iostream, "SDL_IOStream", php_sdl_iostream_methods);
        ce_iostream.create_object = php_sdl_iostream_new;
        php_sdl_iostream_ce = zend_register_internal_class(&ce_iostream);
        memcpy(&php_sdl_iostream_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
        php_sdl_iostream_handlers.free_obj = php_sdl_iostream_free;

        zend_declare_property_long(php_sdl_iostream_ce, ZEND_STRL("type"), 0, ZEND_ACC_PUBLIC);

        /* RWops Types */
        /*REGISTER_RWOPS_CLASS_CONST_LONG("UNKNOWN",        SDL_RWOPS_UNKNOWN);
        REGISTER_RWOPS_CLASS_CONST_LONG("WINFILE",        SDL_RWOPS_WINFILE);
        REGISTER_RWOPS_CLASS_CONST_LONG("STDFILE",        SDL_RWOPS_STDFILE);
        REGISTER_RWOPS_CLASS_CONST_LONG("JNIFILE",        SDL_RWOPS_JNIFILE);
        REGISTER_RWOPS_CLASS_CONST_LONG("MEMORY",         SDL_RWOPS_MEMORY);
        REGISTER_RWOPS_CLASS_CONST_LONG("MEMORY_RO",      SDL_RWOPS_MEMORY_RO);

        REGISTER_LONG_CONSTANT("RW_SEEK_SET",    SDL_RW_SEEK_SET, CONST_CS | CONST_PERSISTENT);
        REGISTER_LONG_CONSTANT("RW_SEEK_CUR",    SDL_RW_SEEK_CUR, CONST_CS | CONST_PERSISTENT);
        REGISTER_LONG_CONSTANT("RW_SEEK_END",    SDL_RW_SEEK_END, CONST_CS | CONST_PERSISTENT);
*/
        return SUCCESS;
        }
/* }}} */
