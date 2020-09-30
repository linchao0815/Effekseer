﻿
#ifndef __EFFEKSEER_BASE_PRE_H__
#define __EFFEKSEER_BASE_PRE_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------
#include <array>
#include <atomic>
#include <cfloat>
#include <climits>
#include <memory>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <vector>

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#ifdef _WIN32
#define EFK_STDCALL __stdcall
#else
#define EFK_STDCALL
#endif

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------

#ifdef _WIN32
//#include <windows.h>
#elif defined(_PSVITA)
#include "Effekseer.PSVita.h"
#elif defined(_PS4)
#include "Effekseer.PS4.h"
#elif defined(_SWITCH)
#include "Effekseer.Switch.h"
#elif defined(_XBOXONE)
#include "Effekseer.XBoxOne.h"
#else
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#endif

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
typedef char16_t EFK_CHAR;

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Effekseer
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
struct Vector2D;
struct Vector3D;
struct Matrix43;
struct Matrix44;
struct RectF;

class Manager;
class Effect;
class EffectNode;

class ParticleRenderer;
class SpriteRenderer;
class RibbonRenderer;
class RingRenderer;
class ModelRenderer;
class TrackRenderer;

class Setting;
class EffectLoader;
class TextureLoader;
class MaterialLoader;

class SoundPlayer;
class SoundLoader;

class ModelLoader;
class ProcedualModelGenerator;

class Model;

class CurveLoader;
class Curve;

struct ProcedualModelParameter;

typedef int Handle;

/**
	@brief	Memory Allocation function
*/
typedef void*(EFK_STDCALL* MallocFunc)(unsigned int size);

/**
	@brief	Memory Free function
*/
typedef void(EFK_STDCALL* FreeFunc)(void* p, unsigned int size);

/**
	@brief	AlignedMemory Allocation function
*/
typedef void*(EFK_STDCALL* AlignedMallocFunc)(unsigned int size, unsigned int alignment);

/**
	@brief	AlignedMemory Free function
*/
typedef void(EFK_STDCALL* AlignedFreeFunc)(void* p, unsigned int size);

/**
	@brief	Random Function
*/
typedef int(EFK_STDCALL* RandFunc)(void);

/**
	@brief	エフェクトのインスタンス破棄時のコールバックイベント
	@param	manager	[in]	所属しているマネージャー
	@param	handle	[in]	エフェクトのインスタンスのハンドル
	@param	isRemovingManager	[in]	マネージャーを破棄したときにエフェクトのインスタンスを破棄しているか
*/
typedef void(EFK_STDCALL* EffectInstanceRemovingCallback)(Manager* manager, Handle handle, bool isRemovingManager);

#define ES_SAFE_ADDREF(val) \
	if ((val) != NULL)      \
	{                       \
		(val)->AddRef();    \
	}
#define ES_SAFE_RELEASE(val) \
	if ((val) != NULL)       \
	{                        \
		(val)->Release();    \
		(val) = NULL;        \
	}
#define ES_SAFE_DELETE(val) \
	if ((val) != NULL)      \
	{                       \
		delete (val);       \
		(val) = NULL;       \
	}
#define ES_SAFE_DELETE_ARRAY(val) \
	if ((val) != NULL)            \
	{                             \
		delete[](val);            \
		(val) = NULL;             \
	}

#define EFK_ASSERT(x) assert(x)

//! the maximum number of texture slot which can be specified by an user
const int32_t UserTextureSlotMax = 6;

//! the maximum number of texture slot including textures system specified
const int32_t TextureSlotMax = 8;

const int32_t LocalFieldSlotMax = 4;

const float EFK_PI = 3.141592653589f;

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
/**
	@brief	アルファブレンド
*/
enum class AlphaBlendType : int32_t
{
	/// <summary>
	/// 不透明
	/// </summary>
	Opacity = 0,
	/// <summary>
	/// 透明
	/// </summary>
	Blend = 1,
	/// <summary>
	/// 加算
	/// </summary>
	Add = 2,
	/// <summary>
	/// 減算
	/// </summary>
	Sub = 3,
	/// <summary>
	/// 乗算
	/// </summary>
	Mul = 4,
};

enum class TextureFilterType : int32_t
{
	Nearest = 0,
	Linear = 1,
};

enum class TextureWrapType : int32_t
{
	Repeat = 0,
	Clamp = 1,
};

