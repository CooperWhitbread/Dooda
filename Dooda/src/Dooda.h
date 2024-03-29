#pragma once

///////////////////////////
//For use by applications//
///////////////////////////

//Core 
#include "Dooda/Core/Application.h"
#include "Dooda/Core/Layer.h"
#include "Dooda/Core/Log.h"
#include "Dooda/Core/Core.h"
#include "Dooda/Core/Timestep.h"
#include "Dooda/Core/Assert.h"

//Events
#include "Dooda/Core/KeyCodes.h"
#include "Dooda/Core/Input.h"
#include "Dooda/Core/MouseCodes.h"

//Imgui
#include "Dooda/ImGui/ImGuiLayer.h"

//Scenes
#include "Dooda/Scene/Scene.h"
#include "Dooda/Scene/Component.h"
#include "Dooda/Scene/Entity.h"
#include "Dooda/Scene/ScriptableEntity.h"

//Renderer
#include "Dooda/Renderer/Renderer.h"
#include "Dooda/Renderer/Renderer2D.h"
#include "Dooda/Renderer/RenderCommand.h"

//Renderer Resorces
#include "Dooda/Renderer/Buffer.h"
#include "Dooda/Renderer/Framebuffer.h"
#include "Dooda/Renderer/Shader.h"
#include "Dooda/Renderer/Framebuffer.h"
#include "Dooda/Renderer/Texture.h"
#include "Dooda/Renderer/VertexArray.h"

//Renderer Objects
#include "Dooda/Renderer/OrthographicCamera.h"

//Camera Objects
#include "Dooda/Renderer/OrthographicCameraController.h"

//////////////////////
//Dooda Layout Style//
//////////////////////

/*
--General Rules--
-Use init instead of Constructer to set up classes.
-Use tabs instead of spaces.
-_ only used for variable formating or macros.
-Capital letter used for new word in a lable unless in a macro
*/

/*
--Key--
  [C] = Upper Case Letter
  [l] = Lower Case Letter
  ..	= The rest of the name
  [C..] = Full Upper Case Letters
*/

/*
--Varaible Formatting--
Engine Member Variable	= d_[C]..
Temporary Variable		= [l]..
Parameter Variable		= [l]..
Struct Variables		= [C]..
Static Member Variable	= sd_[C]..
Static Global Variable	= s_[C]..
Uniform Variable		= u_[C]..
Varying Variable		= v_[C]..
Attribute Variable		= a_[C]..
*/

/*
--Macros--
General macro			= [C..]_[C..] 
*/

/*
--Function Formatting--
Class Function			= [C]..
Static Member Function	= SD_[C]..
Static Gloabal Function	= S_[C]..
Getter Function (const) = Get[C]..
Setter Function			= Set[C]..
*/

/*
--Class Structure
-Constructors and general functions (no comment)
-Getters
-Setters
-Iterators
-Operators
-Private Functions
-Static Functions
-Variables
*/