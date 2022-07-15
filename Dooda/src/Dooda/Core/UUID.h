#pragma once


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

	template <typename T> struct hash;

	template<>
	struct hash<Dooda::UUID>
	{
		std::size_t operator()(const Dooda::UUID& uuid) const
		{
			return (uint64_t)uuid;
		}
	};

}
