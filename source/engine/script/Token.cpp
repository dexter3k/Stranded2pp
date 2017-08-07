#include "Token.h"

#include <utility>

namespace script
{

const std::unordered_map<std::string, Token::Type> Token::tokenNames = {
	{"on", Event},
	{"if", If},
	{"elseif", Elseif},
	{"else", Else},
	{"skip", Skip},
	{"loop", Loop}
};

Token::Type Token::getTokenType(std::string const& name)
{
	auto it = tokenNames.find(name);
	if (it == tokenNames.end())
	{
		return Unknown;
	}
	
	return it->second;
}

Token::Token() :
	type(Unknown),
	value("")
{}

Token::Token(Type type, std::string const& value) :
	type(type),
	value(value)
{}

Token::Token(Token const& other) :
	type(other.type),
	value(other.value)
{}

Token::Token(Token && other) :
	type(other.type),
	value(std::move(other.value))
{}

Token & Token::operator=(Token const& other)
{
	type = other.type;
	value = other.value;

	return *this;
}

Token & Token::operator=(Token && other)
{
	type = other.type;
	value = std::move(other.value);

	return *this;
}

Token::Type Token::getType() const
{
	return type;
}

void Token::setType(Type type)
{
	this->type = type;
}

std::string const& Token::getValue() const
{
	return value;
}

void Token::setValue(std::string const& value)
{
	this->value = value;
}

bool Token::operator==(Token const& other) const
{
	return (type == other.type) && (value == other.value);
}

bool Token::operator!=(Token const& other) const
{
	return !operator==(other);
}

} // namespace script
