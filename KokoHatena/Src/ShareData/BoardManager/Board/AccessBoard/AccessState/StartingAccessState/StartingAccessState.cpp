#include "StartingAccessState.hpp"
#include "../../AccessObject/PlayerAccessObject/PlayerAccessObject.hpp"
#include "../../../../../../Config/Config.hpp"

namespace Kokoha
{
	String StartingAccessState::stageName;

	StartingAccessState::StartingAccessState(const String& argStageName)
		: m_noiseCount(-1)
	{
		stageName = argStageName;
		setMakeObjectList();
	}

	StartingAccessState::StartingAccessState()
		: m_noiseCount(0)
	{		
		setMakeObjectList();
	}

	void StartingAccessState::input(const Vec2& cursorPos)
	{
		static const double NOISE_DIST = Config::get<double>(U"StartingAccessState.noiseDist");
		static const int32  NOISE_SPAN = Config::get<int32>(U"StartingAccessState.noiseSpan");

		if (m_playerPos.distanceFrom(cursorPos) < NOISE_DIST && m_noiseCount > NOISE_SPAN)
		{
			m_noiseCount = -1; // updateで0になる
		}
	}

	Optional<std::shared_ptr<AccessState>> StartingAccessState::update(
		AccessObject::GuidToObject& objectMap,
		AccessObject::TypeToGuidSet& typeToGuidSet)
	{
		if (!m_makeObjectList.empty())
		{
			for (const auto& ptr : m_makeObjectList)
			{
				AccessObject::setMakingObject(ptr, objectMap, typeToGuidSet);
			}
			m_makeObjectList.clear();
		}

		for (const auto& guid : typeToGuidSet[AccessObject::Type::PLAYER])
		{
			m_playerPos = objectMap[guid]->body().center;
		}

		++m_noiseCount;

		return none;
	}

	bool StartingAccessState::isUpdatingObject() const
	{
		return false;
	}

	void StartingAccessState::draw() const
	{
		// Boardの中心座標
		static const Vec2 CENTER_POS = Config::get<Vec2>(U"StartingAccessState.centerPos");
		// 表示する場所の比率
		static const double RATE = Config::get<double>(U"StartingAccessState.rate");
		// 文字を揺らす大きさ
		static const double NOISE_AMOUNT = Config::get<double>(U"StartingAccessState.noiseAmount");

		Vec2 drawPos = RATE * m_playerPos + (1 - RATE) * CENTER_POS;
		if (m_noiseCount == 0)
		{
			drawPos.x += Random(-NOISE_AMOUNT, +NOISE_AMOUNT);
			drawPos.y += Random(-NOISE_AMOUNT, +NOISE_AMOUNT);
		}
		FontAsset(U"15")(U"Click").drawAt(drawPos);
	}

	void StartingAccessState::setMakeObjectList()
	{
		// オブジェクトの作成用のマップ
		static std::unordered_map<String, std::function<AccessObject::Ptr(const Vec2& pos)>> makeObjectMap =
		{
			{U"player",[](const Vec2& pos) { return std::make_shared<PlayerAccessObject>(pos); }}
		};

		// オブジェクトの読み込み
		const TOMLReader objectToml(U"asset/data/stage/object.toml");
		for (const auto object : objectToml[stageName].tableArrayView())
		{
			const String type = object[U"type"].getString();
			const Vec2   pos = Terrain::toPixel(Point(object[U"x"].get<int32>(), object[U"y"].get<int32>()));

			m_makeObjectList.emplace_back(makeObjectMap[type](pos));
		}
	}
}
