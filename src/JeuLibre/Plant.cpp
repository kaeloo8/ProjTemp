#include "pch.h"
#include "Plant.h"

Plant::Plant()
{
    PlantType = "carrot";
    std::string cSeed = std::string(PlantType) + "_01";
    std::string cLittlePlant = std::string(PlantType) + "_02";
    std::string cTallPlant = std::string(PlantType) + "_03";
    std::string cFinalPlant = std::string(PlantType) + "_04";
}

Plant::~Plant()
{
}

void Plant::OnUpdate()
{
}

void Plant::OnCollision(Entity* pCollidedWith)
{
}

void Plant::SetImage(const char* path)
{
}
