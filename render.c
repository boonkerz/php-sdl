#include "php.h"
#include <zend_API.h>
#include <SDL3/SDL.h>
#include "render.h"
#include "window.h"
#include "surface.h"
#include "pixels.h"
#include "rect.h"

#define SDL_RENDERER_RES_NAME "SDL Renderer"
int le_sdl_renderer;

#define SDL_TEXTURE_RES_NAME "SDL Texture"
int le_sdl_texture;

PHP_FUNCTION(SDL_SetRenderDrawColor)
{
	zval *z_renderer;
	zend_long r, g, b, a;
	SDL_Renderer *renderer;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_ZVAL(z_renderer)
		Z_PARAM_LONG(r)
		Z_PARAM_LONG(g)
		Z_PARAM_LONG(b)
		Z_PARAM_LONG(a)
	ZEND_PARSE_PARAMETERS_END();

    renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);

	RETURN_LONG(SDL_SetRenderDrawColor(renderer, r, g, b, a));
}

PHP_FUNCTION(SDL_RenderClear)
{
	zval *z_renderer;
	SDL_Renderer *renderer;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "z", &z_renderer) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

    renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);

	RETURN_LONG(SDL_RenderClear(renderer));
}

PHP_FUNCTION(SDL_DestroyRenderer)
{
	zval *z_renderer;
	SDL_Renderer *renderer;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "z", &z_renderer) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

    renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);

	SDL_DestroyRenderer(renderer);
}

PHP_FUNCTION(SDL_DestroyTexture)
{
	zval *z_texture;
	SDL_Texture *texture;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "z", &z_texture) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

    texture = (SDL_Texture*)zend_fetch_resource(Z_RES_P(z_texture), SDL_TEXTURE_RES_NAME, le_sdl_texture);

	SDL_DestroyTexture(texture);
}

PHP_FUNCTION(SDL_RenderFillRect)
{
	zval *z_renderer = NULL;
	zval *z_rect = NULL;
	SDL_Rect rect;
	SDL_Renderer *renderer = NULL;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "zO", &z_renderer, &z_rect, get_php_sdl_rect_ce()) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

	zval_to_sdl_rect(z_rect, &rect);

    renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);

	RETURN_LONG(SDL_RenderFillRect(renderer, &rect));
}

PHP_FUNCTION(SDL_RenderRect)
{
	zval *z_renderer = NULL;
	zval *z_rect = NULL;
	SDL_Rect rect;
	SDL_Renderer *renderer = NULL;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "zO", &z_renderer, &z_rect, get_php_sdl_rect_ce()) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

	zval_to_sdl_rect(z_rect, &rect);

	renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);

	RETURN_LONG(SDL_RenderRect(renderer, &rect));
}

PHP_FUNCTION(SDL_RenderLine)
{
	zval *z_renderer = NULL;
	SDL_Renderer *renderer = NULL;
	zend_long x1, y1, x2, y2;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_ZVAL(z_renderer)
		Z_PARAM_LONG(x1)
		Z_PARAM_LONG(y1)
		Z_PARAM_LONG(x2)
		Z_PARAM_LONG(y2)
	ZEND_PARSE_PARAMETERS_END();

	renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);

	RETURN_LONG(SDL_RenderLine(renderer, (int)x1, (int)y1, (int)x2, (int)y2));
}

PHP_FUNCTION(SDL_RenderPresent)
{
	zval *z_renderer;
	SDL_Renderer *renderer;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(z_renderer)
	ZEND_PARSE_PARAMETERS_END();

    renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);

	SDL_RenderPresent(renderer);
}

PHP_FUNCTION(SDL_RenderPoint)
{
	zval *z_renderer = NULL;
	SDL_Renderer *renderer = NULL;
	zend_long x, y;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_ZVAL(z_renderer)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
	ZEND_PARSE_PARAMETERS_END();

    renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);

	RETURN_LONG(SDL_RenderPoint(renderer, (int)x, (int)y));
}

PHP_FUNCTION(SDL_CreateTextureFromSurface)
{
	zval *z_renderer, *z_surface;
	SDL_Renderer *renderer = NULL;
	SDL_Surface *surface = NULL;

	SDL_Texture *texture = NULL;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "zO", &z_renderer, &z_surface, get_php_sdl_surface_ce() ) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

    renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);
	surface = zval_to_sdl_surface(z_surface);

	if( renderer && surface ) {
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		RETURN_RES(zend_register_resource(texture, le_sdl_texture));
	}
}

PHP_FUNCTION(SDL_CreateTexture)
{
	zval *z_renderer;
	zend_long format, access, w, h;
	SDL_Renderer *renderer = NULL;

	SDL_Texture *texture = NULL;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "zllll", &z_renderer, &format, &access, &w, &h ) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

	renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);

	if( renderer ) {
		texture = SDL_CreateTexture(renderer, format, access, w, h);
		RETURN_RES(zend_register_resource(texture, le_sdl_texture));
	}
}

