#include <irrlicht.h>
#include "event.h"


MyEventReceiver::MyEventReceiver() {
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; i++) {
        KeysIsDown[i] = false;
    }
}

virtual bool MyEventReceiver::OnEvent(const SEvent& event) {
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    return false;
}

virtual bool MyEventReceiver::IsKeyDown(EKEY_CODE keyCode) {
    return KeyIsDown[keyCode];
}