enum class CullingType : int32_t
{
	Front = 0,
	Back = 1,
	Double = 2,
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
enum class BillboardType : int32_t
{
	Billboard = 0,
	YAxisFixed = 1,
	Fixed = 2,
	RotatedBillboard = 3,
};

enum class CoordinateSystem : int32_t
{
	LH,
	RH,
};

enum class CullingShape : int32_t
{
	NoneShape = 0,
	Sphere = 1,
};

enum class TextureType : int32_t
{
	Color,
	Normal,
	Distortion,
};

enum class MaterialFileType : int32_t
{
	Code,
	Compiled,
};

enum class TextureFormatType : int32_t
{
	ABGR8,
	BC1,
	BC2,
	BC3,
};

enum class ZSortType : int32_t
{
	None,
	NormalOrder,
	ReverseOrder,
};

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
enum class RenderMode : int32_t
{
	Normal,	   // 通常描画
	Wireframe, // ワイヤーフレーム描画
};

/**
	@brief
	\~English	A thread where reload function is called
	\~Japanese	リロードの関数が呼ばれるスレッド
*/
enum class ReloadingThreadType
{
	Main,
	Render,
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
/**
	@brief	最大値取得
*/
template <typename T, typename U>
T Max(T t, U u)
{
	if (t > (T)u)
	{
		return t;
	}
	return u;
}

/**
	@brief	最小値取得
*/
template <typename T, typename U>
T Min(T t, U u)
{
	if (t < (T)u)
	{
		return t;
	}
	return u;
}

/**
	@brief	範囲内値取得
*/
template <typename T, typename U, typename V>
T Clamp(T t, U max_, V min_)
{
	if (t > (T)max_)
	{
		t = (T)max_;
	}

	if (t < (T)min_)
	{
		t = (T)min_;
	}

	return t;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
/**
	@brief	文字コードを変換する。(UTF16 -> UTF8)
	@param	dst	[out]	出力配列の先頭ポインタ
	@param	dst_size	[in]	出力配列の長さ
	@param	src			[in]	入力配列の先頭ポインタ
	@return	文字数
*/
inline int32_t ConvertUtf16ToUtf8(int8_t* dst, int32_t dst_size, const int16_t* src)
{
	int32_t cnt = 0;
	const int16_t* wp = src;
	int8_t* cp = dst;

	if (dst_size == 0)
		return 0;

	dst_size -= 3;

	for (cnt = 0; cnt < dst_size;)
	{
		int16_t wc = *wp++;
		if (wc == 0)
		{
			break;
		}
		if ((wc & ~0x7f) == 0)
		{
			*cp++ = wc & 0x7f;
			cnt += 1;
		}
		else if ((wc & ~0x7ff) == 0)
		{
			*cp++ = ((wc >> 6) & 0x1f) | 0xc0;
			*cp++ = ((wc)&0x3f) | 0x80;
			cnt += 2;
		}
		else
		{
			*cp++ = ((wc >> 12) & 0xf) | 0xe0;
			*cp++ = ((wc >> 6) & 0x3f) | 0x80;
			*cp++ = ((wc)&0x3f) | 0x80;
			cnt += 3;
		}
	}
	*cp = '\0';
	return cnt;
}

/**
    @brief    Convert UTF8 into UTF16
    @param    dst    a pointer to destination buffer
    @param    dst_size    a length of destination buffer
    @param    src            a source buffer
    @return    length except 0
*/
inline int32_t ConvertUtf8ToUtf16(char16_t* dst, int32_t dst_size, const char* src)
{
    int32_t i, code = 0;
    int8_t c0, c1, c2 = 0;
    int8_t* srci = reinterpret_cast<int8_t*>(const_cast<char*>(src));
    if (dst_size == 0)
        return 0;

    dst_size -= 1;

    for (i = 0; i < dst_size; i++)
    {
        uint16_t wc;

        c0 = *srci;
        srci++;
        if (c0 == '\0')
        {
            break;
        }
        // convert UTF8 to UTF16
        code = (uint8_t)c0 >> 4;
        if (code <= 7)
        {
            // 8bit character
            wc = c0;
        }
        else if (code >= 12 && code <= 13)
        {
            // 16bit  character
            c1 = *srci;
            srci++;
            wc = ((c0 & 0x1F) << 6) | (c1 & 0x3F);
        }
        else if (code == 14)
        {
            // 24bit character
            c1 = *srci;
            srci++;
            c2 = *srci;
            srci++;
            wc = ((c0 & 0x0F) << 12) | ((c1 & 0x3F) << 6) | (c2 & 0x3F);
        }
        else
        {
            continue;
        }
        dst[i] = wc;
    }
    dst[i] = 0;
    return i;
}

/**
	@brief	文字コードを変換する。(UTF8 -> UTF16)
	@param	dst	[out]	出力配列の先頭ポインタ
	@param	dst_size	[in]	出力配列の長さ
	@param	src			[in]	入力配列の先頭ポインタ
	@return	文字数
*/
inline int32_t ConvertUtf8ToUtf16(int16_t* dst, int32_t dst_size, const int8_t* src)
{
	int32_t i, code;
	int8_t c0, c1, c2;

	if (dst_size == 0)
		return 0;

	dst_size -= 1;

	for (i = 0; i < dst_size; i++)
	{
		int16_t wc;

		c0 = *src++;
		if (c0 == '\0')
		{
			break;
		}
		// UTF8からUTF16に変換
		code = (uint8_t)c0 >> 4;
		if (code <= 7)
		{
			// 8bit文字
			wc = c0;
		}
		else if (code >= 12 && code <= 13)
		{
			// 16bit文字
			c1 = *src++;
			wc = ((c0 & 0x1F) << 6) | (c1 & 0x3F);
		}
		else if (code == 14)
		{
			// 24bit文字
			c1 = *src++;
			c2 = *src++;
			wc = ((c0 & 0x0F) << 12) | ((c1 & 0x3F) << 6) | (c2 & 0x3F);
		}
		else
		{
			continue;
		}
		dst[i] = wc;
	}
	dst[i] = 0;
	return i;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
/**
@brief	参照カウンタのインターフェース
*/
class IReference
{
public:
	/**
	@brief	参照カウンタを加算する。
	@return	加算後の参照カウンタ
	*/
	virtual int AddRef() = 0;

	/**
	@brief	参照カウンタを取得する。
	@return	参照カウンタ
	*/
	virtual int GetRef() = 0;

	/**
	@brief	参照カウンタを減算する。0になった時、インスタンスを削除する。
	@return	減算後の参照カウンタ
	*/
	virtual int Release() = 0;
};

/**
	@brief	a deleter for IReference
*/
template <typename T>
struct ReferenceDeleter
{
	void operator()(T* ptr) const
	{
		if (ptr != nullptr)
		{
			ptr->Release();
		}
	}
};

template <typename T>
inline std::unique_ptr<T, ReferenceDeleter<T>> CreateUniqueReference(T* ptr, bool addRef = false)
{
	if (ptr == nullptr)
		return std::unique_ptr<T, ReferenceDeleter<T>>(nullptr);

	if (addRef)
	{
		ptr->AddRef();
	}

	return std::unique_ptr<T, ReferenceDeleter<T>>(ptr);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
/**
@brief	参照カウンタオブジェクト
*/
class ReferenceObject : public IReference
{
private:
	mutable std::atomic<int32_t> m_reference;

public:
	ReferenceObject()
		: m_reference(1)
	{
	}

	virtual ~ReferenceObject()
	{
	}

	virtual int AddRef()
	{
		std::atomic_fetch_add_explicit(&m_reference, 1, std::memory_order_consume);

		return m_reference;
	}

	virtual int GetRef()
	{
		return m_reference;
	}

	virtual int Release()
	{
		bool destroy = std::atomic_fetch_sub_explicit(&m_reference, 1, std::memory_order_consume) == 1;
		if (destroy)
		{
			delete this;
			return 0;
		}

		return m_reference;
	}
};

/**
	@brief	This object generates random values.
*/
class IRandObject
{
public:
	IRandObject() = default;
	virtual ~IRandObject() = default;

	virtual int32_t GetRandInt() = 0;

	virtual float GetRand() = 0;

	virtual float GetRand(float min_, float max_) = 0;
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------

enum class ColorSpaceType : int32_t
{
	Gamma,
	Linear,
};

/**
	@brief	\~english	Texture data
			\~japanese	テクスチャデータ
*/
struct TextureData
{
	int32_t Width;
	int32_t Height;
	TextureFormatType TextureFormat;
	void* UserPtr;
	int64_t UserID;

	//! for OpenGL, it is ignored in other apis
	bool HasMipmap = true;
};

enum class ShadingModelType : int32_t
{
	Lit,
	Unlit,
};

/**
	@brief	material type
*/
enum class RendererMaterialType : int32_t
{
	Default = 0,
	BackDistortion = 6,
	Lighting = 7,
	File = 128,
};

/**
	@brief	\~english	Material data
			\~japanese	マテリアルデータ
*/
class MaterialData
{
public:
	ShadingModelType ShadingModel = ShadingModelType::Lit;
	bool IsSimpleVertex = false;
	bool IsRefractionRequired = false;
	int32_t CustomData1 = 0;
	int32_t CustomData2 = 0;
	int32_t TextureCount = 0;
	int32_t UniformCount = 0;
	std::array<TextureWrapType, UserTextureSlotMax> TextureWrapTypes;
	void* UserPtr = nullptr;
	void* ModelUserPtr = nullptr;
	void* RefractionUserPtr = nullptr;
	void* RefractionModelUserPtr = nullptr;

	MaterialData() = default;
	virtual ~MaterialData() = default;
};

/**
	@brief	\~english	Textures used by material
			\~japanese	マテリアルに使用されるテクスチャ
*/
struct MaterialTextureParameter
{
	//! 0 - color, 1 - value
	int32_t Type = 0;
	int32_t Index = 0;
};

/**
	@brief	\~english	Material parameter for shaders
			\~japanese	シェーダー向けマテリアルパラメーター
*/
struct MaterialParameter
{
	//! material index in MaterialType::File
	int32_t MaterialIndex = -1;

	//! used textures in MaterialType::File
	std::vector<MaterialTextureParameter> MaterialTextures;

	//! used uniforms in MaterialType::File
	std::vector<std::array<float, 4>> MaterialUniforms;
};

/**
	@brief	\~english	Parameters about a depth which is passed into a renderer
			\~japanese	レンダラーに渡されるデプスに関するパラメーター
*/
struct NodeRendererDepthParameter
{
	float DepthOffset = 0.0f;
	bool IsDepthOffsetScaledWithCamera = false;
	bool IsDepthOffsetScaledWithParticleScale = false;
	ZSortType ZSort = ZSortType::None;
	float SuppressionOfScalingByDepth = 1.0f;
	float DepthClipping = FLT_MAX;
};

/**
	@brief	\~english	Common parameters which is passed into a renderer
			\~japanese	レンダラーに渡される共通に関するパラメーター
*/
struct NodeRendererBasicParameter
{
	RendererMaterialType MaterialType = RendererMaterialType::Default;
	int32_t Texture1Index = -1;
	int32_t Texture2Index = -1;
	int32_t Texture3Index = -1;
	int32_t Texture4Index = -1;
	int32_t Texture5Index = -1;
	int32_t Texture6Index = -1;
	int32_t Texture7Index = -1;

	float DistortionIntensity = 0.0f;
	MaterialParameter* MaterialParameterPtr = nullptr;
	AlphaBlendType AlphaBlend = AlphaBlendType::Blend;

	TextureFilterType TextureFilter1 = TextureFilterType::Nearest;
	TextureWrapType TextureWrap1 = TextureWrapType::Repeat;
	TextureFilterType TextureFilter2 = TextureFilterType::Nearest;
	TextureWrapType TextureWrap2 = TextureWrapType::Repeat;
	TextureFilterType TextureFilter3 = TextureFilterType::Nearest;
	TextureWrapType TextureWrap3 = TextureWrapType::Repeat;

	TextureFilterType TextureFilter4 = TextureFilterType::Nearest;
	TextureWrapType TextureWrap4 = TextureWrapType::Repeat;

	TextureFilterType TextureFilter5 = TextureFilterType::Nearest;
	TextureWrapType TextureWrap5 = TextureWrapType::Repeat;

	TextureFilterType TextureFilter6 = TextureFilterType::Nearest;
	TextureWrapType TextureWrap6 = TextureWrapType::Repeat;

	TextureFilterType TextureFilter7 = TextureFilterType::Nearest;
	TextureWrapType TextureWrap7 = TextureWrapType::Repeat;

	float UVDistortionIntensity = 1.0f;

	int32_t TextureBlendType = -1;

	float BlendUVDistortionIntensity = 1.0f;

	bool EnableInterpolation = false;
	int32_t UVLoopType = 0;
	int32_t InterpolationType = 0;
	int32_t FlipbookDivideX = 1;
	int32_t FlipbookDivideY = 1;

	int32_t EmissiveScaling = 1;

	float EdgeThreshold = 0.0f;
	uint8_t EdgeColor[4] = { 0 };
	int32_t EdgeColorScaling = 1;

	//! copy from alphacutoff
	bool IsAlphaCutoffEnabled = false;
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
} // namespace Effekseer
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif // __EFFEKSEER_BASE_PRE_H__

#ifndef __EFFEKSEER_CUSTOM_ALLOCATOR_H__
#define __EFFEKSEER_CUSTOM_ALLOCATOR_H__

#include <list>
#include <map>
#include <new>
#include <set>
#include <unordered_map>
#include <vector>

namespace Effekseer
{
/**
	@brief
	\~English get an allocator
	\~Japanese メモリ確保関数を取得する。
*/
MallocFunc GetMallocFunc();

/**
	\~English specify an allocator
	\~Japanese メモリ確保関数を設定する。
*/
void SetMallocFunc(MallocFunc func);

/**
	@brief
	\~English get a deallocator
	\~Japanese メモリ破棄関数を取得する。
*/
FreeFunc GetFreeFunc();

/**
	\~English specify a deallocator
	\~Japanese メモリ破棄関数を設定する。
*/
void SetFreeFunc(FreeFunc func);

/**
	@brief
	\~English get an allocator
	\~Japanese メモリ確保関数を取得する。
*/
AlignedMallocFunc GetAlignedMallocFunc();

/**
	\~English specify an allocator
	\~Japanese メモリ確保関数を設定する。
*/
void SetAlignedMallocFunc(AlignedMallocFunc func);

/**
	@brief
	\~English get a deallocator
	\~Japanese メモリ破棄関数を取得する。
*/
AlignedFreeFunc GetAlignedFreeFunc();

/**
	\~English specify a deallocator
	\~Japanese メモリ破棄関数を設定する。
*/
void SetAlignedFreeFunc(AlignedFreeFunc func);

/**
	@brief
	\~English get an allocator
	\~Japanese メモリ確保関数を取得する。
*/
MallocFunc GetMallocFunc();

/**
	\~English specify an allocator
	\~Japanese メモリ確保関数を設定する。
*/
void SetMallocFunc(MallocFunc func);

/**
	@brief
	\~English get a deallocator
	\~Japanese メモリ破棄関数を取得する。
*/
FreeFunc GetFreeFunc();

/**
	\~English specify a deallocator
	\~Japanese メモリ破棄関数を設定する。
*/
void SetFreeFunc(FreeFunc func);

template <class T>
struct CustomAllocator
{
	using value_type = T;

	CustomAllocator()
	{
	}

	template <class U>
	CustomAllocator(const CustomAllocator<U>&)
	{
	}

	T* allocate(std::size_t n)
	{
		return reinterpret_cast<T*>(GetMallocFunc()(sizeof(T) * static_cast<uint32_t>(n)));
	}
	void deallocate(T* p, std::size_t n)
	{
		GetFreeFunc()(p, sizeof(T) * static_cast<uint32_t>(n));
	}
};

template <class T>
struct CustomAlignedAllocator
{
	using value_type = T;

	CustomAlignedAllocator()
	{
	}

	template <class U>
	CustomAlignedAllocator(const CustomAlignedAllocator<U>&)
	{
	}

	T* allocate(std::size_t n)
	{
		return reinterpret_cast<T*>(GetAlignedMallocFunc()(sizeof(T) * static_cast<uint32_t>(n), 16));
	}
	void deallocate(T* p, std::size_t n)
	{
		GetAlignedFreeFunc()(p, sizeof(T) * static_cast<uint32_t>(n));
	}

	bool operator==(const CustomAlignedAllocator<T>&)
	{
		return true;
	}

	bool operator!=(const CustomAlignedAllocator<T>&)
	{
		return false;
	}
};

template <class T, class U>
bool operator==(const CustomAllocator<T>&, const CustomAllocator<U>&)
{
	return true;
}

template <class T, class U>
bool operator!=(const CustomAllocator<T>&, const CustomAllocator<U>&)
{
	return false;
}

template <class T>
using CustomVector = std::vector<T, CustomAllocator<T>>;
template <class T>
using CustomAlignedVector = std::vector<T, CustomAlignedAllocator<T>>;
template <class T>
using CustomList = std::list<T, CustomAllocator<T>>;
template <class T>
using CustomSet = std::set<T, std::less<T>, CustomAllocator<T>>;
template <class T, class U>
using CustomMap = std::map<T, U, std::less<T>, CustomAllocator<std::pair<const T, U>>>;
template <class T, class U>
using CustomAlignedMap = std::map<T, U, std::less<T>, CustomAlignedAllocator<std::pair<const T, U>>>;
template <class T, class U>
using CustomUnorderedMap = std::unordered_map<T, U, std::hash<T>, std::equal_to<T>, CustomAllocator<std::pair<const T, U>>>;
template <class T, class U>
using CustomAlignedUnorderedMap = std::unordered_map<T, U, std::hash<T>, std::equal_to<T>, CustomAlignedAllocator<std::pair<const T, U>>>;

} // namespace Effekseer

#endif // __EFFEKSEER_BASE_PRE_H__
#ifndef __EFFEKSEER_VECTOR2D_H__
#define __EFFEKSEER_VECTOR2D_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Effekseer
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
/**
	@brief	3次元ベクトル
*/
struct Vector2D
{
public:
	/**
		@brief	X
	*/
	float X;

	/**
		@brief	Y
	*/
	float Y;

	/**
		@brief	コンストラクタ
	*/
	Vector2D();

	/**
		@brief	コンストラクタ
	*/
	Vector2D(float x, float y);

	Vector2D& operator+=(const Vector2D& value);
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
} // namespace Effekseer
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif // __EFFEKSEER_VECTOR3D_H__

#ifndef __EFFEKSEER_VECTOR3D_H__
#define __EFFEKSEER_VECTOR3D_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Effekseer
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
/**
	@brief	3次元ベクトル
*/
struct Vector3D
{
public:
	/**
		@brief	X
	*/
	float X;

	/**
		@brief	Y
	*/
	float Y;

	/**
		@brief	Z
	*/
	float Z;

	/**
		@brief	コンストラクタ
	*/
	Vector3D();

	/**
		@brief	コンストラクタ
	*/
	Vector3D(float x, float y, float z);

	Vector3D operator-();

	Vector3D operator+(const Vector3D& o) const;

	Vector3D operator-(const Vector3D& o) const;

	Vector3D operator*(const float& o) const;

	Vector3D operator/(const float& o) const;

	Vector3D operator*(const Vector3D& o) const;

	Vector3D operator/(const Vector3D& o) const;

	Vector3D& operator+=(const Vector3D& o);

	Vector3D& operator-=(const Vector3D& o);

	Vector3D& operator*=(const float& o);

	Vector3D& operator/=(const float& o);

	bool operator==(const Vector3D& o);

	/**
		@brief	加算
	*/
	static void Add(Vector3D* pOut, const Vector3D* pIn1, const Vector3D* pIn2);

	/**
		@brief	減算
	*/
	static Vector3D& Sub(Vector3D& o, const Vector3D& in1, const Vector3D& in2);

	/**
		@brief	長さ
	*/
	static float Length(const Vector3D& in);

	/**
		@brief	長さの二乗
	*/
	static float LengthSq(const Vector3D& in);

	/**
		@brief	内積
	*/
	static float Dot(const Vector3D& in1, const Vector3D& in2);

	/**
		@brief	単位ベクトル
	*/
	static void Normal(Vector3D& o, const Vector3D& in);

	/**
		@brief	外積
		@note
		右手系の場合、右手の親指がin1、人差し指がin2としたとき、中指の方向を返す。<BR>
		左手系の場合、左手の親指がin1、人差し指がin2としたとき、中指の方向を返す。<BR>
	*/
	static Vector3D& Cross(Vector3D& o, const Vector3D& in1, const Vector3D& in2);

	static Vector3D& Transform(Vector3D& o, const Vector3D& in, const Matrix43& mat);

	static Vector3D& Transform(Vector3D& o, const Vector3D& in, const Matrix44& mat);

	static Vector3D& TransformWithW(Vector3D& o, const Vector3D& in, const Matrix44& mat);
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
} // namespace Effekseer
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif // __EFFEKSEER_VECTOR3D_H__

#ifndef __EFFEKSEER_COLOR_H__
#define __EFFEKSEER_COLOR_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Effekseer
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
enum ColorMode
{
	COLOR_MODE_RGBA,
	COLOR_MODE_HSVA,
	COLOR_MODE_DWORD = 0x7FFFFFFF
};

/**
	@brief	色
*/
#pragma pack(push, 1)
struct Color
{
	/**
		@brief	赤
	*/
	uint8_t R;

	/**
		@brief	緑
	*/
	uint8_t G;

	/**
		@brief	青
	*/
	uint8_t B;

	/**
		@brief	透明度
	*/
	uint8_t A;

	/**
		@brief	コンストラクタ
	*/
	Color() = default;

	/**
		@brief	コンストラクタ
	*/
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

	/**
		@brief	乗算
	*/
	static Color Mul(Color in1, Color in2);
	static Color Mul(Color in1, float in2);

	/**
		@brief	線形補間
	*/
	static Color Lerp(const Color in1, const Color in2, float t);
};
#pragma pack(pop)
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
} // namespace Effekseer
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif // __EFFEKSEER_COLOR_H__

#ifndef __EFFEKSEER_RECTF_H__
#define __EFFEKSEER_RECTF_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Effekseer
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
/**
	@brief	四角形
*/
struct RectF
{
private:
public:
	float X;

	float Y;

	float Width;

	float Height;

	RectF();

	RectF(float x, float y, float width, float height);

	Vector2D Position() const;

	Vector2D Size() const;
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
} // namespace Effekseer
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif // __EFFEKSEER_RECTF_H__

#ifndef __EFFEKSEER_MATRIX43_H__
#define __EFFEKSEER_MATRIX43_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Effekseer
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------

struct Matrix44;

/**
	@brief	4x3行列
	@note
	右手系(回転:反時計回り)<BR>
	V[x,y,z,1] * M の形でベクトルとの乗算が可能である。<BR>
	[0,0][0,1][0,2]<BR>
	[1,0][1,1][1,2]<BR>
	[2,0][2,1][2,2]<BR>
	[3,0][3,1][3,2]<BR>
*/
struct Matrix43
{
private:
public:
	/**
		@brief	行列の値
	*/
	float Value[4][3];

	/**
		@brief	単位行列化を行う。
	*/
	void Indentity();

	/**
		@brief	拡大行列化を行う。
		@param	x	[in]	X方向拡大率
		@param	y	[in]	Y方向拡大率
		@param	z	[in]	Z方向拡大率
	*/
	void Scaling(float x, float y, float z);

	/**
		@brief	反時計周り方向のX軸回転行列化を行う。
		@param	angle	[in]	角度(ラジアン)
	*/
	void RotationX(float angle);

	/**
		@brief	反時計周り方向のY軸回転行列化を行う。
		@param	angle	[in]	角度(ラジアン)
	*/
	void RotationY(float angle);

	/**
		@brief	反時計周り方向のZ軸回転行列化を行う。
		@param	angle	[in]	角度(ラジアン)
	*/
	void RotationZ(float angle);

	/**
		@brief	反時計周り方向のXYZ軸回転行列化を行う。
		@param	rx	[in]	角度(ラジアン)
		@param	ry	[in]	角度(ラジアン)
		@param	rz	[in]	角度(ラジアン)
	*/
	void RotationXYZ(float rx, float ry, float rz);

	/**
		@brief	反時計周り方向のZXY軸回転行列化を行う。
		@param	rz	[in]	角度(ラジアン)
		@param	rx	[in]	角度(ラジアン)
		@param	ry	[in]	角度(ラジアン)
	*/
	void RotationZXY(float rz, float rx, float ry);

	/**
		@brief	任意軸に対する反時計周り方向回転行列化を行う。
		@param	axis	[in]	回転軸
		@param	angle	[in]	角度(ラジアン)
	*/
	void RotationAxis(const Vector3D& axis, float angle);

	/**
		@brief	任意軸に対する反時計周り方向回転行列化を行う。
		@param	axis	[in]	回転軸
		@param	s	[in]	サイン
		@param	c	[in]	コサイン
	*/
	void RotationAxis(const Vector3D& axis, float s, float c);

	/**
		@brief	移動行列化を行う。
		@param	x	[in]	X方向移動
		@param	y	[in]	Y方向移動
		@param	z	[in]	Z方向移動
	*/
	void Translation(float x, float y, float z);

	/**
		@brief	行列を、拡大、回転、移動の行列とベクトルに分解する。
		@param	s	[out]	拡大行列
		@param	r	[out]	回転行列
		@param	t	[out]	位置
	*/
	void GetSRT(Vector3D& s, Matrix43& r, Vector3D& t) const;

	/**
		@brief	行列から拡大ベクトルを取得する。
		@param	s	[out]	拡大ベクトル
	*/
	void GetScale(Vector3D& s) const;

	/**
		@brief	行列から回転行列を取得する。
		@param	s	[out]	回転行列
	*/
	void GetRotation(Matrix43& r) const;

	/**
		@brief	行列から移動ベクトルを取得する。
		@param	t	[out]	移動ベクトル
	*/
	void GetTranslation(Vector3D& t) const;

	/**
		@brief	行列の拡大、回転、移動を設定する。
		@param	s	[in]	拡大行列
		@param	r	[in]	回転行列
		@param	t	[in]	位置
	*/
	void SetSRT(const Vector3D& s, const Matrix43& r, const Vector3D& t);

	/**
		@brief	convert into matrix44
	*/
	void ToMatrix44(Matrix44& dst);

	/**
		@brief	check whether all values are not valid number(not nan, not inf)
	*/
	bool IsValid() const;

	/**
		@brief	行列同士の乗算を行う。
		@param	out	[out]	結果
		@param	in1	[in]	乗算の左側
		@param	in2	[in]	乗算の右側
	*/
	static void Multiple(Matrix43& out, const Matrix43& in1, const Matrix43& in2);
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
} // namespace Effekseer
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif // __EFFEKSEER_MATRIX43_H__

#ifndef __EFFEKSEER_MATRIX44_H__
#define __EFFEKSEER_MATRIX44_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Effekseer
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------

/**
	@brief	行列
	@note
	右手系<BR>
	左手系<BR>
	V[x,y,z,1] * M の形<BR>
	[0,0][0,1][0,2][0,3]
	[1,0][1,1][1,2][1,3]
	[2,0][2,1][2,2][2,3]
	[3,0][3,1][3,2][3,3]
*/
#pragma pack(push, 1)
struct Matrix44
{
private:
public:
	/**
		@brief	コンストラクタ
	*/
	Matrix44();

	/**
		@brief	行列の値
	*/
	float Values[4][4];

	/**
		@brief	単位行列化
	*/
	Matrix44& Indentity();

	/**
	@brief	転置行列化
	*/
	Matrix44& Transpose();

	/**
		@brief	カメラ行列化(右手系)
	*/
	Matrix44& LookAtRH(const Vector3D& eye, const Vector3D& at, const Vector3D& up);

	/**
		@brief	カメラ行列化(左手系)
	*/
	Matrix44& LookAtLH(const Vector3D& eye, const Vector3D& at, const Vector3D& up);

	/**
		@brief	射影行列化(右手系)
	*/
	Matrix44& PerspectiveFovRH(float ovY, float aspect, float zn, float zf);

	/**
		@brief	OpenGL用射影行列化(右手系)
	*/
	Matrix44& PerspectiveFovRH_OpenGL(float ovY, float aspect, float zn, float zf);

	/**
		@brief	射影行列化(左手系)
	*/
	Matrix44& PerspectiveFovLH(float ovY, float aspect, float zn, float zf);

	/**
	 @brief	OpenGL用射影行列化(左手系)
	 */
	Matrix44& PerspectiveFovLH_OpenGL(float ovY, float aspect, float zn, float zf);

	/**
		@brief	正射影行列化(右手系)
	*/
	Matrix44& OrthographicRH(float width, float height, float zn, float zf);

	/**
		@brief	正射影行列化(左手系)
	*/
	Matrix44& OrthographicLH(float width, float height, float zn, float zf);

	/**
		@brief	拡大行列化
	*/
	void Scaling(float x, float y, float z);

	/**
		@brief	X軸回転行列(右手)
	*/
	void RotationX(float angle);

	/**
		@brief	Y軸回転行列(右手)
	*/
	void RotationY(float angle);

	/**
		@brief	Z軸回転行列(右手)
	*/
	void RotationZ(float angle);

	/**
		@brief	移動行列
	*/
	void Translation(float x, float y, float z);

	/**
		@brief	任意軸反時計回転行列
	*/
	void RotationAxis(const Vector3D& axis, float angle);

	/**
		@brief	クオータニオンから行列に変換
	*/
	void Quaternion(float x, float y, float z, float w);

	/**
		@brief	乗算
	*/
	static Matrix44& Mul(Matrix44& o, const Matrix44& in1, const Matrix44& in2);

	/**
		@brief	逆行列
	*/
	static Matrix44& Inverse(Matrix44& o, const Matrix44& in);
};

#pragma pack(pop)
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
} // namespace Effekseer
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif // __EFFEKSEER_MATRIX44_H__

#ifndef __EFFEKSEER_FILE_H__
#define __EFFEKSEER_FILE_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Effekseer
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
/**
	@brief	ファイル読み込みクラス
*/
class FileReader
{
private:
public:
	FileReader()
	{
	}

	virtual ~FileReader()
	{
	}

	virtual size_t Read(void* buffer, size_t size) = 0;

	virtual void Seek(int position) = 0;

	virtual int GetPosition() = 0;

	virtual size_t GetLength() = 0;
};

/**
	@brief	ファイル書き込みクラス
*/
class FileWriter
{
private:
public:
	FileWriter()
	{
	}

	virtual ~FileWriter()
	{
	}

	virtual size_t Write(const void* buffer, size_t size) = 0;

	virtual void Flush() = 0;

	virtual void Seek(int position) = 0;

	virtual int GetPosition() = 0;

	virtual size_t GetLength() = 0;
};

/**
	@brief
	\~English	factory class for io
	\~Japanese	IOのためのファクトリークラス
*/
class FileInterface
{
private:
public:
	FileInterface() = default;
	virtual ~FileInterface() = default;

	virtual FileReader* OpenRead(const EFK_CHAR* path) = 0;

	/**
		@brief
		\~English	try to open a reader. It need not to succeeds in opening it.
		\~Japanese	リーダーを開くことを試します。成功する必要はありません。
	*/
	virtual FileReader* TryOpenRead(const EFK_CHAR* path)
	{
		return OpenRead(path);
	}

	virtual FileWriter* OpenWrite(const EFK_CHAR* path) = 0;
};

} // namespace Effekseer
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif // __EFFEKSEER_FILE_H__

#ifndef __EFFEKSEER_DEFAULT_FILE_H__
#define __EFFEKSEER_DEFAULT_FILE_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Effekseer
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
/**
	@brief	標準のファイル読み込みクラス
*/

class DefaultFileReader : public FileReader
{
private:
	FILE* m_filePtr;

public:
	DefaultFileReader(FILE* filePtr);

	~DefaultFileReader();

	size_t Read(void* buffer, size_t size);

	void Seek(int position);

	int GetPosition();

	size_t GetLength();
};

class DefaultFileWriter : public FileWriter
{
private:
	FILE* m_filePtr;

public:
	DefaultFileWriter(FILE* filePtr);

	~DefaultFileWriter();

	size_t Write(const void* buffer, size_t size);

	void Flush();

	void Seek(int position);

	int GetPosition();

	size_t GetLength();
};

class DefaultFileInterface : public FileInterface
{
private:
public:
	FileReader* OpenRead(const EFK_CHAR* path);

	FileWriter* OpenWrite(const EFK_CHAR* path);
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
} // namespace Effekseer
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif // __EFFEKSEER_DEFAULT_FILE_H__

#ifndef __EFFEKSEER_EFFECT_H__
#define __EFFEKSEER_EFFECT_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Effekseer
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------

/**
@brief
\~English	Terms where an effect exists
\~Japanese	エフェクトが存在する期間
*/
struct EffectTerm
{
	/**
@brief
\~English	Minimum end time that the effect may exist
\~Japanese	エフェクトが存在する可能性のある最小の終了時間
*/
	int32_t TermMin;

	/**
	@brief
	\~English	Maximum end time that the effect may exist
	\~Japanese	エフェクトが存在する可能性のある最大の終了時間
	*/
	int32_t TermMax;
};

/**
@brief
\~English	Terms where instances exists
\~Japanese	インスタンスが存在する期間
*/
struct EffectInstanceTerm
{
	/**
	@brief
	\~English	Minimum start time that the first instance may exist
	\~Japanese	最初のインスタンスが存在する可能性のある最小の開始時間
	*/
	int32_t FirstInstanceStartMin = 0;

	/**
	@brief
	\~English	Maximum start time that the first instance may exist
	\~Japanese	最初のインスタンスが存在する可能性のある最大の開始時間
	*/
	int32_t FirstInstanceStartMax = 0;

	/**
	@brief
	\~English	Minimum end time that the first instance may exist
	\~Japanese	最初のインスタンスが存在する可能性のある最小の終了時間
	*/
	int32_t FirstInstanceEndMin = INT_MAX;

	/**
	@brief
	\~English	Maximum end time that the first instance may exist
	\~Japanese	最初のインスタンスが存在する可能性のある最大の終了時間
	*/
	int32_t FirstInstanceEndMax = INT_MAX;

	/**
	@brief
	\~English	Minimum start time that the last instance may exist
	\~Japanese	最後のインスタンスが存在する可能性のある最小の開始時間
	*/
	int32_t LastInstanceStartMin = 0;

	/**
	@brief
	\~English	Maximum start time that the last instance may exist
	\~Japanese	最後のインスタンスが存在する可能性のある最大の開始時間
	*/
	int32_t LastInstanceStartMax = 0;

	/**
	@brief
	\~English	Minimum end time that the last instance may exist
	\~Japanese	最後のインスタンスが存在する可能性のある最小の終了時間
	*/
	int32_t LastInstanceEndMin = INT_MAX;

	/**
	@brief
	\~English	Maximum end time that the last instance may exist
	\~Japanese	最後のインスタンスが存在する可能性のある最大の終了時間
	*/
	int32_t LastInstanceEndMax = INT_MAX;
};

/**
	@brief
	\~English A class to edit an instance of EffectParameter for supporting original format when a binary is loaded.
	\~Japanese	独自フォーマットをサポートするための、バイナリが読み込まれた時にEffectParameterのインスタンスを編集するクラス
*/
class EffectFactory : public ReferenceObject
{
public:
	EffectFactory();

	virtual ~EffectFactory();

	/**
	@brief
	\~English load body data(parameters of effect) from a binary
	\~Japanese	バイナリから本体(エフェクトのパラメーター)を読み込む。
	*/
	bool LoadBody(Effect* effect, const void* data, int32_t size, float magnification, const EFK_CHAR* materialPath);

	/**
	@brief
	\~English set texture data into specified index
	\~Japanese	指定されたインデックスにテクスチャを設定する。
	*/
	void SetTexture(Effect* effect, int32_t index, TextureType type, TextureData* data);

	/**
	@brief
	\~English set sound data into specified index
	\~Japanese	指定されたインデックスに音を設定する。
	*/

	void SetSound(Effect* effect, int32_t index, void* data);

	/**
	@brief
	\~English set model data into specified index
	\~Japanese	指定されたインデックスにモデルを設定する。
	*/
	void SetModel(Effect* effect, int32_t index, Model* data);

	/**
	@brief
	\~English set material data into specified index
	\~Japanese	指定されたインデックスにマテリアルを設定する。
	*/
	void SetMaterial(Effect* effect, int32_t index, MaterialData* data);

	/**
	@brief
	\~English set curve data into specified index
	\~Japanese	指定されたインデックスにカーブを設定する。
	*/
	void SetCurve(Effect* effect, int32_t index, void* data);

	/**
	@brief
	\~English set model data into specified index
	\~Japanese	指定されたインデックスにモデルを設定する。
	*/
	void SetProcedualModel(Effect* effect, int32_t index, Model* data);

	/**
	@brief
	\~English set loading data
	\~Japanese	ロード用データを設定する。
	*/
	void SetLoadingParameter(Effect* effect, ReferenceObject* obj);

	/**
		@brief
		\~English this method is called to check whether loaded binary are supported.
		\~Japanese	バイナリがサポートされているか確認するためにこのメソッドが呼ばれる。
	*/
	virtual bool OnCheckIsBinarySupported(const void* data, int32_t size);

	/**
		@brief
		\~English this method is called to check whether reloading are supported.
		\~Japanese	リロードがサポートされているか確認するためにこのメソッドが呼ばれる。
	*/
	virtual bool OnCheckIsReloadSupported();

	/**
		@brief
		\~English this method is called when load a effect from binary
		\~Japanese	バイナリからエフェクトを読み込む時に、このメソッドが呼ばれる。
	*/
	virtual bool OnLoading(Effect* effect, const void* data, int32_t size, float magnification, const EFK_CHAR* materialPath);

	/**
		@brief
		\~English this method is called when load resources
		\~Japanese	リソースを読み込む時に、このメソッドが呼ばれる。
	*/
	virtual void OnLoadingResource(Effect* effect, const void* data, int32_t size, const EFK_CHAR* materialPath);

	/**
	@brief
	\~English this method is called when unload resources
	\~Japanese	リソースを廃棄される時に、このメソッドが呼ばれる。
	*/
	virtual void OnUnloadingResource(Effect* effect);

	/**
	\~English get factory's name
	\~Japanese	ファクトリーの名称を取得する。
	*/
	virtual const char* GetName() const;

	/**
	\~English get whether resources are loaded automatically when a binary is loaded
	\~Japanese	バイナリを読み込んだときに自動的にリソースを読み込むか取得する。
	*/
	virtual bool GetIsResourcesLoadedAutomatically() const;
};

/**
	@brief
	\~English	Effect parameters
	\~Japanese	エフェクトパラメータークラス
*/
class Effect : public IReference
{
protected:
	Effect()
	{
	}
	virtual ~Effect()
	{
	}

public:
	/**
		@brief	エフェクトを生成する。
		@param	manager			[in]	管理クラス
		@param	data			[in]	データ配列の先頭のポインタ
		@param	size			[in]	データ配列の長さ
		@param	magnification	[in]	読み込み時の拡大率
		@param	materialPath	[in]	素材ロード時の基準パス
		@return	エフェクト。失敗した場合はNULLを返す。
	*/
	static Effect* Create(Manager* manager, void* data, int32_t size, float magnification = 1.0f, const EFK_CHAR* materialPath = NULL);

	/**
		@brief	エフェクトを生成する。
		@param	manager			[in]	管理クラス
		@param	path			[in]	読込元のパス
		@param	magnification	[in]	読み込み時の拡大率
		@param	materialPath	[in]	素材ロード時の基準パス
		@return	エフェクト。失敗した場合はNULLを返す。
	*/
	static Effect* Create(Manager* manager, const EFK_CHAR* path, float magnification = 1.0f, const EFK_CHAR* materialPath = NULL);

	/**
	@brief	エフェクトを生成する。
	@param	setting			[in]	設定クラス
	@param	data			[in]	データ配列の先頭のポインタ
	@param	size			[in]	データ配列の長さ
	@param	magnification	[in]	読み込み時の拡大率
	@param	materialPath	[in]	素材ロード時の基準パス
	@return	エフェクト。失敗した場合はNULLを返す。
*/
	static Effect* Create(Setting* setting, void* data, int32_t size, float magnification = 1.0f, const EFK_CHAR* materialPath = NULL);

	/**
		@brief	エフェクトを生成する。
		@param	setting			[in]	設定クラス
		@param	path			[in]	読込元のパス
		@param	magnification	[in]	読み込み時の拡大率
		@param	materialPath	[in]	素材ロード時の基準パス
		@return	エフェクト。失敗した場合はNULLを返す。
	*/
	static Effect* Create(Setting* setting, const EFK_CHAR* path, float magnification = 1.0f, const EFK_CHAR* materialPath = NULL);

	/**
	@brief	標準のエフェクト読込インスタンスを生成する。
	*/
	static ::Effekseer::EffectLoader* CreateEffectLoader(::Effekseer::FileInterface* fileInterface = NULL);

	/**
	@brief
	\~English	Get this effect's name. If this effect is loaded from file, default name is file name without extention.
	\~Japanese	エフェクトの名前を取得する。もしファイルからエフェクトを読み込んだ場合、名前は拡張子を除いたファイル名である。
	*/
	virtual const char16_t* GetName() const = 0;

	/**
		\~English	Set this effect's name
	\~Japanese	エフェクトの名前を設定する。
	*/
	virtual void SetName(const char16_t* name) = 0;

	/**
	@brief	設定を取得する。
	@return	設定
	*/
	virtual Setting* GetSetting() const = 0;

	/**
	@brief	\~English	Get the magnification multiplied by the magnification at the time of loaded and exported.
			\~Japanese	読み込み時と出力時の拡大率をかけた拡大率を取得する。
	*/
	virtual float GetMaginification() const = 0;

	/**
		@brief	エフェクトデータのバージョン取得
	*/
	virtual int GetVersion() const = 0;

	/**
		@brief
		\~English	Get loading parameter supecfied by EffectFactory. This parameter is not used unless EffectFactory is used
		\~Japanese
	   EffectFactoryによって指定されたロード用パラメーターを取得する。EffectFactoryを使用しない限り、子のパラメーターは使用しない。
	*/
	virtual ReferenceObject* GetLoadingParameter() const = 0;

	/**
		@brief	格納されている色画像のポインタを取得する。
		@param	n	[in]	画像のインデックス
		@return	画像のポインタ
	*/
	virtual TextureData* GetColorImage(int n) const = 0;

	/**
	@brief	格納されている画像のポインタの個数を取得する。
	*/
	virtual int32_t GetColorImageCount() const = 0;

	/**
	@brief	\~English	Get a color image's path
	\~Japanese	色画像のパスを取得する。
	*/
	virtual const EFK_CHAR* GetColorImagePath(int n) const = 0;

	/**
	@brief	格納されている法線画像のポインタを取得する。
	@param	n	[in]	画像のインデックス
	@return	画像のポインタ
	*/
	virtual TextureData* GetNormalImage(int n) const = 0;

	/**
	@brief	格納されている法線画像のポインタの個数を取得する。
	*/
	virtual int32_t GetNormalImageCount() const = 0;

	/**
	@brief	\~English	Get a normal image's path
	\~Japanese	法線画像のパスを取得する。
	*/
	virtual const EFK_CHAR* GetNormalImagePath(int n) const = 0;

	/**
	@brief	格納されている歪み画像のポインタを取得する。
	@param	n	[in]	画像のインデックス
	@return	画像のポインタ
	*/
	virtual TextureData* GetDistortionImage(int n) const = 0;

	/**
	@brief	格納されている歪み画像のポインタの個数を取得する。
	*/
	virtual int32_t GetDistortionImageCount() const = 0;

	/**
	@brief	\~English	Get a distortion image's path
	\~Japanese	歪み画像のパスを取得する。
	*/
	virtual const EFK_CHAR* GetDistortionImagePath(int n) const = 0;

	/**
		@brief	格納されている音波形のポインタを取得する。
	*/
	virtual void* GetWave(int n) const = 0;

	/**
	@brief	格納されている音波形のポインタの個数を取得する。
	*/
	virtual int32_t GetWaveCount() const = 0;

	/**
	@brief	\~English	Get a wave's path
	\~Japanese	音波形のパスを取得する。
	*/
	virtual const EFK_CHAR* GetWavePath(int n) const = 0;

	/**
		@brief	格納されているモデルのポインタを取得する。
	*/
	virtual Model* GetModel(int n) const = 0;

	/**
	@brief	格納されているモデルのポインタの個数を取得する。
	*/
	virtual int32_t GetModelCount() const = 0;

	/**
	@brief	\~English	Get a model's path
	\~Japanese	モデルのパスを取得する。
	*/
	virtual const EFK_CHAR* GetModelPath(int n) const = 0;

	/**
	@brief	\~English	Get a material's pointer
	\~Japanese	格納されているマテリアルのポインタを取得する。
	*/
	virtual MaterialData* GetMaterial(int n) const = 0;

	/**
	@brief	\~English	Get the number of stored material pointer
	\~Japanese	格納されているマテリアルのポインタの個数を取得する。
	*/
	virtual int32_t GetMaterialCount() const = 0;

	/**
	@brief	\~English	Get a material's path
	\~Japanese	マテリアルのパスを取得する。
	*/
	virtual const EFK_CHAR* GetMaterialPath(int n) const = 0;

	/**
	@brief	\~English	Get a curve's pointer
	\~Japanese	格納されているカーブのポインタを取得する。
	*/
	virtual void* GetCurve(int n) const = 0;

	/**
	@brief	\~English	Get the number of stored curve pointer
	\~Japanese	格納されているカーブのポインタの個数を取得する。
	*/
	virtual int32_t GetCurveCount() const = 0;

	/**
	@brief	\~English	Get a curve's path
	\~Japanese	カーブのパスを取得する。
	*/
	virtual const EFK_CHAR* GetCurvePath(int n) const = 0;

	/**
	@brief	\~English	Get a procedual model's pointer
	\~Japanese	格納されているプロシージャルモデルのポインタを取得する。
	*/
	virtual Model* GetProcedualModel(int n) const = 0;

	/**
	@brief	\~English	Get the number of stored procedual model's pointer
	\~Japanese	格納されているプロシージャルモデルのポインタの個数を取得する。
	*/
	virtual int32_t GetProcedualModelCount() const = 0;

	/**
	@brief	\~English	Get a procedual model's parameter
	\~Japanese	格納されているプロシージャルモデルのパラメーターを取得する。
	*/
	virtual const ProcedualModelParameter* GetProcedualModelParameter(int n) const = 0;

	/**
		@brief
		\~English set texture data into specified index
		\~Japanese	指定されたインデックスにテクスチャを設定する。
	*/
	virtual void SetTexture(int32_t index, TextureType type, TextureData* data) = 0;

	/**
		@brief
		\~English set sound data into specified index
		\~Japanese	指定されたインデックスに音を設定する。
	*/

	virtual void SetSound(int32_t index, void* data) = 0;

	/**
		@brief
		\~English set model data into specified index
		\~Japanese	指定されたインデックスにモデルを設定する。
	*/
	virtual void SetModel(int32_t index, Model* data) = 0;

	/**
		@brief
		\~English set material data into specified index
		\~Japanese	指定されたインデックスにマテリアルを設定する。
	*/
	virtual void SetMaterial(int32_t index, MaterialData* data) = 0;

	/**
		@brief
		\~English set curve data into specified index
		\~Japanese	指定されたインデックスにカーブを設定する。
	*/
	virtual void SetCurve(int32_t index, void* data) = 0;

	/**
		@brief
		\~English	Reload this effect
		\~Japanese	エフェクトのリロードを行う。
		@param	data
		\~English	An effect's data
		\~Japanese	エフェクトのデータ
		@param	size
		\~English	An effect's size
		\~Japanese	エフェクトのデータサイズ
		@param	materialPath
		\~English	A path where reaources are loaded
		\~Japanese	リソースの読み込み元
		@param	reloadingThreadType
		\~English	A thread where reload function is called
		\~Japanese	リロードの関数が呼ばれるスレッド
		@return
		\~English	Result
		\~Japanese	結果
		@note
		\~English
		If reloadingThreadType is RenderThread, new resources aren't loaded and old resources aren't disposed.
		\~Japanese
		もし、reloadingThreadType が RenderThreadの場合、新規のリソースは読み込まれず、古いリソースは破棄されない。
	*/
	virtual bool Reload(void* data,
						int32_t size,
						const EFK_CHAR* materialPath = nullptr,
						ReloadingThreadType reloadingThreadType = ReloadingThreadType::Main) = 0;

	/**
		@brief
		\~English	Reload this effect
		\~Japanese	エフェクトのリロードを行う。
		@param	path
		\~English	An effect's path
		\~Japanese	エフェクトのパス
		@param	materialPath
		\~English	A path where reaources are loaded
		\~Japanese	リソースの読み込み元
		@param	reloadingThreadType
		\~English	A thread where reload function is called
		\~Japanese	リロードの関数が呼ばれるスレッド
		@return
		\~English	Result
		\~Japanese	結果
		@note
		\~English
		If reloadingThreadType is RenderThread, new resources aren't loaded and old resources aren't disposed.
		\~Japanese
		もし、reloadingThreadType が RenderThreadの場合、新規のリソースは読み込まれず、古いリソースは破棄されない。
	*/
	virtual bool Reload(const EFK_CHAR* path,
						const EFK_CHAR* materialPath = nullptr,
						ReloadingThreadType reloadingThreadType = ReloadingThreadType::Main) = 0;

	/**
		@brief
		\~English	Reload this effect
		\~Japanese	エフェクトのリロードを行う。
		@param	managers
		\~English	An array of manager instances
		\~Japanese	マネージャーの配列
		@param	managersCount
		\~English	Length of array
		\~Japanese	マネージャーの個数
		@param	data
		\~English	An effect's data
		\~Japanese	エフェクトのデータ
		@param	size
		\~English	An effect's size
		\~Japanese	エフェクトのデータサイズ
		@param	materialPath
		\~English	A path where reaources are loaded
		\~Japanese	リソースの読み込み元
		@param	reloadingThreadType
		\~English	A thread where reload function is called
		\~Japanese	リロードの関数が呼ばれるスレッド
		@return
		\~English	Result
		\~Japanese	結果
		@note
		\~English
		If an effect is generated with Setting, the effect in managers is reloaded with managers
		If reloadingThreadType is RenderThread, new resources aren't loaded and old resources aren't disposed.
		\~Japanese
		Settingを用いてエフェクトを生成したときに、Managerを指定することで対象のManager内のエフェクトのリロードを行う。
		もし、reloadingThreadType が RenderThreadの場合、新規のリソースは読み込まれず、古いリソースは破棄されない。
	*/
	virtual bool Reload(Manager** managers,
						int32_t managersCount,
						void* data,
						int32_t size,
						const EFK_CHAR* materialPath = nullptr,
						ReloadingThreadType reloadingThreadType = ReloadingThreadType::Main) = 0;

	/**
		@brief
		\~English	Reload this effect
		\~Japanese	エフェクトのリロードを行う。
		@param	managers
		\~English	An array of manager instances
		\~Japanese	マネージャーの配列
		@param	managersCount
		\~English	Length of array
		\~Japanese	マネージャーの個数
		@param	path
		\~English	An effect's path
		\~Japanese	エフェクトのパス
		@param	materialPath
		\~English	A path where reaources are loaded
		\~Japanese	リソースの読み込み元
		@param	reloadingThreadType
		\~English	A thread where reload function is called
		\~Japanese	リロードの関数が呼ばれるスレッド
		@return
		\~English	Result
		\~Japanese	結果
		@note
		\~English
		If an effect is generated with Setting, the effect in managers is reloaded with managers
		If reloadingThreadType is RenderThread, new resources aren't loaded and old resources aren't disposed.
		\~Japanese
		Settingを用いてエフェクトを生成したときに、Managerを指定することで対象のManager内のエフェクトのリロードを行う。
		もし、reloadingThreadType が RenderThreadの場合、新規のリソースは読み込まれず、古いリソースは破棄されない。
	*/
	virtual bool Reload(Manager** managers,
						int32_t managersCount,
						const EFK_CHAR* path,
						const EFK_CHAR* materialPath = nullptr,
						ReloadingThreadType reloadingThreadType = ReloadingThreadType::Main) = 0;

	/**
		@brief	画像等リソースの再読み込みを行う。
	*/
	virtual void ReloadResources(const void* data = nullptr, int32_t size = 0, const EFK_CHAR* materialPath = nullptr) = 0;

	/**
		@brief	画像等リソースの破棄を行う。
	*/
	virtual void UnloadResources() = 0;

	/**
	@brief	Rootを取得する。
	*/
	virtual EffectNode* GetRoot() const = 0;

	/**
		@brief
	\~English	Calculate a term of instances where the effect exists
	\~Japanese	エフェクトが存在する期間を計算する。
	*/
	virtual EffectTerm CalculateTerm() const = 0;
};

/**
@brief	共通描画パラメーター
@note
大きく変更される可能性があります。
*/
struct EffectBasicRenderParameter
{
	int32_t ColorTextureIndex;

	int32_t AlphaTextureIndex;
	TextureWrapType AlphaTexWrapType;

	int32_t UVDistortionIndex;
	TextureWrapType UVDistortionTexWrapType;

	int32_t BlendTextureIndex;
	TextureWrapType BlendTexWrapType;

	int32_t BlendAlphaTextureIndex;
	TextureWrapType BlendAlphaTexWrapType;

	int32_t BlendUVDistortionTextureIndex;
	TextureWrapType BlendUVDistortionTexWrapType;

	struct FlipbookParameters
	{
		bool Enable;
		int32_t LoopType;
		int32_t DivideX;
		int32_t DivideY;
	} FlipbookParams;

	RendererMaterialType MaterialType;

	float UVDistortionIntensity;

	int32_t TextureBlendType;

	float BlendUVDistortionIntensity;

	bool EnableFalloff;
	struct
	{
		int32_t ColorBlendType;
		float BeginColor[4];
		float EndColor[4];
		float Pow = 1.0f;
	} FalloffParam;

	int32_t EmissiveScaling;

	struct
	{
		float Color[4];
		float Threshold;
		int32_t ColorScaling;
	} EdgeParam;

	AlphaBlendType AlphaBlend;
	TextureFilterType FilterType;
	TextureWrapType WrapType;
	bool ZWrite;
	bool ZTest;
	bool Distortion;
	float DistortionIntensity;
};

/**
@brief
	\~English	Model parameter
	\~Japanese	モデルパラメーター
@note
	\~English	It may change greatly.
	\~Japanese	大きく変更される可能性があります。

*/
struct EffectModelParameter
{
	bool Lighting;
};

/**
@brief	ノードインスタンス生成クラス
@note
エフェクトのノードの実体を生成する。
*/
class EffectNode
{
public:
	EffectNode()
	{
	}
	virtual ~EffectNode()
	{
	}

	/**
	@brief	ノードが所属しているエフェクトを取得する。
	*/
	virtual Effect* GetEffect() const = 0;

	/**
	@brief
	\~English	Get a generation in the node tree. The generation increases by 1 as it moves a child node.
	\~Japanese	ノードツリーの世代を取得する。世代は子のノードになるにしたがって1増える。
	*/
	virtual int GetGeneration() const = 0;

	/**
	@brief	子のノードの数を取得する。
	*/
	virtual int GetChildrenCount() const = 0;

	/**
	@brief	子のノードを取得する。
	*/
	virtual EffectNode* GetChild(int index) const = 0;

	/**
	@brief	共通描画パラメーターを取得する。
	*/
	virtual EffectBasicRenderParameter GetBasicRenderParameter() = 0;

	/**
	@brief	共通描画パラメーターを設定する。
	*/
	virtual void SetBasicRenderParameter(EffectBasicRenderParameter param) = 0;

	/**
	@brief
	\~English	Get a model parameter
	\~Japanese	モデルパラメーターを取得する。
	*/
	virtual EffectModelParameter GetEffectModelParameter() = 0;

	/**
	@brief
	\~English	Calculate a term of instances where instances exists
	\~Japanese	インスタンスが存在する期間を計算する。
	*/
	virtual EffectInstanceTerm CalculateInstanceTerm(EffectInstanceTerm& parentTerm) const = 0;
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
} // namespace Effekseer
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif // __EFFEKSEER_EFFECT_H__

#ifndef __EFFEKSEER_MANAGER_H__
#define __EFFEKSEER_MANAGER_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Effekseer
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------

/**
	@brief エフェクト管理クラス
*/
class Manager : public IReference
{
public:
	/**
		@brief
		\~English Parameters when a manager is updated
		\~Japanese マネージャーが更新されるときのパラメーター
	*/
	struct UpdateParameter
	{
		/**
			@brief
			\~English A passing frame
			\~Japanese 経過するフレーム
		*/
		float DeltaFrame = 1.0f;

		/**
			@brief
			\~English An update interval
			\~Japanese 更新間隔
			@note
			\~English For example, DeltaTime is 2 and UpdateInterval is 1, an effect is update twice
			\~Japanese 例えば、DeltaTimeが2でUpdateIntervalが1の場合、エフェクトは2回更新される。
		*/
		float UpdateInterval = 1.0f;
	};

	/**
	@brief
		@brief
		\~English Parameters for Manager::Draw and Manager::DrawHandle
		\~Japanese Manager::Draw and Manager::DrawHandleに使用するパラメーター
	*/
	struct DrawParameter
	{
		Vector3D CameraPosition;
		Vector3D CameraDirection;

		/**
			@brief
			\~English A bitmask to show effects
			\~Japanese エフェクトを表示するためのビットマスク
			@note
			\~English For example, if effect's layer is 1 and CameraCullingMask's first bit is 1, this effect is shown.
			\~Japanese 例えば、エフェクトのレイヤーが0でカリングマスクの最初のビットが1のときエフェクトは表示される。
		*/
		int32_t CameraCullingMask;

		DrawParameter();
	};

protected:
	Manager()
	{
	}
	virtual ~Manager()
	{
	}

public:
	/**
		@brief マネージャーを生成する。
		@param	instance_max	[in]	最大インスタンス数
		@param	autoFlip		[in]	自動でスレッド間のデータを入れ替えるかどうか、を指定する。trueの場合、Update時に入れ替わる。
		@return	マネージャー
	*/
	static Manager* Create(int instance_max, bool autoFlip = true);

	/**
		@brief マネージャーを破棄する。
		@note
		このマネージャーから生成されたエフェクトは全て強制的に破棄される。
	*/
	virtual void Destroy() = 0;

	/**
		@brief
		\~English Starts a specified number of worker threads
		\~Japanese 指定した数のワーカースレッドを起動する
	*/
	virtual void LaunchWorkerThreads(uint32_t threadCount) = 0;

	/**
		@brief
		\~English Get a thread handle (HANDLE(win32), pthread_t(posix) or etc.)
		\~Japanese スレッドハンドルを取得する。(HANDLE(win32) や pthread_t(posix) など)
	*/
	virtual uintptr_t GetWorkerThreadHandle(uint32_t threadID) = 0;

	/**
		@brief
		\~English get an allocator
		\~Japanese メモリ確保関数を取得する。
	*/
	virtual MallocFunc GetMallocFunc() const = 0;

	/**
		\~English specify an allocator
		\~Japanese メモリ確保関数を設定する。
	*/
	virtual void SetMallocFunc(MallocFunc func) = 0;

	/**
		@brief
		\~English get a deallocator
		\~Japanese メモリ破棄関数を取得する。
	*/
	virtual FreeFunc GetFreeFunc() const = 0;

	/**
		\~English specify a deallocator
		\~Japanese メモリ破棄関数を設定する。
	*/
	virtual void SetFreeFunc(FreeFunc func) = 0;

	/**
		@brief	ランダム関数を取得する。
	*/
	virtual RandFunc GetRandFunc() const = 0;

	/**
		@brief	ランダム関数を設定する。
	*/
	virtual void SetRandFunc(RandFunc func) = 0;

	/**
		@brief	ランダム最大値を取得する。
	*/
	virtual int GetRandMax() const = 0;

	/**
		@brief	ランダム関数を設定する。
	*/
	virtual void SetRandMax(int max_) = 0;

	/**
		@brief	座標系を取得する。
		@return	座標系
	*/
	virtual CoordinateSystem GetCoordinateSystem() const = 0;

	/**
		@brief	座標系を設定する。
		@param	coordinateSystem	[in]	座標系
		@note
		座標系を設定する。
		エフェクトファイルを読み込む前に設定する必要がある。
	*/
	virtual void SetCoordinateSystem(CoordinateSystem coordinateSystem) = 0;

	/**
		@brief	スプライト描画機能を取得する。
	*/
	virtual SpriteRenderer* GetSpriteRenderer() = 0;

	/**
		@brief	スプライト描画機能を設定する。
	*/
	virtual void SetSpriteRenderer(SpriteRenderer* renderer) = 0;

	/**
		@brief	ストライプ描画機能を取得する。
	*/
	virtual RibbonRenderer* GetRibbonRenderer() = 0;

	/**
		@brief	ストライプ描画機能を設定する。
	*/
	virtual void SetRibbonRenderer(RibbonRenderer* renderer) = 0;

	/**
		@brief	リング描画機能を取得する。
	*/
	virtual RingRenderer* GetRingRenderer() = 0;

	/**
		@brief	リング描画機能を設定する。
	*/
	virtual void SetRingRenderer(RingRenderer* renderer) = 0;

	/**
		@brief	モデル描画機能を取得する。
	*/
	virtual ModelRenderer* GetModelRenderer() = 0;

	/**
		@brief	モデル描画機能を設定する。
	*/
	virtual void SetModelRenderer(ModelRenderer* renderer) = 0;

	/**
		@brief	軌跡描画機能を取得する。
	*/
	virtual TrackRenderer* GetTrackRenderer() = 0;

	/**
		@brief	軌跡描画機能を設定する。
	*/
	virtual void SetTrackRenderer(TrackRenderer* renderer) = 0;

	/**
		@brief	設定クラスを取得する。
	*/
	virtual Setting* GetSetting() = 0;

	/**
		@brief	設定クラスを設定する。
		@param	setting	[in]	設定
	*/
	virtual void SetSetting(Setting* setting) = 0;

	/**
		@brief	エフェクト読込クラスを取得する。
	*/
	virtual EffectLoader* GetEffectLoader() = 0;

	/**
		@brief	エフェクト読込クラスを設定する。
	*/
	virtual void SetEffectLoader(EffectLoader* effectLoader) = 0;

	/**
		@brief	テクスチャ読込クラスを取得する。
	*/
	virtual TextureLoader* GetTextureLoader() = 0;

	/**
		@brief	テクスチャ読込クラスを設定する。
	*/
	virtual void SetTextureLoader(TextureLoader* textureLoader) = 0;

	/**
		@brief	サウンド再生機能を取得する。
	*/
	virtual SoundPlayer* GetSoundPlayer() = 0;

	/**
		@brief	サウンド再生機能を設定する。
	*/
	virtual void SetSoundPlayer(SoundPlayer* soundPlayer) = 0;

	/**
		@brief	サウンド読込クラスを取得する
	*/
	virtual SoundLoader* GetSoundLoader() = 0;

	/**
		@brief	サウンド読込クラスを設定する。
	*/
	virtual void SetSoundLoader(SoundLoader* soundLoader) = 0;

	/**
		@brief	モデル読込クラスを取得する。
	*/
	virtual ModelLoader* GetModelLoader() = 0;

	/**
		@brief	モデル読込クラスを設定する。
	*/
	virtual void SetModelLoader(ModelLoader* modelLoader) = 0;

	/**
		@brief
		\~English get a material loader
		\~Japanese マテリアルローダーを取得する。
		@return
		\~English	loader
		\~Japanese ローダー
	*/
	virtual MaterialLoader* GetMaterialLoader() = 0;

	/**
		@brief
		\~English specfiy a material loader
		\~Japanese マテリアルローダーを設定する。
		@param	loader
		\~English	loader
		\~Japanese ローダー
	*/
	virtual void SetMaterialLoader(MaterialLoader* loader) = 0;

	/**
		@brief
		\~English get a curve loader
		\~Japanese カーブローダーを取得する。
		@return
		\~English	loader
		\~Japanese ローダー
	*/
	virtual CurveLoader* GetCurveLoader() = 0;

	/**
		@brief
		\~English specfiy a curve loader
		\~Japanese カーブローダーを設定する。
		@param	loader
		\~English	loader
		\~Japanese ローダー
	*/
	virtual void SetCurveLoader(CurveLoader* loader) = 0;

	/**
		@brief	エフェクトを停止する。
		@param	handle	[in]	インスタンスのハンドル
	*/
	virtual void StopEffect(Handle handle) = 0;

	/**
		@brief	全てのエフェクトを停止する。
	*/
	virtual void StopAllEffects() = 0;

	/**
		@brief	エフェクトのルートだけを停止する。
		@param	handle	[in]	インスタンスのハンドル
	*/
	virtual void StopRoot(Handle handle) = 0;

	/**
		@brief	エフェクトのルートだけを停止する。
		@param	effect	[in]	エフェクト
	*/
	virtual void StopRoot(Effect* effect) = 0;

	/**
		@brief	エフェクトのインスタンスが存在しているか取得する。
		@param	handle	[in]	インスタンスのハンドル
		@return	存在してるか?
	*/
	virtual bool Exists(Handle handle) = 0;

	/**
		@brief	エフェクトに使用されているインスタンス数を取得する。
		@param	handle	[in]	インスタンスのハンドル
		@return	インスタンス数
		@note
		Rootも個数に含まれる。つまり、Root削除をしていない限り、
		Managerに残っているインスタンス数+エフェクトに使用されているインスタンス数は存在しているRootの数だけ
		最初に確保した個数よりも多く存在する。
	*/
	virtual int32_t GetInstanceCount(Handle handle) = 0;

	/**
		@brief
		\~English Get the number of instances which is used in playing effects
		\~Japanese 全てのエフェクトに使用されているインスタンス数を取得する。
		@return
		\~English The number of instances
		\~Japanese インスタンス数
		@note
		\~English
		The number of Root is included.
		This means that the number of used instances added resting resting instances is larger than the number of allocated onces by the
	   number of root.
		\~Japanese
		Rootも個数に含まれる。つまり、Root削除をしていない限り、
		Managerに残っているインスタンス数+エフェクトに使用されているインスタンス数は、最初に確保した個数よりも存在しているRootの数の分だけ多く存在する。
	*/
	virtual int32_t GetTotalInstanceCount() const = 0;

	/**
		@brief	エフェクトのインスタンスに設定されている行列を取得する。
		@param	handle	[in]	インスタンスのハンドル
		@return	行列
	*/
	virtual Matrix43 GetMatrix(Handle handle) = 0;

	/**
		@brief	エフェクトのインスタンスに変換行列を設定する。
		@param	handle	[in]	インスタンスのハンドル
		@param	mat		[in]	変換行列
	*/
	virtual void SetMatrix(Handle handle, const Matrix43& mat) = 0;

	/**
		@brief	エフェクトのインスタンスの位置を取得する。
		@param	handle	[in]	インスタンスのハンドル
		@return	位置
	*/
	virtual Vector3D GetLocation(Handle handle) = 0;

	/**
		@brief	エフェクトのインスタンスの位置を指定する。
		@param	x	[in]	X座標
		@param	y	[in]	Y座標
		@param	z	[in]	Z座標
	*/
	virtual void SetLocation(Handle handle, float x, float y, float z) = 0;

	/**
		@brief	エフェクトのインスタンスの位置を指定する。
		@param	location	[in]	位置
	*/
	virtual void SetLocation(Handle handle, const Vector3D& location) = 0;

	/**
		@brief	エフェクトのインスタンスの位置に加算する。
		@param	location	[in]	加算する値
	*/
	virtual void AddLocation(Handle handle, const Vector3D& location) = 0;

	/**
		@brief	エフェクトのインスタンスの回転角度を指定する。(ラジアン)
	*/
	virtual void SetRotation(Handle handle, float x, float y, float z) = 0;

	/**
		@brief	エフェクトのインスタンスの任意軸周りの反時計周りの回転角度を指定する。
		@param	handle	[in]	インスタンスのハンドル
		@param	axis	[in]	軸
		@param	angle	[in]	角度(ラジアン)
	*/
	virtual void SetRotation(Handle handle, const Vector3D& axis, float angle) = 0;

	/**
		@brief	エフェクトのインスタンスの拡大率を指定する。
		@param	handle	[in]	インスタンスのハンドル
		@param	x		[in]	X方向拡大率
		@param	y		[in]	Y方向拡大率
		@param	z		[in]	Z方向拡大率
	*/
	virtual void SetScale(Handle handle, float x, float y, float z) = 0;

	/**
	@brief
		\~English	Specify the color of overall effect.
		\~Japanese	エフェクト全体の色を指定する。
	*/
	virtual void SetAllColor(Handle handle, Color color) = 0;

	/**
		@brief	エフェクトのインスタンスのターゲット位置を指定する。
		@param	x	[in]	X座標
		@param	y	[in]	Y座標
		@param	z	[in]	Z座標
	*/
	virtual void SetTargetLocation(Handle handle, float x, float y, float z) = 0;

	/**
		@brief	エフェクトのインスタンスのターゲット位置を指定する。
		@param	location	[in]	位置
	*/
	virtual void SetTargetLocation(Handle handle, const Vector3D& location) = 0;

	/**
		@brief
		\~English get a dynamic parameter, which changes effect parameters dynamically while playing
		\~Japanese 再生中にエフェクトのパラメーターを変更する動的パラメーターを取得する。
	*/
	virtual float GetDynamicInput(Handle handle, int32_t index) = 0;

	/**
		@brief
		\~English specfiy a dynamic parameter, which changes effect parameters dynamically while playing
		\~Japanese 再生中にエフェクトのパラメーターを変更する動的パラメーターを設定する。
	*/
	virtual void SetDynamicInput(Handle handle, int32_t index, float value) = 0;

	/**
		@brief	エフェクトのベース行列を取得する。
		@param	handle	[in]	インスタンスのハンドル
		@return	ベース行列
	*/
	virtual Matrix43 GetBaseMatrix(Handle handle) = 0;

	/**
		@brief	エフェクトのベース行列を設定する。
		@param	handle	[in]	インスタンスのハンドル
		@param	mat		[in]	設定する行列
		@note
		エフェクト全体の表示位置を指定する行列を設定する。
	*/
	virtual void SetBaseMatrix(Handle handle, const Matrix43& mat) = 0;

	/**
		@brief	エフェクトのインスタンスに廃棄時のコールバックを設定する。
		@param	handle	[in]	インスタンスのハンドル
		@param	callback	[in]	コールバック
	*/
	virtual void SetRemovingCallback(Handle handle, EffectInstanceRemovingCallback callback) = 0;

	/**
	@brief	\~English	Get status that a particle of effect specified is shown.
	\~Japanese	指定したエフェクトのパーティクルが表示されているか取得する。

	@param	handle	\~English	Particle's handle
	\~Japanese	パーティクルのハンドル
	*/
	virtual bool GetShown(Handle handle) = 0;

	/**
		@brief	エフェクトのインスタンスをDraw時に描画するか設定する。
		@param	handle	[in]	インスタンスのハンドル
		@param	shown	[in]	描画するか?
	*/
	virtual void SetShown(Handle handle, bool shown) = 0;

	/**
	@brief	\~English	Get status that a particle of effect specified is paused.
	\~Japanese	指定したエフェクトのパーティクルが一時停止されているか取得する。

	@param	handle	\~English	Particle's handle
			\~Japanese	パーティクルのハンドル
	*/
	virtual bool GetPaused(Handle handle) = 0;

	/**
		@brief	\~English	Pause or resume a particle of effect specified.
		\~Japanese	指定したエフェクトのパーティクルを一時停止、もしくは再開する。

		@param	handle	[in]	インスタンスのハンドル
		@param	paused	[in]	更新するか?
	*/
	virtual void SetPaused(Handle handle, bool paused) = 0;

	/**
			@brief	\~English	Pause or resume all particle of effects.
			\~Japanese	全てのエフェクトのパーティクルを一時停止、もしくは再開する。
			@param	paused \~English	Pause or resume
			\~Japanese	一時停止、もしくは再開
	*/
	virtual void SetPausedToAllEffects(bool paused) = 0;

	/**
		@brief
		\~English	Get a layer index
		\~Japanese	レイヤーのインデックスを取得する
		@note
		\~English For example, if effect's layer is 1 and CameraCullingMask's first bit is 1, this effect is shown.
		\~Japanese 例えば、エフェクトのレイヤーが0でカリングマスクの最初のビットが1のときエフェクトは表示される。
	*/
	virtual int GetLayer(Handle handle) = 0;

	/**
		@brief
		\~English	Set a layer index
		\~Japanese	レイヤーのインデックスを設定する
	*/
	virtual void SetLayer(Handle handle, int32_t layer) = 0;

	/**
		@brief
		\~English	Get a bitmask to specify a group
		\~Japanese	グループを指定するためのビットマスクを取得する。
	*/
	virtual int64_t GetGroupMask(Handle handle) const = 0;

	/**
		@brief
		\~English	Set a bitmask to specify a group
		\~Japanese	グループを指定するためのビットマスクを設定する。
	*/
	virtual void SetGroupMask(Handle handle, int64_t groupmask) = 0;

	/**
	@brief
	\~English	Get a playing speed of particle of effect.
	\~Japanese	エフェクトのパーティクルの再生スピードを取得する。
	@param	handle
	\~English	Particle's handle
	\~Japanese	パーティクルのハンドル
	@return
	\~English	Speed
	\~Japanese	スピード
	*/
	virtual float GetSpeed(Handle handle) const = 0;

	/**
		@brief	エフェクトのインスタンスを再生スピードを設定する。
		@param	handle	[in]	インスタンスのハンドル
		@param	speed	[in]	スピード
	*/
	virtual void SetSpeed(Handle handle, float speed) = 0;

	/**
		@brief
		\~English	Specify a rate of scale in relation to manager's time  by a group.
		\~Japanese	グループごとにマネージャーに対する時間の拡大率を設定する。
	*/
	virtual void SetTimeScaleByGroup(int64_t groupmask, float timeScale) = 0;

	/**
		@brief
		\~English	Specify a rate of scale in relation to manager's time  by a handle.
		\~Japanese	ハンドルごとにマネージャーに対する時間の拡大率を設定する。
	*/
	virtual void SetTimeScaleByHandle(Handle handle, float timeScale) = 0;

	/**
		@brief	エフェクトがDrawで描画されるか設定する。
				autoDrawがfalseの場合、DrawHandleで描画する必要がある。
		@param	autoDraw	[in]	自動描画フラグ
	*/
	virtual void SetAutoDrawing(Handle handle, bool autoDraw) = 0;

	/**
		@brief	今までのPlay等の処理をUpdate実行時に適用するようにする。
	*/
	virtual void Flip() = 0;

	/**
		@brief
		\~English	Update all effects.
		\~Japanese	全てのエフェクトの更新処理を行う。
		@param	deltaFrame
		\~English	passed time (1 is 1/60 seconds)
		\~Japanese	更新するフレーム数(60fps基準)
	*/
	virtual void Update(float deltaFrame = 1.0f) = 0;

	/**
		@brief
		\~English	Update all effects.
		\~Japanese	全てのエフェクトの更新処理を行う。
		@param	parameter
		\~English	A parameter for updating effects
		\~Japanese	エフェクトを更新するためのパラメーター
	*/
	virtual void Update(const UpdateParameter& parameter) = 0;

	/**
		@brief
		\~English	Start to update effects.
		\~Japanese	更新処理を開始する。
		@note
		\~English	It is not required if Update is called.
		\~Japanese	Updateを実行する際は、実行する必要はない。
	*/
	virtual void BeginUpdate() = 0;

	/**
		@brief
		\~English	Stop to update effects.
		\~Japanese	更新処理を終了する。
		@note
		\~English	It is not required if Update is called.
		\~Japanese	Updateを実行する際は、実行する必要はない。
	*/
	virtual void EndUpdate() = 0;

	/**
		@brief
		\~English	Update an effect by a handle.
		\~Japanese	ハンドル単位の更新を行う。
		@param	handle
		\~English	a handle.
		\~Japanese	ハンドル
		@param	deltaFrame
		\~English	passed time (1 is 1/60 seconds)
		\~Japanese	更新するフレーム数(60fps基準)
		@note
		\~English
		You need to call BeginUpdate before starting update and EndUpdate after stopping update.
		\~Japanese
		更新する前にBeginUpdate、更新し終わった後にEndUpdateを実行する必要がある。
	*/
	virtual void UpdateHandle(Handle handle, float deltaFrame = 1.0f) = 0;

	/**
		@brief	
		\~English	Update an effect to move to the specified frame
		\~Japanese	指定した時間に移動するために更新する
		\~English	a handle.
		\~Japanese	ハンドル
		@param	frame
		\~English	frame time (1 is 1/60 seconds)
		\~Japanese	フレーム時間(60fps基準)
		@note
		\~English	This function is slow.
		\~Japanese	この関数は遅い。
	*/
	virtual void UpdateHandleToMoveToFrame(Handle handle, float frame) = 0;

	/**
	@brief
	\~English	Draw particles.
	\~Japanese	描画処理を行う。
	*/
	virtual void Draw(const Manager::DrawParameter& drawParameter = Manager::DrawParameter()) = 0;

	/**
	@brief
	\~English	Draw particles in the back of priority 0.
	\~Japanese	背面の描画処理を行う。
	*/
	virtual void DrawBack(const Manager::DrawParameter& drawParameter = Manager::DrawParameter()) = 0;

	/**
	@brief
	\~English	Draw particles in the front of priority 0.
	\~Japanese	前面の描画処理を行う。
	*/
	virtual void DrawFront(const Manager::DrawParameter& drawParameter = Manager::DrawParameter()) = 0;

	/**
	@brief
	\~English	Draw particles with a handle.
	\~Japanese	ハンドル単位の描画処理を行う。
	*/
	virtual void DrawHandle(Handle handle, const Manager::DrawParameter& drawParameter = Manager::DrawParameter()) = 0;

	/**
	@brief
	\~English	Draw particles in the back of priority 0.
	\~Japanese	背面のハンドル単位の描画処理を行う。
	*/
	virtual void DrawHandleBack(Handle handle, const Manager::DrawParameter& drawParameter = Manager::DrawParameter()) = 0;

	/**
	@brief
	\~English	Draw particles in the front of priority 0.
	\~Japanese	前面のハンドル単位の描画処理を行う。
	*/
	virtual void DrawHandleFront(Handle handle, const Manager::DrawParameter& drawParameter = Manager::DrawParameter()) = 0;

	/**
		@brief	再生する。
		@param	effect	[in]	エフェクト
		@param	x	[in]	X座標
		@param	y	[in]	Y座標
		@param	z	[in]	Z座標
		@return	エフェクトのインスタンスのハンドル
	*/
	virtual Handle Play(Effect* effect, float x, float y, float z) = 0;

	/**
		@brief
		\~English	Play an effect.
		\~Japanese	エフェクトを再生する。
		@param	effect
		\~English	Played effect
		\~Japanese	再生されるエフェクト
		@param	position
		\~English	Initial position
		\~Japanese	初期位置
		@param	startFrame
		\~English	A time to play from middle
		\~Japanese	途中から再生するための時間
	*/
	virtual Handle Play(Effect* effect, const Vector3D& position, int32_t startFrame = 0) = 0;

	/**
		@brief
		\~English	Get a camera's culling mask to show all effects
		\~Japanese	全てのエフェクトを表示するためのカメラのカリングマスクを取得する。
	*/
	virtual int GetCameraCullingMaskToShowAllEffects() = 0;

	/**
		@brief	Update処理時間を取得。
	*/
	virtual int GetUpdateTime() const = 0;

	/**
		@brief	Draw処理時間を取得。
	*/
	virtual int GetDrawTime() const = 0;

	/**
		@brief
		\~English	Gets the number of remaining allocated instances.
		\~Japanese	残りの確保したインスタンス数を取得する。
	*/
	virtual int32_t GetRestInstancesCount() const = 0;

	/**
		@brief	エフェクトをカリングし描画負荷を減らすための空間を生成する。
		@param	xsize	X方向幅
		@param	ysize	Y方向幅
		@param	zsize	Z方向幅
		@param	layerCount	層数(大きいほどカリングの効率は上がるがメモリも大量に使用する)
	*/
	virtual void CreateCullingWorld(float xsize, float ysize, float zsize, int32_t layerCount) = 0;

	/**
		@brief	カリングを行い、カリングされたオブジェクトのみを描画するようにする。
		@param	cameraProjMat	カメラプロジェクション行列
		@param	isOpenGL		OpenGLによる描画か?
	*/
	virtual void CalcCulling(const Matrix44& cameraProjMat, bool isOpenGL) = 0;

	/**
		@brief	現在存在するエフェクトのハンドルからカリングの空間を配置しなおす。
	*/
	virtual void RessignCulling() = 0;
};
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
} // namespace Effekseer
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif // __EFFEKSEER_MANAGER_H__

#ifndef __EFFEKSEER_EFFECTLOADER_H__
#define __EFFEKSEER_EFFECTLOADER_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Effekseer
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
/**
	@brief	エフェクトファイル読み込み破棄関数指定クラス
*/
class EffectLoader
{
public:
	/**
		@brief	コンストラクタ
	*/
	EffectLoader()
	{
	}

