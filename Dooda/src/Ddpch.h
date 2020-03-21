#pragma once

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

//Platform Specific Files
#ifdef DD_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

//Dooda Engine Files
#include "Dooda/Core/Log.h"
#include "Dooda/Core/Core.h"
#include "Dooda/Debug/Instrumentor.h"
