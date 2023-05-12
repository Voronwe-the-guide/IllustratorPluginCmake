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
#ifndef __MENUPLAYPLUGIN_H__
#define __MENUPLAYPLUGIN_H__

#include "MenuPlaySuites.h"
#include "Plugin.hpp"
#include "AIMenuGroups.h"
#include "SDKDef.h"
#include "SDKAboutPluginsHelper.h"
#include "MenuPlayID.h"

/**	Creates a new MenuPlayPlugin.
	@param pluginRef IN unique reference to this plugin.
	@return pointer to new MenuPlayPlugin.
*/
Plugin* AllocatePlugin(SPPluginRef pluginRef);

/**	Reloads the MenuPlayPlugin class state when the plugin is 
	reloaded by the application.
	@param plugin IN pointer to plugin being reloaded.
*/
void FixupReload(Plugin* plugin);

/**	Provides a plugin which demonstrates adding menu items.
*/
class MenuPlayPlugin : public Plugin
{
public:

	/**	Constructor.
		@param pluginRef IN reference to this plugin.
	*/
	MenuPlayPlugin(SPPluginRef pluginRef);

	/**	Destructor.
	*/
	virtual ~MenuPlayPlugin(){}

	/**	Restores state of MenuPlayPlugin during reload.
	*/
	FIXUP_VTABLE_EX(MenuPlayPlugin, Plugin);

protected:
	/** Calls Plugin::Message and handles any errors returned.
		@param caller IN sender of the message.
		@param selector IN nature of the message.
		@param message IN pointer to plugin and call information.
		@return kNoErr on success, other ASErr otherwise.
	*/
	virtual ASErr Message(char* caller, char* selector, void *message);

	/**	Calls Plugin::Startup and initialisation functions, such as 
		AddMenus.
		@param message IN pointer to plugin and call information.
		@return kNoErr on success, other ASErr otherwise.
	*/
	virtual ASErr StartupPlugin(SPInterfaceMessage* message);

	/**	Performs actions required for menu item selected.
		@param message IN pointer to plugin and call information.
		@return kNoErr on success, other ASErr otherwise.
	*/
	virtual ASErr GoMenuItem(AIMenuMessage* message);

	/**	Updates state of menu items.
		@param message IN pointer to plugin and call information.
		@return kNoErr on success, other ASErr otherwise.
	*/
	virtual ASErr UpdateMenuItem(AIMenuMessage* message);
private:
	/**	Menu item handle for Manually updated for guides menu item.
	*/
	AIMenuItemHandle fManualUpdateAIMenu;

	/**	Menu item handle for disabling and enabling the Check me menu item.
	*/
	AIMenuItemHandle fMultiDemoAIMenu;

	/**	Menu item handle for toggling the menu item check icon.
	*/
	AIMenuItemHandle fCheckMeAIMenu;	

	/**	Menu item handle for the about plugin dialog.
	*/
	AIMenuItemHandle fAboutPluginMenu;

	/** Used to toggle the Check me menu item check icon.
	*/
	ASBoolean fCheckMeChecked;

	/** Used to toggle disabling and enabling of Check me menu item.
	*/
	ASBoolean fCheckMeEnabled;
	
	/**	Adds the menu items for this plugin to the application UI.
		@param message IN pointer to plugin and call information.
		@return kNoErr on success, other ASErr otherwise.
	*/
	ASErr AddMenus(SPInterfaceMessage* message);
};

#endif // End MenuPlayPlugin.h