	/**
		@brief	デストラクタ
	*/
	virtual ~EffectLoader()
	{
	}

	/**
		@brief	エフェクトファイルを読み込む。
		@param	path	[in]	読み込み元パス
		@param	data	[out]	データ配列の先頭のポインタを出力する先
		@param	size	[out]	データ配列の長さを出力する先
		@return	成否
		@note
		エフェクトファイルを読み込む。
		::Effekseer::Effect::Create実行時に使用される。
	*/
	virtual bool Load(const EFK_CHAR* path, void*& data, int32_t& size) = 0;

	/**
		@brief	エフェクトファイルを破棄する。
		@param	data	[in]	データ配列の先頭のポインタ
		@param	size	[int]	データ配列の長さ
		@note
		エフェクトファイルを破棄する。
		::Effekseer::Effect::Create実行終了時に使用される。
	*/
	virtual void Unload(void* data, int32_t size) = 0;
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
} // namespace Effekseer
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif // __EFFEKSEER_EFFECTLOADER_H__

#ifndef __EFFEKSEER_TEXTURELOADER_H__
#define __EFFEKSEER_TEXTURELOADER_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Effekseer
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
/**
	@brief	テクスチャ読み込み破棄関数指定クラス
*/
class TextureLoader
{
public:
	/**
		@brief	コンストラクタ
	*/
	TextureLoader()
	{
	}

