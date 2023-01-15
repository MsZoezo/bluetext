//
// Created by Zoezo on 1/15/2023.
//

#ifndef BLUETEXT_INPUTBUFFER_H
#define BLUETEXT_INPUTBUFFER_H

#include <regex>
#include <string>

class InputBuffer {
private:
	 static struct EmojiCode {
		std::regex regex;
		std::string emoji;
	};

	inline static const EmojiCode codes[] = {
			{std::regex(":heart:"), "\3"},
			{std::regex(":robot:"), "d[ o_0 ]b"},
			{std::regex(":fish:"),  "><(((`>"},
			{std::regex(":cat:"),   "=^..^="},
			{std::regex(":love:"),  "(\3_\3)"},
			{std::regex(":party:"), "(/.__.)/  \\(.__.\\)"},
			{std::regex(":yay:"),   "\\(^-^)/"},
			{std::regex(":fox:"),   "-^^,--,~"}
	};

	std::string buffer;

	void translateCodes();

public:
	std::string retrieve(short maxLength) const;
	void add(char character);
	void pop();
	void clear();
	int length();
};


#endif //BLUETEXT_INPUTBUFFER_H
