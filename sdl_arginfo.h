#ifndef SDL_ARGINFO_H
#define SDL_ARGINFO_H

#include "version.h"
#include "sdl.h"
#include "messagebox.h"
#include "window.h"
#include "video.h"
#include "glcontext.h"
#include "surface.h"
#include "rect.h"
#include "pixels.h"
#include "mouse.h"
#include "iostream.h"
#include "render.h"
#include "event.h"
#include "ttf_font.h"
#include "ttf.h"

static const zend_function_entry sdl_functions[] = {
    // Core
    ZEND_FE(SDL_Init,						arginfo_SDL_Init)
    ZEND_FE(SDL_InitSubSystem,				arginfo_SDL_InitSubSystem)
    ZEND_FE(SDL_Quit,						arginfo_SDL_Quit)
    ZEND_FE(SDL_QuitSubSystem,				arginfo_SDL_QuitSubSystem)
    ZEND_FE(SDL_WasInit,					arginfo_SDL_WasInit)
    ZEND_FE(SDL_SetHint,					arginfo_SDL_SetHint)

    // TTF
    ZEND_FE(SDL_TTF_Init,					arginfo_SDL_TTF_Init)
    ZEND_FE(SDL_TTF_OpenFont,				arginfo_SDL_TTF_OpenFont)

	// Window
	ZEND_FE(SDL_CreateWindow, arginfo_SDL_CreateWindow)
	ZEND_FE(SDL_CreateShapedWindow, arginfo_SDL_CreateWindow)
	ZEND_FE(SDL_DestroyWindow, arginfo_SDL_Window)
	ZEND_FE(SDL_UpdateWindowSurface, arginfo_SDL_Window)
	ZEND_FE(SDL_GetWindowTitle, arginfo_SDL_Window)
	ZEND_FE(SDL_SetWindowTitle, arginfo_SDL_SetWindowTitle)
	ZEND_FE(SDL_GetDisplayForWindow, arginfo_SDL_Window)
	ZEND_FE(SDL_ShowWindow, arginfo_SDL_Window)
	ZEND_FE(SDL_HideWindow, arginfo_SDL_Window)
	ZEND_FE(SDL_RaiseWindow, arginfo_SDL_Window)
	ZEND_FE(SDL_MaximizeWindow, arginfo_SDL_Window)
	ZEND_FE(SDL_MinimizeWindow, arginfo_SDL_Window)
	ZEND_FE(SDL_RestoreWindow, arginfo_SDL_Window)
	ZEND_FE(SDL_GetWindowSurface, arginfo_SDL_Window)
	ZEND_FE(SDL_SetWindowFullscreenMode, arginfo_SDL_SetWindowFullscreenMode)
	ZEND_FE(SDL_GetWindowFullscreenMode, arginfo_SDL_GetWindowFullscreenMode)
	ZEND_FE(SDL_GetWindowPixelFormat, arginfo_SDL_Window)
	ZEND_FE(SDL_GetWindowID, arginfo_SDL_Window)
	ZEND_FE(SDL_GetWindowFlags, arginfo_SDL_Window)
	ZEND_FE(SDL_SetWindowIcon, arginfo_SDL_SetWindowIcon)
	ZEND_FE(SDL_SetWindowPosition, arginfo_SDL_SetWindowPosition)
	ZEND_FE(SDL_GetWindowPosition, arginfo_SDL_GetWindowPosition)
	ZEND_FE(SDL_SetWindowSize, arginfo_SDL_SetWindowPosition)
	ZEND_FE(SDL_GetWindowSize, arginfo_SDL_GetWindowPosition)
	ZEND_FE(SDL_SetWindowMinimumSize, arginfo_SDL_SetWindowPosition)
	ZEND_FE(SDL_GetWindowMinimumSize, arginfo_SDL_GetWindowPosition)
	ZEND_FE(SDL_SetWindowMaximumSize, arginfo_SDL_SetWindowPosition)
	ZEND_FE(SDL_GetWindowMaximumSize, arginfo_SDL_GetWindowPosition)
	ZEND_FE(SDL_SetWindowBordered, arginfo_SDL_SetWindowBordered)
	ZEND_FE(SDL_SetWindowFullscreen, arginfo_SDL_SetWindowFullscreen)
	ZEND_FE(SDL_UpdateWindowSurfaceRects, arginfo_SDL_UpdateWindowSurfaceRects)
	ZEND_FE(SDL_SetWindowGrab, arginfo_SDL_SetWindowGrab)
	ZEND_FE(SDL_GetWindowGrab, arginfo_SDL_Window)
	//ZEND_FE(SDL_IsShapedWindow, arginfo_SDL_Window)
	//ZEND_FE(SDL_SetWindowShape, arginfo_SDL_SetWindowShape)
	//ZEND_FE(SDL_GetShapedWindowMode, arginfo_SDL_GetShapedWindowMode)

	ZEND_FE(SDL_WINDOWPOS_UNDEFINED_DISPLAY, arginfo_SDL_WINDOWPOS_DISPLAY)
	ZEND_FE(SDL_WINDOWPOS_CENTERED_DISPLAY, arginfo_SDL_WINDOWPOS_DISPLAY)

	// Video
	ZEND_FE(SDL_GetNumVideoDrivers, arginfo_video_none)
	ZEND_FE(SDL_GetVideoDriver, arginfo_SDL_GetVideoDriver)
	ZEND_FE(SDL_GetCurrentVideoDriver, arginfo_video_none)
	ZEND_FE(SDL_GetDisplays, arginfo_video_none)
	ZEND_FE(SDL_GetDisplayName, arginfo_SDL_dysplayindex)
	ZEND_FE(SDL_GetDisplayBounds, arginfo_SDL_GetDisplayBounds)
	ZEND_FE(SDL_GetFullscreenDisplayModes, arginfo_SDL_dysplayindex)
	ZEND_FE(SDL_GetClosestFullscreenDisplayMode, arginfo_SDL_GetClosestFullscreenDisplayMode)
	ZEND_FE(SDL_ScreenSaverEnabled, arginfo_video_none)
	ZEND_FE(SDL_EnableScreenSaver, arginfo_video_none)
	ZEND_FE(SDL_DisableScreenSaver, arginfo_video_none)

	// GL
	ZEND_FE(SDL_GL_ExtensionSupported, arginfo_SDL_GL_ExtensionSupported)
	ZEND_FE(SDL_GL_SetAttribute, arginfo_SDL_GL_SetAttribute)
	ZEND_FE(SDL_GL_GetAttribute, arginfo_SDL_GL_GetAttribute)
	ZEND_FE(SDL_GL_CreateContext, arginfo_SDL_GLContext__construct)
	ZEND_FE(SDL_GL_DeleteContext, arginfo_SDL_GL_DeleteContext)
	ZEND_FE(SDL_GL_MakeCurrent, arginfo_SDL_GL_MakeCurrent)
	ZEND_FE(SDL_GL_GetCurrentWindow, arginfo_none)
	ZEND_FE(SDL_GL_GetCurrentContext, arginfo_none)
	ZEND_FE(SDL_GetWindowSizeInPixels, arginfo_SDL_GetWindowSizeInPixels)
	ZEND_FE(SDL_GL_SwapWindow, arginfo_SDL_Window)
	ZEND_FE(SDL_GL_SetSwapInterval, arginfo_SDL_GL_SetSwapInterval)
	ZEND_FE(SDL_GL_GetSwapInterval, arginfo_none)

	// Mouse/Cursor
	ZEND_FE(SDL_CreateCursor, arginfo_SDL_Cursor__construct)
	ZEND_FE(SDL_CreateSystemCursor, arginfo_SDL_CreateSystemCursor)
	ZEND_FE(SDL_CreateColorCursor, arginfo_SDL_CreateColorCursor)
	ZEND_FE(SDL_DestroyCursor, arginfo_SDL_Cursor)
	ZEND_FE(SDL_SetCursor, arginfo_SDL_Cursor)
	ZEND_FE(SDL_GetCursor, arginfo_none)
	ZEND_FE(SDL_GetDefaultCursor, arginfo_none)
	ZEND_FE(SDL_ShowCursor, arginfo_SDL_ShowCursor)
	ZEND_FE(SDL_GetMouseFocus, arginfo_none)
	ZEND_FE(SDL_GetMouseState, arginfo_SDL_GetMouseState)
	ZEND_FE(SDL_GetRelativeMouseState, arginfo_SDL_GetMouseState)
	ZEND_FE(SDL_WarpMouseInWindow, arginfo_SDL_WarpMouseInWindow)
	ZEND_FE(SDL_SetRelativeMouseMode, arginfo_SDL_SetRelativeMouseMode)
	ZEND_FE(SDL_GetRelativeMouseMode, arginfo_none)

	// Surface
	ZEND_FE(SDL_CreateSurface, arginfo_SDL_CreateSurface)
	ZEND_FE(SDL_DestroySurface, arginfo_SDL_Surface)
	ZEND_FE(SDL_FillSurfaceRect, arginfo_SDL_FillSurfaceRect)
	ZEND_FE(SDL_FillSurfaceRects, arginfo_SDL_FillSurfaceRects)
	ZEND_FE(SDL_MUSTLOCK, arginfo_SDL_Surface)
	ZEND_FE(SDL_LockSurface, arginfo_SDL_Surface)
	ZEND_FE(SDL_UnlockSurface, arginfo_SDL_Surface)
	ZEND_FE(SDL_LoadBMP_RW, arginfo_SDL_LoadBMP_RW)
	ZEND_FE(SDL_LoadBMP, arginfo_SDL_LoadBMP)
	ZEND_FE(SDL_BlitSurface, arginfo_SDL_BlitSurface)
	ZEND_FE(SDL_BlitSurfaceUnchecked, arginfo_SDL_BlitSurfaceUnchecked)
	ZEND_FE(SDL_BlitSurfaceScaled, arginfo_SDL_BlitSurface)
	ZEND_FE(SDL_BlitSurfaceUncheckedScaled, arginfo_SDL_BlitSurfaceUnchecked)
	ZEND_FE(SDL_SoftStretch, arginfo_SDL_BlitSurface)
	ZEND_FE(SDL_SaveBMP_RW, arginfo_SDL_SaveBMP_RW)
	ZEND_FE(SDL_SaveBMP, arginfo_SDL_SaveBMP)
	ZEND_FE(SDL_SetSurfaceRLE, arginfo_SDL_SetSurfaceRLE)
	ZEND_FE(SDL_SetSurfaceColorKey, arginfo_SDL_SetSurfaceColorKey)
	ZEND_FE(SDL_GetSurfaceColorKey, arginfo_SDL_GetSurfaceColorKey)
	ZEND_FE(SDL_SetSurfaceColorMod, arginfo_SDL_SetSurfaceColorMod)
	ZEND_FE(SDL_GetSurfaceColorMod, arginfo_SDL_GetSurfaceColorMod)
	ZEND_FE(SDL_SetSurfaceAlphaMod, arginfo_SDL_SetSurfaceAlphaMod)
	ZEND_FE(SDL_GetSurfaceAlphaMod, arginfo_SDL_GetSurfaceAlphaMod)
	ZEND_FE(SDL_SetSurfaceBlendMode, arginfo_SDL_SetSurfaceBlendMode)
	ZEND_FE(SDL_GetSurfaceBlendMode, arginfo_SDL_GetSurfaceBlendMode)
	ZEND_FE(SDL_SetSurfaceClipRect, arginfo_SDL_SetSurfaceClipRect)
	ZEND_FE(SDL_GetSurfaceClipRect, arginfo_SDL_GetSurfaceClipRect)
	ZEND_FE(SDL_ConvertSurface, arginfo_SDL_ConvertSurface)
	ZEND_FE(SDL_ConvertSurfaceFormat, arginfo_SDL_ConvertSurfaceFormat)
	ZEND_FE(SDL_ConvertPixels, arginfo_SDL_ConvertPixels)

	// Message box
	ZEND_FE(SDL_ShowSimpleMessageBox, arginfo_SDL_ShowSimpleMessageBox)
	ZEND_FE(SDL_ShowMessageBox, arginfo_SDL_ShowMessageBox)

	// Pixels
	ZEND_FE(SDL_GetPixelFormatName, arginfo_SDL_GetPixelFormatName)
	ZEND_FE(SDL_GetMasksForPixelFormatEnum, arginfo_SDL_GetMasksForPixelFormatEnum)
	ZEND_FE(SDL_GetPixelFormatEnumForMasks, arginfo_SDL_GetPixelFormatEnumForMasks)

	ZEND_FE(SDL_CreatePalette, arginfo_SDL_CreatePalette)
	ZEND_FE(SDL_DestroyPalette, arginfo_SDL_Palette)
	ZEND_FE(SDL_SetPaletteColors, arginfo_SDL_SetPaletteColors)

	ZEND_FE(SDL_CreatePixelFormat, arginfo_SDL_CreatePixelFormat)
	ZEND_FE(SDL_DestroyPixelFormat, arginfo_SDL_PixelFormat)
	ZEND_FE(SDL_SetPixelFormatPalette, arginfo_SDL_SetPixelFormatPalette)
	ZEND_FE(SDL_MapRGB, arginfo_SDL_MapRGB)
	ZEND_FE(SDL_MapRGBA, arginfo_SDL_MapRGBA)
	ZEND_FE(SDL_GetRGB, arginfo_SDL_GetRGB)
	ZEND_FE(SDL_GetRGBA, arginfo_SDL_GetRGBA)


	// Render
	ZEND_FE(SDL_CreateRenderer, arginfo_SDL_CreateRenderer)
	ZEND_FE(SDL_CreateSoftwareRenderer, arginfo_SDL_CreateSoftwareRenderer)
	ZEND_FE(SDL_DestroyRenderer, arginfo_SDL_DestroyRenderer)
	ZEND_FE(SDL_DestroyTexture, arginfo_SDL_DestroyTexture)
	ZEND_FE(SDL_SetRenderDrawColor, arginfo_SDL_SetRenderDrawColor)
	ZEND_FE(SDL_RenderPoint, arginfo_SDL_RenderPoint)
	ZEND_FE(SDL_RenderClear, arginfo_SDL_RenderClear)
	ZEND_FE(SDL_RenderTexture, arginfo_SDL_RenderTexture)
	ZEND_FE(SDL_RenderTextureRotated, arginfo_SDL_RenderTextureRotated)
	ZEND_FE(SDL_RenderFillRect, arginfo_SDL_RenderFillRect)
	ZEND_FE(SDL_RenderRect, arginfo_SDL_RenderRect)
	ZEND_FE(SDL_RenderLine, arginfo_SDL_RenderLine)
	ZEND_FE(SDL_RenderPresent, arginfo_SDL_RenderPresent)
	ZEND_FE(SDL_CreateTextureFromSurface, arginfo_SDL_CreateTextureFromSurface)
	ZEND_FE(SDL_CreateTexture, arginfo_SDL_CreateTexture)
	ZEND_FE(SDL_UpdateTexture, arginfo_SDL_UpdateTexture)
	ZEND_FE(SDL_QueryTexture, arginfo_SDL_QueryTexture)
	ZEND_FE(SDL_SetRenderTarget, arginfo_SDL_SetRenderTarget)
	ZEND_FE(SDL_SetRenderLogicalPresentation, arginfo_SDL_SetRenderLogicalPresentation)
	ZEND_FE(SDL_GetCurrentRenderOutputSize, arginfo_SDL_GetCurrentRenderOutputSize)

	// Events
	ZEND_FE(SDL_WaitEvent, arginfo_SDL_WaitEvent)
	ZEND_FE(SDL_PollEvent, arginfo_SDL_PollEvent)

    // Version
    ZEND_FE(SDL_GetVersion, arginfo_SDL_GetVersion)
    PHP_FE_END
};

#endif //SDL_ARGINFO_H
