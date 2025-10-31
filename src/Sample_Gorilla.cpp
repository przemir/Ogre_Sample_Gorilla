
#include "GraphicsSystem.h"
#include "Sample_GorillaGameState.h"

#include "OgreRoot.h"
#include "Compositor/OgreCompositorManager2.h"
#include "OgreConfigFile.h"
#include "OgreWindow.h"

#include "OgreHlmsManager.h"
#include "OgreArchiveManager.h"

//Declares WinMain / main
#include "MainEntryPointHelper.h"
#include "System/Android/AndroidSystems.h"
#include "System/MainEntryPoints.h"
#include "Gorilla.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
    #include "OSX/macUtils.h"
    #if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
        #include "System/iOS/iOSUtils.h"
    #else
        #include "System/OSX/OSXUtils.h"
    #endif
#endif

namespace Demo
{
    class Sample_GorillaGraphicsSystem : public GraphicsSystem
    {
        Ogre::CompositorWorkspace* setupCompositor() override
        {
            Ogre::CompositorManager2 *compositorManager = mRoot->getCompositorManager2();
            return compositorManager->addWorkspace( mSceneManager, mRenderWindow->getTexture(), mCamera,
                                                    "Sample_GorillaWorkspace", true );
        }

        void setupResources() override
        {
            GraphicsSystem::setupResources();
            
            mSilverback = new Gorilla::Silverback();
        }

    public:
        Sample_GorillaGraphicsSystem( GameState *gameState, Gorilla::Silverback*& silverback ) :
            GraphicsSystem( gameState, "../Data/" ), mSilverback(silverback)
        {
        }
        ~Sample_GorillaGraphicsSystem() {

        }
        
        Gorilla::Silverback*& mSilverback;
    };

    void MainEntryPoints::createSystems( GameState **outGraphicsGameState,
                                         GraphicsSystem **outGraphicsSystem,
                                         GameState **outLogicGameState,
                                         LogicSystem **outLogicSystem )
    {
        Sample_GorillaGameState *gfxGameState = new Sample_GorillaGameState(
        "--- !!! NOTE: THIS SAMPLE IS A WORK IN PROGRESS !!! ---\n"
        "This is sample application using Gorilla\n");

        Sample_GorillaGraphicsSystem *graphicsSystem =
                new Sample_GorillaGraphicsSystem( gfxGameState, gfxGameState->mSilverback );

        gfxGameState->_notifyGraphicsSystem( graphicsSystem );

        *outGraphicsGameState = gfxGameState;
        *outGraphicsSystem = graphicsSystem;
    }

    void MainEntryPoints::destroySystems( GameState *graphicsGameState,
                                          GraphicsSystem *graphicsSystem,
                                          GameState *logicGameState,
                                          LogicSystem *logicSystem )
    {
        delete graphicsSystem;
        delete graphicsGameState;
    }

    const char* MainEntryPoints::getWindowTitle(void)
    {
        return "Tutorial: Gorilla";
    }
}

#if OGRE_PLATFORM != OGRE_PLATFORM_ANDROID
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMainApp( HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR strCmdLine, INT nCmdShow )
#else
int mainApp( int argc, const char *argv[] )
#endif
{
    return Demo::MainEntryPoints::mainAppSingleThreaded( DEMO_MAIN_ENTRY_PARAMS );
}
#endif
