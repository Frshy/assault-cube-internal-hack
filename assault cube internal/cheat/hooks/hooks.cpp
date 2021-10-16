#include "hooks.h"

#include "../ice_hook.h"
#include "../offsets.h"
#include "../engine/entity.h"
#include "../modules/modules.h"

typedef void(__stdcall* twglSwapBuffers)(HDC hdc);
HookSettings wgl_swap_buffers_info;

void __stdcall hwglSwapBuffers(HDC hdc) {
	modules::IniniteHealth();
	modules::Aimbot();

	return reinterpret_cast<twglSwapBuffers>(wgl_swap_buffers_info.gateway)(hdc);
}

void hooks::InitWglSwapBuffers(){
	void* addr = (twglSwapBuffers)(GetProcAddress(GetModuleHandleA("opengl32.dll"), "wglSwapBuffers"));
	
	wgl_swap_buffers_info.src = addr;
	wgl_swap_buffers_info.dst = hwglSwapBuffers;
	wgl_swap_buffers_info.size = 5;

	Hook(wgl_swap_buffers_info);
}

void hooks::UnInitWglSwapBuffers() {
	UnHook(wgl_swap_buffers_info);
}