	/**
		@brief	デストラクタ
	*/
	virtual ~TextureLoader()
	{
	}

	/**
		@brief	テクスチャを読み込む。
		@param	path	[in]	読み込み元パス
		@param	textureType	[in]	テクスチャの種類
		@return	テクスチャのポインタ
		@note
		テクスチャを読み込む。
		::Effekseer::Effect::Create実行時に使用される。
	*/
	virtual TextureData* Load(const EFK_CHAR* path, TextureType textureType)
	{
		return nullptr;
	}

	/**
		@brief
		\~English	a function called when texture is loaded
		\~Japanese	テクスチャが読み込まれるときに呼ばれる関数
		@param	data
		\~English	data pointer
		\~Japanese	データのポインタ
		@param	size
		\~English	the size of data
		\~Japanese	データの大きさ
		@param	textureType
		\~English	a kind of texture
		\~Japanese	テクスチャの種類
		@return
		\~English	a pointer of loaded texture
		\~Japanese	読み込まれたテクスチャのポインタ
	*/
	virtual TextureData* Load(const void* data, int32_t size, TextureType textureType)
	{
		return nullptr;
	}

	/**
		@brief	テクスチャを破棄する。
		@param	data	[in]	テクスチャ
		@note
		テクスチャを破棄する。
		::Effekseer::Effectのインスタンスが破棄された時に使用される。
	*/
	virtual void Unload(TextureData* data)
	{
	}
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
} // namespace Effekseer
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif // __EFFEKSEER_TEXTURELOADER_H__

#ifndef __EFFEKSEER_MODELLOADER_H__
#define __EFFEKSEER_MODELLOADER_H__


namespace Effekseer
{

/**
	\~English	Model loader
	\~Japanese	モデル読み込み破棄関数指定クラス
*/
class ModelLoader
{
public:
	ModelLoader() = default;

