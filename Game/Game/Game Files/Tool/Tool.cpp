#include "Tool.h"


void Tool::SplitStringWords(const std::string & p_string, std::vector<std::string> & p_words)
{
	const std::string Space = " ";
	std::string buffer;

	for (int i = 0; i <= p_string.size(); ++i)
	{
		if (p_string[i] == Space[0] || i == p_string.size())
		{
			p_words.push_back(buffer);
			buffer.clear();
		}
		else
		{
			buffer += p_string[i];
		}
	}
}