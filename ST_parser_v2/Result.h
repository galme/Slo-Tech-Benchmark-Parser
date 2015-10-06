#pragma once
#include <string>
struct Result
{
	std::string nickname; // forum nickname ... used for identifying unique results
	std::string middle; // hardware details (CPU, GPU, RAM, ...)
	double score; // (total score, FPS, ...) ... used for comparison
	std::string link; // benchmark proof, or just the OP

	Result(std::string nickname, std::string middle, double score, std::string link = "")
	{
		this->nickname = nickname;
		this->middle = middle;
		this->score = score;
		this->link = link;
	}
};

