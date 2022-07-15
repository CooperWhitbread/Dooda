#pragma once

#include "Dooda/Core/PlatformDetection.h"

#ifdef DD_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
		#define NOMINMAX
	#endif
#endif

#include <algorithm>
#include <array>
#include <iostream>
#include <functional>
#include <memory>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

//Dooda Engine Files
#include "Dooda/Core/Log.h"
#include "Dooda/Core/Core.h"
#include "Dooda/Debug/Instrumentor.h"

//Platform Specific Files
#ifdef DD_PLATFORM_WINDOWS
	#include <Windows.h>
#endif
