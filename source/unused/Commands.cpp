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


#include "Commands.h"
#include "MenuBar.h"


/*========================================================================*/
CommandsClass::CommandsClass(MainApplication* app, DocumentWindow* window)
: app(app)
{
    commandManager = new ApplicationCommandManager();
    commandManager->registerAllCommandsForTarget(app);
    commandManager->registerAllCommandsForTarget(this);
    commandManager->setFirstCommandTarget(this);
    commandManager->getKeyMappings()->resetToDefaultMappings();
    window->addKeyListener(commandManager->getKeyMappings());


    menuModel = new MenuBar(this);


#if JUCE_MAC
    PopupMenu extraAppleMenuItems;
    createExtraAppleMenuItems(extraAppleMenuItems);

    // workaround broken "Open Recent" submenu: not passing the
    // submenu's title here avoids the defect in JuceMainMenuHandler::addMenuItem
    MenuBarModel::setMacMainMenu(menuModel, &extraAppleMenuItems); //, "Open Recent");
#endif
}

CommandsClass::~CommandsClass()
{
#if JUCE_MAC
    MenuBarModel::setMacMainMenu(nullptr);
#endif

    menuModel = nullptr;
    commandManager = nullptr;
}


/*====================================================================*/
ApplicationCommandManager* CommandsClass::getCommandManager()
{
    return commandManager.get();
}

MenuBarModel* CommandsClass::getMenuModel()
{
    return menuModel.get();
}

StringArray CommandsClass::getMenuNames()
{
    const char* const names[] = { "File", "Edit", "View", "Window", "Tools", nullptr };
    return StringArray(names);
}


/*========================================================================*/
void CommandsClass::createMenu (PopupMenu& menu, const String& menuName)
{
    if      (menuName == "File")        createFileMenu   (menu);
    else if (menuName == "Edit")        createEditMenu   (menu);
    else if (menuName == "View")        createViewMenu   (menu);
    else if (menuName == "Window")      createWindowMenu (menu);
    else if (menuName == "Tools")       createToolsMenu  (menu);
    else                                jassertfalse; // names have changed?
}

void CommandsClass::createFileMenu (PopupMenu& menu)
{
    menu.addCommandItem (commandManager, CommandIDs::newProject);
    menu.addSeparator();
    menu.addCommandItem (commandManager, CommandIDs::open);
    menu.addSeparator();
    menu.addCommandItem (commandManager, CommandIDs::closeDocument);
    menu.addCommandItem (commandManager, CommandIDs::saveDocument);
    menu.addCommandItem (commandManager, CommandIDs::saveDocumentAs);
    menu.addCommandItem (commandManager, CommandIDs::saveAll);
    menu.addSeparator();
    menu.addCommandItem (commandManager, CommandIDs::closeProject);
    menu.addCommandItem (commandManager, CommandIDs::saveProject);
    menu.addSeparator();
    menu.addCommandItem (commandManager, CommandIDs::openInIDE);
    menu.addCommandItem (commandManager, CommandIDs::saveAndOpenInIDE);
    menu.addSeparator();
    menu.addCommandItem (commandManager, CommandIDs::loginLogout);

#if ! JUCE_MAC
    menu.addCommandItem (commandManager, CommandIDs::showGlobalPreferences);
    menu.addSeparator();
    menu.addCommandItem (commandManager, StandardApplicationCommandIDs::quit);
#endif
}

void CommandsClass::createEditMenu (PopupMenu& menu)
{
    menu.addCommandItem (commandManager, StandardApplicationCommandIDs::undo);
    menu.addCommandItem (commandManager, StandardApplicationCommandIDs::redo);
    menu.addSeparator();
    menu.addCommandItem (commandManager, StandardApplicationCommandIDs::cut);
    menu.addCommandItem (commandManager, StandardApplicationCommandIDs::copy);
    menu.addCommandItem (commandManager, StandardApplicationCommandIDs::paste);
    menu.addCommandItem (commandManager, StandardApplicationCommandIDs::del);
    menu.addCommandItem (commandManager, StandardApplicationCommandIDs::selectAll);
    menu.addCommandItem (commandManager, StandardApplicationCommandIDs::deselectAll);
    menu.addSeparator();
    menu.addCommandItem (commandManager, CommandIDs::showFindPanel);
    menu.addCommandItem (commandManager, CommandIDs::findSelection);
    menu.addCommandItem (commandManager, CommandIDs::findNext);
    menu.addCommandItem (commandManager, CommandIDs::findPrevious);
}

