#include "arithmetic.h"

//Р’С‹Р±РѕСЂ РІС…РѕРґРЅРѕРіРѕ РїРѕС‚РѕРєР°
std::string InputDialog();

//Р’С‹Р±РѕСЂ РІС‹С…РѕРґРЅРѕРіРѕ РїРѕС‚РѕРєР°
std::string OutputDialog();

//С„СѓРЅРєС†РёСЏ СЃРѕР·РґР°РµС‚ РїСѓС‚СЊ РёР»Рё РµСЃР»Рё РѕРЅ РЅРµ Р±С‹Р» РїРµСЂРµРґР°РЅ Р·Р°РјРµРЅСЏРµС‚ РµРіРѕ РґРµС„РѕР»С‚РЅС‹Рј
std::string MakePath(std::string s, std::string const default_path);

//РІС‹Р·РѕРІ С„СѓРЅРєС†РёР№ РѕР±СЂР°Р±РѕС‚РєРё СЃС‚СЂРѕРєРё
void CallAndCheck(StringPair data_, std::ostream& out);

//СЃРїСѓСЃРє РІРЅРёР· РїРѕ СЃРїРёСЃРєСѓ РёР»Рё РїРѕР»СѓС‡РµРЅРёРµ Р·РЅР°С‡РµРЅРёСЏ С‚РµРєСѓС‰РµРіРѕ Р°С‚РѕРјР°
int Node::evaluate()
{
	if (std::holds_alternative<char>(value))
	{
		if (std::get<char>(value) == '+')
			return std::get<NodePair>(arguments).first->evaluate() + std::get<NodePair>(arguments).second->evaluate();
		if (std::get<char>(value) == '*')
			return std::get<NodePair>(arguments).first->evaluate() * std::get<NodePair>(arguments).second->evaluate();
		if (std::get<char>(value) == '-')
		{
			if (std::holds_alternative<NodePair>(arguments))
				return std::get<NodePair>(arguments).first->evaluate() - std::get<NodePair>(arguments).second->evaluate();
			else
				return (-1) * std::get<std::shared_ptr<Node>>(arguments)->evaluate();
		}
	}
	else
		return std::get<int>(value);
}

//РёР·РјРµРЅРµРЅРёРµ Р·РЅР°С‡РµРЅРёСЏ С…СЂР°РЅСЏС‰РµРіРѕСЃСЏ РІ РєР»Р°СЃСЃРµ arithmetic
void Arithmetic::SetStringValue(std::string const new_data_)
{
	data_ = new_data_;
}

//РїРѕР»СѓС‡РµРЅРёРµ Р·РЅР°С‡РµРЅРёСЏ С…СЂР°РЅСЏС‰РµРіРѕСЃСЏ РІ РєР»Р°СЃСЃРµ arithmetic
std::string Arithmetic::GetStringValue()
{
	return data_;
}

//РїСЂРѕРІРµСЂРєР° СЂР°СЃСЃС‚Р°РЅРѕРІРєРё СЃРєРѕР±РѕРє
int Arithmetic::CheckBrackets()
{
	//ocnt - open cnt, ccnt - close cnt
	int ocnt = 0, ccnt = 0;

	for (char i : data_)
	{
		if (i == '(')
			ocnt++;

		if (i == ')')
			ccnt++;
	}

	return ocnt - ccnt;
}

//РґРѕР±Р°РІР»РµРЅРёРµ РЅРѕРІРѕР№ РїР°СЂС‹ РєР»СЋС‡/Р·РЅР°С‡РµРЅРёРµ РІ СЃР»РѕРІР°СЂСЊ
void Arithmetic::UpdateMap(const std::string key, int value)
{
	dict[key] = value;
}

//РїСЂРѕРІРµСЂРєР° РЅР° РЅР°С…РѕР¶РґРµРЅРёРµ РїРµСЂРµРґР°РЅРЅРѕРіРѕ Р°СЂРіСѓРјРµРЅС‚Р° РІ СЃР»РѕРІР°СЂРµ
bool Arithmetic::InMap(const std::string value)
{
	return dict.find(value) != dict.end();
}

