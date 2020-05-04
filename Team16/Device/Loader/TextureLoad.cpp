#include "TextureLoad.h"
#include "../../Support/CWindow.h"

//�R���X�g���N�^
TextureLoad::TextureLoad()
{
}

//�f�X�X�g���N�^
TextureLoad::~TextureLoad()
{
	storageTexturesMap.clear();  //�I�����ɋ�ɂ���
	callTextureMap.clear();		 //�I�����ɋ�ɂ���
}
//�e�N�X�`���̒ǉ�
void TextureLoad::add(std::string callName, const TCHAR* textureName)
{
	if (!(storageTexturesMap.size() == 0))
	{
		auto result = storageTexturesMap.find(textureName);
		if (result != storageTexturesMap.end()) return;
	}
	////�ǉ�
	storageTexturesMap.emplace(textureName, callName);      //��������ǉ�
	int gra = LoadGraph(textureName);                       //�e�N�X�`�������[�h����
	callTextureMap.emplace(callName, gra);                  //������ԍ��ƌĂяo������ǉ�
}
//�e�N�X�`�����Ă�
int TextureLoad::set(std::string callName)
{
	return callTextureMap.at(callName);
}
