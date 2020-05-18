#include <iostream>
#include "TestComponent.h"
#include "RGame.h"
#include "Entity.h"

TestComponent::TestComponent(const std::weak_ptr<REntity> _entity, const std::string& _name, const int& _max)
	:RComponent(_entity), name(_name), max(_max)
{
}

void TestComponent::Start()
{
}

void TestComponent::Update()
{
	n++;
	std::cout << n << "." << name << " is ticking!!! " << std::endl;
	if (n >= max)
	{
		std::cout << "Kill " << name << std::endl;
		GetEntity().lock()->Kill();
	}
}
