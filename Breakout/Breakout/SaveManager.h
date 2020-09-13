#pragma once
#include "SDL.h"
#include "Base64Encode.h"
#include <string>
#include <vector>
#include <fstream>

std::vector<std::string> get_scores()
{
	std::vector<std::string> scores;

	std::ifstream scoresIn("Scores.txt");
	int i = 1;

	for (std::string line; getline(scoresIn, line);)
	{
		scores.push_back(base64_decode(line));
	}

	return scores;
}

void set_score(std::string name, unsigned int score)
{
	//insert score above worse and below better scores

	std::string scores = "";
	std::ifstream scoresIn("../Scores.txt");
	unsigned int i = 0;
	std::string currentName;
	std::string decodedLine;
	unsigned int currentScore;

	bool scoreWritten = false;

	for (std::string line; getline(scoresIn, line);)
	{
		decodedLine = base64_decode(line);
		size_t delimiterPos = decodedLine.find_last_of(' ');
		currentName = decodedLine.substr(0, delimiterPos);
		currentScore = atoi(decodedLine.substr(delimiterPos + 1, line.length()).c_str());

		if (currentScore < score && !scoreWritten)
		{
			++i;
			scores += base64_encode(name + " " + std::to_string(score)) + "\n";
			scoreWritten = true;
			if (i > 10) break;
		}

		scores += line + "\n";
		if (i > 10) break;
	}
	scoresIn.close();

	if(i < 10 && !scoreWritten)
		scores += base64_encode(name + " " + std::to_string(score)) + "\n";


	std::ofstream scoreFileOut("Scores.txt");
	scoreFileOut << scores;
	scoreFileOut.close();
}