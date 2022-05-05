#include"MyPixelShader.hpp"

namespace Kokoha
{
	void MyPixelShader::loadPixelShader()
	{
		instance().m_shaderMap.try_emplace
		(
			U"TitleLogo",
			std::move(PixelShader(U"asset/shader/TitleLogoShader.hlsl", { { U"PSConstants2D", 0 }, { U"Shift", 1 } }))
		);

		for (const auto& itr : instance().m_shaderMap)
		{
			if (!itr.second)
			{
				throw Error(U"Faild to load a shader file [" + itr.first + U"]");
			}
		}
	}

	const PixelShader& MyPixelShader::get(const String& name)
	{
		if (!instance().m_shaderMap.count(name))
		{
			throw Error(U"Faild to find a shader file [" + name + U"]");
		}

		return instance().m_shaderMap.find(name)->second;
	}
}