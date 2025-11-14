#include "darkside.hpp"
#include "directx/directx.hpp"
#include "entity_system/entity.hpp"

void destroy(HMODULE h_module) {
    g_hooks->destroy();
    logger::shutdown();
    g_entity_system->level_shutdown();
    FreeConsole();
    // Don't call FreeLibraryAndExitThread in manual-map!
    // Just return.
}

void cheat_main(HMODULE h_module) {
    logger::initialize();
    std::filesystem::create_directory("c:\\airflow\\");
    std::filesystem::create_directory("c:\\airflow\\configs\\");

    g_modules->m_modules.initialize();
    g_interfaces->initialize();
    g_directx->initialize();
    g_hooks->initialize();
    g_config_system->setup_values();
    g_entity_system->initialize();

    LOG_SUCCESS(xorstr_("[*] DarkSide successfully injected!\n"));

    while (!GetAsyncKeyState(VK_END))
        Sleep(100);

    destroy(h_module);
}

// Exported entry point — works with ANY injection
extern "C" __declspec(dllexport)
void __stdcall CheatEntry(HMODULE hModule) {
    // Optional: boost priority
    auto proc = GetCurrentProcess();
    if (GetPriorityClass(proc) < HIGH_PRIORITY_CLASS)
        SetPriorityClass(proc, HIGH_PRIORITY_CLASS);

    CreateThread(nullptr, 0,
        [](LPVOID param) -> DWORD {
            cheat_main((HMODULE)param);
            return 0;
        }, hModule, 0, nullptr);
}

// Optional: keep DllMain for LoadLibrary compatibility
BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        CheatEntry(hModule);  // Reuse same path
    }
    return TRUE;
}
