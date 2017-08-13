#ifndef EVENT_H
#define EVENT_H

#include <irrlicht.h>


using namespace irr;
class EventReceiver : public IEventReceiver {
    public:
        EventReceiver();
        virtual bool OnEvent(const SEvent& event);
        virtual bool IsKeyDown(EKEY_CODE keyCode) const;

    private:
        bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

#endif
