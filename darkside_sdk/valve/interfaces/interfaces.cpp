#include "interfaces.hpp"
#include "../../darkside.hpp"

#define CHECK(name, arg)										\
    if (arg == nullptr) {										\
        LOG_ERROR( xorstr_( "[-] Failed to get: %s" ), name);	\
																\
        return;													\
    }

void c_interfaces::initialize( ) {
	m_client = get_interface<i_client>( &g_modules->m_modules.client_dll, xorstr_( "Source2Client002" ) );
	m_network_client_service = get_interface<i_network_client_service>( &g_modules->m_modules.engine2_dll, xorstr_( "NetworkClientService_001" ) );
	m_schema_system = get_interface<i_schema_system>( &g_modules->m_modules.schemasystem_dll, xorstr_( "SchemaSystem_001" ) );
	m_input_system = get_interface<void>( &g_modules->m_modules.input_system, xorstr_( "InputSystemVersion001" ) );
	m_engine = get_interface<i_engine_client>( &g_modules->m_modules.engine2_dll, xorstr_( "Source2EngineToClient001" ) );
	m_var = get_interface<i_cvar>( &g_modules->m_modules.tier0_dll, xorstr_( "VEngineCvar007" ) );
	m_localize = get_interface<i_localize>( &g_modules->m_modules.localize_dll, xorstr_( "Localize_001" ) );
	m_file_system = get_interface<i_file_system>( &g_modules->m_modules.filesystem_stdio, xorstr_( "VFileSystem017" ) );

	const char* client_dll = g_modules->m_modules.client_dll.get_name( );

	m_global_vars = *reinterpret_cast<i_global_vars**>( g_opcodes->scan_absolute( client_dll, xorstr_( "48 89 15 ? ? ? ? 48 89 42" ), 0x3 ) );
	CHECK( xorstr_( "Global Vars" ), m_global_vars );

	m_trace = *reinterpret_cast<i_trace**>( g_opcodes->scan_absolute( client_dll, xorstr_( "4C 8B 35 ? ? ? ? 24 ? 0C ? 66 0F 7F 45 ? 88 45 ? 48 8B CB 48 8D 05 ? ? ? ? 89 7D ? 48 89 45 ? 89 7D ? C7 45 ? ? ? ? ? 44 88 7D" ), 0x3 ) );
	CHECK( xorstr_( "Traces" ), m_global_vars );

	m_entity_system = *reinterpret_cast<i_entity_system**>( g_opcodes->scan_absolute( client_dll, xorstr_( "48 8B 0D ? ? ? ? 48 89 7C 24 ? 8B FA C1 EB" ), 0x3 ) );
	CHECK( xorstr_( "Entity" ), m_entity_system );

	using get_input_t = i_csgo_input * ( __fastcall* )( ); // old
	get_input_t get_input = reinterpret_cast<get_input_t>( g_opcodes->scan_absolute( client_dll, xorstr_( "E8 ? ? ? ? 48 8B 56 ? 48 8B C8 E8 ? ? ? ? 4C 89 7E" ), 0x1 ) ); // old

	CHECK( xorstr_( "Input" ), get_input )

	m_csgo_input = get_input( );

	m_mem_alloc = *reinterpret_cast<i_mem_alloc**>( g_opcodes->export_fn( (std::size_t)g_modules->m_modules.tier0_dll.get( ), xorstr_( "g_pMemAlloc" ) ) );
	CHECK( "Mem Alloc", m_mem_alloc );

	m_random_float = reinterpret_cast<decltype( m_random_float )>( g_opcodes->export_fn( (std::size_t)g_modules->m_modules.tier0_dll.get( ), xorstr_( "RandomFloat" ) ) );
	CHECK( "Random Float", m_random_float );

	m_random_seed = reinterpret_cast<decltype( m_random_seed )>( g_opcodes->export_fn( (std::size_t)g_modules->m_modules.tier0_dll.get( ), xorstr_( "RandomSeed" ) ) );
	CHECK( "Random Seed", m_random_seed );
	
	LOG_INFO( xorstr_( "[+] Interfaces initialization completed!" ) );
}