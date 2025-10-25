#pragma once

#include "../../sdk/typedefs/c_color.hpp"

class c_scene_light_object
{
public:
	char pad_0000[ 0xE4 ]; // 0x0
	c_color m_color; // 0xE4
};

class c_aggregate_object_data
{
public:
    char pad_0000[4]; //0x0000
    int count; //0x0004
    char pad_0008[40]; //0x0008
    int index; //0x0030
}; //Size: 0x0034

class c_aggregate_object_array
{
public:
    void* object; //0x0000
    c_aggregate_object_data* data; //0x0008
};

class c_material_2
{
public:
    virtual const char* get_name( ) = 0;
    virtual const char* get_shared_name( ) = 0;
};

class c_scene_object
{
public:
    char pad_0000[ 184 ]; //0x0000
    uint8_t r; //0x00B8
    uint8_t g; //0x00B9
    uint8_t b; //0x00BA
    uint8_t a; //0x00BB
    char pad_00BC[ 196 ]; //0x00BC
}; //Size: 0x0180

class c_base_scene_data
{
public:
    char pad_0000[24]; //0x0000
    c_scene_object* m_scene_object; //0x0018
    c_material_2* m_material; //0x0020
    c_material_2* m_material2; //0x0028
    char pad_0030[32]; //0x0030
    uint8_t r; //0x0040
    uint8_t g; //0x0041
    uint8_t b; //0x0042
    uint8_t a; //0x0043
    char pad_0044[20]; //0x0044
}; //Size: 0x0068