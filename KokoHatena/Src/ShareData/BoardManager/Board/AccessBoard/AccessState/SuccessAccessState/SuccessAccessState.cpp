#include "SuccessAccessState.hpp"
#include "../../../../../../Config/Config.hpp"
#include "../../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	SuccessAccessState::SuccessAccessState(const Vec2& playerPos)
		: m_playerPos(playerPos)
		, m_lightRadius(0)
		, m_lightAlpha(1.0)
		, m_alreadySendRequest(false)
	{
	}

	void SuccessAccessState::input(const Vec2&)
	{
	}

	Optional<std::shared_ptr<AccessState>> SuccessAccessState::update(
		AccessObject::GuidToObject& objectMap,
		AccessObject::TypeToGuidSet& typeToGuidSet,
		BoardRequest& boardRequest)
	{
		// プレイヤー以外の光を消す
		static const double CHANGE_ALPHA_RATE = Config::get<double>(U"FailedAccessState.changeAlphaRate");
		for (const auto& guid : typeToGuidSet[AccessObject::Type::MINION])
		{
			objectMap[guid]->light().setAlpha(0, CHANGE_ALPHA_RATE);
		}

		// プレイヤーの光を消す
		static const double CHANGE_ALPHA_PLAYER_RATE = Config::get<double>(U"SuccessAccessState.changeAlphaRate");
		for (const auto& guid : typeToGuidSet[AccessObject::Type::PLAYER])
		{
			objectMap[guid]->light().setAlpha(0, CHANGE_ALPHA_PLAYER_RATE);
		}

		// 光の輪が広がる速度
		static const double LIGHT_RADIUS_SPREAD_SPEED = Config::get<double>(U"SuccessAccessState.lightRadiusSpreadSpeed");
		// 光の輪の最大半径
		static const double LIGHT_MAX_RADIUS = Config::get<double>(U"SuccessAccessState.lightMaxRaduis");
		// 光の不透明度の変更の度合
		static const double LIGHT_ALPHA_RATE = Config::get<double>(U"SuccessAccessState.lightAlphaRate");
		m_lightRadius += Scene::DeltaTime()*LIGHT_RADIUS_SPREAD_SPEED;
		internalDividingPoint(m_lightAlpha, 0, LIGHT_ALPHA_RATE);
		if (m_lightRadius > LIGHT_MAX_RADIUS)
		{
			m_lightRadius = 0;
			m_lightAlpha = 1.0;
			
			if (!m_alreadySendRequest)
			{
				m_alreadySendRequest = true;
				boardRequest.toBoard.emplace_back(BoardRole::MESSAGE, U"Clear");
			}
		}

		return none;
	}

	bool SuccessAccessState::isUpdatingObject() const
	{
		return false;
	}

	void SuccessAccessState::draw() const
	{
		// 光の輪の太さ
		static const double LIGHT_THICKNESS = Config::get<double>(U"SuccessAccessState.lightThickness");

		// 光の色
		ColorF color = ColorF(MyWhite, m_lightAlpha);

		// 光の輪の描画
		Circle(m_playerPos, m_lightRadius).drawFrame(LIGHT_THICKNESS, color);

		// 文字の描画
		FontAsset(U"15")(U"ACCESS").drawAt(m_playerPos, color);
	}
}