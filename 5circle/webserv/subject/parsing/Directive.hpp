#ifndef DIRECTIVE_HPP
#define DIRECTIVE_HPP

class Directive {
private:
public:
	Directive(string name, string value)
	{
		this->name = name;
		this->value = value;
	}
    string name;
	//raw value
    string value;
	void *data;
};

#endif