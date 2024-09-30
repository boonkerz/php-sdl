//
// Created by info on 02.03.2024.
//

#ifndef RECT_H
#define RECT_H
#include "php.h"
#include <zend_API.h>
#include <SDL3/SDL.h>

zend_class_entry *get_php_sdl_point_ce(void);
zend_bool sdl_point_to_zval(SDL_Point *pt, zval *value);
zend_bool zval_to_sdl_point(zval *value, SDL_Point *pt);

zend_class_entry *get_php_sdl_rect_ce(void);
zend_bool sdl_rect_to_zval(SDL_Rect *rect, zval *value);
zend_bool zval_to_sdl_rect(zval *value, SDL_Rect *rect);

zend_class_entry *get_php_sdl_frect_ce(void);
zend_bool zval_to_sdl_frect(zval *value, SDL_FRect *rect);

zend_class_entry *get_php_sdl_fpoint_ce(void);
zend_bool zval_to_sdl_fpoint(zval *value, SDL_FPoint *rect);

PHP_MINIT_FUNCTION(sdl_rect);
PHP_MSHUTDOWN_FUNCTION(sdl_rect);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_PointInRect, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, p, SDL_Point, 0)
	ZEND_ARG_OBJ_INFO(0, r, SDL_Rect, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_RectEmpty, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, r, SDL_Rect, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_RectsEqual, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, a, SDL_Rect, 0)
	ZEND_ARG_OBJ_INFO(0, b, SDL_Rect, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_HasRectIntersection, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, A, SDL_Rect, 0)
	ZEND_ARG_OBJ_INFO(0, B, SDL_Rect, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetRectIntersection, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, A, SDL_Rect, 0)
	ZEND_ARG_OBJ_INFO(0, B, SDL_Rect, 0)
	ZEND_ARG_OBJ_INFO(1, result, SDL_Rect, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetRectUnion, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, A, SDL_Rect, 0)
	ZEND_ARG_OBJ_INFO(0, B, SDL_Rect, 0)
	ZEND_ARG_OBJ_INFO(1, result, SDL_Rect, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_GetRectEnclosingPoints, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, points, SDL_Point, 0)
	ZEND_ARG_TYPE_INFO(0, count, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, clip, SDL_Rect, 0)
	ZEND_ARG_OBJ_INFO(1, result, SDL_Rect, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_FRectEmpty, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, r, SDL_FRect, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_HasRectIntersectionF, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, A, SDL_FRect, 0)
	ZEND_ARG_OBJ_INFO(0, B, SDL_FRect, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_SDL_IntersectFRect, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, A, SDL_FRect, 0)
	ZEND_ARG_OBJ_INFO(0, B, SDL_FRect, 0)
	ZEND_ARG_OBJ_INFO(1, result, SDL_FRect, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_SDL_Point___construct, 0, 0, 2)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_Point___toString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_SDL_Rect___construct, 0, 0, 4)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_SDL_Rect___toString arginfo_class_SDL_Point___toString

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_Rect_Empty, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_Rect_Equal, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, b, SDL_Rect, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_Rect_HasIntersection, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, B, SDL_Rect, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_Rect_Intersect, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, B, SDL_Rect, 0)
	ZEND_ARG_OBJ_INFO(1, result, SDL_Rect, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_Rect_Union, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, B, SDL_Rect, 0)
	ZEND_ARG_OBJ_INFO(1, result, SDL_Rect, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_Rect_IntersectLine, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(1, X1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, Y1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, X2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, Y2, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_SDL_FPoint___construct, 0, 0, 2)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_SDL_FPoint___toString arginfo_class_SDL_Point___toString

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_SDL_FRect___construct, 0, 0, 4)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_SDL_FRect___toString arginfo_class_SDL_Point___toString

#define arginfo_class_SDL_FRect_Empty arginfo_class_SDL_Rect_Empty

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_FRect_HasIntersection, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, B, SDL_FRect, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_FRect_Intersect, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, B, SDL_FRect, 0)
	ZEND_ARG_OBJ_INFO(1, result, SDL_FRect, 1)
ZEND_END_ARG_INFO()


