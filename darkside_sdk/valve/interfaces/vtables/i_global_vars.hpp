#pragma once

class i_global_vars {
public:
public:
    float m_real_time; //0x0000
    int32_t m_frame_count; //0x0004
    float m_absolute_frame_time; //0x0008
    float m_absolute_frame_start_time_std_dev; //0x000C
    int32_t m_max_clients; //0x0010
private:
    char pad_0054[0x1C]; // or 28
public:
    float m_frame_time; //0x0030
    float m_current_time; //0x0034
    float m_player_time; //0x0038
private:
    char pad_0058[0xC];
public:
    int32_t m_tick_count; //0x0048
};