void CommandsClass::createViewMenu (PopupMenu& menu)
{
    menu.addCommandItem (commandManager, CommandIDs::showFilePanel);
    menu.addCommandItem (commandManager, CommandIDs::showConfigPanel);
    menu.addCommandItem (commandManager, CommandIDs::showBuildTab);
    menu.addCommandItem (commandManager, CommandIDs::showProjectSettings);
    menu.addCommandItem (commandManager, CommandIDs::showProjectModules);
}

void CommandsClass::createWindowMenu (PopupMenu& menu)
{
    menu.addCommandItem (commandManager, CommandIDs::closeWindow);
    menu.addSeparator();

    menu.addCommandItem (commandManager, CommandIDs::goToPreviousDoc);
    menu.addCommandItem (commandManager, CommandIDs::goToNextDoc);
    menu.addCommandItem (commandManager, CommandIDs::goToCounterpart);
    menu.addSeparator();

    menu.addCommandItem (commandManager, CommandIDs::closeAllDocuments);
}

void CommandsClass::createToolsMenu (PopupMenu& menu)
{
    menu.addCommandItem (commandManager, CommandIDs::showUTF8Tool);
    menu.addCommandItem (commandManager, CommandIDs::showSVGPathTool);
    menu.addCommandItem (commandManager, CommandIDs::showTranslationTool);
}

void CommandsClass::createExtraAppleMenuItems (PopupMenu& menu)
{
    menu.addCommandItem (commandManager, CommandIDs::showGlobalPreferences);
}


/*========================================================================*/
ApplicationCommandTarget* CommandsClass::getNextCommandTarget()
{
    return nullptr;
}

void CommandsClass::getAllCommands(Array<CommandID>& commands)
{
    app->getAllCommands(commands);

    const CommandID ids[] =
    {
        CommandIDs::newProject,
        CommandIDs::open,
        CommandIDs::saveAll,
        CommandIDs::showGlobalPreferences,
        CommandIDs::showUTF8Tool,
        CommandIDs::showSVGPathTool,
    };

    commands.addArray(ids, numElementsInArray(ids));
}

void CommandsClass::getCommandInfo(CommandID commandID, ApplicationCommandInfo& result)
{
    switch (commandID)
    {
        case CommandIDs::newProject:
            result.setInfo ("New Project...", "Creates a new Jucer project", CommandCategories::general, 0);
            result.defaultKeypresses.add (KeyPress ('n', ModifierKeys::commandModifier, 0));
            break;

        case CommandIDs::open:
            result.setInfo ("Open...", "Opens a Jucer project", CommandCategories::general, 0);
            result.defaultKeypresses.add (KeyPress ('o', ModifierKeys::commandModifier, 0));
            break;

        case CommandIDs::showGlobalPreferences:
            result.setInfo ("Preferences...", "Shows the preferences window.", CommandCategories::general, 0);
            result.defaultKeypresses.add (KeyPress (',', ModifierKeys::commandModifier, 0));
            break;

        case CommandIDs::saveAll:
            result.setInfo ("Save All", "Saves all open documents", CommandCategories::general, 0);
            result.defaultKeypresses.add (KeyPress ('s', ModifierKeys::commandModifier | ModifierKeys::altModifier, 0));
            break;

        case CommandIDs::showUTF8Tool:
            result.setInfo ("UTF-8 String-Literal Helper", "Shows the UTF-8 string literal utility", CommandCategories::general, 0);
            break;

        case CommandIDs::showSVGPathTool:
            result.setInfo ("SVG Path Helper", "Shows the SVG->Path data conversion utility", CommandCategories::general, 0);
            break;

        default:
            app->getCommandInfo(commandID, result);
            break;
    }
}

bool CommandsClass::perform(const InvocationInfo& info)
{
    switch (info.commandID)
    {
        //case CommandIDs::newProject:                createNewProject(); break;
        //case CommandIDs::open:                      askUserToOpenFile(); break;
        //case CommandIDs::saveAll:                   openDocumentManager.saveAll(); break;
        //case CommandIDs::closeAllDocuments:         closeAllDocuments (true); break;
        //case CommandIDs::showUTF8Tool:              showUTF8ToolWindow(); break;
        //case CommandIDs::showSVGPathTool:           showSVGPathDataToolWindow(); break;
        case CommandIDs::showGlobalPreferences:     app->openAudioDeviceSettingsDialog();

            break;
        //case CommandIDs::loginLogout:               loginOrLogout(); break;
        default:                                    return app->perform (info);
    }
    
    return true;
}
