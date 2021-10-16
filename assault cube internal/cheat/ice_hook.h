#include <Windows.h>
#include <iostream>

struct HookSettings {
	void* src;
	void* dst;
	size_t size;
	void* gateway;
};

static void Hook(HookSettings& hk_settings) {
	auto setup_gateway = [&]() {
		//setting up a gateway
		void* gateway = VirtualAlloc(0, hk_settings.size + 5, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		memcpy(gateway, hk_settings.src, hk_settings.size);

		//setting up jmp that will redirect us to wglSwapBuffers + stolen bytes size and placing it at the end of the gateway
		*(BYTE*)((DWORD_PTR)gateway + hk_settings.size) = 0xE9;
		uintptr_t relative_addr = (uintptr_t)hk_settings.src - (uintptr_t)gateway - 5;
		memcpy((void*)((DWORD_PTR)gateway + hk_settings.size + 1), &relative_addr, 4);

		hk_settings.gateway = gateway;
	};

	auto jmp_to_hooked_func = [&]() {
		//well perfectly, so we have set up an gateway now we have to jmp to our hooked func
		//changing memory protection to EXECUTE_READWRITE because we need it to patch memory in this region
		DWORD old_proc;
		VirtualProtect(hk_settings.src, 5, PAGE_EXECUTE_READWRITE, &old_proc);

		//placing jmp to our hooked func
		*(BYTE*)((DWORD_PTR)hk_settings.src) = 0xE9;
		uintptr_t relative_addr = (uintptr_t)hk_settings.dst - (uintptr_t)hk_settings.src - 5;
		memcpy((void*)((DWORD_PTR)hk_settings.src + 1), &relative_addr, 4);

		//setting memory protection to value it was on start
		VirtualProtect(hk_settings.src, 5, old_proc, &old_proc);
	};

	setup_gateway();
	jmp_to_hooked_func();
}

static void UnHook(HookSettings& hk_settings) {
	//changing memory protection to EXECUTE_READWRITE because we need it to patch memory in this region
	DWORD old_proc;
	VirtualProtect(hk_settings.src, hk_settings.size, PAGE_EXECUTE_READWRITE, &old_proc);

	//setting src bytes to start ones
	memcpy(hk_settings.src, hk_settings.gateway, hk_settings.size);

	//setting memory protection to value it was on start
	VirtualProtect(hk_settings.src, hk_settings.size, old_proc, &old_proc);

	//clearing memory so we dont leave any bytes from gateway
	VirtualFree(hk_settings.gateway, hk_settings.size + 5, MEM_FREE);

	//clearing gateway addr so user wont be confused
	hk_settings.gateway = 0;
}