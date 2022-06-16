#ifndef VBENGINE_H
#define VBENGINE_H

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#endif

//BASE
#include "basetypes.h"
#include "raylib.h"
#include "utils.h" 
#include "json.h"

//MULTIMEDIA
#include "vbAtlas.h"
#include "vbButton.h"
#include "vbCanvas.h"
#include "vbContainer.h"
#include "vbEasing.h"
#include "vbErrors.h"
#include "game/vbGame.h"
#include "game/vbState.h"
#include "vbGraphicObject.h"
#include "vbGPIO.h"
#include "vbImage.h"
#include "vbLanguage.h"
#include "vbLivingObject.h"
#include "vbMessage.h"
#include "vbNumericBox.h"
#include "vbRenderer.h"
#include "vbSequence.h"
#include "vbRectangle.h"
#include "vbStyle.h"
#include "vbTextBox.h"
#include "vbTextEngine.h"
#include "vbTimer.h"
#include "vbTexture.h"
#include "vbTween.h"
#include "vbUtils.h"
#include "vbPhysicsObject.h"
#include "vbPhys_Cir.h"
#include "vbPhys_Rec.h"
#include "vbContactListener.h"
#include "UtilityMath.h"
#include "vbGraphicText.h"

//SPINE
#include <spine/spine.h>
#include "glad.h"
#include "gui_textbox_extended.h"
#include "riconsdata.h"

using namespace std;

#endif