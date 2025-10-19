#pragma once

#include "../../../sdk/vfunc/vfunc.hpp"

enum render_frame_stage : int
{
	FRAME_NET_UPDATE_POSTDATAUPDATE_START = 2,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_FULL_FRAME_UPDATE_ON_REMOVE,
	FRAME_RENDER_START,
	FRAME_RENDER_END,
	FRAME_NET_UPDATE_END,
	FRAME_NET_CREATION,
	FRAME_RESTORE_SERVER_STATE,
	FRAME_SIMULATE_END
};

class c_local_data
{
public:
	char pad_0000[12]; //0x0000
	vec3_t m_eye_pos; //0x000C
}; //Size: 0x0018

class c_networked_client_info
{
public:
	char pad_0000[4]; //0x0000
	int32_t m_render_tick; //0x0004
	float m_render_tick_fraction; //0x0008
	int32_t m_player_tick_count; //0x000C
	float m_player_tick_fraction; //0x0010
	char pad_0014[4]; //0x0014
	c_local_data* m_local_data; //0x0018
	char pad_0030[24]; //0x0030
}; //Size: 0x0048

class i_engine_client {
public:
	bool is_in_game( ) {
		return vmt::call_virtual<bool>( this, 38 );
	}

	bool is_connected( ) {
		return vmt::call_virtual<bool>( this, 39 );
	}

	int get_local_player_index( ) {
		int idx = -1;

		vmt::call_virtual<void>( this, 53, &idx, 0 );
		return idx + 1;
	}

	c_networked_client_info* get_networked_client_info( ) {
		c_networked_client_info client_info;

		vmt::call_virtual<void*>( this, 179, &client_info );
		return &client_info;
	}
};