	virtual ~ModelLoader() = default;

	/*
	@brief
	\~English load a model
	\~Japanese モデルを読み込む。
	@param path
	\~English a file path
	\~Japanese 読み込み元パス
	@ return
	\~English a pointer of loaded a model
	\~Japanese 読み込まれたモデルのポインタ
	*/
	virtual Model* Load(const EFK_CHAR* path);

	/**
		@brief
		\~English	a function called when model is loaded
		\~Japanese	モデルが読み込まれるときに呼ばれる関数
		@param	data
		\~English	data pointer
		\~Japanese	データのポインタ
		@param	size
		\~English	the size of data
		\~Japanese	データの大きさ
		@return
		\~English	a pointer of loaded model
		\~Japanese	読み込まれたモデルのポインタ
	*/
	virtual Effekseer::Model* Load(const void* data, int32_t size);

	/**
		@brief
		\~English	dispose a model
		\~Japanese	モデルを破棄する。
		@param	data
		\~English	a pointer of loaded a model
		\~Japanese	読み込まれたモデルのポインタ
	*/
	virtual void Unload(Model* data);
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
} // namespace Effekseer
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif // __EFFEKSEER_MODELLOADER_H__

#ifndef __EFFEKSEER_MATERIALLOADER_H__
#define __EFFEKSEER_MATERIALLOADER_H__


namespace Effekseer
{

/**
	@brief
	\~English	Material loader
	\~Japanese	マテリアル読み込み破棄関数指定クラス
*/
class MaterialLoader
{
public:
	/**
	@brief
	\~English	Constructor
	\~Japanese	コンストラクタ
	*/
	MaterialLoader() = default;

