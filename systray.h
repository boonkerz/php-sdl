#ifndef PHP_SYSTRAY_H
#define PHP_SYSTRAY_H
#include "php.h"
#include <zend_API.h>
#include <tray.h>

ZEND_BEGIN_ARG_INFO_EX(arginfo_systray_init, 0, 0, 1)
ZEND_ARG_OBJ_INFO(0, tray, Tray, 0)
ZEND_END_ARG_INFO()

PHP_MINIT_FUNCTION(systray);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Tray___toString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(php_tray_poll_arginfo, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(php_tray_close_arginfo, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(php_tray_init_arginfo, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Tray___construct, 0, 0, 2)
ZEND_ARG_TYPE_INFO(0, tooltip, IS_STRING, 0)
ZEND_ARG_TYPE_INFO(0, icon_filepath, IS_STRING, 0)
ZEND_END_ARG_INFO()


ZEND_METHOD(Tray, __construct);
ZEND_METHOD(Tray, __toString);
ZEND_METHOD(Tray, poll);
ZEND_METHOD(Tray, close);
ZEND_METHOD(Tray, init);

static const zend_function_entry class_Tray_methods[] = {
    ZEND_ME(Tray, __construct, arginfo_class_Tray___construct, ZEND_ACC_PUBLIC)
    ZEND_ME(Tray, __toString, arginfo_class_Tray___toString, ZEND_ACC_PUBLIC)
    ZEND_ME(Tray, poll,         php_tray_poll_arginfo, ZEND_ACC_PUBLIC)
    ZEND_ME(Tray, close,         php_tray_close_arginfo, ZEND_ACC_PUBLIC)
    ZEND_ME(Tray, init,         php_tray_init_arginfo, ZEND_ACC_PUBLIC)
    ZEND_FE_END
};

static zend_class_entry *register_class_Tray(void)
{
    zend_class_entry ce, *class_entry;

    INIT_CLASS_ENTRY(ce, "Tray", class_Tray_methods);
    class_entry = zend_register_internal_class_ex(&ce, NULL);

    zval property_tooltip_default_value;
    ZVAL_STRING(&property_tooltip_default_value, "");
    zend_string *property_tooltip_name = zend_string_init("tooltip", sizeof("tooltip")-1, 1);
    zend_declare_typed_property(class_entry, property_tooltip_name, &property_tooltip_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING));
    zend_string_release(property_tooltip_name);

    zval property_icon_filepath_default_value;
    ZVAL_STRING(&property_icon_filepath_default_value, "");
    zend_string *property_icon_filepath_name = zend_string_init("icon_filepath", sizeof("icon_filepath")-1, 1);
    zend_declare_typed_property(class_entry, property_icon_filepath_name, &property_icon_filepath_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING));
    zend_string_release(property_icon_filepath_name);


    return class_entry;
}


#endif

