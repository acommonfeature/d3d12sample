#ifndef _INPUT_CONTROLLER_WIN_H_
#define _INPUT_CONTROLLER_WIN_H_

#include "inputcontrollerbase.h"

namespace Graphic
{
	class InputControllerWin : public InputControllerBase
	{
	public:
		InputControllerWin();
		bool HandleNativeMessage(const void* MsgData) override;

		const MouseState& GetMouseState();
	private:
		void UpdateMousePos();
	};
}
#endif