	/**
	@brief
	\~English	Destructor
	\~Japanese	デストラクタ
	*/
	virtual ~MaterialLoader() = default;

	/**
		@brief
		\~English	load a material
		\~Japanese	マテリアルを読み込む。
		@param	path
		\~English	a file path
		\~Japanese	読み込み元パス
		@return
		\~English	a pointer of loaded a material
		\~Japanese	読み込まれたマテリアルのポインタ
	*/
	virtual MaterialData* Load(const EFK_CHAR* path)
	{
		return nullptr;
	}

	/**
		@brief
		\~English	a function called when a material is loaded
		\~Japanese	マテリアルが読み込まれるときに呼ばれる関数
		@param	data
		\~English	data pointer
		\~Japanese	データのポインタ
		@param	size
		\~English	the size of data
		\~Japanese	データの大きさ
		@param	fileType
		\~English	file type
		\~Japanese	ファイルの種類
		@return
		\~English	a pointer of loaded a material
		\~Japanese	読み込まれたマテリアルのポインタ
	*/
	virtual MaterialData* Load(const void* data, int32_t size, MaterialFileType fileType)
	{
		return nullptr;
	}

	/**
		@brief
		\~English	dispose a material
		\~Japanese	マテリアルを破棄する。
		@param	data
		\~English	a pointer of loaded a material
		\~Japanese	読み込まれたマテリアルのポインタ
	*/
	virtual void Unload(MaterialData* data)
	{
	}
};

} // namespace Effekseer

#endif // __EFFEKSEER_TEXTURELOADER_H__

#ifndef __EFFEKSEER_MODEL_H__
#define __EFFEKSEER_MODEL_H__


namespace Effekseer
{

namespace Backend
{
class GraphicsDevice;
class VertexBuffer;
class IndexBuffer;
} // namespace Backend

/**
	@brief
	\~English	Model class
	\~Japanese	モデルクラス
*/
class Model
{
public:
	static const int32_t Version = 1;

	struct Vertex
	{
		Vector3D Position;
		Vector3D Normal;
		Vector3D Binormal;
		Vector3D Tangent;
		Vector2D UV;
		Color VColor;
	};

	struct Face
	{
		std::array<int32_t, 3> Indexes;
	};

	struct Emitter
	{
		Vector3D Position;
		Vector3D Normal;
		Vector3D Binormal;
		Vector3D Tangent;
	};

protected:
	struct InternalModel
	{
		CustomVector<Vertex> vertexes;
		CustomVector<Face> faces;
		Backend::VertexBuffer* vertexBuffer = nullptr;
		Backend::IndexBuffer* indexBuffer = nullptr;
	};

	int32_t version_ = 0;
	CustomVector<InternalModel> models_;
	bool isBufferStoredOnGPU_ = false;

public:
	Model(const CustomVector<Vertex>& vertecies, const CustomVector<Face>& faces);

	Model(void* data, int32_t size);

	virtual ~Model();

	Backend::VertexBuffer* GetVertexBuffer(int32_t index) const;

	Backend::IndexBuffer* GetIndexBuffer(int32_t index) const;

	const Vertex* GetVertexes(int32_t index = 0) const;

	int32_t GetVertexCount(int32_t index = 0) const;

	const Face* GetFaces(int32_t index = 0) const;

	int32_t GetFaceCount(int32_t index = 0) const;

	int32_t GetFrameCount() const;

	Emitter GetEmitter(IRandObject* g, int32_t time, CoordinateSystem coordinate, float magnification);

	Emitter GetEmitterFromVertex(IRandObject* g, int32_t time, CoordinateSystem coordinate, float magnification);

	Emitter GetEmitterFromVertex(int32_t index, int32_t time, CoordinateSystem coordinate, float magnification);

	Emitter GetEmitterFromFace(IRandObject* g, int32_t time, CoordinateSystem coordinate, float magnification);

	Emitter GetEmitterFromFace(int32_t index, int32_t time, CoordinateSystem coordinate, float magnification);

	bool StoreBufferToGPU(Backend::GraphicsDevice* graphicsDevice);

	bool GetIsBufferStoredOnGPU() const;
};

} // namespace Effekseer

#endif // __EFFEKSEER_MODEL_H__

#ifndef	__EFFEKSEER_CURVE_H__
#define	__EFFEKSEER_CURVE_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------

#include <vector>
#include <limits>
#include <cmath>

namespace Effekseer
{


class dVector4
{
public:
	double X, Y, Z, W;

public:
	dVector4(double x = 0, double y = 0, double z = 0, double w = 0) :
		X(x), Y(y), Z(z), W(w)
	{
	}
};

/**
@brief
\~English	Curve class
\~Japanese	カーブクラス
*/
class Curve
{
	friend class CurveLoader;
public:
	static const int32_t Version = 1;

private:
	int mControllPointCount;
	std::vector<dVector4> mControllPoint;

