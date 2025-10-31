
#ifndef _Demo_Sample_GorillaGameState_H_
#define _Demo_Sample_GorillaGameState_H_

#include "OgrePrerequisites.h"
#include "TutorialGameState.h"
#include "Gorilla.h"

namespace Demo
{
    class Sample_GorillaGameState : public TutorialGameState
    {
        Ogre::Node* mNode = nullptr;
        Ogre::Light *mDirectionalLight;
        Gorilla::Screen* mScreen;
        Gorilla::Layer*  mLayer;
        virtual void generateDebugText( float timeSinceLast, Ogre::String &outText );
    public:
        Gorilla::Silverback* mSilverback;
        
    public:
        Sample_GorillaGameState( const Ogre::String &helpDescription );

        virtual void createScene01(void);
        void createGorillaHUD();
        virtual void destroyScene(void);

        virtual void update( float timeSinceLast );

        virtual void keyReleased( const SDL_KeyboardEvent &arg );

    };
}

#endif
