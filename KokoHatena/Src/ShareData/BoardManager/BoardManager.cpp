#include"BoardManager.hpp"
#include"Board/MailBoard/MailBoard.hpp"
#include"Board/AccessBoard/AccessBoard.hpp"
#include"../../Config/Config.hpp"
#include"../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	BoardManager::BoardManager()
	{

	}

	void BoardManager::load(RecordManager&)
	{
		m_boardList.clear();

		m_boardList.emplace_back(std::make_unique<MailBoard>());
		m_boardList.emplace_back(std::make_unique<AccessBoard>());
	}

	void BoardManager::update()
	{
		// �A�C�R�����������Ƃ��̏���
		for (auto itr = m_boardList.begin(); itr != m_boardList.end(); ++itr)
		{
			if (!(*itr)->onIconClicked()) { continue; }

			const bool isTop = (itr == m_boardList.begin() && (*itr)->state() == Board::State::IS_DISPLAYED);
			if (isTop) // �{�[�h���擪�ŕ\�����̂Ƃ�
			{
				hideBoard((*itr)->role()); // ��\���ɂ���
			}
			else // �{�[�h���擪�ɂȂ��Ƃ�
			{
				displayBoard((*itr)->role()); // �擪�ɕ\������
			}

			break;
		}

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
		Scene::Rect().draw(Palette::Gray);

		// �\�����̃{�[�h�̕`��
		for (auto itr = m_boardList.rbegin(); itr != m_boardList.rend(); ++itr)
		{
			(*itr)->draw();
		}

		// �A�C�R���̕`��
		static const int32 ICON_BAR_HEIGHT = Config::get<int32>(U"Board.iconSize.y");
		const Rect iconBar(0, Scene::Height() - ICON_BAR_HEIGHT, Scene::Width(), ICON_BAR_HEIGHT);
		iconBar.draw(MyBlack);
		iconBar.drawFrame(0, 2, MyWhite);
		for (const auto& board : m_boardList)
		{
			board->drawIcon();
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
		m_boardList.back()->hide();
	}
}