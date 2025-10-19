#pragma once

#include "../schema/schema.hpp"

#include "../../sdk/typedefs/c_handle.hpp"
#include "../../sdk/typedefs/c_strong_handle.hpp"
#include "../../sdk/typedefs/c_utl_vector.hpp"
#include "../../sdk/typedefs/c_utl_memory.hpp"
#include "../../sdk/typedefs/vec_t.hpp"
#include "../../sdk/typedefs/c_color.hpp"

#include "game_enums.hpp"

class c_utl_binary_block
{
public:
	c_utl_memory<unsigned char> m_Memory;
	int m_nActualLength;
};

class c_quaternion_storage
{
public:
	float x, y, z, w;
};

class CAnimDesc_Flag
{
public:
	bool m_bLooping; // 0x0	
	bool m_bAllZeros; // 0x1	
	bool m_bHidden; // 0x2	
	bool m_bDelta; // 0x3	
	bool m_bLegacyWorldspace; // 0x4	
	bool m_bModelDoc; // 0x5	
	bool m_bImplicitSeqIgnoreDelta; // 0x6	
	bool m_bAnimGraphAdditive; // 0x7	
};

class CAnimBoneDifference
{
public:
	const char* m_name; // 0x0	
	const char* m_parent; // 0x10	
	vec3_t m_posError; // 0x20	
	bool m_bHasRotation; // 0x2c	
	bool m_bHasMovement; // 0x2d	
};

class CAnimMorphDifference
{
public:
	const char* m_name; // 0x0	
};

class CAnimUserDifference
{
public:
	const char* m_name; // 0x0	
	int32_t m_nType; // 0x10	
};

class CAnimEncodeDifference
{
public:
	c_utl_vector< CAnimBoneDifference > m_boneArray; // 0x0	
	c_utl_vector< CAnimMorphDifference > m_morphArray; // 0x18	
	c_utl_vector< CAnimUserDifference > m_userArray; // 0x30	
	c_utl_vector< unsigned char > m_bHasRotationBitArray; // 0x48	
	c_utl_vector< unsigned char > m_bHasMovementBitArray; // 0x60	
	c_utl_vector< unsigned char > m_bHasMorphBitArray; // 0x78	
	c_utl_vector< unsigned char > m_bHasUserBitArray; // 0x90	
};

class CAnimFrameBlockAnim
{
public:
	int32_t m_nStartFrame; // 0x0	
	int32_t m_nEndFrame; // 0x4	
	c_utl_vector< int32_t > m_segmentIndexArray; // 0x8	
};

class CAnimEncodedFrames
{
public:
	const char* m_fileName; // 0x0	
	int32_t m_nFrames; // 0x10	
	int32_t m_nFramesPerBlock; // 0x14	
	c_utl_vector< CAnimFrameBlockAnim > m_frameblockArray; // 0x18	
	// -> m_boneArray - 0x30
	// -> m_morphArray - 0x48
	// -> m_userArray - 0x60
	// -> m_bHasRotationBitArray - 0x78
	// -> m_bHasMovementBitArray - 0x90
	// -> m_bHasMorphBitArray - 0xa8
	// -> m_bHasUserBitArray - 0xc0
	CAnimEncodeDifference m_usageDifferences; // 0x30	
};

class CAnimEventDefinition
{
private:
	[[maybe_unused]] uint8_t __pad0000[0x8]; // 0x0
public:
	int32_t m_nFrame; // 0x8	
	float m_flCycle; // 0xc	
	//KeyValues3 m_EventData; // 0x10	
	// MKV3TransferName "m_sOptions"
	const char* m_sLegacyOptions; // 0x20	
	//CGlobalSymbol m_sEventName; // 0x30	
};

class CAnimMovement
{
public:
	int32_t endframe; // 0x0	
	int32_t motionflags; // 0x4	
	float v0; // 0x8	
	float v1; // 0xc	
	float angle; // 0x10	
	vec3_t vector_; // 0x14	
	vec3_t position; // 0x20	
};

