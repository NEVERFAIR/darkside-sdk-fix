#pragma once

class i_global_vars
{
public:
	float m_real_time; //0x0000
	int32_t m_frame_count; //0x0004
	float m_absolute_frame_time; //0x0008
	float m_absolute_frame_start_time_std_dev; //0x000C
	int32_t m_max_clients; //0x0010
	int16_t m_tickbase; //0x0014
	char pad_0016[22]; //0x0016
	float m_frame_time; //0x002C
	float m_current_time; //0x0030
	float m_player_time; //0x0034
	char pad_0038[16]; //0x0038
	int32_t m_tick_count; //0x0048
	float m_tick_fraction; //0x004C
	char pad_0050[296]; //0x0050
	char* m_map_name; //0x0178
	char* m_map_name_short; //0x0180
}; //Size: 0x0188