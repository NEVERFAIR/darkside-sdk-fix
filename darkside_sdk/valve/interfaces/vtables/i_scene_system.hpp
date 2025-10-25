#pragma once

class c_light_data_queue
{
public:
    char pad_0000[24]; // 0x0000
    void* light_data; // 0x0018
};

class i_scene_system
{
public:
    char pad_0000[10952]; // 0x0000
    c_light_data_queue* light_data_queue; // 0x2AC8
};