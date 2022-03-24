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
#include "vbGame.h"
#include "vbGraphicObject.h"
#include "vbGPIO.h"
#include "vbImage.h"
#include "vbLanguage.h"
#include "vbLivingObject.h"
#include "vbMessage.h"
#include "vbNumericBox.h"
#include "vbRenderer.h"
#include "vbSequence.h"
#include "vbState.h"
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
using namespace std;

#endif