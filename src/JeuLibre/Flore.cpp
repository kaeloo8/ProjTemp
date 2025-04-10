#include "pch.h"
#include "Flore.h"

Flore::Flore()
{
	
}

Flore::~Flore()
{
}

void Flore::SetFloreLife(int _life)
{
	FloreLife = _life;
}

void Flore::HitFlore()
{
	FloreLife = FloreLife - 1;
    UpdateImagetype();
    if (mFloreType == FloreType::Tree)
    {
        DeadTree();
    }
    else {
		DeadStone();
    }
	return;
}

void Flore::DeadTree()
{
	for (int i = 0; i < 3; i++)
	{
		Drop* D = CreateEntity<Drop>("Wood_Drop");
		D->SetOrigin(0.5f, 0.5f);
		D->SetPosition(GetPosition().x, GetPosition().y);
		D->SetSize(25, 25);
		D->Layout = 5;
		D->SetVelocity(4);
		D->IsDroped();
		lDrop.push_back(D);

	}
    if (FloreLife <= 0)
    {
        Destroy();
    }
}

void Flore::DeadStone()
{

    for (int i = 0; i < 3; i++)
    {
        const char* type = "0";

        switch (mStoneType)
        {
        case StoneType::Stone:
			type = "DropM_0004";
            break;

        case StoneType::Coal:
           type = "DropM_0001";
            break;

        case StoneType::Iron:
            type = "DropM_0000";
            break;

        case StoneType::Gold:
            type = "DropM_0003";
            break;

        case StoneType::Diamond:
            type = "DropM_0002";
            break;
        }
        Drop* D = CreateEntity<Drop>(type);
        D->SetOrigin(0.5f, 0.5f);
        D->SetPosition(GetPosition().x, GetPosition().y);
        D->SetSize(40, 40);
        D->Layout = 5;
        D->SetVelocity(4);
        D->IsDroped();
        lDrop.push_back(D);
    }
    if (FloreLife <= 0)
    {
        Destroy();
    }
}

void Flore::UpdateImagetype()
{
    // Gérer l'image en fonction du type de pierre
    switch (mStoneType)
    {
    case StoneType::Stone:
        if (FloreLife == 3)
            SetImage("Rock_0012");
        else if (FloreLife == 2)
            SetImage("Rock_0013");
        else if (FloreLife == 1)
            SetImage("Rock_0014");
        break;

    case StoneType::Coal:
        if (FloreLife == 3)
            SetImage("Rock_0003");
        else if (FloreLife == 2)
            SetImage("Rock_0004");
        else if (FloreLife == 1)
            SetImage("Rock_0005");
        break;

    case StoneType::Iron:
        if (FloreLife == 3)
            SetImage("Rock_0000");
        else if (FloreLife == 2)
            SetImage("Rock_0001");
        else if (FloreLife == 1)
            SetImage("Rock_0002");
        break;

    case StoneType::Gold:
        if (FloreLife == 3)
            SetImage("Rock_0009");
        else if (FloreLife == 2)
            SetImage("Rock_0010");
        else if (FloreLife == 1)
            SetImage("Rock_0011");
        break;

    case StoneType::Diamond:
        if (FloreLife == 3)
            SetImage("Rock_0006");
        else if (FloreLife == 2)
            SetImage("Rock_0007");
        else if (FloreLife == 1)
            SetImage("Rock_0008");
        break;
    }
}


void Flore::OnUpdate()
{
}

void Flore::OnCollision(Entity* pCollidedWith)
{
}

void Flore::SetImage(const char* path)
{
	mSprite.setTexture(GameManager::Get()->GetAssetManager()->GetTexture(path));
}