//Р—Р°РјРµРЅР° СЃС‚СЂРѕРєРё РІРёРґР° power(a, b) РЅР° Р·РЅР°С‡РµРЅРёРµ РґР°РЅРЅРѕР№ РѕРїРµСЂР°С†РёРё 
bool Arithmetic::RemakePowerToInt()
{
	//РЅР°С…РѕРґРёРј РѕС‡РµСЂРµРґРЅРѕР№ РїРѕРґСЃС‚СЂРѕРєСѓ РІРёРґР° power( РёСЃРїРѕР»СЊР·РѕРІР°РЅРёРµ rfind РѕР±СѓСЃР»РѕРІР»РµРЅРѕ РІРѕР·РјРѕР¶РЅРѕСЃС‚СЊСЋ С‚Р°РєРѕР№ Р·Р°РїРёСЃРё: power(power(, ), )
	size_t PowerStartInd = data_.rfind("power(");

	//РµСЃР»Рё РЅР° РѕС‡РµСЂРµРґРЅРѕРј РІС‹Р·РѕРІРµ С„СѓРЅРєС†РёРё РЅРµ Р±С‹Р»Рѕ РЅР°Р№РґРµРЅРѕ power(, С‚Рѕ РѕСЃСѓС‰РµСЃС‚РІР»СЏРµС‚СЃСЏ РІС‹С…РѕРґ РёР· СЂРµРєСѓСЂСЃРёРё СЃ СЂРµР·СѓР»СЊС‚Р°С‚РѕРј true
	if (PowerStartInd == std::string::npos)
		return 1;

	//РµСЃР»Рё РїРѕРґСЃС‚СЂРѕРєР° РІСЃРµ-С‚Р°РєРё Р±С‹Р»Р° РЅР°Р№РґРµРЅР°, С‚Рѕ РѕСЃСѓС‰РµСЃС‚РІР»СЏРµС‚СЃСЏ Р·Р°РїРёСЃСЊ Р·РЅР°С‡РµРЅРёСЏ РІРёРґР° power(..., ...) РІ РїРµСЂРµРјРµРЅРЅСѓСЋ PowerData
	size_t tmp = PowerStartInd;
	while (data_[++tmp] != ')') {}

	size_t PowerEndInd = ++tmp;
	std::string PowerData(data_.begin() + PowerStartInd, data_.begin() + PowerEndInd);
	std::regex regular("power\\([a-zA-Z0-9_]+\\s*,\\s*[a-zA-Z0-9_]+\\)");

	//РїСЂРѕРІРµСЂРєР° РЅР° РєРѕСЂСЂРµРєС‚РЅРѕСЃС‚СЊ СЂР°РЅРµРµ Р·Р°РїРёСЃР°РЅРЅРѕРіРѕ power(,) РїСЂРё РїРѕРјРѕС‰Рё СЂРµРіСѓР»СЏСЂРЅРѕРіРѕ РІС‹СЂР°Р¶РµРЅРёСЏ
	if (!std::regex_match(PowerData, regular))
		return 0;

	//Р·Р°РїРёСЃСЊ РІРѕР·РІРѕРґРёРјРѕРіРѕ Р·РЅР°С‡РµРЅРёСЏ РІ СЃС‚СЂРѕРєСѓ VariableName 
	std::string VariableName = "";
	tmp = 6;

	while (PowerData[tmp] != ' ' && PowerData[tmp] != ',') 
	{ 
		VariableName += PowerData[tmp]; 
		tmp++; 
	}
	std::cout << VariableName << std::endl;

	IntBoolPair value1 = PowerHelper(VariableName);
	if (!value1.second)
		return 0;

	//Р·Р°РїРёСЃСЊ СЃС‚РµРїРµРЅРё РІ СЃС‚СЂРѕРєСѓ VariableName
	VariableName.clear();
	tmp = PowerData.find(',');

	while (PowerData[++tmp] != ')') 
	{ 
		if (PowerData[tmp] != ' ') 
			VariableName += PowerData[tmp]; 
	}

	IntBoolPair value2 = PowerHelper(VariableName);
	if (!value2.second)
		return 0;

	//РµСЃР»Рё РѕР±Р° С‡РёСЃР»Р° СѓРґР°Р»РѕСЃСЊ СЃС‡РёС‚Р°С‚СЊ, С‚Рѕ Р·РЅР°С‡РµРЅРёРµ РІС‹СЂР°Р¶РµРЅРёСЏ РІС‹СЃС‡РёС‚С‹РІР°РµС‚СЃСЏ РїСЂРё РїРѕРјРѕС‰Рё std::pow Рё Р·Р°РЅРѕСЃРёС‚СЃСЏ РІ РїРµСЂРµРјРµРЅРЅСѓСЋ s
	std::string s = std::to_string(static_cast<int>(std::pow(value1.first, value2.first)));

	//РЅР° РјРµСЃС‚Рѕ power(,) РІСЃС‚Р°РІР»СЏРµС‚СЃСЏ СЂР°РЅРµРµ РїРѕСЃС‡РёС‚Р°РЅРЅРѕРµ Р·РЅР°С‡РµРЅРёРµ
	data_.erase(data_.begin() + PowerStartInd, data_.begin() + PowerEndInd);
	data_.insert(data_.begin() + PowerStartInd, s.begin(), s.end());

	return RemakePowerToInt();

}

