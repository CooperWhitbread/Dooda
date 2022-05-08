#include "ddpch.h"
#include "RenderCommand.h"

namespace Dooda {

	Scope<RendererAPI> RenderCommand::sd_RendererAPI = RendererAPI::SD_Create();

}