ZEND_FUNCTION(SDL_PointInRect);
ZEND_FUNCTION(SDL_RectEmpty);
ZEND_FUNCTION(SDL_RectsEqual);
ZEND_FUNCTION(SDL_HasRectIntersection);
ZEND_FUNCTION(SDL_GetRectIntersection);
ZEND_FUNCTION(SDL_GetRectUnion);
ZEND_FUNCTION(SDL_GetRectEnclosingPoints);
ZEND_FUNCTION(SDL_FRectEmpty);
ZEND_FUNCTION(SDL_HasRectIntersectionF);
ZEND_FUNCTION(SDL_IntersectFRect);
ZEND_METHOD(SDL_Point, __construct);
ZEND_METHOD(SDL_Point, __toString);
ZEND_METHOD(SDL_Rect, __construct);
ZEND_METHOD(SDL_Rect, __toString);
ZEND_METHOD(SDL_FPoint, __construct);
ZEND_METHOD(SDL_FPoint, __toString);
ZEND_METHOD(SDL_FRect, __construct);
ZEND_METHOD(SDL_FRect, __toString);


static const zend_function_entry ext_functions[] = {
	ZEND_FE(SDL_PointInRect, arginfo_SDL_PointInRect)
	ZEND_FE(SDL_RectEmpty, arginfo_SDL_RectEmpty)
	ZEND_FE(SDL_RectsEqual, arginfo_SDL_RectsEqual)
	ZEND_FE(SDL_HasRectIntersection, arginfo_SDL_HasRectIntersection)
	ZEND_FE(SDL_GetRectIntersection, arginfo_SDL_GetRectIntersection)
	ZEND_FE(SDL_GetRectUnion, arginfo_SDL_GetRectUnion)
	ZEND_FE(SDL_GetRectEnclosingPoints, arginfo_SDL_GetRectEnclosingPoints)
	ZEND_FE(SDL_FRectEmpty, arginfo_SDL_FRectEmpty)
	ZEND_FE(SDL_HasRectIntersectionF, arginfo_SDL_HasRectIntersectionF)
	ZEND_FE(SDL_IntersectFRect, arginfo_SDL_IntersectFRect)
	ZEND_FE_END
};


