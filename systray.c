#include "php.h"
#include <zend_API.h>
#include <tray.h>
#include "systray.h"

typedef struct tray tray;

tray trayval = {
    .clicked = "null",
    .tooltip = "null",
    .icon_filepath = ""
};

typedef struct tray_menu_item Tray_Menu_Item;

static zend_class_entry *php_tray_ce;
static zend_object_handlers php_tray_handlers;

struct php_tray
{
    zend_object zo;
};

zend_class_entry *get_php_tray_ce(void)
{
    return php_tray_ce;
}

zend_bool tray_to_zval(tray *tray, zval *value)
{
    if (tray)
    {
        object_init_ex(value, php_tray_ce);
        zend_update_property_string(php_tray_ce, Z_OBJ_P(value), "tooltip", sizeof("tooltip") - 1, tray->tooltip);
        zend_update_property_string(php_tray_ce, Z_OBJ_P(value), "icon_filepath", sizeof("icon_filepath") - 1, tray->icon_filepath);

        return 1;
    }
    ZVAL_NULL(value);
    return 0;
}

zend_bool zval_to_tray(zval *value, tray *tray)
{
    if (instanceof_function(Z_OBJCE_P(value), php_tray_ce))
    {
        zval *val, rv;
        zval *val_icon, rv_icon;

        val = zend_read_property(php_tray_ce, Z_OBJ_P(value), "tooltip", sizeof("tooltip") - 1, 0, &rv);
        convert_to_string(val);
        tray->tooltip = Z_STRVAL_P(val);
        val_icon = zend_read_property(php_tray_ce, Z_OBJ_P(value), "icon_filepath", sizeof("icon_filepath") - 1, 0, &rv_icon);
        convert_to_string(val_icon);
        tray->icon_filepath = Z_STRVAL_P(val_icon);
        tray->clicked = "";
        return 1;
    }
    tray->tooltip = "not set";
    tray->clicked = "";
    memset(tray, 0, sizeof(tray));
    return 0;
}

PHP_METHOD(Tray, __construct)
{
    zend_string *tooltip = zend_string_init("", strlen(""), 0);
    int *tooltip_len;
    zend_string *icon_filepath = zend_string_init("", strlen(""), 0);
    int *icon_filepath_len;
    if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "|ss", &tooltip, &tooltip_len, &icon_filepath, &icon_filepath_len))
    {
        return;
    }

    zend_update_property_string(php_tray_ce, Z_OBJ_P(getThis()), "tooltip", sizeof("tooltip") - 1, tooltip);
    zend_update_property_string(php_tray_ce, Z_OBJ_P(getThis()), "icon_filepath", sizeof("icon_filepath") - 1, icon_filepath);
}

PHP_METHOD(Tray, poll)
{
    /*php_parallel_events_t *events = php_parallel_events_from(getThis());
     *
     *   PARALLEL_PARAMETERS_NONE(return);
     *
     *   php_parallel_events_poll(events, return_value);*/
    tray_loop(0);
    if(trayval.clicked == NULL) {
        RETVAL_NULL();
        return;
    }
    struct tray*tray = tray_get_instance();
    zend_string *clicked = zend_string_init(trayval.clicked, strlen(trayval.clicked), 0);
    RETVAL_STR(clicked);
    tray->clicked = "";
}

PHP_METHOD(Tray, __toString)
{
    tray tray;

    if (zend_parse_parameters_none() == FAILURE)
    {
        return;
    }

    RETVAL_STR(tray.tooltip);
}

/*struct tray tray = {
    .tooltip = "Tray",
    .menu =
    (struct tray_menu_item[]) {
        {.text = "Change Icon"},
        {.text = "Checked", .checked = 1},
        {.text = "Disabled", .disabled = 1},
        {.text = "-"},
        {.text = "SubMenu",
            .submenu =
            (struct tray_menu_item[]) {
                {.text = "FIRST", .checked = 1},
                {.text = "SECOND",
                    .submenu =
                    (struct tray_menu_item[]) {
                        {.text = "THIRD",
                            .submenu =
                            (struct tray_menu_item[]) {
                                {.text = "7"},
                                {.text = "-"},
                                {.text = "8"},
                                {.text = NULL}}},
                                {.text = "FOUR",
                                    .submenu =
                                    (struct tray_menu_item[]) {
                                        {.text = "5"},
                                        {.text = "6"},
                                        {.text = NULL}}},
                                        {.text = NULL}}},
                                        {.text = NULL}}},
                                        {.text = "-"},
                                        {.text = "Quit"},
                                        {.text = NULL}},
};
*/

PHP_METHOD(Tray, init)
{

    zval *z_tray;
    if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_tray, php_tray_ce) == FAILURE)
    {
        return;
    }
    zval_to_tray(z_tray, &trayval);


    RETURN_LONG(tray_init(&trayval));
}

PHP_METHOD(Tray, close)
{

    tray_exit();
}

PHP_MINIT_FUNCTION(systray)
{

    php_tray_ce = register_class_Tray();
    memcpy(&php_tray_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));


    return SUCCESS;
}

