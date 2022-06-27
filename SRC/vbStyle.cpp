#include "vbEngine.h"

// Load an image from RAW file data
Image LoadImageRawFromBuffer(unsigned char* fileData, unsigned int dataSize, int width, int height, int format, int headerSize)
{
	Image image = { 0 };

	if (fileData != NULL && dataSize > 0)
	{
		unsigned char* dataPtr = fileData;
		unsigned int size = GetPixelDataSize(width, height, format);

		if (headerSize > 0) dataPtr += headerSize;

		image.data = RL_MALLOC(size);      // Allocate required memory in bytes
		memcpy(image.data, dataPtr, size); // Copy required data to image
		image.width = width;
		image.height = height;
		image.mipmaps = 1;
		image.format = format;
	}

	return image;
}

// vbStyle
styleElement vbStyle::operator[](vbString str)
{
	styleElement* ret = checkName(str);
	if (ret == NULL)
	{
		string msg = "STYLE name '" + str + "' NOT FOUND";
		PANIC(msg.c_str());
	}
	return *ret;
}
styleElement* vbStyle::checkName(vbString str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	vbStyle::iterator it = this->find(str);
	if (it != this->end())
		return &this->at(str);
	else
		return NULL;
}

// vbStyleMap
vbStyle vbStyleMap::operator[](vbString str)
{
	vbStyle* ret = checkName(str);
	if (ret == NULL)
	{
		string msg = "STYLE name '" + str + "' NOT FOUND";
		PANIC(msg.c_str());
	}
	return *ret;
}
vbStyle* vbStyleMap::checkName(vbString str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	vbStyleMap::iterator it = this->find(str);
	if (it != this->end())
		return &this->at(str);
	else
		return NULL;
}
BYTE vbStyleMap::loadStyle(vbString stylename, vbString filepath)
{
	std::transform(stylename.begin(), stylename.end(), stylename.begin(), ::toupper);
	WORD jsonlen = 0;
	unsigned char* jsonContent = LoadFileData(filepath.c_str(), &jsonlen);
	if (jsonContent == NULL)
		PANIC(TextFormat("CONFIG FILE NOT FOUND: %s", filepath.c_str()));
	json_value* root = json_parse((json_char*)jsonContent, jsonlen);
	if (root == NULL)
		PANIC(TextFormat("CONFIG FORMAT ERROR: %s", filepath.c_str()));
	if (strcmp(root->u.object.values[0].name, "style") == 0)
	{
		vbStyle newstyle;
		const json_value* slist = &(*root)["style"];
		if (slist->type != json_object)
			PANIC("Error parsing config file");
		else
		{
			for (unsigned int i = 0; i < slist->u.object.length; i++)
			{
				vbString nam = slist->u.object.values[i].name;
				std::transform(nam.begin(), nam.end(), nam.begin(), ::toupper);
				if (slist->u.object.values[i].value->type == json_array && nam != "")
				{
					if (slist->u.object.values[i].value->u.array.length == 0) //empty array
						continue;	//move on

					styleElement element = {0};
					const json_value* first = slist->u.object.values[i].value->u.array.values[0];
					const json_value* second = (slist->u.object.values[i].value->u.array.length == 2) ? second = slist->u.object.values[i].value->u.array.values[1] : NULL;

					const json_value* elem_coord = (first->type == json_array) ? first : NULL;
					const json_value* elem_string = (first->type == json_string) ? first : NULL;

					if (second != NULL)
					{	if (second->type == json_array && elem_coord == NULL) elem_coord = second;
						if (second->type == json_string && elem_string == NULL) elem_string = second;
					}

					if (elem_coord != NULL) //we have coordinates
					{
						if (elem_coord->u.array.length >= 2)
						{
							Vector2* setcoord = NULL;
							setcoord = (Vector2*)malloc(sizeof(Vector2));
							ZeroMemory(setcoord, sizeof(Vector2));
							setcoord->x = elem_coord->u.array.values[0]->u.integer;
							setcoord->y = elem_coord->u.array.values[1]->u.integer;
							element.position = setcoord;
							if (elem_coord->u.array.length >= 4)
							{
								Vector2* setsize = NULL;
								setsize = (Vector2*)malloc(sizeof(Vector2));
								ZeroMemory(setsize, sizeof(Vector2));
								setsize->x = elem_coord->u.array.values[2]->u.integer;
								setsize->y = elem_coord->u.array.values[3]->u.integer;
								element.size = setsize;
							}
						}
					}

					if (elem_string != NULL)
					{
						element.texture = pGAME->textureMap.getTexturePtr(elem_string->u.string.ptr, TRUE);
						if (element.texture == NULL)
							element.fontName = elem_string->u.string.ptr;
					}

					newstyle.insert(make_pair(nam, element));
				}
			}
			this->insert(make_pair(stylename, newstyle));
		}
	}

	json_value_free(root);
	UnloadFileData(jsonContent);
	return 0;
}


