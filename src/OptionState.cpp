#include "OptionState.h"
#include "StateSelector.h"

#include <Graphics/CameraComponent.hpp>
#include <Graphics/TextComponent.hpp>
#include <Gui/GuiManager.hpp>
#include <Core/ResourceManager.hpp>

#include <OgreFontManager.h>

void OptionState::OnInitialize()
{
    ResourceManager::Get()->AddResourceLocation("gui","FileSystem", true);
    ResourceManager::Get()->AddResourceLocation("", "FileSystem", true);

    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    Scene* scene = AddScene(new Scene("Option"));

    Node* camnode = scene->AddChildNode(new dt::Node("camnode"));
    camnode->SetPosition(Ogre::Vector3(0, 0, 10));
    camnode->AddComponent(new dt::CameraComponent("cam"))->LookAt(Ogre::Vector3(0, 0, 0));
    
    //************************************************************
    //The following lines are for test purpose only.
    //Todo: Replace them with the actual content.
    Ogre::FontManager::getSingleton().load("DejaVuSans", "General");

    Node* node1 = scene->AddChildNode(new dt::Node("node1"));
    dt::TextComponent* text1 = node1->AddComponent(new dt::TextComponent("Option", "text1"));
    text1->SetBackgroundMaterial("TextOverlayBackground");
    text1->SetColor(Ogre::ColourValue::White);
    text1->SetFont("DejaVuSans");
    text1->SetFontSize(72);
    text1->SetPadding(Ogre::Vector2(20, 20));

    GuiRootWindow& rootWindow = GuiManager::Get()->GetRootWindow();
    mReturnButton = rootWindow.CreateChild<GuiButton>("return");

    mReturnButton->SetPosition(100, 100);
    mReturnButton->SetSize(250, 100);
    mReturnButton->SetCaption("Return");
    mReturnButton->SetVisible(true);
    dynamic_cast<MyGUI::Button*>(mReturnButton->GetMyGUIWidget())->eventMouseButtonClick
        += MyGUI::newDelegate(this, &OptionState::OnReturnClick);
    //************************************************************
}

void OptionState::OnReturnClick(MyGUI::Widget* sender)
{
    StateSelector::GetInstance()->Select(StateSelector::MAIN_MENU);
}

void OptionState::UpdateStateFrame(double simulationFrameTime)
{
}