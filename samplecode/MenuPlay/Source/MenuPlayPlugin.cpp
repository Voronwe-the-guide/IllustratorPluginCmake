//========================================================================================
//  
//  $File$
//
//  $Revision$
//
//  Copyright 1987 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "IllustratorSDK.h"
#include "MenuPlayPlugin.h"

/*
*/
Plugin* AllocatePlugin(SPPluginRef pluginRef)
{
	return new MenuPlayPlugin(pluginRef);
}

/*
*/
void FixupReload(Plugin* plugin)
{
	MenuPlayPlugin::FixupVTable((MenuPlayPlugin*) plugin);
}

/*
*/
MenuPlayPlugin::MenuPlayPlugin(SPPluginRef pluginRef) 
	: Plugin(pluginRef),
	fManualUpdateAIMenu(NULL),
	fMultiDemoAIMenu(NULL),
	fCheckMeAIMenu(NULL),
	fAboutPluginMenu(NULL),
	fCheckMeChecked(false),
	fCheckMeEnabled(false)
{
	strncpy(fPluginName, kMenuPlayPluginName, kMaxStringLength);
}

/*
*/
ASErr MenuPlayPlugin::Message(char* caller, char* selector, void *message) 
{
	ASErr error = kNoErr;

	try {
		error = Plugin::Message(caller, selector, message);
	}
	catch (ai::Error& ex) {
		error = ex;
	}
	catch (...) {
		error = kCantHappenErr;
	}
	if (error) {
		if (error == kUnhandledMsgErr) {
			// Defined by Plugin.hpp and used in Plugin::Message - ignore.
			error = kNoErr;
		}
		else {
			Plugin::ReportError(error, caller, selector, message);
		}
	}	
	return error;
}


/*
*/
ASErr MenuPlayPlugin::StartupPlugin(SPInterfaceMessage* message) 
{
	ASErr error = kNoErr;
	error = Plugin::StartupPlugin(message);
    if (error) { return error; }
	error = this->AddMenus(message);
	return error;
}

/*
*/
ASErr MenuPlayPlugin::AddMenus(SPInterfaceMessage* message) 
{
	ASErr error = kNoErr;

	// Add a menu item to the About SDK Plug-ins menu group.
	SDKAboutPluginsHelper aboutPluginsHelper;
	aboutPluginsHelper.AddAboutPluginsMenuItem(message, 
				kSDKDefAboutSDKCompanyPluginsGroupName, 
				ai::UnicodeString(kSDKDefAboutSDKCompanyPluginsGroupNameString), 
				"MenuPlay...", 
				&fAboutPluginMenu);

	// First we create a normal plug-in menu to use a hierarchical root		
	AIPlatformAddMenuItemDataUS throwAwayMenuData;
	throwAwayMenuData.groupName = "Window Utilities";	
	throwAwayMenuData.itemText = ai::UnicodeString(kMenuPlaySDKString);  
	AIMenuItemHandle throwAwayAIMenu;
	error = sAIMenu->AddMenuItem(message->d.self, kSDKMenuGroup, &throwAwayMenuData, 0, &throwAwayAIMenu);
	if (error)
		goto error;

	// Now we declare the menu item a menu group
	AIMenuGroup	throwAwayMenuGroup;
	sAIMenu->AddMenuGroupAsSubMenu(kSDKMenuGroup, 0, throwAwayAIMenu, &throwAwayMenuGroup);
	
	// Now we can add menu items to it.
	throwAwayMenuData.groupName = kSDKMenuGroup;
	throwAwayMenuData.itemText = ai::UnicodeString(kMenuPlayString);	
	error = sAIMenu->AddMenuItem(message->d.self, "MenuPlay", &throwAwayMenuData, 0, &throwAwayAIMenu);
	if (error)
		goto error;		

	sAIMenu->AddMenuGroupAsSubMenu(kMenuPlayMenuGroup, 0, throwAwayAIMenu, &throwAwayMenuGroup);

	throwAwayMenuData.groupName = kMenuPlayMenuGroup;
	throwAwayMenuData.itemText = ai::UnicodeString(kMenuPlayGroupString);	
	error = sAIMenu->AddMenuItem(message->d.self, "If enabled 1", &throwAwayMenuData, 0, &throwAwayAIMenu);
	if (error)
		goto error;		

	error = sAIMenu->UpdateMenuItemAutomatically(throwAwayAIMenu, kAutoEnableMenuItemAction,
				0, 0,	 // don't care about what's in artwork
				kIfGroup, // is selected and
				kIfTextPath,	 // are not selected
				0, 0);	 // don't care about other update options
		
	if (error)
		goto error;

	// The second item just auto dims if the layer is locked or has locked objects.
	throwAwayMenuData.groupName = kMenuPlayMenuGroup;	
	throwAwayMenuData.itemText = ai::UnicodeString(kMenuPlayLockString);	
	error = sAIMenu->AddMenuItem(message->d.self, "If enabled 2", &throwAwayMenuData, 0, &throwAwayAIMenu);
	if (error)
		goto error;		
	error = sAIMenu->UpdateMenuItemAutomatically(throwAwayAIMenu, kAutoEnableMenuItemAction,
				0, 0,	 // don't care about what's in artwork
				0, // is selected and
				0,	 // are not selected
				kIfCurrentLayerIsEditable, // is true
				kIfAnyLockedObjects);	 // is false
						
	if (error)
		goto error;		

	// The third item doesn't auto dim, but requests the update selector.
	// The automatic update option is the best way to handle menu updates.
	throwAwayMenuData.groupName = kMenuPlayMenuGroup;
	throwAwayMenuData.itemText = ai::UnicodeString(kMenuPlayGuideString);
	error = sAIMenu->AddMenuItem(message->d.self, "Manually updated for guides", &throwAwayMenuData, 
								kMenuItemWantsUpdateOption, &fManualUpdateAIMenu);
	if (error)
		goto error;	

	throwAwayMenuData.groupName = kMenuPlayMenuGroup;	
	error = sAIMenu->AddMenuItem(message->d.self, "seperator", &throwAwayMenuData, 
								kMenuItemIsSeparator, &throwAwayAIMenu);
	if (error)
		goto error;		

	// These menus we'll actually make do something, in this case check and uncheck itself
	throwAwayMenuData.groupName = kMenuPlayMenuGroup;	
	throwAwayMenuData.itemText = ai::UnicodeString(kMenuPlayCheckString);
	// We keep the AIMenuItemHandle to figure out which menu was selected later
	error = sAIMenu->AddMenuItem(message->d.self, "Check me", &throwAwayMenuData, 0, &fCheckMeAIMenu);
	if (error)
		goto error;		

	this->fCheckMeChecked = false;

	// This menu will dim the above menu and change it's own icon
	throwAwayMenuData.groupName = kMenuPlayMenuGroup;	
	throwAwayMenuData.itemText = ai::UnicodeString(kMenuPlayHighlightString);
	error = sAIMenu->AddMenuItem(message->d.self, "Enable or Disable", &throwAwayMenuData, 0, &fMultiDemoAIMenu);
	if (error)
		goto error;		
	
	this->fCheckMeEnabled = true;

error:
	return error;
}

