#include "Program.h"

#include <cctype>
#include <algorithm>
#include <iostream>

#include "ExecutionContext.h"

namespace script
{

Program::Program(ExecutionContext* context) :
	context(context)
{}

void Program::execute(std::string const& event)
{}

bool Program::compile(std::string const& code)
{
	auto tokens = tokenize(code);
	if (tokens.empty())
	{
		return true;
	}

	return true;
}

std::list<script::Token> Program::tokenize(std::string const& code) const
{
	// TODO: Rewrite this ASAP

	std::list<script::Token> tokens;

	if (code.empty())
	{
		return tokens;
	}

	std::string currentToken = "";

	char const* cString = code.c_str();
	char c = 0;

	// NOTE: c is current char, cString points to next char
	while ((c = *cString++))
	{
		// Skip all whitespace non-standard symbols
		if (std::isspace(c) != 0 ||
			std::isprint(c) == 0)
		{
			continue;
		}

		// Skip single-line comment
		if ((c == '#') || // '#'- comment
			(c == '/' && *cString == '/')) // '//'- comment
		{
			do
			{
				c = *cString++;
			} while (c != 0 && c != '\n');

			if (c == 0)
			{
				break; // End parsing
			}
			else
			{
				continue;
			}
		}

		/* Skip multi-line comment */
		if (c == '/' && *cString == '*')
		{
			do
			{
				c = *cString++;
			} while (c != 0 && !(c == '*' && *cString == '/'));

			if (c == 0)
			{
				break;
			}
			else
			{
				++cString;

				continue;
			}
		}

		// Read text token (keywords and identifiers)
		if (std::isalpha(c) != 0 ||
			c == '_')
		{
			currentToken = c;

			while ((c = *cString++))
			{
				if (std::isalnum(c) != 0 ||
					c == '_')
				{
					currentToken += c;
				}
				else
				{
					--cString; // Make it point to the first unparsed char

					break;
				}
			}

			// Check for keyword
			Token::Type tokenType = Token::getTokenType(currentToken);
			if (tokenType != Token::Unknown)
			{
				//std::cout << "Token: " << currentToken << std::endl;

				tokens.emplace_back(tokenType, currentToken);

				continue;
			}

			// Not a keyword? Then its an identifier!
			//std::cout << "Identifier: " << currentToken << std::endl;

			tokens.emplace_back(Token::Identifier, currentToken);

			continue;
		}

		// Read values
		if (std::isdigit(c) != 0 ||
			(c == '.' && std::isdigit(*cString) != 0)) // i.e. .338
		{
			currentToken.clear();

			// is hex?
			if (c == '0' && *cString == 'x')
			{
				bool isNonZero = false;

				currentToken = "0x";

				++cString; // skip 'x'

				while ((c = *cString++))
				{
					if (std::isxdigit(c) == 0 &&
						c != '.')
					{
						break;
					}

					// Skip leading zeros
					if (!isNonZero)
					{
						if (c == '0')
						{
							continue;
						}
						else
						{
							isNonZero = true;
						}
					}

					currentToken += c;
				}
				--cString;

				if (!isNonZero)
				{
					currentToken += "0";
				}

				//std::cout << "Hex: " << currentToken << std::endl;
			}
			else
			{
				bool isDotPrefixed = c == '.' ? true : false;
				bool isNonZero = c != '0' ? true : false;

				if (c != '0')
				{
					currentToken += c;
				}

				while ((c = *cString++))
				{
					if (std::isdigit(c) == 0 &&
						c != '.')
					{
						break;
					}

					// Skip leading zeros
					if (!isNonZero)
					{
						if (c == '0')
						{
							continue;
						}
						else
						{
							isNonZero = true;
						}
					}

					currentToken += c;
				}
				--cString;

				if (isDotPrefixed)
				{
					currentToken = "0." + currentToken;
				}
				if (!isNonZero)
				{
					currentToken += "0";
				}
				if (currentToken[0] == '.')
				{
					currentToken = "0" + currentToken;
				}

				//std::cout << "Dec: " << currentToken << std::endl;
			}

			tokens.emplace_back(Token::Value, currentToken);

			continue;
		}

		if (c == '"')
		{
			currentToken = "\"";
			while ((c = *cString++))
			{
				if (c == '\\' && *cString == '"')
				{
					currentToken += "\"";
					++cString;

					continue;
				}
				else if (c == '"')
				{
					currentToken += '"';

					break;
				}

				currentToken += c;
			}

			//std::cout << "String: " << currentToken << std::endl;

			tokens.emplace_back(Token::String, currentToken);

			continue;
		}

		// Read operators
		if (c == '@' ||
			c == '$' ||
			c == '=' ||
			c == '+' ||
			c == '-' || /*
			c == '*' ||
			c == '/' || */
			c == '<' ||
			c == '>')
		{
			currentToken = c;

			// Check for ++'s and --'s
			if ((c == '+' || c == '-') &&
				*cString == '+')
			{
				currentToken += *cString;
			}

			// Check for x='s
			if ((*cString == '=') &&
				(	c == '+' ||
					c == '-' || /*
					c == '*' ||
					c == '/' || */
					c == '=' ||
					c == '<' ||
					c == '>'))
			{
				currentToken += *cString++;
			}

			//std::cout << "Operator: " << currentToken << std::endl;

			tokens.emplace_back(Token::Operator, currentToken);

			continue;
		}

		// Read other tokens
		currentToken = c;

		//std::cout << "Other: " << currentToken << std::endl;

		tokens.emplace_back(Token::Other, currentToken);
	}

	return tokens;
}

} // namespace script