class CAnimLocalHierarchy
{
public:
	const char* m_sBone; // 0x0	
	const char* m_sNewParent; // 0x10	
	int32_t m_nStartFrame; // 0x20	
	int32_t m_nPeakFrame; // 0x24	
	int32_t m_nTailFrame; // 0x28	
	int32_t m_nEndFrame; // 0x2c	
};

class CAnimActivity
{
public:
	const char* m_name; // 0x0	
	int32_t m_nActivity; // 0x10	
	int32_t m_nFlags; // 0x14	
	int32_t m_nWeight; // 0x18	
};

class CAnimSequenceParams
{
public:
	float m_flFadeInTime; // 0x0	
	float m_flFadeOutTime; // 0x4	
};

class CAnimDesc
{
public:
	const char* m_name; // 0x0	
	// -> m_bLooping - 0x10
	// -> m_bAllZeros - 0x11
	// -> m_bHidden - 0x12
	// -> m_bDelta - 0x13
	// -> m_bLegacyWorldspace - 0x14
	// -> m_bModelDoc - 0x15
	// -> m_bImplicitSeqIgnoreDelta - 0x16
	// -> m_bAnimGraphAdditive - 0x17
	CAnimDesc_Flag m_flags; // 0x10	
	float fps; // 0x18	
private:
	[[maybe_unused]] uint8_t __pad001c[0x4]; // 0x1c
public:
	// MKV3TransferName "m_pData"
	// -> m_fileName - 0x20
	// -> m_nFrames - 0x30
	// -> m_nFramesPerBlock - 0x34
	// -> m_frameblockArray - 0x38
	// -> m_usageDifferences - 0x50
	CAnimEncodedFrames m_Data; // 0x20	
	c_utl_vector< CAnimMovement > m_movementArray; // 0xf8	
	c_utl_vector< CAnimEventDefinition > m_eventArray; // 0x110	
	c_utl_vector< CAnimActivity > m_activityArray; // 0x128	
	c_utl_vector< CAnimLocalHierarchy > m_hierarchyArray; // 0x140	
	float framestalltime; // 0x158	
	vec3_t m_vecRootMin; // 0x15c	
	vec3_t m_vecRootMax; // 0x168	
private:
	[[maybe_unused]] uint8_t __pad0174[0x4]; // 0x174
public:
	c_utl_vector< vec3_t > m_vecBoneWorldMin; // 0x178	
	c_utl_vector< vec3_t > m_vecBoneWorldMax; // 0x190	
	// -> m_flFadeInTime - 0x1a8
	// -> m_flFadeOutTime - 0x1ac
	CAnimSequenceParams m_sequenceParams; // 0x1a8	
};

class CAnimDecoder
{
public:
	const char* m_szName; // 0x0	
	int32_t m_nVersion; // 0x10	
	int32_t m_nType; // 0x14	
};

class CAnimFrameSegment
{
public:
	int32_t m_nUniqueFrameIndex; // 0x0	
	uint32_t m_nLocalElementMasks; // 0x4	
	int32_t m_nLocalChannel; // 0x8	
private:
	[[maybe_unused]] uint8_t __pad000c[0x4]; // 0xc
public:
	c_utl_binary_block m_container; // 0x10	
};

class CAnimData
{
private:
	[[maybe_unused]] uint8_t __pad0000[0x10]; // 0x0
public:
	const char* m_name; // 0x10	
	c_utl_vector< CAnimDesc > m_animArray; // 0x20	
	c_utl_vector< CAnimDecoder > m_decoderArray; // 0x38	
	int32_t m_nMaxUniqueFrameIndex; // 0x50	
private:
	[[maybe_unused]] uint8_t __pad0054[0x4]; // 0x54
public:
	c_utl_vector< CAnimFrameSegment > m_segmentArray; // 0x58	
};

