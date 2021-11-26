#include "vbEngine.h"

styleElement *vbGame::style(vbString element_name)
{
	if (current_style != NULL)
		return this->current_style->checkName(element_name);
	else
		return NULL;
}

void vbGame::changeStyle(vbContainer* c, vbString stylename)
{
	vbStyle* newstyle = this->styles.checkName(stylename);
	if (newstyle != NULL)
		pGAME->current_style = newstyle;

	gObjectList* objList = NULL;
	objList = &c->gObjects;

	for (auto it = objList->begin(); it != objList->end(); it++)
	{
		styleElement* prop = newstyle->checkName((*it)->name);
		if (prop != NULL)
		{
			(*it)->applyStyle(prop);
		}
		if ((*it)->type == TYPE_CONTAINER)
			changeStyle((vbContainer*)(*it), stylename);
	}
}

BYTE vbStylesMap::loadStyle(vbString stylename, vbString filepath)
{
	std::transform(stylename.begin(), stylename.end(), stylename.begin(), ::toupper);
	WORD jsonlen = 0;
	unsigned char* jsonContent = LoadFileData(filepath.c_str(), &jsonlen);
	if (jsonContent == NULL)
		PANIC(FormatText("CONFIG FILE NOT FOUND: %s", filepath.c_str()));

	json_value* root = json_parse((json_char*)jsonContent, jsonlen);
	if (root == NULL)
		PANIC(FormatText("CONFIG FORMAT ERROR: %s", filepath.c_str()));

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
					Vector2* setcoord = NULL;
					Vector2* setsize = NULL;
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
							setcoord = (Vector2*)malloc(sizeof(Vector2));
							ZeroMemory(setcoord, sizeof(Rectangle));
							setcoord->x = elem_coord->u.array.values[0]->u.integer;
							setcoord->y = elem_coord->u.array.values[1]->u.integer;
							element.position = setcoord;
							if (elem_coord->u.array.length >= 4)
							{
								setsize = (Vector2*)malloc(sizeof(Vector2));
								ZeroMemory(setsize, sizeof(Rectangle));
								setsize->x = elem_coord->u.array.values[2]->u.integer;
								setsize->y = elem_coord->u.array.values[3]->u.integer;
								element.size = setsize;
							}
						}
					}

					if (elem_string != NULL)
						element.texture = pGAME->textureMap[elem_string->u.string.ptr];

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