//РґР°РЅРЅР°СЏ С„СѓРЅРєС†РёСЏ РїС‹С‚Р°РµС‚СЃСЏ РїРѕР»СѓС‡РёС‚СЊ С‡РёСЃР»Рѕ РёР· РїРµСЂРµРґР°РЅРЅРѕР№ СЃС‚СЂРѕРєРё, РµСЃР»Рё РІСЃРµ РїСЂРѕС…РѕРґРёС‚ СѓСЃРїРµС€РЅРѕ, С‚Рѕ РІРѕР·РІСЂР°С‰Р°РµС‚СЃСЏ true Рё Р·РЅР°С‡РµРЅРёРµ СЃС‡РёС‚Р°РЅРЅРѕРіРѕ С‡РёСЃР»Р°
IntBoolPair Arithmetic::PowerHelper(std::string VariableName)
{
	int VariableValue;

	if (!InMap(VariableName))
	{
		std::istringstream stream(VariableName);
		stream >> VariableValue;
		if (stream.fail() || stream.peek() != EOF)
			return std::make_pair(0, 0);
	}
	else
		VariableValue = dict[VariableName];

	return std::make_pair(VariableValue, 1);


}

//РІРІРѕРґ РґР°РЅРЅС‹С… РІ СЃРїРёСЃРѕРє
bool Arithmetic::ListFormation(std::shared_ptr<Node> nd, const std::string s, std::ostream& out)
{
	out << "Next processed brackest value: " + s + "\r\n";
	size_t ind = 0, f;

	while (ind < s.size() && s[ind] == '(' || s[ind] == ' ') { ind++; }


	if ((s[ind] != '+' && s[ind + 1] == ' ') && s[ind] != '*' && (s[ind] != '-' && s[ind + 1] == ' '))
		return 0;

	auto arg1 = std::make_shared<Node>();
	nd->value = s[ind];

	ind++;
	while (ind < s.size() && s[ind] == ' ') { ind++; }

	if (s[ind] == '(')
	{
		f = ListFormation(arg1, ExtractBracketsValue(s, ind), out);
		if (!f)
			return 0;
	}
	else
	{
		IntBoolPair result = ExtractValueForListFormation(s, ind);
		if (!result.second)
			return 0;

		arg1->value = result.first;
	}

	while (ind < s.size() && s[ind] == ' ') { ind++; }

	if (s[ind] == ')')
	{
		if (std::get<char>(nd->value) == '-')
		{
			nd->arguments = arg1;
			return 1;
		}
		else
			return 0;
	}

	auto arg2 = std::make_shared<Node>();

	if (s[ind] == '(')
	{
		f = ListFormation(arg2, ExtractBracketsValue(s, ind), out);
		if (!f)
			return 0;
	}
	else
	{
		IntBoolPair result = ExtractValueForListFormation(s, ind);
		if (!result.second)
			return 0;

		arg2->value = result.first;
	}
	nd->arguments = std::make_pair(arg1, arg2);

	return 1;
}