struct ModelSkeletonData_t
{
public:
	c_utl_vector< const char* > m_boneName; // 0x0	
	char pad[0x8];
	c_utl_vector< int16_t > m_nParent; // 0x18	
	char pad2[0x8];
	c_utl_vector< float > m_boneSphere; // 0x30	
	char pad3[0x8];
	c_utl_vector< std::uint32_t > m_nFlag; // 0x48	
	char pad4[0x8];
	c_utl_vector< vec3_t > m_bonePosParent; // 0x60	
	char pad5[0x8];
	c_utl_vector< c_quaternion_storage > m_boneRotParent; // 0x78	
	char pad6[0x8];
	c_utl_vector< float > m_boneScaleParent; // 0x90	
	char pad7[0x8];
};

class CModelConfigElement
{
private:
	[[maybe_unused]] uint8_t __pad0000[0x8]; // 0x0
public:
	const char* m_ElementName; // 0x8	
	c_utl_vector< CModelConfigElement* > m_NestedElements; // 0x10	
};

class CModelConfig
{
public:
	const char* m_ConfigName; // 0x0	
	c_utl_vector< CModelConfigElement* > m_Elements; // 0x8	
	bool m_bTopLevel; // 0x20	
};

class CSequenceGroupData
{
public:
	char pad[0x138];
};

class CAnimBone
{
public:
	const char* m_name; // 0x0	
	int32_t m_parent; // 0x10	
	vec3_t m_pos; // 0x14	
	c_quaternion_storage m_quat; // 0x20	
	float m_scale; // 0x30	
	c_quaternion_storage m_qAlignment; // 0x34	
	int32_t m_flags; // 0x44	
};

// Registered binary: animationsystem.dll (project 'animationsystem')
// Alignment: 8
// Size: 0x18
// 
// MGetKV3ClassDefaults
class CAnimUser
{
public:
	const char* m_name; // 0x0	
	int32_t m_nType; // 0x10	
};

class CAnimDataChannelDesc
{
public:
	const char* m_szChannelClass; // 0x0	
	const char* m_szVariableName; // 0x10	
	int32_t m_nFlags; // 0x20	
	int32_t m_nType; // 0x24	
	const char* m_szGrouping; // 0x28	ru-chat
	const char* m_szDescription; // 0x38	
	c_utl_vector< const char* > m_szElementNameArray; // 0x48	
	c_utl_vector< int32_t > m_nElementIndexArray; // 0x60	
	c_utl_vector< uint32_t > m_nElementMaskArray; // 0x78	
};

class CAnimKeyData
{
public:
	const char* m_name; // 0x0	
	c_utl_vector< CAnimBone > m_boneArray; // 0x10	
	c_utl_vector< CAnimUser > m_userArray; // 0x28	
	c_utl_vector< const char* > m_morphArray; // 0x40	
	int32_t m_nChannelElements; // 0x58	
private:
	[[maybe_unused]] uint8_t __pad005c[0x4]; // 0x5c
public:
	c_utl_vector< CAnimDataChannelDesc > m_dataChannelArray; // 0x60	
};

class CAnimationGroup
{
private:
	[[maybe_unused]] uint8_t __pad0000[0x10]; // 0x0
public:
	uint32_t m_nFlags; // 0x10	
private:
	[[maybe_unused]] uint8_t __pad0014[0x4]; // 0x14
public:
	const char* m_name; // 0x18	
private:
	[[maybe_unused]] uint8_t __pad0028[0x38]; // 0x28
public:
	// MKV3TransferName "m_localHAnimArray"
	c_utl_vector< c_strong_handle< CAnimData > > m_localHAnimArray_Handle; // 0x60	
	// MKV3TransferName "m_includedGroupArray"
	c_utl_vector< c_strong_handle< CAnimationGroup > > m_includedGroupArray_Handle; // 0x78	
	// MKV3TransferName "m_directHSeqGroup"
	c_utl_vector<c_strong_handle< CSequenceGroupData >> m_directHSeqGroup_Handle; // 0x90	
	// -> m_name - 0x98
	// -> m_boneArray - 0xa8
	// -> m_userArray - 0xc0
	// -> m_morphArray - 0xd8
	// -> m_nChannelElements - 0xf0
	// -> m_dataChannelArray - 0xf8
	CAnimKeyData m_decodeKey; // 0x98	
	c_utl_vector< const char* > m_szScripts; // 0x110	
};

