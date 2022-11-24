#include "MyLibrary.hpp"


namespace Kokoha
{

	void registerAsset(const String& dirName)
	{
		// �w�肳�ꂽ�f�B���N�g���̃t�@�C���p�X��z���
		Array<FilePath> contents = FileSystem::DirectoryContents(dirName, false);

		for (const auto& content : contents)
		{
			String fileName = FileSystem::FileName(content);

			// �w�肳�ꂽ�p�X���f�B���N�g���ł���Ƃ�
			if (FileSystem::IsDirectory(content))
			{
				registerAsset(dirName + fileName + U"/");
			}

			// �w�肳�ꂽ�p�X���t�@�C���ł���Ƃ�
			else if (FileSystem::IsFile(content))
			{
				// �g���q��png�̂Ƃ�
				if (FileSystem::Extension(content) == U"png")
				{
					TextureAsset::Register(FileSystem::BaseName(content), dirName + fileName);
				}

				// �g���q��mp3�̂Ƃ�
				if (FileSystem::Extension(content) == U"mp3")
				{
					AudioAsset::Register(FileSystem::BaseName(content), dirName + fileName);
				}

			}
		}
	}


	void showFPS()
	{
#ifdef _DEBUG

		// ���̃t���[����FPS(DelataTime�̋t��)���擾
		static std::list<double> fpsList;
		fpsList.emplace_back(1.0 / Scene::DeltaTime());
		if (fpsList.size() > 60) { fpsList.pop_front(); }

		for (const auto& fps : fpsList)
		{
			Circle(800.0 / 120.0 * fps, 2, 4).draw(ColorF(0, 1, 1, 0.4));
		}

#endif // _DEBUG
	}


	Array<Point> getGridPoint(const Rect& rect)
	{
		Array<Point> rtn;

		for (int32 x : Range(rect.x, rect.x + rect.w))
		{
			for (int32 y : Range(rect.y, rect.y + rect.h))
			{
				rtn.emplace_back(x, y);
			}
		}

		return rtn;
	}
}