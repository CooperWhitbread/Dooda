#include "ddpch.h"
#include "RenderCommand.h"

namespace Dooda {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::SD_Create();

}