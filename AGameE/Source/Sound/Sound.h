#pragma once
#ifndef SOUND_H_
#define SOUND_H_

#include"DirectSound.h"
#pragma comment(lib, "dsound.lib")
#include"..\Common\Utility.h"

std::unique_ptr<CSoundManager> pDSound;

bool DirectSound_Init(HWND hwnd);
void DIrectSound_Shutdown();

std::shared_ptr<CSound> LoadSound(std::string filename);
void EPlaySound(std::shared_ptr<CSound> sound);
void ELoopSound(std::shared_ptr<CSound> sound);
void EStopSound(std::shared_ptr<CSound> sound);

#endif // !SOUND_H_