#include "directx.hpp"
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

LRESULT hk_wnd_proc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {
	ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

	if ( uMsg == WM_KEYUP && wParam == VK_INSERT )
		g_menu->m_opened = !g_menu->m_opened;

	static auto original = hooks::enable_cursor::m_enable_cursor.get_original<decltype( &hooks::enable_cursor::hk_enable_cursor )>( );
	original( g_interfaces->m_input_system, g_menu->m_opened ? false : hooks::enable_cursor::m_enable_cursor_input );

	return CallWindowProc( g_directx->m_window_proc_original, hWnd, uMsg, wParam, lParam );
}
inline IDXGISwapChain* CreateDummySwapChain()
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferCount = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.Width = 1;
	sd.BufferDesc.Height = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = GetForegroundWindow();
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;
	IDXGISwapChain* swapChain = nullptr;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &sd, &swapChain, &device, nullptr, &context);

	if (FAILED(hr))
	{
		return nullptr;
	}

	if (device) device->Release();
	if (context) context->Release();

	return swapChain;
}
void c_directx::initialize( ) {
	m_swap_chain = CreateDummySwapChain();
	if (!m_swap_chain)
		return;

	m_present_address = vmt::get_v_method( m_swap_chain, 8 );
}

void c_directx::unitialize( ) {
	if ( !m_window_proc_original )
		return;

	SetWindowLongPtr( m_window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>( m_window_proc_original ) );
}

std::once_flag init_flag;

void c_directx::start_frame( IDXGISwapChain* swap_chain ) {
	ID3D11Texture2D* back_buffer;
	DXGI_SWAP_CHAIN_DESC desc;
	swap_chain->GetDesc( &desc );

	m_window = desc.OutputWindow;

	std::call_once( init_flag, [&]( )
	{
		swap_chain->GetDevice( __uuidof( ID3D11Device ), reinterpret_cast<void**>( &m_device ) );
		m_device->GetImmediateContext( &m_device_context );
		swap_chain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), reinterpret_cast<void**>( &back_buffer ) );

		m_device->CreateRenderTargetView( back_buffer, nullptr, &m_render_target );

		if ( back_buffer )
			back_buffer->Release( );

		m_window_proc_original = reinterpret_cast<WNDPROC>( SetWindowLongPtr( m_window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>( hk_wnd_proc ) ) );

		ImGui::CreateContext( );
		ImGui_ImplWin32_Init( m_window );
		ImGui_ImplDX11_Init( m_device, m_device_context );

		g_render->initialize( );
	} );
}

void c_directx::new_frame( ) {
	ImGuiIO io = ImGui::GetIO( );

	g_render->update_screen_size( io );

	ImGui_ImplDX11_NewFrame( );
	ImGui_ImplWin32_NewFrame( );
	ImGui::NewFrame( );
}

void c_directx::end_frame( ) {
	ImGui::Render( );

	m_device_context->OMSetRenderTargets( 1, &m_render_target, nullptr );

	ImGui_ImplDX11_RenderDrawData( ImGui::GetDrawData( ) );
}