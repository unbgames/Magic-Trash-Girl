/*
 * Musics.h
 *
 *  Created on: 31/05/2018
 *      Author: gabriel
 */

#ifndef IDJ_GAME_FINAL_HEADERS_MUSICS_H_
#define IDJ_GAME_FINAL_HEADERS_MUSICS_H_

#include "Sound.h"
#include <iostream>
#include <vector>

class Musics{
public:
	Musics();
	~Musics();

	void AddMusic(std::string file);
	bool AddMusicV(std::string file);
	void AddMusic(std::string file, int volume);
	void AddMusic(std::string file, int volume, FadeTypes fade);
	void RemoveMusic(std::string file);

	void Pause(std::string file);		// Pausa a musica
	void PauseAll();


	void Play(std::string file);		// Toca a musica
	void Play(std::string file, int times);
	void Play(int index,int times);
	void Play(int index,float timeout);
	void PlayAll();
	void ResumeAll();					// Resume todas as músicas pausadas (não faz sentido fazer um resume individual pois Play cuida disso)

	void Stop(std::string file);
	void StopAll();

	void Reset(std::string file, int volume=128);		// Move pro inicio, e pausa
	void ResetAll(int volume=128);
	void Restart(std::string file, int volume=128);		// Move pro incio e toca
	void RestartAll(int volume=128);

	bool GetPlayStatus(std::string file);
	bool GetPlayStatus(int index);

	Sound* GetMusic(std::string file);

	void SetMusicVolume(int index, int volume);
	void SetMusicVolume(std::string file, int volume);
	void SetMusicVolumeAll(int volume);

	void IncreaseMusicVolume(std::string file, int inc);
	void IncreaseMusicVolumeAll(int inc);

	void DecreaseMusicVolume(std::string file, int dec);
	void DecreaseMusicVolumeAll(int dec);

	void SetFade(std::string file, FadeTypes fade);
	void SetFadeAll(FadeTypes fade);
	void FadeMusicTo(int index,int time,  int volume);
	void FadeMusicTo(std::string file, int time, int volume);
	void FadeMusicToAll(int time, int volume);

	void Update(float dt);

	void ClearMusics();

	void NotOnWater();
	void ApplyWaterDepth(float d);

private:
	std::vector<Sound*> musics;


};



#endif /* IDJ_GAME_FINAL_HEADERS_MUSICS_H_ */
