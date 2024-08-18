#include "Config.hpp"


namespace Kokoha
{

	Config::Config()
		: m_toml(Resource(U"asset/data/config.toml"))
	{
	}

}