	int mKnotCount;
	std::vector<double> mKnotValue;

	int mOrder;
	int mStep;
	int mType;
	int mDimension;

	float mLength;

private:
	/**
	 * CalcBSplineBasisFunc : B-スプライン基底関数の計算
	 * 
	 * const vector<double>& knot : ノット列
	 * unsigned int j : ノット列の開始番号
	 * unsigned int p : 次数
	 * double t : 計算対象の独立変数
	 * 
	 * ノット列は昇順である必要があるが、そのチェックは行わない
	 * 
	 * 戻り値 : 計算結果
	 */
	double CalcBSplineBasisFunc(const std::vector<double>& knot, unsigned int j, unsigned int p, double t)
	{
		if (knot.size() == 0) return std::numeric_limits<double>::quiet_NaN();

		// ノット列のデータ長が充分でない場合は nan を返す
		unsigned int m = static_cast<unsigned int>(knot.size()) - 1;
		if (m < j + p + 1) return std::numeric_limits<double>::quiet_NaN();

		// 正値をとる範囲外ならゼロを返す
		if ((t < knot[j]) || (t > knot[j + p + 1])) return(0);
		// p = 0 かつ knot[j] <= t <= knot[j + p + 1] なら 1 を返す
		if (p == 0) return(1);
		// p = 1 の場合、三角の頂点の値は特別扱い
		if (p == 1 && t == knot[j + 1]) return(1);

		// 漸化式の計算
		double d1 = (knot[j + p] == knot[j]) ? 0 :
			(t - knot[j]) * CalcBSplineBasisFunc(knot, j, p - 1, t) / (knot[j + p] - knot[j]);
		double d2 = (knot[j + p + 1] == knot[j + 1]) ? 0 :
			(knot[j + p + 1] - t) * CalcBSplineBasisFunc(knot, j + 1, p - 1, t) / (knot[j + p + 1] - knot[j + 1]);

		return (d1 + d2);
	}

public:
	Curve()
	{
	}

	Curve(void* data, int32_t size)
	{
		uint8_t* pData = new uint8_t[size];
		memcpy(pData, data, size);

		uint8_t* p = (uint8_t*)pData;

		// load converter version
		int converter_version = 0;
		memcpy(&converter_version, p, sizeof(int32_t));
		p += sizeof(int32_t);

		// load controll point count
		memcpy(&mControllPointCount, p, sizeof(int32_t));
		p += sizeof(int32_t);

		// load controll points
		for (int i = 0; i < mControllPointCount; i++)
		{
			dVector4 value;
			memcpy(&value, p, sizeof(dVector4));
			p += sizeof(dVector4);
			mControllPoint.push_back(value);
		}

		// load knot count
		memcpy(&mKnotCount, p, sizeof(int32_t));
		p += sizeof(int32_t);

		// load knot values
		for (int i = 0; i < mKnotCount; i++)
		{
			double value;
			memcpy(&value, p, sizeof(double));
			p += sizeof(double);
			mKnotValue.push_back(value);
		}

		// load order
		memcpy(&mOrder, p, sizeof(int32_t));
		p += sizeof(int32_t);

		// load step
		memcpy(&mStep, p, sizeof(int32_t));
		p += sizeof(int32_t);

		// load type
		memcpy(&mType, p, sizeof(int32_t));
		p += sizeof(int32_t);

		// load dimension
		memcpy(&mDimension, p, sizeof(int32_t));
		p += sizeof(int32_t);

		// calc curve length
		mLength = 0;

		for (int i = 1; i < mControllPointCount; i++)
		{
			dVector4 p0 = mControllPoint[i - 1];
			dVector4 p1 = mControllPoint[i];

			float len = Vector3D::Length(Vector3D((float)p1.X, (float)p1.Y, (float)p1.Z) - Vector3D((float)p0.X, (float)p0.Y, (float)p0.Z));
			mLength += len;
		}

		ES_SAFE_DELETE_ARRAY(pData);
	}

	~Curve()
	{
	}

	Vector3D CalcuratePoint(float t, float magnification) {
		int p = mOrder; // 次数

		std::vector< double > bs(mControllPointCount); // B-Spline 基底関数の計算結果(重み値を積算)

		// ノット列の要素を +1 する
		auto knot = mKnotValue;
		knot.push_back(mKnotValue[mKnotValue.size() - 1] + 1);

		float t_rate = float(knot.back() - 1);

		double wSum = 0; // bs の合計
		for (int j = 0; j < mControllPointCount; ++j) {
			bs[j] = mControllPoint[j].W * CalcBSplineBasisFunc(knot, j, p, t * (t_rate));

			if (!std::isnan(bs[j]))
			{
				wSum += bs[j];
			}
		}

		Vector3D ans(0, 0, 0); // 計算結果
		for (int j = 0; j < mControllPointCount; ++j)
		{
			Vector3D d;
			d.X = (float)mControllPoint[j].X * magnification * (float)bs[j] / (float)wSum;
			d.Y = (float)mControllPoint[j].Y * magnification * (float)bs[j] / (float)wSum;
			d.Z = (float)mControllPoint[j].Z * magnification * (float)bs[j] / (float)wSum;
			if (!std::isnan(d.X) && !std::isnan(d.Y) && !std::isnan(d.Z))
			{
				ans += d;
			}
		}

		return ans;
	}

	//
	//  Getter
	//
	int GetControllPointCount() { return mControllPointCount; }
	dVector4 GetControllPoint(int index) { return mControllPoint[index]; }

	int GetKnotCount() { return mKnotCount; }
	double GetKnotValue(int index) { return mKnotValue[index]; }

	int GetOrder() { return mOrder; }
	int GetStep() { return mStep; }
	int GetType() { return mType; }
	int GetDimension() { return mDimension; }

	float GetLength() { return mLength; }

}; // end class


} // end namespace Effekseer

#endif  // __EFFEKSEER_CURVE_H__

#ifndef __EFFEKSEER_CURVELOADER_H__
#define __EFFEKSEER_CURVELOADER_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------

#include <memory>

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Effekseer
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
/**
@brief	カーブ読み込み破棄関数指定クラス
*/
class CurveLoader
{
public:
	/**
	@brief	コンストラクタ
	*/
	CurveLoader()
	{
	}

	/**
	@brief	デストラクタ
	*/
	virtual ~CurveLoader()
	{
	}

	/**
	@brief	Nカーブを読み込む。
	@param	path	[in]	読み込み元パス
	@return	カーブのポインタ
	@note
	カーブを読み込む。
	::Effekseer::Effect::Create実行時に使用される。
	*/
	virtual void* Load(const EFK_CHAR* path)
	{
		::Effekseer::DefaultFileInterface fileInterface;
		std::unique_ptr<::Effekseer::FileReader>reader(fileInterface.OpenRead(path));
		if (reader.get() == NULL)
		{
			return nullptr;
		}

		Effekseer::Curve* curve = new Effekseer::Curve();

		// load converter version
		int converter_version = 0;
		reader->Read(&converter_version, sizeof(int));

		// load controll point count
		reader->Read(&curve->mControllPointCount, sizeof(int));

		// load controll points
		for (int i = 0; i < curve->mControllPointCount; i++)
		{
			dVector4 value;
			reader->Read(&value, sizeof(dVector4));
			curve->mControllPoint.push_back(value);
		}

		// load knot count
		reader->Read(&curve->mKnotCount, sizeof(int));

		// load knot values
		for (int i = 0; i < curve->mKnotCount; i++)
		{
			double value;
			reader->Read(&value, sizeof(double));
			curve->mKnotValue.push_back(value);
		}

		// load order
		reader->Read(&curve->mOrder, sizeof(int));

		// load step
		reader->Read(&curve->mStep, sizeof(int));

		// load type
		reader->Read(&curve->mType, sizeof(int));

		// load dimension
		reader->Read(&curve->mDimension, sizeof(int));

		// calc curve length
		curve->mLength = 0;

		for (int i = 1; i < curve->mControllPointCount; i++)
		{
			dVector4 p0 = curve->mControllPoint[i - 1];
			dVector4 p1 = curve->mControllPoint[i];

			float len = Vector3D::Length(Vector3D((float)p1.X, (float)p1.Y, (float)p1.Z) - Vector3D((float)p0.X, (float)p0.Y, (float)p0.Z));
			curve->mLength += len;
		}

		return static_cast<void*>(curve);
	}

	/**
	@brief	カーブを破棄する。
	@param	data	[in]	カーブ
	@note
	カーブを破棄する。
	::Effekseer::Effectのインスタンスが破棄された時に使用される。
	*/
	virtual void Unload(void* data)
	{
		if (data != NULL)
		{
			Curve* curve = (Curve*)data;
			ES_SAFE_DELETE(curve);
		}
	}
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
} // namespace Effekseer
  //----------------------------------------------------------------------------------
  //
  //----------------------------------------------------------------------------------
#endif // __EFFEKSEER_MODELLOADER_H__

#ifndef	__EFFEKSEER_SOUND_PLAYER_H__
#define	__EFFEKSEER_SOUND_PLAYER_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Effekseer
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------

typedef void* SoundHandle;
typedef void* SoundTag;

class SoundPlayer
{
public:
	struct InstanceParameter
	{
		void*		Data;
		float		Volume;
		float		Pan;
		float		Pitch;
		bool		Mode3D;
		Vector3D	Position;
		float		Distance;
	};

public:
	SoundPlayer() {}

	virtual ~SoundPlayer() {}

	virtual SoundHandle Play( SoundTag tag, const InstanceParameter& parameter ) = 0;
	
	virtual void Stop( SoundHandle handle, SoundTag tag ) = 0;

	virtual void Pause( SoundHandle handle, SoundTag tag, bool pause ) = 0;

	virtual bool CheckPlaying( SoundHandle handle, SoundTag tag ) = 0;

	virtual void StopTag( SoundTag tag ) = 0;

	virtual void PauseTag( SoundTag tag, bool pause ) = 0;

	virtual bool CheckPlayingTag( SoundTag tag ) = 0;

	virtual void StopAll() = 0;
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif	// __EFFEKSEER_SOUND_PLAYER_H__

#ifndef __EFFEKSEER_SOUNDLOADER_H__
#define __EFFEKSEER_SOUNDLOADER_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Effekseer
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
/**
	@brief	サウンド読み込み破棄関数指定クラス
*/
class SoundLoader
{
public:
	/**
		@brief	コンストラクタ
	*/
	SoundLoader()
	{
	}

	/**
		@brief	デストラクタ
	*/
	virtual ~SoundLoader()
	{
	}

	/**
		@brief	サウンドを読み込む。
		@param	path	[in]	読み込み元パス
		@return	サウンドのポインタ
		@note
		サウンドを読み込む。
		::Effekseer::Effect::Create実行時に使用される。
	*/
	virtual void* Load(const EFK_CHAR* path)
	{
		return NULL;
	}

	/**
		@brief
		\~English	a function called when sound is loaded
		\~Japanese	サウンドが読み込まれるときに呼ばれる関数
		@param	data
		\~English	data pointer
		\~Japanese	データのポインタ
		@param	size
		\~English	the size of data
		\~Japanese	データの大きさ
		@return
		\~English	a pointer of loaded texture
		\~Japanese	読み込まれたサウンドのポインタ
	*/
	virtual void* Load(const void* data, int32_t size)
	{
		return nullptr;
	}

	/**
		@brief	サウンドを破棄する。
		@param	data	[in]	サウンド
		@note
		サウンドを破棄する。
		::Effekseer::Effectのインスタンスが破棄された時に使用される。
	*/
	virtual void Unload(void* source)
	{
	}
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
} // namespace Effekseer
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif // __EFFEKSEER_SOUNDLOADER_H__

#ifndef __EFFEKSEER_LOADER_H__
#define __EFFEKSEER_LOADER_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Effekseer
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------

class EffectFactory;

/**
	@brief	設定クラス
	@note
	EffectLoader等、ファイル読み込みに関する設定することができる。
	Managerの代わりにエフェクト読み込み時に使用することで、Managerとは独立してEffectインスタンスを生成することができる。
*/
class Setting : public ReferenceObject
{
private:
	//! coordinate system
	CoordinateSystem m_coordinateSystem;

	EffectLoader* m_effectLoader;
	TextureLoader* m_textureLoader;
	SoundLoader* m_soundLoader;
	ModelLoader* m_modelLoader;
	MaterialLoader* m_materialLoader = nullptr;
	CurveLoader* m_curveLoader = nullptr;
	ProcedualModelGenerator* procedualMeshGenerator_ = nullptr;
	std::vector<EffectFactory*> effectFactories;

protected:
	/**
		@brief	コンストラクタ
		*/
	Setting();

	/**
		@brief	デストラクタ
		*/
	~Setting();

public:
	/**
		@brief	設定インスタンスを生成する。
	*/
	static Setting* Create();

	/**
	@brief	座標系を取得する。
	@return	座標系
	*/
	CoordinateSystem GetCoordinateSystem() const;

	/**
	@brief	座標系を設定する。
	@param	coordinateSystem	[in]	座標系
	@note
	座標系を設定する。
	エフェクトファイルを読み込む前に設定する必要がある。
	*/
	void SetCoordinateSystem(CoordinateSystem coordinateSystem);

	/**
		@brief	エフェクトローダーを取得する。
		@return	エフェクトローダー
		*/
	EffectLoader* GetEffectLoader();

	/**
		@brief	エフェクトローダーを設定する。
		@param	loader	[in]		ローダー
		*/
	void SetEffectLoader(EffectLoader* loader);

	/**
		@brief	テクスチャローダーを取得する。
		@return	テクスチャローダー
		*/
	TextureLoader* GetTextureLoader();

	/**
		@brief	テクスチャローダーを設定する。
		@param	loader	[in]		ローダー
		*/
	void SetTextureLoader(TextureLoader* loader);

	/**
		@brief	モデルローダーを取得する。
		@return	モデルローダー
		*/
	ModelLoader* GetModelLoader();

	/**
		@brief	モデルローダーを設定する。
		@param	loader	[in]		ローダー
		*/
	void SetModelLoader(ModelLoader* loader);

	/**
		@brief	サウンドローダーを取得する。
		@return	サウンドローダー
		*/
	SoundLoader* GetSoundLoader();

	/**
		@brief	サウンドローダーを設定する。
		@param	loader	[in]		ローダー
		*/
	void SetSoundLoader(SoundLoader* loader);

	/**
		@brief
		\~English get a material loader
		\~Japanese マテリアルローダーを取得する。
		@return
		\~English	loader
		\~Japanese ローダー
	*/
	MaterialLoader* GetMaterialLoader();

	/**
		@brief
		\~English specfiy a material loader
		\~Japanese マテリアルローダーを設定する。
		@param	loader
		\~English	loader
		\~Japanese ローダー
		*/
	void SetMaterialLoader(MaterialLoader* loader);

	/**
		@brief
		\~English get a curve loader
		\~Japanese カーブローダーを取得する。
		@return
		\~English	loader
		\~Japanese ローダー
	*/
	CurveLoader* GetCurveLoader();

	/**
		@brief
		\~English specfiy a curve loader
		\~Japanese カーブローダーを設定する。
		@param	loader
		\~English	loader
		\~Japanese ローダー
	*/
	void SetCurveLoader(CurveLoader* loader);

	/**
		@brief
		\~English get a mesh generator
		\~Japanese メッシュジェネレーターを取得する。
		@return
		\~English	generator
		\~Japanese ローダー
	*/
	ProcedualModelGenerator* GetProcedualMeshGenerator() const;

	/**
		@brief
		\~English specfiy a mesh generator
		\~Japanese メッシュジェネレーターを設定する。
		@param	generator
		\~English	generator
		\~Japanese generator
	*/
	void SetProcedualMeshGenerator(ProcedualModelGenerator* generator);

