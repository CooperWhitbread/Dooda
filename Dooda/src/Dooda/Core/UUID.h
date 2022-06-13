#pragma once

#include <xhash>

namespace Dooda 
{

	class UUID
	{
	public:
		UUID();
		UUID(uint64_t uuid);
		UUID(const UUID&) = default;

		operator uint64_t() const { return d_UUID; }
	private:
		uint64_t d_UUID;
	};

}

namespace std {

	template<>
	struct hash<Dooda::UUID>
	{
		std::size_t operator()(const Dooda::UUID& uuid) const
		{
			return hash<uint64_t>()((uint64_t)uuid);
		}
	};

}
