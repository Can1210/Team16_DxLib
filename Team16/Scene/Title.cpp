#include "Title.h"
#include"../Device/Sound.h"

//�R���X�g���N�^
Title::Title(Input* input)
{
	m_pInput = input;     //���C���Ŏg���Ă�����̂����炤
}

//�f�X�X�g���N�^
Title::~Title()
{
}
//������
void Title::initialize()
{
	isSceneEnd = false;       //�ŏ���false
	CWindow::getInstance().log("���^�C�g���ɐ؂�ւ����\n");
}
//�X�V
void Title::update(float deltaTime)
{
	if (m_pInput->isKeyDown(KEYCORD::Z))
	{
		Sound::getInstance().playSE("click01");
		isSceneEnd = true;    //Z�����ꂽ��V�[���I���i�������j
	}

}
//�`��
void Title::draw(Renderer* renderer, Renderer3D* renderer3D)
{
	renderer->drawText("Font", "TITLE", Vector2(180, 450), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
}
//�I������
void Title::shutdown()
{
}
//�V�[�����I��������ǂ���
bool Title::isEnd()
{
	return isSceneEnd;
}
//���̃V�[��
std::string Title::nextScene()
{
	return "gameplay";
}