static const zend_function_entry class_SDL_Point_methods[] = {
	ZEND_ME(SDL_Point, __construct, arginfo_class_SDL_Point___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(SDL_Point, __toString, arginfo_class_SDL_Point___toString, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_SDL_Rect_methods[] = {
	ZEND_ME(SDL_Rect, __construct, arginfo_class_SDL_Rect___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(SDL_Rect, __toString, arginfo_class_SDL_Rect___toString, ZEND_ACC_PUBLIC)
	ZEND_ME_MAPPING(Empty, SDL_RectEmpty, arginfo_class_SDL_Rect_Empty, ZEND_ACC_PUBLIC)
	ZEND_ME_MAPPING(Equal, SDL_RectsEqual, arginfo_class_SDL_Rect_Equal, ZEND_ACC_PUBLIC)
	ZEND_ME_MAPPING(HasIntersection, SDL_HasRectIntersection, arginfo_class_SDL_Rect_HasIntersection, ZEND_ACC_PUBLIC)
	ZEND_ME_MAPPING(Intersect, SDL_GetRectIntersection, arginfo_class_SDL_Rect_Intersect, ZEND_ACC_PUBLIC)
	ZEND_ME_MAPPING(Union, SDL_GetRectUnion, arginfo_class_SDL_Rect_Union, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_SDL_FPoint_methods[] = {
	ZEND_ME(SDL_FPoint, __construct, arginfo_class_SDL_FPoint___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(SDL_FPoint, __toString, arginfo_class_SDL_FPoint___toString, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_SDL_FRect_methods[] = {
	ZEND_ME(SDL_FRect, __construct, arginfo_class_SDL_FRect___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(SDL_FRect, __toString, arginfo_class_SDL_FRect___toString, ZEND_ACC_PUBLIC)
	ZEND_ME_MAPPING(Empty, SDL_FRectEmpty, arginfo_class_SDL_FRect_Empty, ZEND_ACC_PUBLIC)
	ZEND_ME_MAPPING(HasIntersection, SDL_HasRectIntersectionF, arginfo_class_SDL_FRect_HasIntersection, ZEND_ACC_PUBLIC)
	ZEND_ME_MAPPING(Intersect, SDL_IntersectFRect, arginfo_class_SDL_FRect_Intersect, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_SDL_Point(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_Point", class_SDL_Point_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);

	zval property_x_default_value;
	ZVAL_UNDEF(&property_x_default_value);
	zend_string *property_x_name = zend_string_init("x", sizeof("x") - 1, 1);
	zend_declare_typed_property(class_entry, property_x_name, &property_x_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_x_name);

	zval property_y_default_value;
	ZVAL_UNDEF(&property_y_default_value);
	zend_string *property_y_name = zend_string_init("y", sizeof("y") - 1, 1);
	zend_declare_typed_property(class_entry, property_y_name, &property_y_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_y_name);

	return class_entry;
}

static zend_class_entry *register_class_SDL_Rect(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_Rect", class_SDL_Rect_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);

	zval property_x_default_value;
	ZVAL_UNDEF(&property_x_default_value);
	zend_string *property_x_name = zend_string_init("x", sizeof("x") - 1, 1);
	zend_declare_typed_property(class_entry, property_x_name, &property_x_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_x_name);

	zval property_y_default_value;
	ZVAL_UNDEF(&property_y_default_value);
	zend_string *property_y_name = zend_string_init("y", sizeof("y") - 1, 1);
	zend_declare_typed_property(class_entry, property_y_name, &property_y_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_y_name);

	zval property_w_default_value;
	ZVAL_UNDEF(&property_w_default_value);
	zend_string *property_w_name = zend_string_init("w", sizeof("w") - 1, 1);
	zend_declare_typed_property(class_entry, property_w_name, &property_w_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_w_name);

	zval property_h_default_value;
	ZVAL_UNDEF(&property_h_default_value);
	zend_string *property_h_name = zend_string_init("h", sizeof("h") - 1, 1);
	zend_declare_typed_property(class_entry, property_h_name, &property_h_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_h_name);

	return class_entry;
}

static zend_class_entry *register_class_SDL_FPoint(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_FPoint", class_SDL_FPoint_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);

	zval property_x_default_value;
	ZVAL_UNDEF(&property_x_default_value);
	zend_string *property_x_name = zend_string_init("x", sizeof("x") - 1, 1);
	zend_declare_typed_property(class_entry, property_x_name, &property_x_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_x_name);

	zval property_y_default_value;
	ZVAL_UNDEF(&property_y_default_value);
	zend_string *property_y_name = zend_string_init("y", sizeof("y") - 1, 1);
	zend_declare_typed_property(class_entry, property_y_name, &property_y_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_y_name);

	return class_entry;
}

static zend_class_entry *register_class_SDL_FRect(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SDL_FRect", class_SDL_FRect_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);

	zval property_x_default_value;
	ZVAL_UNDEF(&property_x_default_value);
	zend_string *property_x_name = zend_string_init("x", sizeof("x") - 1, 1);
	zend_declare_typed_property(class_entry, property_x_name, &property_x_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_x_name);

	zval property_y_default_value;
	ZVAL_UNDEF(&property_y_default_value);
	zend_string *property_y_name = zend_string_init("y", sizeof("y") - 1, 1);
	zend_declare_typed_property(class_entry, property_y_name, &property_y_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_y_name);

	zval property_w_default_value;
	ZVAL_UNDEF(&property_w_default_value);
	zend_string *property_w_name = zend_string_init("w", sizeof("w") - 1, 1);
	zend_declare_typed_property(class_entry, property_w_name, &property_w_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_w_name);

	zval property_h_default_value;
	ZVAL_UNDEF(&property_h_default_value);
	zend_string *property_h_name = zend_string_init("h", sizeof("h") - 1, 1);
	zend_declare_typed_property(class_entry, property_h_name, &property_h_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_h_name);

	return class_entry;
}

#endif //RECT_H
