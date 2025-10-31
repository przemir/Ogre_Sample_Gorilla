
#include "Sample_GorillaGameState.h"
#include "CameraController.h"
#include "GraphicsSystem.h"
#include "Utils/MeshUtils.h"

#include "OgreSceneManager.h"

#include "OgreRoot.h"
#include "Vao/OgreVaoManager.h"
#include "Vao/OgreVertexArrayObject.h"

#include "OgreCamera.h"
#include "OgreWindow.h"

#include "OgreMeshManager.h"
#include "OgreMeshManager2.h"

#include "OgreHlmsManager.h"
#include "OgreHlms.h"
#include "Compositor/OgreCompositorManager2.h"
#include "Compositor/OgreCompositorWorkspace.h"

#include "OgreTextureGpuManager.h"

#include "OgreLwString.h"
#include "OgreGpuProgramManager.h"

#include "OgreItem.h"

#include <OgreHlmsPbsDatablock.h>

#include "Gorilla.h"

#include <iostream>
#include <fstream>

using namespace Demo;

namespace Demo
{
    Sample_GorillaGameState::Sample_GorillaGameState( const Ogre::String &helpDescription ) :
        TutorialGameState( helpDescription ),
        mDirectionalLight( 0 )
    {
    }
    //-----------------------------------------------------------------------------------
    void Sample_GorillaGameState::createScene01(void)
    {
        Ogre::Root *root = mGraphicsSystem->getRoot();
        Ogre::SceneManager *sceneManager = mGraphicsSystem->getSceneManager();
        Ogre::RenderQueue *renderQueue = sceneManager->getRenderQueue();

        mGraphicsSystem->getCamera()->setPosition( Ogre::Vector3( 0, 30, 100 ) );

        Ogre::SceneNode* rootNode = sceneManager->getRootSceneNode( Ogre::SCENE_STATIC );

        Ogre::v1::MeshPtr planeMeshV1 = Ogre::v1::MeshManager::getSingleton().createPlane( "Plane v1",
                                            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                            Ogre::Plane( Ogre::Vector3::UNIT_Y, 1.0f ), 5000.0f, 5000.0f,
                                            1, 1, true, 1, 4.0f, 4.0f, Ogre::Vector3::UNIT_Z,
                                            Ogre::v1::HardwareBuffer::HBU_STATIC,
                                            Ogre::v1::HardwareBuffer::HBU_STATIC );

        Ogre::MeshPtr planeMesh = Ogre::MeshManager::getSingleton().createByImportingV1(
                    "Plane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                    planeMeshV1.get(), true, true, true );

        {
            Ogre::Item *item = sceneManager->createItem( planeMesh, Ogre::SCENE_DYNAMIC );
            Ogre::SceneNode *sceneNode = sceneManager->getRootSceneNode( Ogre::SCENE_DYNAMIC )->
                                                    createChildSceneNode( Ogre::SCENE_DYNAMIC );
            sceneNode->setPosition( 0, -1, 0 );
            sceneNode->attachObject( item );
        }

        mDirectionalLight = sceneManager->createLight();
        Ogre::SceneNode *lightNode = rootNode->createChildSceneNode();
        lightNode->attachObject( mDirectionalLight );
        mDirectionalLight->setPowerScale( Ogre::Math::PI );
        mDirectionalLight->setType( Ogre::Light::LT_DIRECTIONAL );
        mDirectionalLight->setDirection( Ogre::Vector3( -1, -1, -1 ).normalisedCopy() );

        sceneManager->setAmbientLight( Ogre::ColourValue( 0.33f, 0.61f, 0.98f ) * 0.01f,
                                       Ogre::ColourValue( 0.02f, 0.53f, 0.96f ) * 0.01f,
                                       Ogre::Vector3::UNIT_Y );

        mCameraController = new CameraController( mGraphicsSystem, false );
        mGraphicsSystem->getCamera()->setFarClipDistance( 100000.0f );
        mGraphicsSystem->getCamera()->setPosition( -10.0f, 10.0f, 10.0f );
        mGraphicsSystem->getCamera()->lookAt(Ogre::Vector3(10.0f, 0.0f, 10.0f));

        TutorialGameState::createScene01();
        
        createGorillaHUD();
    }
    
    void Sample_GorillaGameState::createGorillaHUD(void)
    {
        // Create Silverback and load in dejavu
        mSilverback->loadAtlas("dejavu");

        Ogre::SceneManager *sceneManager = mGraphicsSystem->getSceneManager();
        Ogre::Window* renderWindow = mGraphicsSystem->getRenderWindow();

        mScreen = mSilverback->createScreen(sceneManager, renderWindow->getTexture(), "dejavu");
        mLayer = mScreen->createLayer(10);
        mLayer->setVisible(true);
        Gorilla::Caption* caption = mLayer->createCaption(24, 450.0f, 500.0, "Gorilla text");
        caption->colour(Gorilla::Colours::Black);

        Gorilla::Rectangle* rect = mLayer->createRectangle(475.0f, 550.0f, 100.0f, 100.0f);
        rect->background_image("ogrehead");
    }

    //-----------------------------------------------------------------------------------
    void Sample_GorillaGameState::destroyScene(void)
    {
        mSilverback->destroyScreen(mScreen);
        delete mSilverback;

        TutorialGameState::destroyScene();
    }

    //-----------------------------------------------------------------------------------
    void Sample_GorillaGameState::update( float timeSinceLast )
    {


        TutorialGameState::update( timeSinceLast );
    }
    //-----------------------------------------------------------------------------------
    void Sample_GorillaGameState::generateDebugText( float timeSinceLast, Ogre::String &outText )
    {
        TutorialGameState::generateDebugText( timeSinceLast, outText );

        if( mDisplayHelpMode == 1 )
        {
            char tmp[128];
            Ogre::LwString str( Ogre::LwString::FromEmptyPointer(tmp, sizeof(tmp)) );
            Ogre::Vector3 camPos = mGraphicsSystem->getCamera()->getPosition();

            using namespace Ogre;

            outText += "\n\nCamera: ";
            str.a( "[", LwString::Float( camPos.x, 2, 2 ), ", ",
                        LwString::Float( camPos.y, 2, 2 ), ", ",
                        LwString::Float( camPos.z, 2, 2 ), "]" );
            outText += str.c_str();
        }
    }
    //-----------------------------------------------------------------------------------
    void Sample_GorillaGameState::keyReleased( const SDL_KeyboardEvent &arg )
    {
        if( arg.keysym.sym == SDLK_F4 && (arg.keysym.mod & (KMOD_LCTRL|KMOD_RCTRL)) )
        {
            //Hot reload of Particle shaders.
            Ogre::Root *root = mGraphicsSystem->getRoot();
            Ogre::HlmsManager *hlmsManager = root->getHlmsManager();

            Ogre::Hlms *hlms = hlmsManager->getHlms( Ogre::HLMS_USER0 );
            Ogre::GpuProgramManager::getSingleton().clearMicrocodeCache();
            hlms->reloadFrom( hlms->getDataFolder() );
        }
        else if( (arg.keysym.mod & ~(KMOD_NUM|KMOD_CAPS)) != 0 )
        {
            TutorialGameState::keyReleased( arg );
            return;
        }

        TutorialGameState::keyReleased( arg );
    }

}
