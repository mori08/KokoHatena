#include "StartingAccessState.hpp"
#include "../PlayingAccessState/PlayingAccessState.hpp"
#include "../TutorialAccessState/TutorialAccessState.hpp"
#include "../../AccessObject/PlayerAccessObject/PlayerAccessObject.hpp"
#include "../../AccessObject/EnemyAccessObject/EnemyAccessObject.hpp"
#include "../../AccessObject/EnemyAccessObject/RandomWalkingEnemyAccessObject/RandomWalkingEnemyAccessObject.hpp"
#include "../../AccessObject/EnemyAccessObject/ChasingEnemyAccessObject/ChasingEnemyAccessObject.hpp"
#include "../../AccessObject/GoalAccessObject/GoalAccessObject.hpp"
#include "../../../../../../Config/Config.hpp"
#include "../../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	String StartingAccessState::stageName;

	StartingAccessState::StartingAccessState(const String& argStageName)
		: m_noiseCount(-1)
		, m_nextStateFlag(false)
	{
		stageName = argStageName;
		setMakeObjectList();
	}

	StartingAccessState::StartingAccessState()
		: m_noiseCount(0)
		, m_nextStateFlag(false)
	{		
		setMakeObjectList();
	}

	void StartingAccessState::input(const BoardArg& board)
	{
		static const double NOISE_DIST = Config::get<double>(U"StartingAccessState.noiseDist");
		static const int32  NOISE_SPAN = Config::get<int32>(U"StartingAccessState.noiseSpan");

		if (m_playerPos.distanceFrom(board.cursorPos()) < NOISE_DIST && m_noiseCount > NOISE_SPAN)
		{
			m_noiseCount = -1; // updateで0になる
		}

		if (board.rect().leftClicked() && m_playerPos.distanceFrom(board.cursorPos()) < NOISE_DIST)
		{
			m_nextStateFlag = true;
		}
	}

	Optional<std::shared_ptr<AccessState>> StartingAccessState::update(
		AccessObject::GuidToObject& objectMap,
		AccessObject::TypeToGuidSet& typeToGuidSet,
		BoardRequest&)
	{
		if (!m_makeObjectList.empty())
		{
			objectMap.clear();
			for (auto& guidSet : typeToGuidSet)
			{
				guidSet.second.clear();
			}

			for (const auto& ptr : m_makeObjectList)
			{
				AccessObject::setMakingObject(ptr, objectMap, typeToGuidSet);
			}
			m_makeObjectList.clear();
		}

		for (const auto& guid : typeToGuidSet[AccessObject::Type::PLAYER])
		{
			// Boardの中心座標
			static const Vec2 CENTER_POS = Config::get<Vec2>(U"StartingAccessState.centerPos");
			// 表示する場所の比率
			static const double RATE = Config::get<double>(U"StartingAccessState.rate");

			m_playerPos = objectMap[guid]->body().center;
			m_playerPos = RATE * m_playerPos + (1 - RATE) * CENTER_POS;;
		}

		++m_noiseCount;

		if (m_nextStateFlag)
		{
			std::shared_ptr<AccessState> rtn;
			if (stageName == U"day0")
			{
				rtn = std::make_shared<TutorialAccessState>();
			}
			else
			{
				rtn = std::make_shared<PlayingAccessState>();
			}
			return rtn;
		}

		return none;
	}

	bool StartingAccessState::isUpdatingObject() const
	{
		return false;
	}

	void StartingAccessState::draw() const
	{
		// 文字を揺らす大きさ
		static const double NOISE_AMOUNT = Config::get<double>(U"StartingAccessState.noiseAmount");

		Scene::Rect().draw(MyBlack);

		Vec2 drawPos = m_playerPos;
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
			{U"player",[](const Vec2& pos) { return std::make_shared<PlayerAccessObject>(pos); }},

			{U"enemy", [](const Vec2& pos) { return std::make_shared<EnemyAccessObject> (pos); }},
			{U"enemy_randomWalking", [](const Vec2& pos) { return std::make_shared<RandomWalkingEnemyAccessObject>(pos); }},
			{U"enemy_chasing", [](const Vec2& pos) { return std::make_shared<ChasingEnemyAccessObject>(pos); }},

			{U"goal",  [](const Vec2& pos) { return std::make_shared<GoalAccessObject>  (pos); }}
		};

		// オブジェクトの読み込み
		const TOMLReader objectToml(U"asset/data/stage/object.toml");
		for (const auto object : objectToml[stageName].tableArrayView())
		{
			const String type = object[U"type"].getString();
			const Vec2   pos = Terrain::toPixel(Point(object[U"x"].get<int32>(), object[U"y"].get<int32>()));

			if (!makeObjectMap.count(type))
			{
				throw Error(U"Faild to make [" + type + U"] object");
			}

			m_makeObjectList.emplace_back(makeObjectMap[type](pos));
		}
	}
}
