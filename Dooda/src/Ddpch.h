#pragma once

#include "Dooda/Core/PlatformDetection.h"

#ifdef DD_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
		#define NOMINMAX
	#endif
#endif

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <fstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>

//Dooda Engine Files
#include "Dooda/Core/Log.h"
#include "Dooda/Core/Core.h"
#include "Dooda/Debug/Instrumentor.h"

//Platform Specific Files
#ifdef DD_PLATFORM_WINDOWS
	#include <Windows.h>
#endif