//РїРѕР»СѓС‡РµРЅРёРµ С‡РёСЃР»Р° РёР· СЃС‚СЂРѕРєРё РґР»СЏ РїСЂРµРґС‹РґСѓС‰РµРіРѕ РјРµС‚РѕРґР°
IntBoolPair Arithmetic::ExtractValueForListFormation(const std::string& s, size_t& ind)
{
	std::string tmp = "";

	//СЃС‡РёС‚С‹РІР°РЅРёРµ Р·РЅР°С‡РµРЅРёСЏ РІ РїРµСЂРµРјРµРЅРЅСѓСЋ tmp
	while (ind < s.size() && s[ind] != ' ' && s[ind] != ')')
	{
		tmp += s[ind];
		ind++;
	}

	//РїСЂРѕРІРµСЂРєР° РЅР° С‚Рѕ, С‡С‚Рѕ СЃС‡РёС‚Р°РЅРЅРѕРµ Р·РЅР°С‡РµРЅРёРµ - РїРµСЂРµРјРµРЅРЅР°СЏ
	if (InMap(tmp))
		return std::make_pair(dict[tmp], 1);

	//РЎРѕР·РґР°РµРј СЃС‚СЂРѕРєРѕРІС‹Р№ РїРѕС‚РѕРє РѕС‚РєСѓРґР° РїС‹С‚Р°РµРјСЃСЏ СЃС‡РёС‚Р°С‚СЊ int
	std::istringstream stream(tmp);
	int result;
	stream >> result;

	//РµСЃР»Рё РїРѕС‚РѕРє "СѓРїР°Р»" РёР»Рё РЅРµ РґРѕС€РµР» РґРѕ РєРѕРЅС†Р° РІ СЂРµР·СѓР»СЊС‚Р°С‚Рµ СЃС‡РёС‚С‹РІР°РЅРёСЏ int, С‚Рѕ С„СѓРЅРєС†РёСЏ РІРѕР·РІСЂР°С‰Р°РµС‚ false
	if (stream.fail() || stream.peek() != EOF)
		return std::make_pair(0, 0);

	return std::make_pair(result, 1);
}

//РїРѕР»СѓС‡РµРЅРёРµ Р·РЅР°С‡РµРЅРёСЏ С…СЂР°РЅСЏС‰РµРіРѕСЃСЏ РІ РѕС‡РµСЂРµРґРЅС‹С… СЃРєРѕР±РєР°С… РґР»СЏ РїСЂРµРґРїСЂРµРґС‹РґСѓС‰РµРіРѕ РјРµС‚РѕРґР°
std::string Arithmetic::ExtractBracketsValue(const std::string& s, size_t& ind)
{
	//error - РїРµСЂРµРјРµРЅРЅР°СЏ РЅРµРѕР±С…РѕРґРёРјР°СЏ РґР»СЏ РѕР±СЂР°Р±РѕС‚РєРё РґР°РЅРЅРѕРіРѕ СЃР»СѓС‡Р°СЏ (...(...)...) РѕРЅР° РїРѕР·РІРѕР»СЏРµС‚ РїРѕР»СѓС‡РёС‚СЊ Р·РЅР°С‡РµРЅРёРµ Р»РµР¶Р°С‰РµРµ С‚РѕС‡РЅРѕ РѕС‚ СѓР¶Рµ РЅР°Р№РґРµРЅРЅРѕР№ РѕС‚РєСЂС‹РІР°СЋС‰РµР№ РґРѕ РєРѕСЂСЂРµРєС‚РЅРѕР№ Р·Р°РєСЂС‹РІР°СЋС‰РµР№ СЃРєРѕР±РєРё
	int tmp_ind = ind, error = 0;
	std::string tmp_s = "";

	while (1)
	{
		//Р·Р°РїРёСЃСЊ РѕС‡РµСЂРµРґРЅРѕРіРѕ СЃРёРјРІРѕР»Р°
		tmp_s += s[tmp_ind];
		tmp_ind++;

		if (s[tmp_ind] == '(')
			error++;
		if (s[tmp_ind] == ')')
			error--;
		if (error < 0)
			break;
	}

	//Р·Р°РїРёСЃСЊ )
	tmp_s += s[tmp_ind];

	//РїРµСЂРµРЅРѕСЃ РёРЅРґРµРєСЃР° Р·Р° РІС‹СЂР°Р¶РµРЅРёРµ РІ СЃРєРѕР±РєР°С… РґСЏР» СЃС‡РёС‚С‹РІР°РЅРёСЏ РІС‚РѕСЂРѕРіРѕ Р°СЂРіСѓРјРµРЅС‚Р°
	ind = tmp_ind + 1;
	return tmp_s;
}

