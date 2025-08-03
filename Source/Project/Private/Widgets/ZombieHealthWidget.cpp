// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ZombieHealthWidget.h"

UProgressBar* UZombieHealthWidget::GetProgressBar() const
{
	return HealthBar;
}