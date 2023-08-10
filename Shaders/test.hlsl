struct PS_INPUT
{
    float4 dx_Position : SV_Position;
    float4 gl_Position : TEXCOORD11;
    float4 v0 : TEXCOORD0;
    float4 v1 : TEXCOORD1;
    float3 v2 : TEXCOORD2;
    float3 v3 : TEXCOORD3;
    float3 v4 : TEXCOORD4;
    float3 v5 : TEXCOORD5;
    float2 v6 : TEXCOORD6;
    float v7 : TEXCOORD7;
    float v8 : TEXCOORD8;
    float v9 : TEXCOORD9;
    float v10 : TEXCOORD10;
};

#pragma warning( disable: 3556 3571 )
float float_ctor_int(int x0)
{
    return float(x0);
}
float float_ctor_uint(uint x0)
{
    return float(x0);
}
float2 vec2_ctor(float x0, float x1)
{
    return float2(x0, x1);
}
float3 vec3_ctor(float x0)
{
    return float3(x0, x0, x0);
}
float3 vec3_ctor(float x0, float x1, float x2)
{
    return float3(x0, x1, x2);
}
float3 vec3_ctor(float2 x0, float x1)
{
    return float3(x0, x1);
}
float4 vec4_ctor(float x0)
{
    return float4(x0, x0, x0, x0);
}
float4 vec4_ctor(float x0, float2 x1, float x2)
{
    return float4(x0, x1, x2);
}
float4 vec4_ctor(float2 x0, float x1, float x2)
{
    return float4(x0, x1, x2);
}
float4 vec4_ctor(float3 x0, float x1)
{
    return float4(x0, x1);
}
float4x4 mat4_ctor_float4_float4_float4_float4(float4 x0, float4 x1, float4 x2, float4 x3)
{
    return float4x4(x0, x1, x2, x3);
}
int int_ctor(float x0)
{
    return int(x0);
}
uint uint_ctor(float x0)
{
    return uint(x0);
}
uint uint_ctor_int(int x0)
{
    return uint(x0);
}
// Uniforms

uniform float _color_ratio : register(c0);
uniform float _color_type : register(c1);
uniform int _zoomer_uv_id : register(c2);
uniform float _symbol_ctrl : register(c3);
uniform float _symbol_switch : register(c4);
uniform float3 _inside_color : register(c5);
uniform float3 _outline_color : register(c6);
uniform float3 _addition_color : register(c7);
uniform float4 _edge : register(c8);
uniform float _breath_ctrl : register(c9);
uniform float _addition_switch : register(c10);
uniform int _zoomer_using : register(c11);
uniform int _zoomer_edge_corner : register(c12);
uniform float _nation_switch : register(c13);
uniform float3 _nation_color : register(c14);
uniform float _mark_ctrl : register(c15);
uniform float3 _mark_inside_color : register(c16);
uniform float3 _mark_outline_color : register(c17);
uniform float4 _mark_edge : register(c18);
uniform float4 _grid_range : register(c19);
uniform int _red_grids : register(c20);
uniform int _green_grids : register(c21);
uniform float4 _FogColor : register(c22);
uniform float4 _ShadowParam : register(c23);
uniform int _DecalNum : register(c24);
uniform float4 _DecalAttrs[240] : register(c25);
uniform float _DecalTexScale : register(c265);
uniform float _layer_count : register(c266);
uniform float _floor_mask_ctrl : register(c267);
uniform float4 _floor_mask : register(c268);
uniform float4 _DirLightAttr[10] : register(c269);
uniform float3 _CameraPosition : register(c279);
uniform float4 _Ambient : register(c280);
uniform float _FrameTime : register(c281);
static const uint _SamTexture0 = 0;
static const uint _SamTexture1 = 1;
static const uint _SamTexture2 = 2;
static const uint _SamTexture3 = 3;
static const uint _SamBlend11 = 4;
static const uint _SamTexture4 = 5;
static const uint _SamTexture5 = 6;
static const uint _SamTexture6 = 7;
static const uint _SamTexture7 = 8;
static const uint _SamTexture8 = 9;
static const uint _SamTexture9 = 10;
static const uint _SamTexture10 = 11;
static const uint _diffuse_mask = 12;
static const uint _DecalTexture = 13;
uniform Texture2D<float4> textures2D[14] : register(t0);
uniform SamplerState samplers2D[14] : register(s0);
static const uint _ShadowMap = 14;
static const uint textureIndexOffset2D_comparison = 14;
static const uint samplerIndexOffset2D_comparison = 14;
uniform Texture2D textures2D_comparison[1] : register(t14);
uniform SamplerComparisonState samplers2D_comparison[1] : register(s14);
#define ANGLE_USES_NESTED_BREAK
#ifdef ANGLE_ENABLE_LOOP_FLATTEN
#define LOOP [loop]
#define FLATTEN [flatten]
#else
#define LOOP
#define FLATTEN
#endif

#define ATOMIC_COUNTER_ARRAY_STRIDE 4

// Varyings
static  float4 _v2f_pos_world = {0, 0, 0, 0};
static  float2 _v2f_color_uv = {0, 0};
static  float3 _v2f_tangent_world = {0, 0, 0};
static  float3 _v2f_normal_world = {0, 0, 0};
static  float3 _v2f_binormal_world = {0, 0, 0};
static  float3 _v2f_vertex_color = {0, 0, 0};
static  float _v2f_water_depth_ratio = {0};
static  float _v2f_water_algorithm_color_atten = {0};
static  float _v2f_warfog_combine_ratio = {0};
static  float _v2f_fog_factor_info = {0};
static  float4 _v2f_PosLightProj = {0, 0, 0, 0};

static float4 out__entryPointOutput = {0, 0, 0, 0};

cbuffer DriverConstants : register(b1)
{
    struct SamplerMetadata
    {
        int baseLevel;
        int internalFormatBits;
        int wrapModes;
        int padding;
        int4 intBorderColor;
    };
    SamplerMetadata samplerMetadata[15] : packoffset(c5);
};

float4 gl_texture2DLod(uint samplerIndex, float2 t, float lod)
{
    return textures2D[samplerIndex].SampleLevel(samplers2D[samplerIndex], float2(t.x, t.y), lod);
}

float4 gl_texture2DLod0(uint samplerIndex, float2 t)
{
    return textures2D[samplerIndex].SampleLevel(samplers2D[samplerIndex], float2(t.x, t.y), 0);
}

float gl_texture2D_comparisonLod(uint samplerIndex, float3 t, float lod)
{
    const uint textureIndex = samplerIndex - textureIndexOffset2D_comparison;
    const uint samplerArrayIndex = samplerIndex - samplerIndexOffset2D_comparison;
    return textures2D_comparison[textureIndex].SampleCmp(samplers2D_comparison[samplerArrayIndex], float2(t.x, t.y), t.z);
}

float mod_emu(float x, float y)
{
    return x - y * floor(x / y);
}


float2 mod_emu(float2 x, float2 y)
{
    return x - y * floor(x / y);
}


struct PS_OUTPUT
{
    float4 out__entryPointOutput : SV_TARGET0;
};

PS_OUTPUT generateOutput()
{
    PS_OUTPUT output;
    output.out__entryPointOutput = out__entryPointOutput;
    return output;
}


