#pragma once

#include "Includes.h"
#include "Account/AccountScreen.h"


void makeBorder(HANDLE&);

void makeAccountWindow(HANDLE&);

void makeDisplayWindow(HANDLE&);

void makeAskDisplay(HANDLE&, COORD&);

void infoWindow(HANDLE&, COORD&);

void bootWindow(HANDLE&);

void clearDisplayWindow(HANDLE& h);

void clearAskDisplay(HANDLE&, COORD&);

void clearLine(HANDLE&, COORD&);

void exitBank(HANDLE&, COORD&);