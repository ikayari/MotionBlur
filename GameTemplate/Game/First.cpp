#include "stdafx.h"
#include "First.h"

#include "Game.h"
#include "Title.h"

First::First()
{

}

First::~First()
{

}

bool First::Start()
{
	NewGO<Game>(0, "game");
	return true;
}

void First::Update()
{
	if (m_isCreate == true)
	{
		NewGO<Title>(0, "title");
		m_isCreate = false;
	}
}