//РІС‹РІРѕРґ СЃР»РѕРІР°СЂСЏ
void Arithmetic::print_dict(std::ostream& out)
{
	for (auto i : dict)
		out << i.first << " = " << i.second << "\r\n";
}

//СЂР°СЃРїР°РєРѕРІРєР° Р·РЅР°С‡РµРЅРёР№ РїРµСЂРµРјРµРЅРЅС‹С…
bool Arithmetic::ExtractVariableValues(std::string value, std::ostream& out)
{
	//РІС‹С…РѕРґ РёР· СЂРµРєСѓСЂСЃРёРё
	if (value == "()")
		return 1;

	//РїРѕРёСЃРє РїРµСЂРІРѕРіРѕ РїСЂРѕР±РµР»Р°
	size_t ind = value.find(' ');

	//СЃРѕСЃС‚Р°РІР»РµРЅРёРµ РёРјРµРЅРё РїРµСЂРµРјРµРЅРЅРѕР№
	std::string VariableName(value.begin() + 2, value.begin() + ind);

	//РїСЂРѕРІРµСЂРєР° РЅР° РєРѕР»Р»РёР·РёРё
	if (InMap(VariableName))
	{
		out << "Incorrect data! One variable with two values!\r\n";
		return 0;
	}
	ind++;

	//Р·Р°РїРёСЃСЊ Р·РЅР°С‡РµРЅРёСЏ РїРµСЂРµРјРµРЅРЅРѕР№ 
	std::string VariableValue;
	while (value[ind] != ')')
	{
		VariableValue += value[ind];
		ind++;
	}

	//РёСЃРїРѕР»СЊР·РѕРІР°РЅРёРµ С„СѓРЅРєС†РёРё stoi РѕР±СѓСЃР»РѕРІР»РµРЅРѕ РїСЂРѕРІРµСЂРєРѕР№ СЂРµРіСѓР»СЏСЂРЅС‹Рј РІС‹СЂР°Р¶РµРЅРёРµРј
	UpdateMap(VariableName, stoi(VariableValue));

	//СѓРґР°Р»РµРЅРёРµ РїРµСЂРІРѕР№ СЃРєРѕР±РєРё РІРёРґР° (VariableName, VariableValue)
	value.erase(value.begin() + 1, value.begin() + ind + 1);

	//СЂРµРєСѓСЂСЃРёРІРЅС‹Р№ РІС‹Р·РѕРІ РѕС‚ СѓР¶Рµ РёР·РјРµРЅРµРЅРЅРѕР№ СЃС‚СЂРѕРєРё
	return ExtractVariableValues(value, out);
}

std::string InputDialog()
{
	std::string ivar;
	std::cout << "Choose input format:\n\t1)Console\n\n\t2) Read from file (Default file is located along the path:"
		"TestInput.txt)\n\tIf you want to change file location, you have to enter path as second argument\n\t"
		"Don't forget to change all \'\\\' to \'/\'" << std::endl;
	std::getline(std::cin, ivar);
	return ivar;
}

