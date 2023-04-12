#include "SuccessAccessState.hpp"
#include "../../../../../../Config/Config.hpp"
#include "../../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	void SuccessAccessState::input(const Vec2&)
	{
	}

	Optional<std::shared_ptr<AccessState>> SuccessAccessState::update(
		AccessObject::GuidToObject& objectMap,
		AccessObject::TypeToGuidSet& typeToGuidSet)
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

		return none;
	}

	bool SuccessAccessState::isUpdatingObject() const
	{
		return false;
	}

	void SuccessAccessState::draw() const
	{
	}
}