PS_OUTPUT main(PS_INPUT input){
    _v2f_pos_world = input.v0;
    _v2f_PosLightProj = input.v1;
    _v2f_tangent_world = input.v2.xyz;
    _v2f_normal_world = input.v3.xyz;
    _v2f_binormal_world = input.v4.xyz;
    _v2f_vertex_color = input.v5.xyz;
    _v2f_color_uv = input.v6.xy;
    _v2f_water_depth_ratio = input.v7.x;
    _v2f_water_algorithm_color_atten = input.v8.x;
    _v2f_warfog_combine_ratio = input.v9.x;
    _v2f_fog_factor_info = input.v10.x;

float2 __28155667 = (_v2f_color_uv * float2(2.0, 1.0));
float2 __28185668 = (_v2f_color_uv + float2(0.5, 0.0));
float __28205669 = __28155667.y;
float __28215670 = (__28205669 * 0.125);
float4 __28275671 = gl_texture2DLod(_SamTexture0, _v2f_color_uv, 0.0);
float4 __28325672 = gl_texture2DLod(_SamTexture0, __28185668, 0.0);
float4 __66465673 = {0, 0, 0, 0};
float4 __66475674 = {0, 0, 0, 0};
if ((_layer_count > 1.5))
{
float4 __28455675 = vec4_ctor(_v2f_vertex_color.x);
(__66475674 = lerp(__28325672, gl_texture2DLod(_SamTexture1, __28185668, 0.0), __28455675));
(__66465673 = lerp(__28275671, gl_texture2DLod(_SamTexture1, _v2f_color_uv, 0.0), __28455675));
}
else
{
(__66475674 = __28325672);
(__66465673 = __28275671);
}
float4 __66485676 = {0, 0, 0, 0};
float4 __66495677 = {0, 0, 0, 0};
if ((_layer_count > 2.5))
{
float4 __28705678 = vec4_ctor(_v2f_vertex_color.y);
(__66495677 = lerp(__66475674, gl_texture2DLod(_SamTexture2, __28185668, 0.0), __28705678));
(__66485676 = lerp(__66465673, gl_texture2DLod(_SamTexture2, _v2f_color_uv, 0.0), __28705678));
}
else
{
(__66495677 = __66475674);
(__66485676 = __66465673);
}
float4 __66505679 = {0, 0, 0, 0};
float4 __66515680 = {0, 0, 0, 0};
if ((_layer_count > 3.5))
{
float4 __28955681 = vec4_ctor(_v2f_vertex_color.z);
(__66515680 = lerp(__66495677, gl_texture2DLod(_SamTexture3, __28185668, 0.0), __28955681));
(__66505679 = lerp(__66485676, gl_texture2DLod(_SamTexture3, _v2f_color_uv, 0.0), __28955681));
}
else
{
(__66515680 = __66495677);
(__66505679 = __66485676);
}
float4 __66525682 = {0, 0, 0, 0};
float4 __66535683 = {0, 0, 0, 0};
if ((_layer_count > 4.5))
{
float4 __29295684 = vec4_ctor(gl_texture2DLod(_SamBlend11, vec2_ctor(__28155667.x, (0.75 + __28215670)), 0.0).w);
(__66535683 = lerp(__66515680, gl_texture2DLod(_SamTexture4, __28185668, 0.0), __29295684));
(__66525682 = lerp(__66505679, gl_texture2DLod(_SamTexture4, _v2f_color_uv, 0.0), __29295684));
}
else
{
(__66535683 = __66515680);
(__66525682 = __66505679);
}
float4 __66545685 = {0, 0, 0, 0};
float4 __66555686 = {0, 0, 0, 0};
if ((_layer_count > 5.5))
{
float4 __29625687 = vec4_ctor(gl_texture2DLod(_SamBlend11, vec2_ctor(__28155667.x, (0.625 + __28215670)), 0.0).w);
(__66555686 = lerp(__66535683, gl_texture2DLod(_SamTexture5, __28185668, 0.0), __29625687));
(__66545685 = lerp(__66525682, gl_texture2DLod(_SamTexture5, _v2f_color_uv, 0.0), __29625687));
}
else
{
(__66555686 = __66535683);
(__66545685 = __66525682);
}
float4 __66565688 = {0, 0, 0, 0};
float4 __66575689 = {0, 0, 0, 0};
if ((_layer_count > 6.5))
{
float4 __29955690 = vec4_ctor(gl_texture2DLod(_SamBlend11, vec2_ctor(__28155667.x, (0.5 + __28215670)), 0.0).w);
(__66575689 = lerp(__66555686, gl_texture2DLod(_SamTexture6, __28185668, 0.0), __29955690));
(__66565688 = lerp(__66545685, gl_texture2DLod(_SamTexture6, _v2f_color_uv, 0.0), __29955690));
}
else
{
(__66575689 = __66555686);
(__66565688 = __66545685);
}
float4 __66585691 = {0, 0, 0, 0};
float4 __66595692 = {0, 0, 0, 0};
if ((_layer_count > 7.5))
{
float4 __30285693 = vec4_ctor(gl_texture2DLod(_SamBlend11, vec2_ctor(__28155667.x, (0.375 + __28215670)), 0.0).w);
(__66595692 = lerp(__66575689, gl_texture2DLod(_SamTexture7, __28185668, 0.0), __30285693));
(__66585691 = lerp(__66565688, gl_texture2DLod(_SamTexture7, _v2f_color_uv, 0.0), __30285693));
}
else
{
(__66595692 = __66575689);
(__66585691 = __66565688);
}
float4 __66605694 = {0, 0, 0, 0};
float4 __66615695 = {0, 0, 0, 0};
if ((_layer_count > 8.5))
{
float4 __30615696 = vec4_ctor(gl_texture2DLod(_SamBlend11, vec2_ctor(__28155667.x, (0.25 + __28215670)), 0.0).w);
(__66615695 = lerp(__66595692, gl_texture2DLod(_SamTexture8, __28185668, 0.0), __30615696));
(__66605694 = lerp(__66585691, gl_texture2DLod(_SamTexture8, _v2f_color_uv, 0.0), __30615696));
}
else
{
(__66615695 = __66595692);
(__66605694 = __66585691);
}
float4 __66625697 = {0, 0, 0, 0};
float4 __66635698 = {0, 0, 0, 0};
if ((_layer_count > 9.5))
{
float4 __30945699 = vec4_ctor(gl_texture2DLod(_SamBlend11, vec2_ctor(__28155667.x, (0.125 + __28215670)), 0.0).w);
(__66635698 = lerp(__66615695, gl_texture2DLod(_SamTexture9, __28185668, 0.0), __30945699));
(__66625697 = lerp(__66605694, gl_texture2DLod(_SamTexture9, _v2f_color_uv, 0.0), __30945699));
}
else
{
(__66635698 = __66615695);
(__66625697 = __66605694);
}
float4 __66645700 = {0, 0, 0, 0};
float4 __66655701 = {0, 0, 0, 0};
if ((_layer_count > 10.5))
{
float4 __31275702 = vec4_ctor(gl_texture2DLod(_SamBlend11, vec2_ctor(__28155667.x, __28215670), 0.0).w);
(__66655701 = lerp(__66635698, gl_texture2DLod(_SamTexture10, __28185668, 0.0), __31275702));
(__66645700 = lerp(__66625697, gl_texture2DLod(_SamTexture10, _v2f_color_uv, 0.0), __31275702));
}
else
{
(__66655701 = __66635698);
(__66645700 = __66625697);
}
float __62575703 = {0};
float4 __66665704 = {0, 0, 0, 0};
float4 __66675705 = {0, 0, 0, 0};
if ((_floor_mask_ctrl > 0.001))
{
float __31875706 = (gl_texture2DLod(_diffuse_mask, vec2_ctor((((_floor_mask.x * 0.5) + 0.001) + ((_v2f_color_uv.x * _floor_mask.z) * 0.94999999)), ((_floor_mask.y + 0.001) + ((_v2f_color_uv.y * _floor_mask.w) * 0.94999999))), 0.0).w * _floor_mask_ctrl);
float4 __31915707 = vec4_ctor(__31875706);
(__66675705 = lerp(__66655701, gl_texture2DLod(_diffuse_mask, __28185668, 0.0), __31915707));
(__66665704 = lerp(__66645700, vec4_ctor(gl_texture2DLod(_diffuse_mask, _v2f_color_uv, 0.0).xyz, 0.0), __31915707));
(__62575703 = __31875706);
}
else
{
(__66675705 = __66655701);
(__66665704 = __66645700);
(__62575703 = 1.0);
}
float3 __62445708 = {0, 0, 0};
float __62475709 = {0};
float3 __62505710 = {0, 0, 0};
float __62535711 = {0};
{LOOP do
{
if ((_DecalNum <= 0))
{
(__62535711 = __66665704.w);
(__62505710 = __66675705.xyz);
(__62475709 = __66675705.w);
(__62445708 = __66665704.xyz);
break;
}
uint __34235712 = uint_ctor_int(_DecalNum);
uint __34265713 = ((__34235712 + 3) / 4);
uint __61815714 = {0};
float3 __61875715 = {0, 0, 0};
float __61905716 = {0};
float3 __61935717 = {0, 0, 0};
float __61965718 = {0};
bool __62325719 = {0};
(__62325719 = false);
(__61965718 = __66665704.w);
(__61935717 = __66675705.xyz);
(__61905716 = __66675705.w);
(__61875715 = __66665704.xyz);
(__61815714 = 0);
float4 __33995720[3] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
bool __34055721[5] = {0, 0, 0, 0, 0};
float4 __34085722[5] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float3 __61865723 = {0, 0, 0};
float __61895724 = {0};
float3 __61925725 = {0, 0, 0};
float __61955726 = {0};
bool __62305727 = {0};
bool __62435728 = {0};
float3 __62455729 = {0, 0, 0};
float __62485730 = {0};
float3 __62515731 = {0, 0, 0};
float __62545732 = {0};
{LOOP for(; ; )
{
FLATTEN if ((__61815714 < __34265713))
{
(__61955726 = (__61965718 + 0.0));
(__61925725 = (__61935717 + float3(0.0, 0.0, 0.0)));
(__61895724 = (__61905716 + 0.0));
(__61865723 = (__61875715 + float3(0.0, 0.0, 0.0)));
float3 __64025733 = {0, 0, 0};
float __64055734 = {0};
float3 __64085735 = {0, 0, 0};
float __64115736 = {0};
uint __61825737 = {0};
{LOOP for(; ; )
{
FLATTEN if ((__61825737 < 4))
{
uint __34415738 = ((__61815714 * 4) + __61825737);
if ((__34415738 >= __34235712))
{
(__62305727 = (true + false));
break;
}
uint __34485739 = (__34415738 * 8);
uint __34935740 = (__34415738 * 8);
uint __34945741 = (__34935740 + 4);
(__33995720[0] = (_DecalAttrs[(__34935740 + 5)] + float4(0.0, 0.0, 0.0, 0.0)));
(__33995720[1] = (_DecalAttrs[(__34935740 + 6)] + float4(0.0, 0.0, 0.0, 0.0)));
(__33995720[2] = (_DecalAttrs[(__34935740 + 7)] + float4(0.0, 0.0, 0.0, 0.0)));
float4 __35255742 = mul(transpose(mat4_ctor_float4_float4_float4_float4(_DecalAttrs[__34485739], _DecalAttrs[(__34485739 + 1)], _DecalAttrs[(__34485739 + 2)], _DecalAttrs[(__34485739 + 3)])), vec4_ctor(_v2f_pos_world.xyz, 1.0));
float __35275743 = __35255742.x;
float __35345744 = __35255742.y;
float __35425745 = __35255742.z;
FLATTEN if (((((((__35275743 >= -0.5) && (__35275743 <= 0.5)) && (__35345744 >= -0.5)) && (__35345744 <= 0.5)) && (__35425745 >= -0.5)) && (__35425745 <= 0.5)))
{
{LOOP for(uint __61845746 = {0}; (__61845746 < 5); (__61845746++))
{
uint __35565747 = (__61845746 / 2);
float2 __66685748 = {0, 0};
if ((int_ctor(mod_emu(float_ctor_uint(__61845746), 2.0)) == 0))
{
(__66685748 = (__33995720[__35565747].xy + float2(0.0, 0.0)));
}
else
{
(__66685748 = (__33995720[__35565747].zw + float2(0.0, 0.0)));
}
if ((__66685748.x < 0.0))
{
(__34055721[__61845746] = (false + false));
}
else
{
float2 __35965749 = ((clamp(mod_emu(((__35255742.xz + float2(0.5, 0.5)) * _DecalAttrs[__34945741].yz), float2(1.0, 1.0)), float2(0.0099999998, 0.0099999998), float2(0.99000001, 0.99000001)) * _DecalTexScale) + __66685748);
float2 __64605750 = __35965749;
(__64605750.y = ((1.0 - __35965749.y) + 0.0));
(__34085722[__61845746] = (gl_texture2DLod0(_DecalTexture, __64605750) + float4(0.0, 0.0, 0.0, 0.0)));
(__34055721[__61845746] = (true + false));
}
}
}
float __61985751 = {0};
if (__34055721[4])
{
(__61985751 = ((_DecalAttrs[__34945741].x * __34085722[4].w) + 0.0));
}
else
{
(__61985751 = (_DecalAttrs[__34945741].x + 0.0));
}
float3 __62145752 = {0, 0, 0};
if (__34055721[0])
{
(__62145752 = (lerp(__61865723, __34085722[0].xyz, vec3_ctor(__61985751)) + float3(0.0, 0.0, 0.0)));
}
else
{
(__62145752 = (__61865723 + float3(0.0, 0.0, 0.0)));
}
float __62175753 = {0};
if (__34055721[1])
{
(__62175753 = (lerp(__61895724, __34085722[1].w, __61985751) + 0.0));
}
else
{
(__62175753 = (__61895724 + 0.0));
}
float3 __62195754 = {0, 0, 0};
if (__34055721[2])
{
float3 __36865755 = ((__34085722[2].xyz * 2.0) - float3(1.0, 1.0, 1.0));
float2 __36905756 = (__36865755.xy * __61985751);
float3 __37015757 = ((__61925725 * float3(2.0, 2.0, 2.0)) + float3(-1.0, -1.0, 0.0));
float3 __37045758 = ((((normalize(vec3_ctor(__36905756.x, __36905756.y, __36865755.z)) * 0.5) + float3(0.5, 0.5, 0.5)) * float3(-2.0, -2.0, 2.0)) + float3(1.0, 1.0, -1.0));
(__62195754 = (((normalize(((__37015757 * dot(__37015757, __37045758)) - (__37045758 * __37015757.z))) * 0.5) + float3(0.5, 0.5, 0.5)) + float3(0.0, 0.0, 0.0)));
}
else
{
(__62195754 = (__61925725 + float3(0.0, 0.0, 0.0)));
}
float __62205759 = {0};
if (__34055721[3])
{
(__62205759 = (lerp(__61955726, __34085722[3].w, __61985751) + 0.0));
}
else
{
(__62205759 = (__61955726 + 0.0));
}
(__64115736 = (__62205759 + 0.0));
(__64085735 = (__62195754 + float3(0.0, 0.0, 0.0)));
(__64055734 = (__62175753 + 0.0));
(__64025733 = (__62145752 + float3(0.0, 0.0, 0.0)));
}
else
{
(__64115736 = (__61955726 + 0.0));
(__64085735 = (__61925725 + float3(0.0, 0.0, 0.0)));
(__64055734 = (__61895724 + 0.0));
(__64025733 = (__61865723 + float3(0.0, 0.0, 0.0)));
}
(__61955726 = (__64115736 + 0.0));
(__61925725 = (__64085735 + float3(0.0, 0.0, 0.0)));
(__61895724 = (__64055734 + 0.0));
(__61865723 = (__64025733 + float3(0.0, 0.0, 0.0)));
(__61825737++);
continue;
}
else
{
(__62305727 = (__62325719 + false));
break;
}
}
}
if (__62305727)
{
(__62545732 = (__61955726 + 0.0));
(__62515731 = (__61925725 + float3(0.0, 0.0, 0.0)));
(__62485730 = (__61895724 + 0.0));
(__62455729 = (__61865723 + float3(0.0, 0.0, 0.0)));
(__62435728 = (__62305727 + false));
break;
}
(__62325719 = (__62305727 + false));
(__61965718 = (__61955726 + 0.0));
(__61935717 = (__61925725 + float3(0.0, 0.0, 0.0)));
(__61905716 = (__61895724 + 0.0));
(__61875715 = (__61865723 + float3(0.0, 0.0, 0.0)));
(__61815714++);
continue;
}
else
{
(__62545732 = (__61965718 + 0.0));
(__62515731 = (__61935717 + float3(0.0, 0.0, 0.0)));
(__62485730 = (__61905716 + 0.0));
(__62455729 = (__61875715 + float3(0.0, 0.0, 0.0)));
(__62435728 = (__62325719 + false));
break;
}
}
}
if (__62435728)
{
(__62535711 = __62545732);
(__62505710 = __62515731);
(__62475709 = __62485730);
(__62445708 = __62455729);
break;
}
(__62535711 = __62545732);
(__62505710 = __62515731);
(__62475709 = __62485730);
(__62445708 = __62455729);
break;
}
while (false);
}
float2 __37375760 = ((__62505710.xy * 2.0) - float2(1.0, 1.0));
float3 __32445761 = normalize((((_v2f_tangent_world * __37375760.x) + (_v2f_binormal_world * __37375760.y)) + (_v2f_normal_world * sqrt(clamp((1.0 - dot(__37375760, __37375760)), 0.0, 1.0)))));
float3 __32525762 = (-normalize(_DirLightAttr[3].xyz));
float3 __37545763 = pow(max(float3(0.0, 0.0, 0.0), __62445708.xyz), float3(2.2, 2.2, 2.2));
float3 __32685764 = normalize((_CameraPosition - _v2f_pos_world.xyz));
float s1737 = {0};
if ((_v2f_PosLightProj.w == 0.0))
{
(s1737 = 0.0);
}
else
{
(s1737 = (1.0 / _v2f_PosLightProj.w));
}
float4 __38135765 = (_v2f_PosLightProj * s1737);
float __37645766 = __38135765.z;
float __37675767 = __38135765.x;
float __37715768 = __38135765.y;
float __37815769 = ((((step(__37645766, 1.0) * step(__37675767, 1.0)) * step(__37715768, 1.0)) * step(0.0, __37675767)) * step(0.0, __37715768));
float __32765770 = dot(__32445761, __32525762);
float3 __38435771 = lerp(float3(0.0080000004, 0.0080000004, 0.0080000004), __37545763, vec3_ctor(__62535711));
float3 __38645772 = (float3(1.0, 1.0, 1.0) - __38435771);
float __38665773 = (1.0 - clamp(dot(__32685764, normalize((__32525762 + __32685764))), 0.0, 1.0));
float __38775774 = (__38665773 * __38665773);
float3 __39085775 = normalize((float3(-0.50251901, 0.70352602, 0.50251901) + __32685764));
float __39125776 = clamp(dot(__32445761, __39085775), 0.0, 1.0);
float __39165777 = clamp(dot(__32445761, __32685764), 0.0, 1.0);
float __39205778 = clamp(dot(__32445761, float3(-0.50251901, 0.70352602, 0.50251901)), 0.0, 1.0);
float __39695779 = (__62475709 * __62475709);
float __39725780 = (__39695779 * __39695779);
float __39815781 = (((__39725780 - 1.0) * (__39125776 * __39125776)) + 1.0);
float __39995782 = (__62475709 + 1.0);
float __40035783 = ((__39995782 * __39995782) * 0.125);
float __40055784 = (1.0 - __40035783);
float __40325785 = (1.0 - clamp(dot(__32685764, __39085775), 0.0, 1.0));
float __40435786 = (__40325785 * __40325785);
float3 __40545787 = ((((((((((float3(1.0, 1.0, 1.0) - ((__38645772 * ((__38775774 * __38775774) * __38665773)) + __38435771)) * (1.0 - __62535711)) * __37545763) * (0.31830999 * clamp(__32765770, 0.0, 1.0))) + (((((__38645772 * ((__40435786 * __40435786) * __40325785)) + __38435771) * ((__39725780 * (1.0 / ((3.1415901 * __39815781) * __39815781))) * ((__39205778 * (1.0 / ((__40055784 * __39205778) + __40035783))) * (__39165777 * (1.0 / ((__40055784 * __39165777) + __40035783)))))) * (1.0 / (((4.0 * __39165777) * __39205778) + 0.001))) * __39205778)) * _DirLightAttr[1].xyz) * 4.0) * (1.0 - ((1.0 - lerp(1.0, _ShadowParam.w, (__37815769 - (__37815769 * gl_texture2D_comparisonLod(_ShadowMap, vec3_ctor(vec3_ctor(__37675767, __37715768, __37645766).xy, __37645766), 0.0))))) * step(0.0, __32765770)))) + (((__37545763 * _Ambient.xyz) * 0.60000002) * 1.0)) * 1.0);
float __33185788 = (1.0 - _v2f_water_depth_ratio);
float3 __33325789 = (lerp(pow(max(float3(0.0, 0.0, 0.0), ((__40545787 * ((__40545787 * 2.51) + float3(0.029999999, 0.029999999, 0.029999999))) / ((((__40545787 * 2.4300001) + float3(0.58999997, 0.58999997, 0.58999997)) * __40545787) + float3(0.14, 0.14, 0.14)))), float3(0.45449999, 0.45449999, 0.45449999)), lerp(float3(0.43700001, 0.417, 0.21799999), float3(0.1, 0.1, 0.11), vec3_ctor(_v2f_water_depth_ratio)), vec3_ctor((1.0 - (__33185788 * __33185788)))) * clamp((1.0 - _v2f_warfog_combine_ratio), 0.0, 1.0));
float __33395790 = ((abs((mod_emu((0.5 * _FrameTime), 1.0) - 0.5)) * 1.4) + 0.30000001);
float __33465791 = (_v2f_water_algorithm_color_atten - (_v2f_water_algorithm_color_atten * __62575703));
float3 __63475792 = {0, 0, 0};
{ do
{
if (((_symbol_ctrl < 0.001) || (_symbol_switch < 0.001)))
{
(__63475792 = __33325789);
break;
}
float __45435793 = (_color_type + 0.5);
float __45455794 = step(__45435793, 1.0);
float __45545795 = (step(1.0, __45435793) * step(__45435793, 2.0));
float3 __45825796 = mul(transpose(float3x3(17.882401, 3.4556501, 0.0299566, 43.516102, 27.155399, 0.18430901, 4.11935, 3.8671401, 1.46709)), _inside_color);
float3 __46005797 = vec3_ctor(_color_ratio);
float __45645798 = (step(2.0, __45435793) * step(__45435793, 3.0));
float __45715799 = step(3.0, __45435793);
float4 __46915800 = lerp(vec4_ctor(_inside_color.zy, -1.0, 0.66666698), vec4_ctor(_inside_color.yz, 0.0, -0.33333299), vec4_ctor(step(_inside_color.z, _inside_color.y)));
float __46965801 = __46915800.x;
float4 __47145802 = lerp(vec4_ctor(__46965801, __46915800.yw, _inside_color.x), vec4_ctor(_inside_color.x, __46915800.yz, __46965801), vec4_ctor(step(__46965801, _inside_color.x)));
float __47165803 = __47145802.x;
float __47185804 = __47145802.w;
float __47205805 = __47145802.y;
float __47225806 = (__47165803 - min(__47185804, __47205805));
float __47365807 = abs((__47145802.z + ((__47185804 - __47205805) / ((6.0 * __47225806) + 1e-10))));
float __46365808 = (__47365807 + 0.30000001);
float3 __65005809 = vec3_ctor(__47365807, (__47225806 / (__47165803 + 1e-10)), __47165803);
(__65005809.x = __46365808);
float3 __66975810 = {0, 0, 0};
if ((__46365808 > 1.0))
{
float3 __65045811 = __65005809;
(__65045811.x = (0.69999999 - __47365807));
(__66975810 = __65045811);
}
else
{
(__66975810 = __65005809);
}
float3 __66985812 = {0, 0, 0};
if ((__66975810.x < 0.0))
{
float3 __65075813 = __66975810;
(__65075813.x = 0.0);
(__66985812 = __65075813);
}
else
{
(__66985812 = __66975810);
}
float3 __45765814 = ((((_inside_color * __45455794) + (lerp(_inside_color, clamp((mul(transpose(float3x3(0.0, 0.69999999, 0.69999999, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0)), (_inside_color - mul(transpose(float3x3(0.080944397, -0.0102485, -0.00036529699, -0.130504, 0.054019298, -0.00412161, 0.116721, -0.113615, 0.69351101)), mul(transpose(float3x3(0.0, 0.0, 0.0, 2.0234399, 1.0, 0.0, -2.52581, 0.0, 1.0)), __45825796)))) + _inside_color), float3(0.0, 0.0, 0.0), float3(1.0, 1.0, 1.0)), __46005797) * __45545795)) + (lerp(_inside_color, clamp((mul(transpose(float3x3(1.0, 0.0, 0.0, 0.69999999, 0.0, 0.69999999, 0.0, 0.0, 1.0)), (_inside_color - mul(transpose(float3x3(0.080944397, -0.0102485, -0.00036529699, -0.130504, 0.054019298, -0.00412161, 0.116721, -0.113615, 0.69351101)), mul(transpose(float3x3(1.0, 0.49420699, 0.0, 0.0, 0.0, 0.0, 0.0, 1.24827, 1.0)), __45825796)))) + _inside_color), float3(0.0, 0.0, 0.0), float3(1.0, 1.0, 1.0)), __46005797) * __45645798)) + (lerp(_inside_color, (lerp(float3(1.0, 1.0, 1.0), clamp((abs(((frac((__66985812.xxx + float3(1.0, 0.66666698, 0.33333299))) * 6.0) - float3(3.0, 3.0, 3.0))) - float3(1.0, 1.0, 1.0)), float3(0.0, 0.0, 0.0), float3(1.0, 1.0, 1.0)), vec3_ctor(__66985812.y)) * __66985812.z), __46005797) * __45715799));
float3 __48255815 = mul(transpose(float3x3(17.882401, 3.4556501, 0.0299566, 43.516102, 27.155399, 0.18430901, 4.11935, 3.8671401, 1.46709)), _outline_color);
float4 __49345816 = lerp(vec4_ctor(_outline_color.zy, -1.0, 0.66666698), vec4_ctor(_outline_color.yz, 0.0, -0.33333299), vec4_ctor(step(_outline_color.z, _outline_color.y)));
float __49395817 = __49345816.x;
float4 __49575818 = lerp(vec4_ctor(__49395817, __49345816.yw, _outline_color.x), vec4_ctor(_outline_color.x, __49345816.yz, __49395817), vec4_ctor(step(__49395817, _outline_color.x)));
float __49595819 = __49575818.x;
float __49615820 = __49575818.w;
float __49635821 = __49575818.y;
float __49655822 = (__49595819 - min(__49615820, __49635821));
float __49795823 = abs((__49575818.z + ((__49615820 - __49635821) / ((6.0 * __49655822) + 1e-10))));
float __48795824 = (__49795823 + 0.30000001);
float3 __65265825 = vec3_ctor(__49795823, (__49655822 / (__49595819 + 1e-10)), __49595819);
(__65265825.x = __48795824);
float3 __66995826 = {0, 0, 0};
if ((__48795824 > 1.0))
{
float3 __65305827 = __65265825;
(__65305827.x = (0.69999999 - __49795823));
(__66995826 = __65305827);
}
else
{
(__66995826 = __65265825);
}
float3 __67005828 = {0, 0, 0};
if ((__66995826.x < 0.0))
{
float3 __65335829 = __66995826;
(__65335829.x = 0.0);
(__67005828 = __65335829);
}
else
{
(__67005828 = __66995826);
}
float3 __50685830 = mul(transpose(float3x3(17.882401, 3.4556501, 0.0299566, 43.516102, 27.155399, 0.18430901, 4.11935, 3.8671401, 1.46709)), _addition_color);
float4 __51775831 = lerp(vec4_ctor(_addition_color.zy, -1.0, 0.66666698), vec4_ctor(_addition_color.yz, 0.0, -0.33333299), vec4_ctor(step(_addition_color.z, _addition_color.y)));
float __51825832 = __51775831.x;
float4 __52005833 = lerp(vec4_ctor(__51825832, __51775831.yw, _addition_color.x), vec4_ctor(_addition_color.x, __51775831.yz, __51825832), vec4_ctor(step(__51825832, _addition_color.x)));
float __52025834 = __52005833.x;
float __52045835 = __52005833.w;
float __52065836 = __52005833.y;
float __52085837 = (__52025834 - min(__52045835, __52065836));
float __52225838 = abs((__52005833.z + ((__52045835 - __52065836) / ((6.0 * __52085837) + 1e-10))));
float __51225839 = (__52225838 + 0.30000001);
float3 __65525840 = vec3_ctor(__52225838, (__52085837 / (__52025834 + 1e-10)), __52025834);
(__65525840.x = __51225839);
float3 __67015841 = {0, 0, 0};
if ((__51225839 > 1.0))
{
float3 __65565842 = __65525840;
(__65565842.x = (0.69999999 - __52225838));
(__67015841 = __65565842);
}
else
{
(__67015841 = __65525840);
}
float3 __67025843 = {0, 0, 0};
if ((__67015841.x < 0.0))
{
float3 __65595844 = __67015841;
(__65595844.x = 0.0);
(__67025843 = __65595844);
}
else
{
(__67025843 = __67015841);
}
float3 __50625845 = ((((_addition_color * __45455794) + (lerp(_addition_color, clamp((mul(transpose(float3x3(0.0, 0.69999999, 0.69999999, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0)), (_addition_color - mul(transpose(float3x3(0.080944397, -0.0102485, -0.00036529699, -0.130504, 0.054019298, -0.00412161, 0.116721, -0.113615, 0.69351101)), mul(transpose(float3x3(0.0, 0.0, 0.0, 2.0234399, 1.0, 0.0, -2.52581, 0.0, 1.0)), __50685830)))) + _addition_color), float3(0.0, 0.0, 0.0), float3(1.0, 1.0, 1.0)), __46005797) * __45545795)) + (lerp(_addition_color, clamp((mul(transpose(float3x3(1.0, 0.0, 0.0, 0.69999999, 0.0, 0.69999999, 0.0, 0.0, 1.0)), (_addition_color - mul(transpose(float3x3(0.080944397, -0.0102485, -0.00036529699, -0.130504, 0.054019298, -0.00412161, 0.116721, -0.113615, 0.69351101)), mul(transpose(float3x3(1.0, 0.49420699, 0.0, 0.0, 0.0, 0.0, 0.0, 1.24827, 1.0)), __50685830)))) + _addition_color), float3(0.0, 0.0, 0.0), float3(1.0, 1.0, 1.0)), __46005797) * __45645798)) + (lerp(_addition_color, (lerp(float3(1.0, 1.0, 1.0), clamp((abs(((frac((__67025843.xxx + float3(1.0, 0.66666698, 0.33333299))) * 6.0) - float3(3.0, 3.0, 3.0))) - float3(1.0, 1.0, 1.0)), float3(0.0, 0.0, 0.0), float3(1.0, 1.0, 1.0)), vec3_ctor(__67025843.y)) * __67025843.z), __46005797) * __45715799));
float __52675846 = (_edge.z - 1.0);
float __52805847 = (_edge.z - _edge.x);
float __41785848 = __28155667.x;
float __41915849 = lerp(0.5, __41785848, clamp(((step((__52675846 * sign(__52675846)), 0.0099999998) * step(__41785848, 0.5)) + (step((__52805847 * sign(__52805847)), 0.0099999998) * step(0.5, __41785848))), 0.0, 1.0));
float __52935850 = (_edge.w - 1.0);
float __53065851 = (_edge.w - _edge.y);
float __42125852 = lerp(0.5, __28205669, clamp(((step((__52935850 * sign(__52935850)), 0.0099999998) * step(__28205669, 0.5)) + (step((__53065851 * sign(__53065851)), 0.0099999998) * step(0.5, __28205669))), 0.0, 1.0));
float __42155853 = abs((__41915849 - 0.5));
float __42185854 = abs((__42125852 - 0.5));
float __42215855 = max(__42155853, __42185854);
float __42505856 = (((_symbol_ctrl * _symbol_switch) * clamp((__33395790 + (1.0 - _breath_ctrl)), 0.0, 1.0)) * __33465791);
float __42625857 = ((1.0 - ((step(0.345, __42155853) * step(0.345, __42185854)) * step(0.125, length(vec2_ctor(mod_emu(__42155853, 0.345), mod_emu(__42185854, 0.345)))))) * (1.0 - floor((__42215855 * 2.12766))));
bool __42645858 = (_addition_switch > 0.0099999998);
float3 __62895859 = {0, 0, 0};
if (__42645858)
{
float3 __62905860 = {0, 0, 0};
if (((_zoomer_using > 0) && (!(mod_emu(float_ctor_int(_zoomer_uv_id), 32.0) == 31.0))))
{
(__62905860 = __33325789);
}
else
{
float s173a = (2.0 * __42215855);
(__62905860 = lerp(__33325789, __50625845, vec3_ctor(((__42505856 * _addition_switch) * (__42625857 * (((s173a * s173a) * s173a) * s173a))))));
}
(__62895859 = __62905860);
}
else
{
(__62895859 = __33325789);
}
bool __42895861 = (_zoomer_using > 0);
bool __42915862 = (__42895861 && (!(mod_emu(float_ctor_int(_zoomer_uv_id), 32.0) == 31.0)));
float3 __63115863 = {0, 0, 0};
if (__42915862)
{
float3 __63125864 = {0, 0, 0};
if (__42645858)
{
(__63125864 = lerp(__62895859, __50625845, float3(0.40000001, 0.40000001, 0.40000001)));
}
else
{
(__63125864 = lerp(__62895859, __45765814, float3(0.40000001, 0.40000001, 0.40000001)));
}
(__63115863 = __63125864);
}
else
{
float s173b = (2.0 * __42215855);
(__63115863 = lerp(__62895859, __45765814, vec3_ctor(((__42505856 * (((((s173b * s173b) * s173b) * s173b) * s173b) * s173b)) * (((-_addition_switch) * __42625857) + 1.0)))));
}
float __63375865 = {0};
if (__42915862)
{
uint __43355866 = uint_ctor_int(_zoomer_edge_corner);
uint __43375867 = (__43355866 / 16);
uint __43415868 = uint_ctor(mod_emu(float_ctor_uint(__43355866), 16.0));
float __43505869 = float_ctor_uint(__43375867);
float __43625870 = (__41785848 - __28205669);
float __43685871 = ((__41785848 + __28205669) - 1.0);
bool __43705872 = (__43625870 <= 0.0);
bool __43725873 = (__43685871 <= 0.0);
float __63435874 = {0};
if ((__43705872 && __43725873))
{
(__63435874 = float_ctor_uint(uint_ctor((mod_emu(__43505869, 4.0) * 0.5))));
}
else
{
bool __43815875 = (__43685871 >= 0.0);
float __63445876 = {0};
if ((__43705872 && __43815875))
{
(__63445876 = float_ctor_uint(uint_ctor(mod_emu(float_ctor_uint((__43375867 / 4)), 2.0))));
}
else
{
bool __43885877 = (__43625870 >= 0.0);
float __63455878 = {0};
if ((__43885877 && __43815875))
{
(__63455878 = float_ctor_uint((__43375867 / 8)));
}
else
{
float __63465879 = {0};
if ((__43885877 && __43725873))
{
(__63465879 = float_ctor_uint(uint_ctor(mod_emu(__43505869, 2.0))));
}
else
{
(__63465879 = 1.0);
}
(__63455878 = __63465879);
}
(__63445876 = __63455878);
}
(__63435874 = __63445876);
}
float __44165880 = float_ctor_uint(__43415868);
float __44265881 = __28155667.x;
bool __44285882 = (__44265881 <= 0.045000002);
float __44305883 = __28155667.y;
bool __44325884 = (__44305883 <= 0.045000002);
bool __44385885 = (__44265881 >= 0.95499998);
bool __44535886 = (__44305883 >= 0.95499998);
float __63395887 = {0};
if ((__44285882 && __44325884))
{
(__63395887 = float_ctor_uint(uint_ctor(mod_emu(__44165880, 2.0))));
}
else
{
float __63405888 = {0};
if ((__44385885 && __44325884))
{
(__63405888 = float_ctor_uint((__43415868 / 8)));
}
else
{
float __63415889 = {0};
if ((__44385885 && __44535886))
{
(__63415889 = float_ctor_uint(uint_ctor(mod_emu(float_ctor_uint((__43415868 / 4)), 2.0))));
}
else
{
float __63425890 = {0};
if ((__44285882 && __44535886))
{
(__63425890 = float_ctor_uint(uint_ctor((mod_emu(__44165880, 4.0) * 0.5))));
}
else
{
(__63425890 = __63435874);
}
(__63415889 = __63425890);
}
(__63405888 = __63415889);
}
(__63395887 = __63405888);
}
(__63375865 = __63395887);
}
else
{
(__63375865 = 1.0);
}
float s1738 = {0};
if (__42915862)
{
(s1738 = 0.4641);
}
else
{
float s1739 = {0};
if (__42895861)
{
(s1739 = 0.4641);
}
else
{
(s1739 = 0.49000001);
}
(s1738 = s1739);
}
float3 __45035891 = lerp(__63115863, ((((_outline_color * __45455794) + (lerp(_outline_color, clamp((mul(transpose(float3x3(0.0, 0.69999999, 0.69999999, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0)), (_outline_color - mul(transpose(float3x3(0.080944397, -0.0102485, -0.00036529699, -0.130504, 0.054019298, -0.00412161, 0.116721, -0.113615, 0.69351101)), mul(transpose(float3x3(0.0, 0.0, 0.0, 2.0234399, 1.0, 0.0, -2.52581, 0.0, 1.0)), __48255815)))) + _outline_color), float3(0.0, 0.0, 0.0), float3(1.0, 1.0, 1.0)), __46005797) * __45545795)) + (lerp(_outline_color, clamp((mul(transpose(float3x3(1.0, 0.0, 0.0, 0.69999999, 0.0, 0.69999999, 0.0, 0.0, 1.0)), (_outline_color - mul(transpose(float3x3(0.080944397, -0.0102485, -0.00036529699, -0.130504, 0.054019298, -0.00412161, 0.116721, -0.113615, 0.69351101)), mul(transpose(float3x3(1.0, 0.49420699, 0.0, 0.0, 0.0, 0.0, 0.0, 1.24827, 1.0)), __48255815)))) + _outline_color), float3(0.0, 0.0, 0.0), float3(1.0, 1.0, 1.0)), __46005797) * __45645798)) + (lerp(_outline_color, (lerp(float3(1.0, 1.0, 1.0), clamp((abs(((frac((__67005828.xxx + float3(1.0, 0.66666698, 0.33333299))) * 6.0) - float3(3.0, 3.0, 3.0))) - float3(1.0, 1.0, 1.0)), float3(0.0, 0.0, 0.0), float3(1.0, 1.0, 1.0)), vec3_ctor(__67005828.y)) * __67005828.z), __46005797) * __45715799)), vec3_ctor(((__42505856 * floor((__42215855 * (1.0 / s1738)))) * __63375865)));
float3 __63485892 = {0, 0, 0};
if (((_zoomer_using <= 0) && (_nation_switch > 0.0099999998)))
{
(__63485892 = lerp(__45035891, _nation_color, vec3_ctor(((__42505856 * _nation_switch) * (1.0 - clamp(((3.0 * (__41915849 + 0.2)) * (1.2 - __42125852)), 0.0, 1.0))))));
}
else
{
(__63485892 = __45035891);
}
(__63475792 = __63485892);
break;
}
while (false);
}
float3 __63615893 = {0, 0, 0};
{ do
{
if ((_mark_ctrl < 0.0099999998))
{
(__63615893 = __63475792);
break;
}
float __54685894 = (_color_type + 0.5);
float __54705895 = step(__54685894, 1.0);
float __54795896 = (step(1.0, __54685894) * step(__54685894, 2.0));
float3 __55075897 = mul(transpose(float3x3(17.882401, 3.4556501, 0.0299566, 43.516102, 27.155399, 0.18430901, 4.11935, 3.8671401, 1.46709)), _mark_inside_color);
float3 __55255898 = vec3_ctor(_color_ratio);
float __54895899 = (step(2.0, __54685894) * step(__54685894, 3.0));
float __54965900 = step(3.0, __54685894);
float4 __56165901 = lerp(vec4_ctor(_mark_inside_color.zy, -1.0, 0.66666698), vec4_ctor(_mark_inside_color.yz, 0.0, -0.33333299), vec4_ctor(step(_mark_inside_color.z, _mark_inside_color.y)));
float __56215902 = __56165901.x;
float4 __56395903 = lerp(vec4_ctor(__56215902, __56165901.yw, _mark_inside_color.x), vec4_ctor(_mark_inside_color.x, __56165901.yz, __56215902), vec4_ctor(step(__56215902, _mark_inside_color.x)));
float __56415904 = __56395903.x;
float __56435905 = __56395903.w;
float __56455906 = __56395903.y;
float __56475907 = (__56415904 - min(__56435905, __56455906));
float __56615908 = abs((__56395903.z + ((__56435905 - __56455906) / ((6.0 * __56475907) + 1e-10))));
float __55615909 = (__56615908 + 0.30000001);
float3 __65965910 = vec3_ctor(__56615908, (__56475907 / (__56415904 + 1e-10)), __56415904);
(__65965910.x = __55615909);
float3 __67035911 = {0, 0, 0};
if ((__55615909 > 1.0))
{
float3 __66005912 = __65965910;
(__66005912.x = (0.69999999 - __56615908));
(__67035911 = __66005912);
}
else
{
(__67035911 = __65965910);
}
float3 __67045913 = {0, 0, 0};
if ((__67035911.x < 0.0))
{
float3 __66035914 = __67035911;
(__66035914.x = 0.0);
(__67045913 = __66035914);
}
else
{
(__67045913 = __67035911);
}
float3 __57505915 = mul(transpose(float3x3(17.882401, 3.4556501, 0.0299566, 43.516102, 27.155399, 0.18430901, 4.11935, 3.8671401, 1.46709)), _mark_outline_color);
float4 __58595916 = lerp(vec4_ctor(_mark_outline_color.zy, -1.0, 0.66666698), vec4_ctor(_mark_outline_color.yz, 0.0, -0.33333299), vec4_ctor(step(_mark_outline_color.z, _mark_outline_color.y)));
float __58645917 = __58595916.x;
float4 __58825918 = lerp(vec4_ctor(__58645917, __58595916.yw, _mark_outline_color.x), vec4_ctor(_mark_outline_color.x, __58595916.yz, __58645917), vec4_ctor(step(__58645917, _mark_outline_color.x)));
float __58845919 = __58825918.x;
float __58865920 = __58825918.w;
float __58885921 = __58825918.y;
float __58905922 = (__58845919 - min(__58865920, __58885921));
float __59045923 = abs((__58825918.z + ((__58865920 - __58885921) / ((6.0 * __58905922) + 1e-10))));
float __58045924 = (__59045923 + 0.30000001);
float3 __66225925 = vec3_ctor(__59045923, (__58905922 / (__58845919 + 1e-10)), __58845919);
(__66225925.x = __58045924);
float3 __67055926 = {0, 0, 0};
if ((__58045924 > 1.0))
{
float3 __66265927 = __66225925;
(__66265927.x = (0.69999999 - __59045923));
(__67055926 = __66265927);
}
else
{
(__67055926 = __66225925);
}
float3 __67065928 = {0, 0, 0};
if ((__67055926.x < 0.0))
{
float3 __66295929 = __67055926;
(__66295929.x = 0.0);
(__67065928 = __66295929);
}
else
{
(__67065928 = __67055926);
}
float __59495930 = (_mark_edge.z - 1.0);
float __59625931 = (_mark_edge.z - _mark_edge.x);
float __53825932 = __28155667.x;
float __59755933 = (_mark_edge.w - 1.0);
float __59885934 = (_mark_edge.w - _mark_edge.y);
float __54285935 = max(abs((lerp(0.5, __53825932, clamp(((step((__59495930 * sign(__59495930)), 0.0099999998) * step(__53825932, 0.5)) + (step((__59625931 * sign(__59625931)), 0.0099999998) * step(0.5, __53825932))), 0.0, 1.0)) - 0.5)), abs((lerp(0.5, __28205669, clamp(((step((__59755933 * sign(__59755933)), 0.0099999998) * step(__28205669, 0.5)) + (step((__59885934 * sign(__59885934)), 0.0099999998) * step(0.5, __28205669))), 0.0, 1.0)) - 0.5)));
float __54405936 = (((_mark_ctrl * 0.69999999) * __33395790) * __33465791);
float s173c = (2.0 * __54285935);
(__63615893 = lerp(lerp(__63475792, ((((_mark_inside_color * __54705895) + (lerp(_mark_inside_color, clamp((mul(transpose(float3x3(0.0, 0.69999999, 0.69999999, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0)), (_mark_inside_color - mul(transpose(float3x3(0.080944397, -0.0102485, -0.00036529699, -0.130504, 0.054019298, -0.00412161, 0.116721, -0.113615, 0.69351101)), mul(transpose(float3x3(0.0, 0.0, 0.0, 2.0234399, 1.0, 0.0, -2.52581, 0.0, 1.0)), __55075897)))) + _mark_inside_color), float3(0.0, 0.0, 0.0), float3(1.0, 1.0, 1.0)), __55255898) * __54795896)) + (lerp(_mark_inside_color, clamp((mul(transpose(float3x3(1.0, 0.0, 0.0, 0.69999999, 0.0, 0.69999999, 0.0, 0.0, 1.0)), (_mark_inside_color - mul(transpose(float3x3(0.080944397, -0.0102485, -0.00036529699, -0.130504, 0.054019298, -0.00412161, 0.116721, -0.113615, 0.69351101)), mul(transpose(float3x3(1.0, 0.49420699, 0.0, 0.0, 0.0, 0.0, 0.0, 1.24827, 1.0)), __55075897)))) + _mark_inside_color), float3(0.0, 0.0, 0.0), float3(1.0, 1.0, 1.0)), __55255898) * __54895899)) + (lerp(_mark_inside_color, (lerp(float3(1.0, 1.0, 1.0), clamp((abs(((frac((__67045913.xxx + float3(1.0, 0.66666698, 0.33333299))) * 6.0) - float3(3.0, 3.0, 3.0))) - float3(1.0, 1.0, 1.0)), float3(0.0, 0.0, 0.0), float3(1.0, 1.0, 1.0)), vec3_ctor(__67045913.y)) * __67045913.z), __55255898) * __54965900)), vec3_ctor((__54405936 * max(0.5, (((((s173c * s173c) * s173c) * s173c) * s173c) * s173c))))), ((((_mark_outline_color * __54705895) + (lerp(_mark_outline_color, clamp((mul(transpose(float3x3(0.0, 0.69999999, 0.69999999, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0)), (_mark_outline_color - mul(transpose(float3x3(0.080944397, -0.0102485, -0.00036529699, -0.130504, 0.054019298, -0.00412161, 0.116721, -0.113615, 0.69351101)), mul(transpose(float3x3(0.0, 0.0, 0.0, 2.0234399, 1.0, 0.0, -2.52581, 0.0, 1.0)), __57505915)))) + _mark_outline_color), float3(0.0, 0.0, 0.0), float3(1.0, 1.0, 1.0)), __55255898) * __54795896)) + (lerp(_mark_outline_color, clamp((mul(transpose(float3x3(1.0, 0.0, 0.0, 0.69999999, 0.0, 0.69999999, 0.0, 0.0, 1.0)), (_mark_outline_color - mul(transpose(float3x3(0.080944397, -0.0102485, -0.00036529699, -0.130504, 0.054019298, -0.00412161, 0.116721, -0.113615, 0.69351101)), mul(transpose(float3x3(1.0, 0.49420699, 0.0, 0.0, 0.0, 0.0, 0.0, 1.24827, 1.0)), __57505915)))) + _mark_outline_color), float3(0.0, 0.0, 0.0), float3(1.0, 1.0, 1.0)), __55255898) * __54895899)) + (lerp(_mark_outline_color, (lerp(float3(1.0, 1.0, 1.0), clamp((abs(((frac((__67065928.xxx + float3(1.0, 0.66666698, 0.33333299))) * 6.0) - float3(3.0, 3.0, 3.0))) - float3(1.0, 1.0, 1.0)), float3(0.0, 0.0, 0.0), float3(1.0, 1.0, 1.0)), vec3_ctor(__67065928.y)) * __67065928.z), __55255898) * __54965900)), vec3_ctor((__54405936 * floor((__54285935 * 2.0408199))))));
break;
}
while (false);
}
float3 __63925937 = {0, 0, 0};
if ((__62575703 > 0.1))
{
float __63905938 = {0};
(__63905938 = 0.0);
{ for(float __63895939 = {0.0}; (__63895939 < 6.0); )
{
float __60095940 = (0.2 * __63895939);
(__63905938 = max(max(__63905938, step(abs((__28155667.x - __60095940)), 0.0049999999)), step(abs((__28205669 - __60095940)), 0.0049999999)));
(__63895939 += 1.0);
continue;
}
}
float __60315941 = __28155667.x;
(__63925937 = lerp(__63615893, float3(1.0, 1.0, 1.0), vec3_ctor(((0.5 * __63905938) * (min(step((0.2 * _grid_range.x), __60315941), step(__60315941, (0.2 * _grid_range.z))) * min(step((0.2 * _grid_range.y), __28205669), step(__28205669, (0.2 * _grid_range.w))))))));
}
else
{
(__63925937 = __63615893);
}
int __60805942 = ((int_ctor((__28155667.x * 5.0)) * 5) + int_ctor((__28155667.y * 5.0)));
(out__entryPointOutput = vec4_ctor(lerp(lerp(lerp(__63925937, float3(1.0, 0.0, 0.0), vec3_ctor((0.5 * float_ctor_int(((_red_grids >> __60805942) & 1))))), float3(0.0, 1.0, 0.0), vec3_ctor((0.5 * float_ctor_int(((_green_grids >> __60805942) & 1))))), _FogColor.xyz, vec3_ctor(clamp((_v2f_fog_factor_info * _FogColor.w), 0.0, 1.0))), 1.0));
return generateOutput();
}