std::string OutputDialog()
{
	std::string ovar;
	std::cout << "Choose output format:\n\t1)Console\n\n\t2)File (Default file is located along the path: TestOutput.txt)\n\t"
		"If you want to change file location, you have to enter path as second argument\n\t"
		"Remember that debagging output will be saved with programm result" << std::endl;
	std::getline(std::cin, ovar);
	return ovar;
}

std::string MakePath(std::string s, std::string const default_path)
{
	//РЎРѕСЃС‚Р°РІР»РµРЅРёРµ РїСѓС‚Рё
	std::string path;

	//Р·Р°РїРёСЃСЊ РїРѕР»СѓС‡РµРЅРЅРѕРіРѕ РїСѓС‚Рё РІ РїРµСЂРµРјРµРЅРЅСѓСЋ path
	for (auto i = ++s.begin(); i != s.end(); i++)
		if (*i != ' ')
			path += *i;

	//РїСЂРѕРІРµСЂРєР° РЅР° С‚Рѕ, С‡С‚Рѕ РїСѓС‚СЊ Р±С‹Р» РІРІРµРґРµРЅ
	if (path.empty())
		path = default_path;
	return path;
}

void CallAndCheck(StringPair data_, std::ostream& out)
{
	Arithmetic ar;

	//РїРµС‡Р°С‚СЊ РІС…РѕРґРЅС‹С… РґР°РЅРЅС‹С…
	out << "\r\nEntered string: " + data_.first + ", Entered variable list: ";
	if (data_.second == "()")
		out << "empty\r\n";
	else
		out << data_.second + "\r\n";

	//Р РµРіСѓР»СЏСЂРЅРѕРµ РІС‹СЂР°Р¶РµРЅРёРµ, СЃРѕР·РґР°РІР°РµРјРѕРµ СЃ С†РµР»СЊСЋ РїСЂРѕРІРµСЂРєРё РєРѕСЂСЂРµРєС‚РЅРѕСЃС‚Рё С„РѕСЂРјР°С‚Р° СЃС‚СЂРѕРєРё, СЃРѕРїРѕСЃС‚Р°РІР»СЏСЋС‰РµР№ РёРјРµРЅР° РїРµСЂРµРјРµРЅРЅС‹С… Рё РёС… Р·РЅР°С‡РµРЅРёСЏ
	std::regex regular("\\((\\([a-zA-Z0-9_]+ [0-9+-]+\\))+\\)");

	ar.SetStringValue(data_.first);

	//РџСЂРѕРІРµСЂРєР° РєРѕСЂСЂРµРєС‚РЅРѕСЃС‚Рё СЂР°СЃСЃС‚Р°РЅРѕРІРєРё СЃРєРѕР±РѕРє
	int CheckResult = ar.CheckBrackets();
	if (CheckResult)
	{
		out << ((CheckResult > 0) ? "Oops, you forgot about close bracket(s)\r\n\r\n" : "Oops you forgot about open bracket(s)\r\n\r\n");
		return;
	}

	//РџСЂРѕРІРµСЂРєР° РЅР° РєРѕСЂСЂРµРєС‚РЅРѕСЃС‚СЊ РїРѕР»СѓС‡РµРЅРЅРѕРіРѕ СЃРїРёСЃРєР° РїРµСЂРµРјРµРЅРЅС‹С…/Р·РЅР°С‡РµРЅРёР№
	if (data_.second != "()" && !std::regex_match(data_.second.c_str(), regular))
	{
		out << "Incorrect variable list!\r\n\r\n";
		return;
	}

	//РЎРѕРїРѕСЃС‚Р°РІР»РµРЅРёРµ РёРјРµРЅР°Рј РїРµСЂРµРјРµРЅРЅС‹С… РёС… Р·РЅР°С‡РµРЅРёР№
	if (!ar.ExtractVariableValues(data_.second, out))
		return;

	//РїРµС‡Р°С‚СЊ СЃР»РѕРІР°СЂСЏ РµСЃР»Рё РѕРЅ РЅРµ РїСѓСЃС‚
	if (data_.second != "()")
	{
		out << "Variable list after unpacking:\r\n";
		ar.print_dict(out);
	}

	//Р—Р°РјРµРЅР° power РЅР° РµРіРѕ Р·РЅР°С‡РµРЅРёРµ, Р° Р·Р°РѕРґРЅРѕ Рё РїСЂРѕРІРµСЂРєР° РЅР° РєРѕСЂСЂРµРєС‚РЅРѕСЃС‚СЊ Р·Р°РїРёСЃРё power
	if (!ar.RemakePowerToInt())
	{
		out << "Incorrect power option!\r\n\r\n";
		return;
	}
	out << "String version after remake power to int: " + ar.GetStringValue() + "\r\n";

	auto nd = std::make_shared<Node>();

	if (!ar.ListFormation(nd, ar.GetStringValue(), out))
	{
		out << "Incorrect expression!\r\n\r\n";
		return;
	}
	out << "Result: " << nd->evaluate() << "\r\n";
	out << "-----------------------------------------------------------------------------------\r\n\r\n";

}