PHP_FUNCTION(SDL_UpdateTexture)
{
	zval *z_texture, *z_rect, *z_pixels;
	zend_long pitch;

	SDL_Rect def_rect;
	SDL_Rect *rect = NULL;
	SDL_Texture *texture = NULL;
	SDL_Pixels *pixels;

	ZEND_PARSE_PARAMETERS_START(4, 4)
	Z_PARAM_ZVAL(z_texture)
	Z_PARAM_OBJECT_OF_CLASS_OR_NULL(z_rect, get_php_sdl_rect_ce())
	Z_PARAM_OBJECT_OF_CLASS(z_pixels, get_php_sdl_pixels_ce())
	Z_PARAM_LONG(pitch)
	ZEND_PARSE_PARAMETERS_END();

	if(z_rect != NULL && Z_TYPE_P(z_rect) != IS_NULL) {
		rect = &def_rect;
		zval_to_sdl_rect(z_rect, rect);
		rect = NULL; 
	}

	if (!(pixels = zval_to_sdl_pixels(z_pixels)))
	{
		php_error_docref(NULL, E_WARNING, "Invalid source SDL_Pixels object");
	}

	texture = (SDL_Texture*)zend_fetch_resource(Z_RES_P(z_texture), SDL_TEXTURE_RES_NAME, le_sdl_texture);

	if( texture ) {
		RETURN_LONG(SDL_UpdateTexture(texture, rect, pixels->pixels, pitch));
	}
}

PHP_FUNCTION(SDL_SetRenderTarget)
{
	zval *z_renderer, *z_texture;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *texture = NULL;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "zz", &z_renderer, &z_texture ) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

	renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);
	texture = (SDL_Texture*)zend_fetch_resource(Z_RES_P(z_texture), SDL_TEXTURE_RES_NAME, le_sdl_texture);

	if( renderer && texture ) {
		RETURN_LONG(SDL_SetRenderTarget(renderer, texture));
	}
}

PHP_FUNCTION(SDL_CreateRenderer)
{
	zend_long index, flags;
	zval *z_window;
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "Oll", &z_window, get_php_sdl_window_ce(), &index, &flags) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

	if( z_window != NULL ) {
		window = zval_to_sdl_window(z_window);
	}

	renderer = SDL_CreateRenderer(window, NULL, flags);
	RETURN_RES(zend_register_resource(renderer, le_sdl_renderer));
}

PHP_FUNCTION(SDL_CreateSoftwareRenderer)
{
	zval *z_surface;
	SDL_Surface *surface = NULL;
	SDL_Renderer *renderer = NULL;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "O", &z_surface, get_php_sdl_surface_ce()) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

	if( z_surface != NULL ) {
		surface = zval_to_sdl_surface(z_surface);
	}

	renderer = SDL_CreateSoftwareRenderer(surface);
	RETURN_RES(zend_register_resource(renderer, le_sdl_renderer));
}

PHP_FUNCTION(SDL_RenderTexture)
{
	zval *z_renderer, *z_texture;
	zval *z_srcrect, *z_dstrect;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *texture = NULL;
	SDL_FRect *srcrect = NULL, *dstrect = NULL;
	SDL_FRect def_srcrect, def_dstrect;

	ZEND_PARSE_PARAMETERS_START(4, 4)
	Z_PARAM_ZVAL(z_renderer)
	Z_PARAM_ZVAL(z_texture)
	Z_PARAM_OBJECT_OF_CLASS_OR_NULL(z_srcrect, get_php_sdl_frect_ce())
	Z_PARAM_OBJECT_OF_CLASS_OR_NULL(z_dstrect, get_php_sdl_frect_ce())
	ZEND_PARSE_PARAMETERS_END();

    renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);
    texture = (SDL_Texture*)zend_fetch_resource(Z_RES_P(z_texture), SDL_TEXTURE_RES_NAME, le_sdl_texture);

	if(z_srcrect != NULL && Z_TYPE_P(z_srcrect) != IS_NULL) {
		srcrect = &def_srcrect;
		zval_to_sdl_frect(z_srcrect, srcrect);
	}
	if(z_dstrect != NULL && Z_TYPE_P(z_dstrect) != IS_NULL) {
		dstrect = &def_dstrect;
		zval_to_sdl_frect(z_dstrect, dstrect);
	}

	RETURN_LONG(SDL_RenderTexture(renderer, texture, srcrect, dstrect));
}

