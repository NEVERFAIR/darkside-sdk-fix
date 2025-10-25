#pragma once
#include "../../../sdk/typedefs/vec_t.hpp"
#include "../../../sdk/vfunc/vfunc.hpp"
#include "../../../utils/utils.hpp"

#include "usercmd.pb.h"
#include "cs_usercmd.pb.h"
#include "network_connection.pb.h"
#include "networkbasetypes.pb.h"

#define	FL_ONGROUND				(1 << 0)
#define FL_DUCKING				(1 << 1)
#define	FL_WATERJUMP			(1 << 3)
#define FL_ONTRAIN				(1 << 4)
#define FL_INRAIN				(1 << 5)
#define FL_FROZEN				(1 << 6)
#define FL_ATCONTROLS			(1 << 7)
#define	FL_CLIENT				(1 << 8)
#define FL_FAKECLIENT			(1 << 9)
#define	FL_INWATER				(1 << 10)
#define FL_HIDEHUD_SCOPE		(1 << 11)

enum e_button : std::uint32_t
{
    IN_ATTACK = (1 << 0),
    IN_JUMP = (1 << 1),
    IN_DUCK = (1 << 2),
    IN_FORWARD = (1 << 3),
    IN_BACK = (1 << 4),
    IN_USE = (1 << 5),
    IN_CANCEL = (1 << 6),
    IN_LEFT = (1 << 7),
    IN_RIGHT = (1 << 8),
    IN_MOVELEFT = (1 << 9),
    IN_MOVERIGHT = (1 << 10),
    IN_ATTACK2 = (1 << 11),
    IN_RUN = (1 << 12),
    IN_RELOAD = (1 << 13),
    IN_LEFT_ALT = (1 << 14),
    IN_RIGHT_ALT = (1 << 15),
    IN_SCORE = (1 << 16),
    IN_SPEED = (1 << 17),
    IN_WALK = (1 << 18),
    IN_ZOOM = (1 << 19),
    IN_FIRST_WEAPON = (1 << 20),
    IN_SECOND_WEAPON = (1 << 21),
    IN_BULLRUSH = (1 << 22),
    IN_FIRST_GRENADE = (1 << 23),
    IN_SECOND_GRENADE = (1 << 24),
    IN_MIDDLE_ATTACK = (1 << 25),
    IN_USE_OR_RELOAD = (1 << 26)
};

class c_in_button_state
{
public:
    void* __vfptr; //0x0000
    uint64_t m_button_state; //0x0008
    uint64_t m_button_state2; //0x0010
    uint64_t m_button_state3; //0x0018
}; //Size: 0x0020
static_assert(sizeof(c_in_button_state) == 0x20);

class c_user_cmd
{
public:
    void* __vfptr;
    int m_command_number;
    CSGOUserCmdPB pb;
    c_in_button_state m_button_state;
    char pad_0068[16];
    int m_has_been_predicted;
    int m_prediction_cmd_type;
    int m_cmd_type;
    int m_cmd_flag;
};

class i_csgo_input
{
public:
    char pad_0000[593]; //0x0000
    bool m_in_third_person; //0x0251
    char pad_0252[6]; //0x0252
    vec3_t m_third_person_angles; //0x0258

    vec3_t get_view_angles()
    {
        using get_view_angles_t = void* (__fastcall*)(i_csgo_input*, int);
        static get_view_angles_t get_view_angles = reinterpret_cast<get_view_angles_t>(g_opcodes->scan(g_modules->m_modules.client_dll.get_name(), "4C 8B C1 85 D2 74 ? 48 8D 05"));

        return *reinterpret_cast<vec3_t*>(get_view_angles(this, 0));
    }

    void set_view_angles(vec3_t& view_angles) 
    {
        using set_view_angles_t = void(__fastcall*)(i_csgo_input*, int, vec3_t&);
        static set_view_angles_t set_view_angles = reinterpret_cast<set_view_angles_t>(g_opcodes->scan(g_modules->m_modules.client_dll.get_name(), "85 D2 75 ? 48 63 81"));

        set_view_angles(this, 0, view_angles);
    }

    c_user_cmd* get_user_cmd(void* local_controller)
    {
        if (!local_controller)
            return nullptr;

        int player_idx = 0;

        using get_entity_index_t = void* (__fastcall*)(void*, int*);
        static get_entity_index_t get_entity_index = reinterpret_cast<get_entity_index_t>(g_opcodes->scan_absolute(g_modules->m_modules.client_dll.get_name(), "E8 ? ? ? ? 8B 8D ? ? ? ? 8D 51", 0x1));

        get_entity_index(local_controller, &player_idx);

        int entity_index = player_idx - 1;
        if (player_idx == -1)
            entity_index = -1;

        static auto construct_input_data = reinterpret_cast<void* (__fastcall*)(void*, int)>(g_opcodes->scan_absolute(g_modules->m_modules.client_dll.get_name(), "E8 ? ? ? ? 48 8B CF 4C 8B F8", 0x1));
        static auto sig_poo = *reinterpret_cast<void**>(g_opcodes->scan_absolute(g_modules->m_modules.client_dll.get_name(), "48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B CF 4C 8B F8", 0x3));

        void* array_inputs = construct_input_data(sig_poo, entity_index);
        int sequence_number = *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(array_inputs) + 0x59A8);

        static auto automake_user_cmd = reinterpret_cast<void*>(g_opcodes->scan_absolute(g_modules->m_modules.client_dll.get_name(), "E8 ? ? ? ? 48 8B 0D ? ? ? ? 45 33 E4 48 89 45", 0x1));
        static auto poo = reinterpret_cast<c_user_cmd * (__fastcall*)(void*, int)>(automake_user_cmd);

        return poo(local_controller, sequence_number);
    }
};