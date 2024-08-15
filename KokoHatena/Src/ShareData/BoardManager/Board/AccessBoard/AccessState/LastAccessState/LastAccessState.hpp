#pragma once

#include "../AccessState.hpp"

namespace Kokoha
{
	class LastAccessState : public AccessState
	{
	private:

		double m_wordsCount;

		size_t m_textId;

	public:

		LastAccessState();

	private:

		void input(const BoardArg& board) override;

		Optional<std::shared_ptr<AccessState>> update(
			AccessObject::GuidToObject& objectMap,
			AccessObject::TypeToGuidSet& typeToGuidSet,
			BoardRequest& boradRequest) override;

		void draw() const override;

		bool isUpdatingObject() const override
		{
			return false;
		}

	private:

		static const Array<String>& textList();
	};
}
