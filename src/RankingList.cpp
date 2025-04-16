#include "RankingList.h"

RankingList* RankingList::rankingList = nullptr;

RankingList::RankingList()
{
	//LEER
	std::ifstream fentrada(RANKING_PATH, std::ios::in | std::ios::binary);

	if (!fentrada) {
		std::cout << "No ranking file" << std::endl;
	}
	else {
		if (!fentrada.is_open()) {
			std::cout << "Cannot open ranking file" << std::endl;
		}
	}

	fentrada.seekg(0, fentrada.end);
	int length = fentrada.tellg();
	fentrada.seekg(0, fentrada.beg);

	if (length > 0) {

		int vectorSize;
		fentrada.read(reinterpret_cast<char*>(&vectorSize), sizeof(int));

		ranking.resize(vectorSize);

		size_t tempNameLength;
		char* tempName;
		int tempScore;
		playersScore tempRankingInfo;

		for (int i = 0; i < ranking.size(); i++) {
			fentrada.read(reinterpret_cast<char*>(&tempNameLength), sizeof(size_t));

			tempName = new char[tempNameLength + 1];
			fentrada.read(tempName, tempNameLength);
			tempName[tempNameLength] = '\0';
			tempRankingInfo.name = tempName;
			delete[]tempName;

			fentrada.read(reinterpret_cast<char*>(&tempScore), sizeof(int));
			tempRankingInfo.score = tempScore;

			ranking[i] = tempRankingInfo;
		}

		for (int i = 0; i < ranking.size(); i++)
		{
			std::cout << ranking[i].name << " " << ranking[i].score << std::endl;
		}
	}

	fentrada.close();

}

RankingList* RankingList::GetInstance()
{
	if (rankingList == nullptr) {
		rankingList = new RankingList();
	}

	return rankingList;
}

void RankingList::InsertPlayer(std::string name, int score)
{
	playersScore temp;
	temp.name = name;
	temp.score = score;

	if (ranking.size() == 0) {
		ranking.push_back(std::move(temp));
		return;
	}

	for (int i = 0; i < ranking.size(); i++) {
		if (temp < ranking[i]) {
			ranking.insert(ranking.begin() + i, temp);
			break;
		}
		if (i == ranking.size() - 1) {
			ranking.push_back(std::move(temp));
			break;
		}
	}

	if (ranking.size() > 5) {
		ranking.pop_back();
	}
}

void RankingList::UpdateFile()
{
	std::ofstream myFile(RANKING_PATH, std::ios::out | std::ios::binary);

	int len = ranking.size();
	//Guardas la longitud del vector
	myFile.write(reinterpret_cast<char*>(&len), sizeof(int));

	std::string tempName;
	size_t tempNameLength;
	int tempScore;

	for (int i = 0; i < ranking.size(); i++) {
		//Guardamos el nombre en una variable temporal
		tempName = ranking[i].name;
		//Guardamos la longitud del nombre
		tempNameLength = tempName.length();
		//Escribe en el fichero la longitud del nombre
		myFile.write(reinterpret_cast<char*>(&tempNameLength), sizeof(size_t));
		//Escribe en el fichero el nombre en si
		myFile.write(tempName.c_str(), tempName.size());

		//Guardamos el score en una variable temporal
		tempScore = ranking[i].score;
		//Escribe en el fichero la puntuación en si
		myFile.write(reinterpret_cast<char*>(&tempScore), sizeof(int));
	}

	myFile.close();
}

void RankingList::PrintPlayer(int playerIndex)
{
	std::cout << ranking[playerIndex].name << ' ' << ranking[playerIndex].score << std::endl;
}

std::string RankingList::GetRankingData(int pos)
{
	if (pos > ranking.size()) {
		return "";
	}
	else {
		return ranking[pos].name + " " + std::to_string(ranking[pos].score);
	}
}

void RankingList::ClearFile()
{
	std::ofstream myFile(RANKING_PATH, std::ios::out | std::ios::trunc | std::ios::binary);
	myFile.close();
	ranking.clear();
}

bool operator<(const RankingList::playersScore& playerScore1, const RankingList::playersScore& playerScore2)
{
	return playerScore1.score < playerScore2.score;
}


