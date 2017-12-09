#include "CompilerUtils.h"

#include "utils/ParseUtils.h"

namespace script
{
	namespace impl
	{
		bool isParseableCharacter(char character)
		{
			return ((std::isspace(character) == 0) &&
				(std::isprint(character) != 0));
		}
	} // namespace impl

	std::list<script::Token> tokenize(std::string const & source)
	{
		std::list<script::Token> tokens;

		if (source.empty())
		{
			return tokens;
		}

		char const* cString = source.c_str();
		// Current character
		char c = 0;

		// Temporary string for constructing tokens out of readed characters
		std::string currentToken = "";

		while ((c = *cString++))
		{
			// cString points to the next character after c

			// Skip all spaces and non-printable characters
			if (!impl::isParseableCharacter(c))
			{
				continue;
			}

			// Skip single-line '//' or '#' comment
			if ((c == '#') ||
				(c == '/' && *cString == '/'))
			{
				do
				{
					c = *cString++;
				} while (c != 0 && c != '\n');

				if (c == 0)
				{
					break;
				}
				else
				{
					continue;
				}
			}

			// Skip multi-line '/* */' comment
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
					// We ended on the asterisk, not the slash, so we must
					// advance pointer
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
						// Current character does not belong to this identifier
						// and should be reparsed
						--cString;

						break;
					}
				}

				// Check for keyword
				auto tokenType = Token::getTokenType(currentToken);
				if (tokenType != Token::Unknown)
				{
					tokens.emplace_back(tokenType, currentToken);
				}
				else
				{
					tokens.emplace_back(Token::Identifier, currentToken);
				}

				continue;
			}

			// Read variable identifiers
			if (c == '$')
			{
				currentToken.clear();

				while ((c = *cString++))
				{
					if (std::isalnum(c) != 0 &&
						c == '_')
					{
						currentToken += c;
					}
					else
					{
						--cString;

						break;
					}
				}

				tokens.emplace_back(Token::Variable, currentToken);

				continue;
			}

			// Read strings enclosed in '"' quotes
			if (c == '"')
			{
				currentToken.clear();

				while ((c = *cString++))
				{
					if (c == '\\' && *cString == '"') // Check for '\"' escape
					{
						currentToken += "\"";

						++cString;

						continue;
					}
					// End of string
					else if (c == '"')
					{
						break;
					}

					currentToken += c;
				}

				tokens.emplace_back(Token::String, currentToken);

				continue;
			}

			// Read number value
			if (std::isdigit(c) != 0 ||
				(c == '.' && (std::isdigit(*cString) != 0))) // i.e. .25 == 0.25
			{
				currentToken.clear();

				// Is hexadecimal number?
				if (c == '0' && *cString == 'x')
				{
					bool isNonZero = false;

					currentToken += "0x";

					++cString; // Skip 'x'

					while ((c = *cString++))
					{
						if (std::isdigit(c) == 0 &&
							c != '.')
						{
							break;
						}

						//  Skip leading zeros
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
				}
				// Decimal number
				else
				{
					bool isDotPrefixed = (c == '.');
					bool isNonZero = (c != '0');

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
				}

				tokens.emplace_back(Token::Value, currentToken);

				continue;
			}

			// Read operators
			if (c == '@' ||
				c == '=' ||
				c == '+' ||
				c == '-' ||
				c == '*' ||
				c == '/' ||
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
						c == '-' ||
						c == '*' ||
						c == '/' ||
						c == '=' ||
						c == '<' ||
						c == '>'))
				{
					currentToken += *cString++;
				}

				tokens.emplace_back(Token::Operator, currentToken);

				continue;
			}

			// Read other tokens
			currentToken = c;

			tokens.emplace_back(Token::Other, currentToken);
		}

		return tokens;
	}
} // namespace script