class c_perm_model_info
{
public:
	uint32_t m_nFlags; // 0x0	
	vec3_t m_vHullMin; // 0x4	
	vec3_t m_vHullMax; // 0x10	
	vec3_t m_vViewMin; // 0x1c	
	vec3_t m_vViewMax; // 0x28	
	float m_flMass; // 0x34	
	vec3_t m_vEyePosition; // 0x38	
	float m_flMaxEyeDeflection; // 0x44	
	const char* m_sSurfaceProperty; // 0x48	
	//const char* m_keyValueText; // 0x50
} /*__attribute((packet))*/;

class c_model;

class c_transform
{
public:
	vec3_t position;
	vec4_t rotate;
	//public:
	//	matrix3x4_t to_matrix();
};

class c_perm_model_ext_part
{
public:
	c_transform m_Transform; // 0x0	
	const char* m_Name; // 0x20	
	int32_t m_nParent; // 0x28	
private:
	[[maybe_unused]] uint8_t __pad002c[0x4]; // 0x2c
public:
	c_strong_handle< c_model > m_refModel; // 0x30	
};

class c_drawcalls
{
public:
	__int32 m_nPrimitiveType; // 0x0000
	__int32 m_nBaseVertex;	  // 0x0004
	__int32 m_nVertexCount;	  // 0x0008
	__int32 m_nStartIndex;	  // 0x000C
	__int32 m_nIndexCount;	  // 0x0010
	float m_flUvDensity;	  // 0x0014
	float m_vTintColor[3];  // 0x0018
	float m_flAlpha;		  // 0x0024
	std::byte pad_0x0028[0xC0]; // 0x0028
};

class c_bones
{
public:
	const char* m_boneName;		   // 0x0000
	const char* m_parentName;	   // 0x0008
	float m_invBindPose[12]; // 0x0010
	vec3_t m_vecCenter;	   // 0x0040
	vec3_t m_vecSize;		   // 0x004C
	float m_flSphereradius;  // 0x0058
	std::byte pad_0x005C[0x4];   // 0x005C
};

class c_attachments
{
public:
	std::byte pad_0x0000[0x10];		  // 0x0000
	const char* m_key;					  // 0x0010
	std::byte pad_0x0018[0x8];		  // 0x0018
	const char* m_name;					  // 0x0020
	const char* m_influenceNames[3];	  // 0x0028
	std::byte pad_0x0030[0x10];		  // 0x0030
	vec4_t m_vInfluenceRotations[3]; // 0x0040
	vec3_t m_vInfluenceOffsets[3];	  // 0x0070
	float m_influenceWeights[3];	  // 0x0094
	std::byte pad_0x00A0[0x10];		  // 0x00A0
};

// big thx to @mmirraacclee
class c_hitbox
{
public:
	char* m_name; //0x0000
	char* m_surface_property; //0x0008
	char* m_bone_name; //0x0010
	vec3_t m_vec_min; //0x0018
	vec3_t m_vec_maxs; //0x0024
	float m_shape_radius; //0x0030
	uint32_t m_bone_hash; //0x0034
	int32_t m_hitgroup; //0x0038
	uint8_t m_shape_type; //0x003C
	bool m_translation_only; //0x003D
	char pad_003E[50]; //0x003E
};

class c_hitboxsets
{
public:
	std::byte pad_0x0000[0x20]; // 0x0000
	uint32_t m_nNameHash;		// 0x0020
	std::byte pad_0x0024[0x4];	// 0x0024
	__int32	m_nHitboxCount;	// 0x0028
	std::byte pad_0x002C[0x4];	// 0x002C
	c_hitbox* m_hitbox;			// 0x0030
	std::byte pad_0x0038[0x18]; // 0x0038
};

