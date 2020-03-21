#pragma once

namespace Dooda {

	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: d_Time(time)
		{
		}

		operator float() const { return d_Time; }

	public: //Getters
		float GetSeconds() const { return d_Time; }
		float GetMilliseconds() const { return d_Time * 1000.0f; }

	private: //Variables
		float d_Time;
	};

}