PHP_FUNCTION(SDL_RenderTextureRotated)
{
	zval *z_renderer, *z_texture;
	zval *z_srcrect, *z_dstrect;
	zval *z_center;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *texture = NULL;
	SDL_Rect *srcrect = NULL, *dstrect = NULL;
	SDL_Rect def_srcrect, def_dstrect;
	double angle;
	SDL_Point *center = NULL;
	SDL_Point def_center;
	zend_long flip;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "zzO!O!dO!l", &z_renderer, &z_texture, &z_srcrect, get_php_sdl_rect_ce(), &z_dstrect, get_php_sdl_rect_ce(), &angle, &z_center, get_php_sdl_point_ce(), &flip) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

	renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);
	texture = (SDL_Texture*)zend_fetch_resource(Z_RES_P(z_texture), SDL_TEXTURE_RES_NAME, le_sdl_texture);

	if(z_srcrect != NULL && Z_TYPE_P(z_srcrect) != IS_NULL) {
		srcrect = &def_srcrect;
		zval_to_sdl_rect(z_srcrect, srcrect);
	}
	if(z_dstrect != NULL && Z_TYPE_P(z_dstrect) != IS_NULL) {
		dstrect = &def_dstrect;
		zval_to_sdl_rect(z_dstrect, dstrect);
	}
	if(z_center != NULL && Z_TYPE_P(z_center) != IS_NULL) {
		center = &def_center;
		zval_to_sdl_point(z_center, center);
	}

	RETURN_LONG(SDL_RenderTextureRotated(renderer, texture, srcrect, dstrect, angle, center, (Uint32)flip));
}

PHP_FUNCTION(SDL_SetRenderLogicalPresentation)
{
	zval *z_renderer;
	zend_long w, h;
	SDL_Renderer *renderer;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "zll", &z_renderer, &w, &h) == FAILURE ) {
		WRONG_PARAM_COUNT;
	}

    renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);

	RETURN_LONG(SDL_SetRenderLogicalPresentation(renderer, w, h, SDL_LOGICAL_PRESENTATION_DISABLED, SDL_SCALEMODE_NEAREST));
}

PHP_FUNCTION(SDL_GetCurrentRenderOutputSize)
{
	zval *z_renderer, *z_width=NULL, *z_height=NULL;
	SDL_Renderer *renderer;
	int w, h;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "zz/z/", &z_renderer, &z_width, &z_height) == FAILURE ) {
		return;
	}

	renderer = (SDL_Renderer*)zend_fetch_resource(Z_RES_P(z_renderer), SDL_RENDERER_RES_NAME, le_sdl_renderer);

	SDL_GetCurrentRenderOutputSize(renderer, &w, &h);

	zval_dtor(z_width);
	ZVAL_LONG(z_width, w);
	zval_dtor(z_height);
	ZVAL_LONG(z_height, h);
}

PHP_FUNCTION(SDL_QueryTexture)
{
	zval *z_texture, *z_format = NULL, *z_access = NULL, *z_width = NULL, *z_height = NULL;
	SDL_Texture *texture;
	int w, h, access, result;
	Uint32 format;

	if( zend_parse_parameters(ZEND_NUM_ARGS(), "z|zzzz", &z_texture, &z_format, &z_access, &z_width, &z_height) == FAILURE ) {
		return;
	}

	texture = (SDL_Texture*)zend_fetch_resource(Z_RES_P(z_texture), SDL_TEXTURE_RES_NAME, le_sdl_texture);

	result = SDL_QueryTexture(texture, &format, &access, &w, &h);

	if(z_format)
		ZEND_TRY_ASSIGN_REF_LONG(z_format, format);
	if(z_access)
		ZEND_TRY_ASSIGN_REF_LONG(z_access, access);
	if(z_width)
		ZEND_TRY_ASSIGN_REF_LONG(z_width, w);
	if(z_height)
		ZEND_TRY_ASSIGN_REF_LONG(z_height, h);

	RETURN_LONG(result);
}


/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_render)
{
	REGISTER_LONG_CONSTANT("SDL_RENDERER_SOFTWARE", SDL_RENDERER_SOFTWARE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_RENDERER_ACCELERATED", SDL_RENDERER_ACCELERATED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_RENDERER_PRESENTVSYNC", SDL_RENDERER_PRESENTVSYNC, CONST_CS | CONST_PERSISTENT);

	REGISTER_LONG_CONSTANT("SDL_FLIP_NONE", SDL_FLIP_NONE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_FLIP_HORIZONTAL", SDL_FLIP_HORIZONTAL, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_FLIP_VERTICAL", SDL_FLIP_VERTICAL, CONST_CS | CONST_PERSISTENT);

	REGISTER_LONG_CONSTANT("SDL_TEXTUREACCESS_STATIC", SDL_TEXTUREACCESS_STATIC, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_TEXTUREACCESS_STREAMING", SDL_TEXTUREACCESS_STREAMING, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("SDL_TEXTUREACCESS_TARGET", SDL_TEXTUREACCESS_TARGET, CONST_CS | CONST_PERSISTENT);

	le_sdl_renderer = zend_register_list_destructors_ex(NULL, NULL, SDL_RENDERER_RES_NAME, module_number);
	le_sdl_texture = zend_register_list_destructors_ex(NULL, NULL, SDL_TEXTURE_RES_NAME, module_number);

	return SUCCESS;
}
/* }}} */
