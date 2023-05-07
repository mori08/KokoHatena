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
		// �v���C���[�ȊO�̌�������
		static const double CHANGE_ALPHA_RATE = Config::get<double>(U"FailedAccessState.changeAlphaRate");
		for (const auto& guid : typeToGuidSet[AccessObject::Type::MINION])
		{
			objectMap[guid]->light().setAlpha(0, CHANGE_ALPHA_RATE);
		}

		// �v���C���[�̌�������
		static const double CHANGE_ALPHA_PLAYER_RATE = Config::get<double>(U"SuccessAccessState.changeAlphaRate");
		for (const auto& guid : typeToGuidSet[AccessObject::Type::PLAYER])
		{
			objectMap[guid]->light().setAlpha(0, CHANGE_ALPHA_PLAYER_RATE);
		}

		// ���̗ւ��L���鑬�x
		static const double LIGHT_RADIUS_SPREAD_SPEED = Config::get<double>(U"SuccessAccessState.lightRadiusSpreadSpeed");
		// ���̗ւ̍ő唼�a
		static const double LIGHT_MAX_RADIUS = Config::get<double>(U"SuccessAccessState.lightMaxRaduis");
		// ���̕s�����x�̕ύX�̓x��
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
		// ���̗ւ̑���
		static const double LIGHT_THICKNESS = Config::get<double>(U"SuccessAccessState.lightThickness");

		// ���̐F
		ColorF color = ColorF(MyWhite, m_lightAlpha);

		// ���̗ւ̕`��
		Circle(m_playerPos, m_lightRadius).drawFrame(LIGHT_THICKNESS, color);

		// �����̕`��
		FontAsset(U"15")(U"ACCESS").drawAt(m_playerPos, color);
	}
}