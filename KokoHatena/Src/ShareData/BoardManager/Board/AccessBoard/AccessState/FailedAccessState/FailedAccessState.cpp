#include "FailedAccessState.hpp"
#include "../StartingAccessState/StartingAccessState.hpp"
#include "../../../../../../Config/Config.hpp"
#include "../../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	FailedAccessState::FailedAccessState(const Point& playerSquare)
		: m_failedDistance(Max(Terrain::HEIGHT, Terrain::WIDTH))
		, m_playerSquare(playerSquare)
	{

	}

	void FailedAccessState::input(const Vec2&)
	{
	}

	Optional<std::shared_ptr<AccessState>> FailedAccessState::update(AccessObject::GuidToObject& objectMap, AccessObject::TypeToGuidSet& typeToGuidSet)
	{
		// �o�O���o�̐i�s���鑬�x
		static const double FAILED_SPEED = Config::get<double>(U"FailedAccessState.failedSpeed");
		static const double FAILED_WIDTH = Config::get<double>(U"FailedAccessState.failedWidth");
		m_failedDistance -= FAILED_SPEED * Scene::DeltaTime();
		if (m_failedDistance < -FAILED_WIDTH)
		{
			std::shared_ptr<AccessState> rtn = std::make_shared<StartingAccessState>();
			return rtn;
		}

		// �v���C���[�ȊO�̌�������
		static const double CHANGE_ALPHA_RATE = Config::get<double>(U"FailedAccessState.changeAlphaRate");
		for (const auto& guid : typeToGuidSet[AccessObject::Type::MINION])
		{
			objectMap[guid]->light().setAlpha(0, CHANGE_ALPHA_RATE);
		}

		return none;
	}

	bool FailedAccessState::isUpdatingObject() const
	{
		return false;
	}

	void FailedAccessState::draw() const
	{
		// �o�O���o�̕�
		static const double FAILED_WIDTH = Config::get<double>(U"FailedAccessState.failedWidth");

		for (int32 i : Range(0, Terrain::N - 1))
		{
			Point sq = Terrain::toSquare(i);
			
			// �v���C���[�ƃ}�X�̋���
			const double dist = sq.distanceFrom(m_playerSquare);
			if (dist < m_failedDistance) { continue; }

			Rect(sq * Terrain::SQUARE_SIZE, Terrain::SQUARE_SIZE).draw(MyWhite);

			Point b = Point::Zero();
			if (dist < m_failedDistance + FAILED_WIDTH)
			{
				b.x = Random(-1, +1);
				b.y = Random(-1, +1);
			}
			Rect(b + sq * Terrain::SQUARE_SIZE, Terrain::SQUARE_SIZE).draw(MyBlack);
		}
	}
}