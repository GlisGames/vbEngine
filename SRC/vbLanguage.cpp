#include "vbEngine.h"
#include <locale>
#include <codecvt>
#include <string>

vbString vbLanguage::operator[] (string text)
{
	return this->get(text);
}

vbString vbLanguage::get(string text)
{
	auto ret = this->dictionary.find(text);
	if (ret != this->dictionary.end())
		return (*ret).second;
	else
	{
		return "";
	}
}

vbLanguage::vbLanguage()
{

}

int vbLanguage::loadDictionary(void* gameptr, string jsonPath)
{
	vbGame* GAME = (vbGame*)gameptr;
	WORD jsonlen = 0;
	unsigned char* jsonContent = LoadFileData(jsonPath.c_str(), &jsonlen);
	if (jsonContent == NULL)
		PANIC(FormatText("DICTIONARY CONFIG FILE NOT FOUND: %s", jsonPath.c_str()));
	//json_settings settings = {  }
	json_value* root = json_parse((json_char*)jsonContent, jsonlen);
	if (root == NULL)
		PANIC("DICTIONARY CONFIG FORMAT ERROR");
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	for (WORD i = 0; i < root->u.object.length; i++)
	{
		string name = root->u.object.values[i].name;
		vbString val = root->u.object.values[i].value->u.string.ptr;// converter.from_bytes(root->u.object.values[i].value->u.string.ptr);
		if (name == "lang_name") this->languageName = val;
		else this->dictionary[name] = val;
	}
	json_value_free(root);
	return this->dictionary.size();
}