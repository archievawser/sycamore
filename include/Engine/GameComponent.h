#pragma once


class TGameComponent
{
public:
	virtual void BeginPlay();
	virtual void Tick(double dt);
};