	/**
		@brief
		\~English	Add effect factory
		\~Japanese Effect factoryを追加する。
	*/
	void AddEffectFactory(EffectFactory* effectFactory);

	/**
		@brief
		\~English	Get effect factory
		\~Japanese Effect Factoryを取得する。
	*/
	EffectFactory* GetEffectFactory(int32_t ind) const;

	/**
		@brief
		\~English	clear effect factories
		\~Japanese 全てのEffect Factoryを削除する。
	*/
	void ClearEffectFactory();

	/**
		@brief
		\~English	Get the number of effect factory
		\~Japanese Effect Factoryの数を取得する。
	*/
	int32_t GetEffectFactoryCount() const;
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
} // namespace Effekseer
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif // __EFFEKSEER_LOADER_H__

#ifndef __EFFEKSEER_SERVER_H__
#define __EFFEKSEER_SERVER_H__

#if !(defined(__EFFEKSEER_NETWORK_DISABLED__))
#if !(defined(_PSVITA) || defined(_XBOXONE))

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Effekseer
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
/**
	@brief
	\~English	A server to edit effect from client such an editor
	\~Japanese	エディタといったクライアントからエフェクトを編集するためのサーバー
*/
class Server
{
public:
	Server()
	{
	}
	virtual ~Server()
	{
	}

	/**
		@brief
		\~English	create a server instance
		\~Japanese	サーバーのインスタンスを生成する。
	*/
	static Server* Create();

	/**
		@brief
		\~English	start a server
		\~Japanese	サーバーを開始する。
	*/
	virtual bool Start(uint16_t port) = 0;

	/**
		@brief
		\~English	stop a server
		\~Japanese	サーバーを終了する。
	*/
	virtual void Stop() = 0;

	/**
		@brief
		\~English	register an effect as a target to edit.
		\~Japanese	エフェクトを編集の対象として登録する。
		@param	key
		\~English	a key to search an effect
		\~Japanese	検索用キー
		@param	effect
		\~English	an effect to be edit
		\~Japanese	編集される対象のエフェクト
	*/
	virtual void Register(const EFK_CHAR* key, Effect* effect) = 0;

	/**
		@brief
		\~English	unregister an effect
		\~Japanese	エフェクトを対象から外す。
		@param	effect
		\~English	an effect registered
		\~Japanese	登録されているエフェクト
	*/
	virtual void Unregister(Effect* effect) = 0;

	/**
		@brief
		\~English	update a server and reload effects
		\~Japanese	サーバーを更新し、エフェクトのリロードを行う。
		@brief	managers
		\~English	all managers which is playing effects.
		\~Japanese	エフェクトを再生している全てのマネージャー
		@brief	managerCount
		\~English	the number of manager
		\~Japanese	マネージャーの個数

	*/
	virtual void
	Update(Manager** managers = nullptr, int32_t managerCount = 0, ReloadingThreadType reloadingThreadType = ReloadingThreadType::Main) = 0;

	/**
		@brief
		\~English	Specify root path to load materials
		\~Japanese	素材のルートパスを設定する。
	*/
	virtual void SetMaterialPath(const EFK_CHAR* materialPath) = 0;

	/**
		@brief
		\~English	deprecated
		\~Japanese	非推奨
	*/
	virtual void Regist(const EFK_CHAR* key, Effect* effect) = 0;

	/**
		@brief
		\~English	deprecated
		\~Japanese	非推奨
	*/
	virtual void Unregist(Effect* effect) = 0;
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
} // namespace Effekseer
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------

#endif // #if !( defined(_PSVITA) || defined(_XBOXONE) )
#endif

#endif // __EFFEKSEER_SERVER_H__

#ifndef __EFFEKSEER_CLIENT_H__
#define __EFFEKSEER_CLIENT_H__

#if !(defined(__EFFEKSEER_NETWORK_DISABLED__))
#if !(defined(_PSVITA) || defined(_PS4) || defined(_SWITCH) || defined(_XBOXONE))

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Effekseer
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
class Client
{
public:
	Client()
	{
	}
	virtual ~Client()
	{
	}

	static Client* Create();

	virtual bool Start(char* host, uint16_t port) = 0;
	virtual void Stop() = 0;

	virtual void Reload(const EFK_CHAR* key, void* data, int32_t size) = 0;
	virtual void Reload(Manager* manager, const EFK_CHAR* path, const EFK_CHAR* key) = 0;
	virtual bool IsConnected() = 0;
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
} // namespace Effekseer
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------

#endif // #if !( defined(_PSVITA) || defined(_PS4) || defined(_SWITCH) || defined(_XBOXONE) )
#endif
#endif // __EFFEKSEER_CLIENT_H__

#ifndef __EFFEKSEER_GRAPHICS_DEVICE_H__
#define __EFFEKSEER_GRAPHICS_DEVICE_H__

#include <array>
#include <stdint.h>
#include <string>

namespace Effekseer
{
namespace Backend
{

enum class UniformBufferLayoutElementType
{
	Vector4,
};

struct UniformLayoutElement
{
	std::string Name;
	UniformBufferLayoutElementType Type;

	//! Ignored in UniformBuffer
	int32_t Offset;
};

/**
	@brief	Layouts in an uniform buffer
	@note
	Only for OpenGL
*/
class UniformLayout
	: public ReferenceObject
{
private:
	CustomVector<UniformLayoutElement> elements_;

public:
	UniformLayout() = default;
	virtual ~UniformLayout() = default;

	const CustomVector<UniformLayoutElement>& GetElements() const
	{
		return elements_;
	}
};

class VertexBuffer
	: public ReferenceObject
{
public:
	VertexBuffer() = default;
	virtual ~VertexBuffer() = default;
};

class IndexBuffer
	: public ReferenceObject
{
public:
	IndexBuffer() = default;
	virtual ~IndexBuffer() = default;
};

class VertexLayout
	: public ReferenceObject
{
public:
	VertexLayout() = default;
	virtual ~VertexLayout() = default;
};

class UniformBuffer
	: public ReferenceObject
{
private:
	UniformLayout* layout_ = nullptr;

public:
	UniformBuffer() = default;
	virtual ~UniformBuffer()
	{
		ES_SAFE_RELEASE(layout_);
	}

	UniformLayout* GetLayout() const
	{
		return layout_;	
	}

	void SetLayout(UniformLayout* layout)
	{
		ES_SAFE_ADDREF(layout);
		ES_SAFE_RELEASE(layout_);
		layout_ = layout;
	}
};

class PipelineState
	: public ReferenceObject
{
public:
	PipelineState() = default;
	virtual ~PipelineState() = default;
};

class Texture
	: public ReferenceObject
{
protected:
	TextureFormatType format_;
	std::array<int32_t, 2> size_;
	int32_t mipmapCount_;

public:
	Texture() = default;
	virtual ~Texture() = default;

	TextureFormatType GetFormat() const
	{
		return format_;
	}

	std::array<int32_t, 2> GetSize() const
	{
		return size_;
	}

	int32_t GetMipmapCount() const
	{
		return mipmapCount_;
	}
};

class Shader
	: public ReferenceObject
{
	UniformLayout* layout_ = nullptr;

public:
	Shader() = default;
	virtual ~Shader()
	{
		ES_SAFE_RELEASE(layout_);
	}
};

class ComputeBuffer
	: public ReferenceObject
{
public:
	ComputeBuffer() = default;
	virtual ~ComputeBuffer() = default;
};

class FrameBuffer
	: public ReferenceObject
{
public:
	FrameBuffer() = default;
	virtual ~FrameBuffer() = default;
};

class RenderPass
	: public ReferenceObject
{
public:
	RenderPass() = default;
	virtual ~RenderPass() = default;
};

enum class IndexBufferStrideType
{
	Stride2,
	Stride4,
};

enum class TextureWrapType
{
	Clamp,
	Repeat,
};

enum class TextureSamplingType
{
	Linear,
	Nearest,
};

struct DrawParameter
{
public:
	static const int TextureSlotCount = 8;

	VertexBuffer* VertexBufferPtr = nullptr;
	IndexBuffer* IndexBufferPtr = nullptr;
	PipelineState* PipelineStatePtr = nullptr;

	std::array<Texture*, TextureSlotCount> TexturePtrs;
	std::array<TextureWrapType, TextureSlotCount> TextureWrapTypes;
	std::array<TextureSamplingType, TextureSlotCount> TextureSamplingTypes;

	int32_t PrimitiveCount = 0;
	int32_t InstanceCount = 0;
};

enum class VertexLayoutFormat
{
	R32_FLOAT,
	R32G32_FLOAT,
	R32G32B32_FLOAT,
	R32G32B32A32_FLOAT,
	R8G8B8A8_UNORM,
	R8G8B8A8_UINT,
};

struct VertexLayoutElement
{
	VertexLayoutFormat Format;

	//! only for OpenGL
	std::string Name;

	//! only for DirectX
	std::string SemanticName;

	//! only for DirectX
	int32_t SemanticIndex = 0;
};

enum class TopologyType
{
	Triangle,
	Line,
	Point,
};

enum class TextureFormatType
{
	R8G8B8A8_UNORM,
	B8G8R8A8_UNORM,
	R8_UNORM,
	R16G16_FLOAT,
	R16G16B16A16_FLOAT,
	R32G32B32A32_FLOAT,
	BC1,
	BC2,
	BC3,
	R8G8B8A8_UNORM_SRGB,
	B8G8R8A8_UNORM_SRGB,
	BC1_SRGB,
	BC2_SRGB,
	BC3_SRGB,
	D32,
	D24S8,
	D32S8,
	Unknown,
};

enum class CullingType
{
	Clockwise,
	CounterClockwise,
	DoubleSide,
};

enum class BlendEquationType
{
	Add,
	Sub,
	ReverseSub,
	Min,
	Max,
};

enum class BlendFuncType
{
	Zero,
	One,
	SrcColor,
	OneMinusSrcColor,
	SrcAlpha,
	OneMinusSrcAlpha,
	DstAlpha,
	OneMinusDstAlpha,
	DstColor,
	OneMinusDstColor,
};

enum class DepthFuncType
{
	Never,
	Less,
	Equal,
	LessEqual,
	Greater,
	NotEqual,
	GreaterEqual,
	Always,
};

enum class CompareFuncType
{
	Never,
	Less,
	Equal,
	LessEqual,
	Greater,
	NotEqual,
	GreaterEqual,
	Always,
};

struct PipelineStateParameter
{
	TopologyType Topology = TopologyType::Triangle;

	CullingType Culling = CullingType::DoubleSide;

	bool IsBlendEnabled = true;

	BlendFuncType BlendSrcFunc = BlendFuncType::SrcAlpha;
	BlendFuncType BlendDstFunc = BlendFuncType::OneMinusSrcAlpha;
	BlendFuncType BlendSrcFuncAlpha = BlendFuncType::SrcAlpha;
	BlendFuncType BlendDstFuncAlpha = BlendFuncType::OneMinusSrcAlpha;

	BlendEquationType BlendEquationRGB = BlendEquationType::Add;
	BlendEquationType BlendEquationAlpha = BlendEquationType::Add;

	bool IsDepthTestEnabled = false;
	bool IsDepthWriteEnabled = false;
	DepthFuncType DepthFunc = DepthFuncType::Less;

	VertexLayout* VertexLayoutPtr = nullptr;
	FrameBuffer* FrameBufferPtr = nullptr;
};

struct TextureParameter
{
	TextureFormatType Format = TextureFormatType::R8G8B8A8_UNORM;
	bool GenerateMipmap = true;
	std::array<float, 2> Size;
	CustomVector<uint8_t> InitialData;
};

struct RenderTextureParameter
{
	TextureFormatType Format = TextureFormatType::R8G8B8A8_UNORM;
	std::array<float, 2> Size;
};

struct DepthTextureParameter
{
	TextureFormatType Format = TextureFormatType::R8G8B8A8_UNORM;
	std::array<float, 2> Size;
};

class GraphicsDevice
	: public ReferenceObject
{
public:
	GraphicsDevice() = default;
	virtual ~GraphicsDevice() = default;

	/**
		@brief	Create VertexBuffer
		@param	size	the size of buffer
		@param	initialData	the initial data of buffer. If it is null, not initialized.
		@param	isDynamic	whether is the buffer dynamic? (for DirectX9, 11 or OpenGL)
		@return	VertexBuffer
	*/
	virtual VertexBuffer* CreateVertexBuffer(int32_t size, const void* initialData, bool isDynamic)
	{
		return nullptr;
	}

	/**
		@brief	Create IndexBuffer
		@param	elementCount	the number of element
		@param	initialData	the initial data of buffer. If it is null, not initialized.
		@param	stride	stride type
		@return	IndexBuffer
	*/
	virtual IndexBuffer* CreateIndexBuffer(int32_t elementCount, const void* initialData, IndexBufferStrideType stride)
	{
		return nullptr;
	}

	/**
		@brief	Update content of a vertex buffer
		@param	buffer	buffer
		@param	size	the size of updated buffer
		@param	offset	the offset of updated buffer
		@param	data	updating data
		@return	Succeeded in updating?
	*/
	virtual bool UpdateVertexBuffer(VertexBuffer* buffer, int32_t size, int32_t offset, const void* data)
	{
		return false;
	}

	/**
		@brief	Update content of a index buffer
		@param	buffer	buffer
		@param	size	the size of updated buffer
		@param	offset	the offset of updated buffer
		@param	data	updating data
		@return	Succeeded in updating?
	*/
	virtual bool UpdateIndexBuffer(IndexBuffer* buffer, int32_t size, int32_t offset, const void* data)
	{
		return false;
	}

	/**
		@brief	Update content of an uniform buffer
		@param	buffer	buffer
		@param	size	the size of updated buffer
		@param	offset	the offset of updated buffer
		@param	data	updating data
		@return	Succeeded in updating?
	*/
	virtual bool UpdateUniformBuffer(UniformBuffer* buffer, int32_t size, int32_t offset, const void* data)
	{
		return false;
	}

	/**
		@brief	Create VertexLayout
		@param	elements	a pointer of array of vertex layout elements
		@param	elementCount	the number of elements
	*/
	virtual VertexLayout* CreateVertexLayout(const VertexLayoutElement* elements, int32_t elementCount)
	{
		return nullptr;
	}

	/**
		@brief	Create UniformBuffer
		@param	size	the size of buffer
		@param	initialData	the initial data of buffer. If it is null, not initialized.
		@return	UniformBuffer
	*/
	virtual UniformBuffer* CreateUniformBuffer(int32_t size, const void* initialData)
	{
		return nullptr;
	}

	virtual PipelineState* CreatePipelineState(const PipelineStateParameter& param)
	{
		return nullptr;
	}

	virtual FrameBuffer* CreateFrameBuffer(const TextureFormatType* formats, int32_t formatCount, TextureFormatType* depthFormat)
	{
		return nullptr;
	}

	virtual RenderPass* CreateRenderPass(Texture** textures, Texture* depthTexture)
	{
		return nullptr;
	}

	virtual Texture* CreateTexture(const TextureParameter& param)
	{
		return nullptr;
	}

	virtual Texture* CreateRenderTexture(const RenderTextureParameter& param)
	{
		return nullptr;
	}

	virtual Texture* CreateDepthTexture(const DepthTextureParameter& param)
	{
		return nullptr;
	}

	/**
		@brief	Create Shader from key
		@param	key	a key which specifies a shader
		@return	Shader
	*/
	virtual Shader* CreateShaderFromKey(const char* key)
	{
		return nullptr;
	}

	/**
		@brief	Create ComputeBuffer
		@param	size	the size of buffer
		@param	initialData	the initial data of buffer. If it is null, not initialized.
		@return	ComputeBuffer
	*/
	// virtual ComputeBuffer* CreateComputeBuffer(int32_t size, const void* initialData)
	// {
	// 	return nullptr;
	// }

	virtual void Draw(const DrawParameter& drawParam)
	{
	}
};

} // namespace Backend
} // namespace Effekseer

#endif