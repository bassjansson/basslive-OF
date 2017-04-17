/*========================================================================*
 |                                                                        |
 |  This file is part of the live coding environment BassLive.            |
 |  Copyright (C) 2017 Bass Jansson.                                      |
 |                                                                        |
 |  This program is free software: you can redistribute it and/or modify  |
 |  it under the terms of the GNU General Public License as published by  |
 |  the Free Software Foundation, either version 3 of the License, or     |
 |  (at your option) any later version.                                   |
 |                                                                        |
 |  This program is distributed in the hope that it will be useful,       |
 |  but WITHOUT ANY WARRANTY; without even the implied warranty of        |
 |  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          |
 |  GNU General Public License for more details.                          |
 |                                                                        |
 |  You should have received a copy of the GNU General Public License     |
 |  along with this program. If not, see <http://www.gnu.org/licenses/>.  |
 |                                                                        |
 *========================================================================*/


#include "MenuBar.h"


/*========================================================================*/
MenuBar::MenuBar(CommandsClass* commands) : commandsClass(commands)
{
    setApplicationCommandManagerToWatch(commandsClass->getCommandManager());
}

MenuBar::~MenuBar()
{

}


/*====================================================================*/
StringArray MenuBar::getMenuBarNames()
{
    return commandsClass->getMenuNames();
}

PopupMenu MenuBar::getMenuForIndex(int topLevelMenuIndex, const String& menuName)
{
    PopupMenu menu;
    commandsClass->createMenu(menu, menuName);
    return menu;
}

/*====================================================================*/
void MenuBar::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
    
}

void MenuBar::menuBarActivated(bool isActive)
{

}
