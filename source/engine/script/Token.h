#pragma once

#include <string>
#include <unordered_map>

namespace script
{

class Token
{
public:
	enum Type
	{
		Unknown,
		Event,
		If,
		Elseif,
		Else,
		Skip,
		Loop,
		Identifier,
		Variable,
		Operator,
		Value,
		String,
		Other
	};
public:
	static Type getTokenType(std::string const& name);
public:
	Token();
	Token(Type type, std::string const& value);
	Token(Token const& other);
	Token(Token && other);

	Token & operator=(Token const& other);
	Token & operator=(Token && other);

	Type getType() const;
	void setType(Type type);

	std::string const& getValue() const;
	void setValue(std::string const& value);

	bool operator==(Token const& other) const;
	bool operator!=(Token const& other) const;
private:
	static const std::unordered_map<std::string, Token::Type> tokenNames;
private:
	Type type;
	std::string value;
};

} // namespace script