/*
*/
ASErr MenuPlayPlugin::GoMenuItem(AIMenuMessage* message) 
{
	ASErr error = kNoErr;

	// Compare the menuItem selected (in the message) with our stored values to see if we do anything
	if (message->menuItem == this->fAboutPluginMenu) {
		// Pop this plug-in's about box.
		SDKAboutPluginsHelper aboutPluginsHelper;
		aboutPluginsHelper.PopAboutBox(message, "About MenuPlay", kSDKDefAboutSDKCompanyPluginsAlertString);
	}	
	else if (message->menuItem == this->fCheckMeAIMenu) { // Check Me menu item
		this->fCheckMeChecked = !this->fCheckMeChecked;
		error = sAIMenu->CheckItem(this->fCheckMeAIMenu, this->fCheckMeChecked);
		}
	else if (message->menuItem == this->fMultiDemoAIMenu) { // Disable Check Me menu item
		if (this->fCheckMeEnabled) {
			error = sAIMenu->DisableItem(this->fCheckMeAIMenu); // disable checkMeMenu
		    error = sAIMenu->SetItemText(fMultiDemoAIMenu, ai::UnicodeString("Enable the above menu item"));
		}
		else { 
			error = sAIMenu->EnableItem(this->fCheckMeAIMenu); // enable checkMeMenu
			error = sAIMenu->SetItemText(fMultiDemoAIMenu, ai::UnicodeString("Disable the above menu item"));
		}		
		this->fCheckMeEnabled = !this->fCheckMeEnabled;
	}
	return error;
}


ASErr MenuPlayPlugin::UpdateMenuItem(AIMenuMessage* message) 
{
	ASErr error = kNoErr;
		
	// This is only valid when kSelectorAIUpdateMenuItem is received, which is why we're here
	ai::int32 inArtwork = 0, isSelected = 0, isTrue = 0;

	error = sAIMenu->GetUpdateFlags(&inArtwork, &isSelected, &isTrue);
	if (error)
		goto error;		

	// Do something based on the result.  It's easier than GetMatchingArt for this example, and can
	// also be used for a quick check before more processing.
	if (isSelected & kIfGuide) // If a guide is selected
	{
		sAIMenu->SetItemText(fManualUpdateAIMenu, ai::UnicodeString("Do Something To Selected Guides"));
	}
	else if (inArtwork & kIfGuide) // If there are guides in the document
	{
		sAIMenu->SetItemText(fManualUpdateAIMenu, ai::UnicodeString("Do Something To All Guides"));
	}
	else // There aren't any guides in the document
	{
		sAIMenu->SetItemText(fManualUpdateAIMenu, ai::UnicodeString("Manually updated for guides"));
	}

error:
	return error;
}

// End MenuPlayPlugin.cpp
