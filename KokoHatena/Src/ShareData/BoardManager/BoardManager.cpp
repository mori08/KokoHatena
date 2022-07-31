#include"BoardManager.hpp"
#include"Board/MailBoard/MailBoard.hpp"

namespace Kokoha
{
	BoardManager::BoardManager()
	{

	}

	void BoardManager::load(RecordManager&)
	{
		m_boardList.clear();

		m_boardList.emplace_back(std::make_unique<MailBoard>());
	}

	void BoardManager::update()
	{
		// �擪�{�[�h�̓��͂��󂯕t����
		if (!m_boardList.empty())
		{
			const auto& boardRequest = m_boardList.front()->input();
		}

		// �\�����̃{�[�h�̍X�V
		for (auto& board : m_boardList)
		{
			board->update();
		}
	}

	void BoardManager::draw() const
	{
		// �\�����̃{�[�h�̕`��
		for (const auto& board : m_boardList)
		{
			board->draw();
		}
	}

	std::list<std::unique_ptr<Board>>::iterator BoardManager::findBoardItr(const Board::Role& role)
	{
		for (auto itr = m_boardList.begin(); itr != m_boardList.end(); ++itr)
		{
			if ((*itr)->role() == role) { return itr; }
		}
		return m_boardList.end();
	}

	void BoardManager::displayBoard(const Board::Role& role, const String& requestText)
	{
		// �擪�Ɉړ�������C�e���[�^
		auto boardItr = findBoardItr(role);

		// �{�[�h��������Ȃ��Ƃ��G���[
		if (boardItr == m_boardList.end())
		{
			throw Error(U"Faild to find Board");
		}

		// �őO�ʂɈړ�
		auto boardPtr = std::move(*boardItr);
		m_boardList.erase(boardItr);
		m_boardList.emplace_front(std::move(boardPtr));

		// �擪�̃{�[�h�̏�Ԃ�IS_DISPLAYED�ɕύX
		m_boardList.front()->display();

		// �擪�̃{�[�h�̏�Ԃɖ��߂��o��
		m_boardList.front()->receiveRequest(requestText);
	}

	void BoardManager::hideBoard(const Board::Role& role)
	{
		// �����Ɉړ�������C�e���[�^
		auto boardItr = findBoardItr(role);

		// �{�[�h��������Ȃ��Ƃ��G���[
		if (boardItr == m_boardList.end())
		{
			throw Error(U"Faild to find Board");
		}

		// �őO�ʂɈړ�
		auto boardPtr = std::move(*boardItr);
		m_boardList.erase(boardItr);
		m_boardList.emplace_back(std::move(boardPtr));

		// �����̃{�[�h�̏�Ԃ�IS_HIDING�ɕύX
		m_boardList.front()->hide();
	}
}