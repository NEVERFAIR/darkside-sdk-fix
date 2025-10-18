#pragma once

#include "../../../sdk/vfunc/vfunc.hpp"

enum EClientFrameStage : int
{
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_FULL_FRAME_UPDATE_ON_REMOVE,
	FRAME_RENDER_START,
	FRAME_RENDER_END,
	FRAME_NET_UPDATE_END,
	FRAME_NET_CREATION,
	FRAME_SIMULATE_END
};

class c_local_data
{
public:
	char pad_0000[8]; //0x0000
	float N0000006F; //0x0008
	vec3_t m_eye_pos; //0x000C
}; //Size: 0x0018

class c_networked_client_info
{
public:
	int32_t unk; //0x0000
	int32_t m_render_tick; //0x0004
	float m_render_tick_fraction; //0x0008
	int32_t m_player_tick_count; //0x000C
	float m_player_tick_fraction; //0x0010
	char pad_0014[4]; //0x0014
	c_local_data* m_local_data; //0x0018
	char pad_0020[32]; //0x0020
}; //Size: 0x0040

class i_engine_client {
public:
	bool is_in_game( ) {
		return vmt::call_virtual<bool>( this, 35 );
	}

	bool is_connected( ) {
		return vmt::call_virtual<bool>( this, 36 );
	}

	int get_local_player_index( ) {
		int idx = -1;

		vmt::call_virtual<void>( this, 49, &idx, 0 );
		return idx + 1;
	}

	c_networked_client_info* get_networked_client_info( ) {
		c_networked_client_info client_info;

		vmt::call_virtual<void*>( this, 178, &client_info );
		return &client_info;
	}
};