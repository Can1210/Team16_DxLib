#include "Title.h"

//�R���X�g���N�^
Title::Title()
{
}

//�f�X�X�g���N�^
Title::~Title()
{
	delete m_pInput;
}
//������
void Title::initialize()
{
	m_pInput = new Input;
	m_pInput->init();         //input������
	isSceneEnd = false;       //�ŏ���false
	//CWindow::getInstance().log("���^�C�g���ɐ؂�ւ����");
}
//�X�V
void Title::update(float deltaTime)
{
	m_pInput->update();         //input�X�V
	if (m_pInput->isKeyDown(KEYCORD::Z))
	{
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