class c_rendermesh
{
public:
	char pad_0000[320]; //0x0000
	c_hitboxsets* m_hitboxsets; //0x0118
	int32_t m_nHitboxSets; //0x0120
};

class c_rendermeshes {
public:
	c_rendermesh* m_meshes;
};

class c_perm_model_data
{
public:
	const char* name; //0x0000
	uint32_t flags; //0x0008
	vec3_t hull_min; //0x000C
	vec3_t hull_max; //0x0018
	vec3_t view_min; //0x0024
	vec3_t view_max; //0x0030
	float mass; //0x003C
	vec3_t eye_position; //0x0040
	float max_eye_deflection; //0x004C
	char* surface_property; //0x0050
	c_utl_vector<c_perm_model_ext_part> ext_parts;
	c_utl_vector<c_rendermesh*>  ref_meshes;
	char pad2[0x8];
	c_utl_vector<uint64_t> mesh_group_mask;
	char pad3[0x8];
	c_utl_vector<uint64_t> phys_group_mask;
	char pad5[0x30];
	c_utl_vector<void*> anim_groups; // 0x120  
	char pad9[0x70];
	ModelSkeletonData_t model_skeleton; // 0x188  
};

class c_model
{
public:
	void* vtable;
	c_perm_model_data perm_model_data;

	c_hitbox* get_hitbox(int index)
	{
		auto model_data = &perm_model_data;

		if (perm_model_data.ref_meshes.m_size <= 0)
			return nullptr;

		auto mesh = perm_model_data.ref_meshes.element(0);
		if (!mesh)
			return nullptr;

		auto hitboxsets = mesh->m_hitboxsets;
		if (!hitboxsets)
			return nullptr;

		if (hitboxsets->m_nHitboxCount <= 0 || index > hitboxsets->m_nHitboxCount)
			return nullptr;

		auto& hitbox = hitboxsets->m_hitbox;
		return &hitbox[index];
	}

	const char* get_bone_name(int index)
	{
		if (perm_model_data.model_skeleton.m_boneName.count() <= 0 || perm_model_data.model_skeleton.m_boneName.count() > index)
			return "root";

		return perm_model_data.model_skeleton.m_boneName.element(index);
	}

	const char* get_hitbox_name(int index)
	{
		auto hitbox = get_hitbox(index);

		if (!hitbox)
			return nullptr;

		return hitbox->m_name;
	}
	int get_max_hitboxes()
	{
		if (perm_model_data.ref_meshes.count() <= 0)
			return -1;

		auto meshes = perm_model_data.ref_meshes.element(0);
		if (!meshes)
			return -1;

		auto hithoxsets = meshes->m_hitboxsets;
		if (!hithoxsets)
			return -1;

		return hithoxsets[0].m_nHitboxCount;
	}

	uint32_t get_hitboxes_num()
	{
		using fnHitboxNum = uint32_t(__fastcall*)(void*);
		static auto HitboxNum = reinterpret_cast<fnHitboxNum>(g_opcodes->scan_absolute(g_modules->m_modules.client_dll.get_name(), "E8 ? ? ? ? 85 C0 7E ? 83 7F 20 00", 0x1));

		return HitboxNum(this);
	}

	uint32_t get_bone_flags(std::uint32_t index)
	{
		static auto fn = reinterpret_cast<uint32_t(__fastcall*)(void*, uint32_t)>(g_opcodes->scan(g_modules->m_modules.client_dll.get_name(), "85 D2 78 ? 3B 91 ? ? ? ? 7D ? 48 8B 81 ? ? ? ? 48 63 D2 8B 04 90"));

		return fn(this, index);
	}

	std::int32_t get_bone_parent(std::uint32_t index)
	{
		static auto fn = reinterpret_cast<uint32_t(__fastcall*)(void*, uint32_t)>(g_opcodes->scan(g_modules->m_modules.client_dll.get_name(), "85 D2 78 ? 3B 91 ? ? ? ? 7D ? 48 8B 81 ? ? ? ? 48 63 D2 0F BF 04 50"));

		return fn(this, index);
	}
};