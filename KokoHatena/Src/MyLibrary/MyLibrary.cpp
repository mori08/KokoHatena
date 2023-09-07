#include "MyLibrary.hpp"


namespace Kokoha
{

	void registerAsset(const String& dirName)
	{
		// 指定されたディレクトリのファイルパスを配列に
		Array<FilePath> contents = FileSystem::DirectoryContents(dirName, Recursive::No);

		for (const auto& content : contents)
		{
			String fileName = FileSystem::FileName(content);

			// 指定されたパスがディレクトリであるとき
			if (FileSystem::IsDirectory(content))
			{
				registerAsset(dirName + fileName + U"/");
			}

			// 指定されたパスがファイルであるとき
			else if (FileSystem::IsFile(content))
			{
				// 拡張子がpngのとき
				if (FileSystem::Extension(content) == U"png")
				{
					TextureAsset::Register(FileSystem::BaseName(content), dirName + fileName);
				}

				// 拡張子がmp3のとき
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

		// このフレームのFPS(DelataTimeの逆数)を取得
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
