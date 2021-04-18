/************************************************************************/
/*!\class Gamesys
    \brief Creates Gamesys class begin game processes.
//
// Copyright (c) 2008-2020 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
*/
/************************************************************************/
#pragma once

#include "Sample.h"


class GameSys : public Sample
{
    URHO3D_OBJECT(GameSys, Sample);

public:
    /// Construct.
    explicit GameSys(Context* context);

    /// Setup after engine initialization and before running the main loop.
    /// Default Start function overridden to allow game loop to begin
    void Start() override;
    
    /// Displays the winning message and art.
    void CreateWinScene();
    
    /// Displays the loss message and art.
    void CreateLossScene();
    
    
    void DeleteCorrectnessText();

protected:
    /// Return XML patch instructions for screen joystick layout for a specific sample app, 
    /// if any.
    String GetScreenJoystickPatchString() const override { return
        "<patch>"
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">"
        "        <attribute name=\"Is Visible\" value=\"false\" />"
        "    </add>"
        "</patch>";
    }

private:
    //! Subscribe to application-wide logic update events.
    void SubscribeToEvents();
    
    //! Handle the logic update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    
    void HandleStartClick(StringHash eventType, VariantMap& eventData);
    
    void HandleCloserClick(StringHash eventType, VariantMap& eventData);
    
    void HandleFurtherClick(StringHash eventType, VariantMap& eventData);
    
    void HandleInsClick(StringHash eventType, VariantMap& eventData);
    
    void HandleBackClick(StringHash eventType, VariantMap& eventData);
    
    void HandleResetClick(StringHash eventType, VariantMap& eventData);
    
    void MoveCamera(float timeStep);
    
    void SetupScene();
    
    void SetupViewport();
    
    void CreateTitleScene();
    
    void CreateMainScene();
    
    void CreateInstructionsScene();
    
    void ChangeTexts(String note="None");
    
    void WriteToPipe(int pipefds[2]);

    Node* CreateBackground(String path);
    Node* CreateShip();
    Button* CreateButton(UIElement* root, String tag, String txtName, String txtCont,
     int x, int y, int width=250);
};
/**
 * inthand function allows close of terminal with ctrl C
 * 
 */
void inthand(int signum);

void readyHandler(int signum);

static void correctHandler(int signum);

static void incorrectHandler(int signum);


/**
 * AnswerHandler function. checks note played and feedsback correct/incorrect.
 * Calls CreateWinScene or CreateLossScene depending on input
 * Gets Ships position and feedsback amount of tries
 */
void AnswerHandler(bool isCorrect, bool didntPlay = false);

Text* CreateText(String content, String tagName, int x, int y, String font="Fonts/Anonymous Pro.ttf");
 