int main(int argc, char** argv)
{
	//data_ - РїР°СЂР° СЃС‚СЂРѕРє: РїРµСЂРІР°СЏ - РІС‹СЂР°Р¶РµРЅРёРµ, РІС‚РѕСЂР°СЏ - СЃРїРёСЃРѕРє СЃ РїРµСЂРµРјРµРЅРЅС‹РјРё Рё РёС… Р·РЅР°С‡РµРЅРёСЏРјРё, iovar - input/outpur variant
	StringPair data_, iovar;

	//Р”Р»СЏ СѓРґРѕР±РЅРѕРіРѕ Р·Р°РїСѓСЃРєР° С‚РµСЃС‚РѕРІ РЅР° РґСЂСѓРіРѕРј РїРє
	if (argc > 1)
	{
		//РЎРѕР·РґР°РЅРёРµ РїРѕС‚РѕРєР° РІРІРѕРґР° Рё С‡С‚РµРЅРёРµ РґР°РЅРЅС‹С… РёР· РЅРµРіРѕ
		std::string tmp_s = "./";
		tmp_s += std::string(argv[1]);
		std::ifstream in(tmp_s);

		if (!in.is_open())
		{
			std::cout << "Bad way!\n";
			return 0;
		}

		if (in.eof())
		{
			std::cout << "File is empty!\n";
			return 0;
		}

		//РЎРѕР·РґР°РЅРёРµ РІРµРєС‚РѕСЂР° РґСЏР» С…СЂР°РЅРµРЅРёСЏ СЃС‚СЂРѕРє РёР· С„Р°Р№Р»Р°
		std::vector<std::string> FileStrings;

		//РЎС‡РёС‚С‹РІР°РЅРёРµ РґР°РЅРЅС‹С… РёР· С„Р°Р№Р»Р°
		while (std::getline(in, tmp_s))
			FileStrings.push_back(tmp_s);

		//РўР°Рє РєР°Рє РґР»СЏ СЂРµС€РµРЅРёСЏ РїРѕРґР·Р°РґР°С‡Рё РЅРµРѕР±С…РѕРґРёРјРѕ РёРјРµС‚СЊ 2 СЃС‚СЂРѕРєРё, С‚Рѕ РєРѕР»-РІРѕ СЃС‚СЂРѕРє РІ С„Р°Р№Р»Рµ РЅРµ РјРѕР¶РµС‚ Р±С‹С‚СЊ РЅРµС‡РµС‚РЅС‹Рј
		if (FileStrings.size() % 2)
		{
			std::cout << "String count cannot be odd\n";
			return 0;
		}

		//of - output format
		int of = 0;
		std::ofstream outf;

		//Р’С‹Р±РѕСЂ СЃРїРѕСЃРѕР±Р° РІС‹РІРѕРґР°
		iovar.second = OutputDialog();
		switch ((iovar.second)[0])
		{
		case '1':
			//std::cout
			of = 0;
			break;

		case '2':
			//ofstream
			outf.open(MakePath(iovar.second, "TestOutput.txt"));
			if (!outf.is_open())
			{
				std::cout << "File doesn't exist!\n";
				return 0;
			}
			of = 1;
			break;

		default:
			std::cout << "Incorrect output format. Goodbye\n";
			return 0;
		}

		//РІС‹Р±РѕСЂ РїРѕС‚РѕРєР° РІС‹РІРѕРґР°
		std::ostream& out = (of) ? outf : std::cout;

		for (size_t i = 0; i < FileStrings.size(); i += 2)
			CallAndCheck(std::make_pair(FileStrings[i], FileStrings[i + 1]), out);

		if (outf.is_open())
			outf.close();

		return 0;
	}
	else
	{
		//РµСЃР»Рё С„Р°Р№Р» РЅРµ Р±С‹Р» РїРµСЂРµРґР°РЅ С‡РµСЂРµР· РєРѕРјР°РЅРґРЅСѓСЋ СЃС‚СЂРѕРєСѓ, С‚Рѕ РЅРµРѕР±С…РѕРґРёРјРѕ РѕРїСЂРµРґРµР»РёС‚СЊ С„РѕСЂРјР°С‚ РІРІРѕРґР°
		iovar.first = InputDialog();
		iovar.second = OutputDialog();
	}

	bool of = 0;
	std::ofstream outf;

	//Р’С‹Р±РѕСЂ С„РѕСЂРјР°С‚Р° РІРІРѕРґР°
	switch ((iovar.second)[0])
	{
	case '1':
		//std::cout
		of = 0;
		break;

	case '2':
		//ofstream
		of = 1;
		outf.open(MakePath(iovar.second, "TestOutput.txt"));
		if (!outf.is_open())
		{
			std::cout << "File doesn't exist!\n";
			return 0;
		}
		break;

	default:
		std::cout << "Incorrect output format. Goodbye\n";
		return 0;
	}

	std::ostream& out = !of ? std::cout : outf;

	//Р’С‹Р±РѕСЂ С„РѕСЂРјР°С‚Р° РІРІРѕРґР°(РµСЃР»Рё Р·Р°РїСѓСЃРє РїСЂРѕРёР·РѕС€РµР» Р±РµР· РґРѕРїРѕР»РЅРёС‚РµР»СЊРЅС‹С… Р°СЂРіСѓРјРµРЅС‚РѕРІ)
	switch ((iovar.first)[0])
	{
	case '1':
		//std::cin
		std::cout << "Enter string and variable values (input format: ((x1 c1)(x2 c2)...) x1, x2, ... - variables, c1, c2,... - their values),\n"
			"If your variable list is empty left this ()\n";
		std::getline(std::cin, data_.first);
		std::getline(std::cin, data_.second);

		CallAndCheck(data_, out);

		break;

	case '2':
	{
	    //std::ifstream
		std::string path = MakePath(iovar.first, "TestInput.txt");
		std::ifstream in(path);
		if (!in.is_open())
		{
			std::cout << "File doesn't exist!\r\n";
			return 0;
		}

		//Р°РЅР°Р»РѕРіРёС‡РЅРѕ argv СЃРѕР·РґР°РµС‚СЃСЏ РІРµРєС‚РѕСЂ С…СЂР°РЅСЏС‰РёР№ РІ СЃРµР±Рµ РІСЃРµ СЃС‚СЂРѕРєРё С„Р°Р№Р»Р°
		std::vector<std::string> FileStrings;
		std::string tmp_s;
		while (std::getline(in, tmp_s)) 
			if (!tmp_s.empty()) 
				FileStrings.push_back(tmp_s);


		if (FileStrings.size() % 2)
		{
			std::cout << "String count cannot be odd\r\n";
			return 0;
		}

		for (size_t i = 0; i < FileStrings.size(); i += 2)
			CallAndCheck(std::make_pair(FileStrings[i], FileStrings[i + 1]), out);

		break;
	}
	default:
		std::cout << "Incorrect input format. Goodbye\n";
		break;
	}

	return 0;
}
