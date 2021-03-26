#ifndef _INPUT_CONTROLLER_BASE_
#define _INPUT_CONTROLLER_BASE_

#include <stdint.h>
#include <type_traits> 

template<typename EnumType>
using _UNDERLYING_ENUM_T = typename std::underlying_type<EnumType>::type;
#    define DEFINE_FLAG_ENUM_OPERATORS(ENUMTYPE)                                                                                                                                                                              \
        extern "C++"                                                                                                                                                                                                          \
        {                                                                                                                                                                                                                     \
            inline ENUMTYPE&          operator|=(ENUMTYPE& a, ENUMTYPE b) throw() { return reinterpret_cast<ENUMTYPE&>(reinterpret_cast<_UNDERLYING_ENUM_T<ENUMTYPE>&>(a) |= static_cast<_UNDERLYING_ENUM_T<ENUMTYPE>>(b)); } \
            inline ENUMTYPE&          operator&=(ENUMTYPE& a, ENUMTYPE b) throw() { return reinterpret_cast<ENUMTYPE&>(reinterpret_cast<_UNDERLYING_ENUM_T<ENUMTYPE>&>(a) &= static_cast<_UNDERLYING_ENUM_T<ENUMTYPE>>(b)); } \
            inline ENUMTYPE&          operator^=(ENUMTYPE& a, ENUMTYPE b) throw() { return reinterpret_cast<ENUMTYPE&>(reinterpret_cast<_UNDERLYING_ENUM_T<ENUMTYPE>&>(a) ^= static_cast<_UNDERLYING_ENUM_T<ENUMTYPE>>(b)); } \
            inline constexpr ENUMTYPE operator|(ENUMTYPE a, ENUMTYPE b) throw() { return static_cast<ENUMTYPE>(static_cast<_UNDERLYING_ENUM_T<ENUMTYPE>>(a) | static_cast<_UNDERLYING_ENUM_T<ENUMTYPE>>(b)); }                \
            inline constexpr ENUMTYPE operator&(ENUMTYPE a, ENUMTYPE b) throw() { return static_cast<ENUMTYPE>(static_cast<_UNDERLYING_ENUM_T<ENUMTYPE>>(a) & static_cast<_UNDERLYING_ENUM_T<ENUMTYPE>>(b)); }                \
            inline constexpr ENUMTYPE operator^(ENUMTYPE a, ENUMTYPE b) throw() { return static_cast<ENUMTYPE>(static_cast<_UNDERLYING_ENUM_T<ENUMTYPE>>(a) ^ static_cast<_UNDERLYING_ENUM_T<ENUMTYPE>>(b)); }                \
            inline constexpr ENUMTYPE operator~(ENUMTYPE a) throw() { return static_cast<ENUMTYPE>(~static_cast<_UNDERLYING_ENUM_T<ENUMTYPE>>(a)); }                                                                          \
		}	
namespace Graphic
{

	struct MouseState
	{
		enum BUTTON_FLAGS : uint8_t
		{
			BUTTON_FLAG_NONE = 0x00,
			BUTTON_FLAG_LEFT = 0x01,
			BUTTON_FLAG_MIDDLE = 0x02,
			BUTTON_FLAG_RIGHT = 0x04,
			BUTTON_FLAG_WHEEL = 0x08	
		};

		float PosX = -1;
		float PosY = -1;
		BUTTON_FLAGS ButtonFlags = BUTTON_FLAG_NONE;
		float WheelDelta = 0;
	};
	DEFINE_FLAG_ENUM_OPERATORS(MouseState::BUTTON_FLAGS)

	enum class InputKeys
	{
		Unknown = 0,
		MoveLeft,
		MoveRight,
		MoveForward,
		MoveBackward,
		MoveUp,
		MoveDown,
		Reset,
		ControlDown,
		ShiftDown,
		AltDown,
		ZoomIn,
		ZoomOut,
		TotalKeys
	};

	enum INPUT_KEY_STATE_FLAGS : uint8_t
	{
		INPUT_KEY_STATE_FLAG_KEY_NONE = 0x00,
		INPUT_KEY_STATE_FLAG_KEY_IS_DOWN = 0x01,
		INPUT_KEY_STATE_FLAG_KEY_WAS_DOWN = 0x80
	};
	DEFINE_FLAG_ENUM_OPERATORS(INPUT_KEY_STATE_FLAGS)

	class InputControllerBase
	{
	public:
		virtual bool HandleNativeMessage(const void* MsgData)
		{
			return false;
		}

		const MouseState& GetMouseState() const 
		{
			return mouseState;
		}

		INPUT_KEY_STATE_FLAGS GetKeyState(InputKeys key) const
		{
			return keys[static_cast<size_t>(key)];
		}

		bool IsKeyDown(InputKeys key) const
		{
			return (GetKeyState(key) & INPUT_KEY_STATE_FLAG_KEY_IS_DOWN) != 0;
		}

		void ClearState()
		{
			mouseState.WheelDelta = 0;

			for (uint32_t i = 0; i < static_cast<uint32_t>(InputKeys::TotalKeys); ++i)
			{
				auto& KeyState = keys[i];
				if (KeyState & INPUT_KEY_STATE_FLAG_KEY_WAS_DOWN)
				{
					KeyState &= ~INPUT_KEY_STATE_FLAG_KEY_WAS_DOWN;
				}
			}
		}

	protected:
		MouseState		mouseState;
		INPUT_KEY_STATE_FLAGS keys[static_cast<size_t>(InputKeys::TotalKeys)] = {};
	};
}

#endif