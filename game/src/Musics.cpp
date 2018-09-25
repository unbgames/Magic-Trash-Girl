/*
 * Musics.cpp
 *
 *  Created on: 31/05/2018
 *      Author: gabriel
 */

#include "Musics.h"
#include "Sound.h"
#include "globals.h"
#include "game.h"


Musics::Musics(){

}

Musics::~Musics(){
	ClearMusics();
	musics.clear();
}

void Musics::AddMusic(std::string file){
	AddMusic(file, musics.size());
}

bool Musics::AddMusicV(std::string file){
	int i = musics.size();
	AddMusic(file, i);
	return (i==musics.size());
}

void Musics::AddMusic(std::string file, int channel){
	Sound * newMusic = new Sound (file, (unsigned int) channel);
	musics.emplace_back(newMusic);
}

void Musics::AddMusic(std::string file, int channel, FadeTypes fade){
	Sound * newMusic = new Sound (file, (unsigned int) channel, fade);
	musics.emplace_back(newMusic);
}

void Musics::RemoveMusic(std::string file){
	int size = musics.size();
	for (int i=0; i<size; i++){
		if (musics[i]->Is(file)){
			musics[i]->Stop();
			musics[i]->~Sound();
			musics.erase(musics.begin() + i);
			i=size;
		}
	}
}

void Musics::Pause(std::string file){
	int size = musics.size();
	for (int i=0; i<size; i++){
		if (musics[i]->Is(file)){
			musics[i]->Pause();
		}
	}
}

void Musics::PauseAll(){
	Mix_Pause(-1);				// :^) (em nota, conferir se isso vai dar ruim com os sons do jogo (inimigo e etc). Se sim, fazer com loop
}

void Musics::Play(std::string file){
	int size = musics.size();
	for (int i=0; i<size; i++){
		if (musics[i]->Is(file)){
			musics[i]->Play(0);
		}
	}
}

void Musics::Play(std::string file, int times){
	int size = musics.size();
	for (int i=0; i<size; i++){
		if (musics[i]->Is(file)){
			musics[i]->Play(times);
		}
	}
}

void Musics::Play(int index,int times){
	musics[index]->Play(times);
}

void Musics::Play(int index,float timeout){
	musics[index]->Play(timeout);
}

void Musics::PlayAll(){
	int size = musics.size();
	for (int i=0; i<size; i++){
			musics[i]->Play(0);
	}
}

void Musics::ResumeAll(){
	Mix_Resume(-1);				// :^)
}

void Musics::Stop(std::string file){
	int size = musics.size();
	for (int i=0; i<size; i++){
		if (musics[i]->Is(file)){
			musics[i]->Stop();
		}
	}
}

void Musics::StopAll(){
	Mix_HaltChannel(-1);		// :^)
}

void Musics::Reset(std::string file, int volume){
	int size = musics.size();
	for (int i=0; i<size; i++){
		if (musics[i]->Is(file)){
			musics[i]->Reset(volume);
		}
	}
}

void Musics::ResetAll(int volume){
	int size = musics.size();
	for (int i=0; i<size; i++){
		musics[i]->Reset(volume);
	}
}

void Musics::Restart(std::string file, int volume){
	int size = musics.size();
	for (int i=0; i<size; i++){
		if (musics[i]->Is(file)){
			musics[i]->Restart(volume);
		}
	}
}

void Musics::RestartAll(int volume){
	int size = musics.size();
	for (int i=0; i<size; i++){
		musics[i]->Restart(volume);
	}
}

Sound * Musics::GetMusic(std::string file){
	int size = musics.size();
	for (int i=0; i<size; i++){
		if (musics[i]->Is(file)){
			return musics[i];
		}
	}
	return nullptr;
}

void Musics::SetMusicVolume(int index, int volume){
	musics[index]->SetVolume(volume);
}

void Musics::SetMusicVolume(std::string file, int volume){
	int size = musics.size();
	for (int i=0; i<size; i++){
		if (musics[i]->Is(file)){
			musics[i]->SetVolume(volume);
		}
	}
}

void Musics::SetMusicVolumeAll(int volume){
	Mix_Volume(-1 , volume);		// :^)
	int size = musics.size();
	for (int i=0; i<size; i++){
		musics[i]->SetVolumeVariable(volume);
	}
}

void Musics::IncreaseMusicVolume(std::string file, int inc){
	int size = musics.size();
	for (int i=0; i<size; i++){
		if (musics[i]->Is(file)){
			musics[i]->IncreaseVolume(inc);
		}
	}
}

void Musics::IncreaseMusicVolumeAll(int inc){
	int size = musics.size();
	for (int i=0; i<size; i++){
		musics[i]->IncreaseVolume(inc);
	}
}

void Musics::DecreaseMusicVolume(std::string file, int dec){
	int size = musics.size();
	for (int i=0; i<size; i++){
		if (musics[i]->Is(file)){
			musics[i]->DecreaseVolume(dec);
		}
	}
}

void Musics::DecreaseMusicVolumeAll(int dec){
	int size = musics.size();
	for (int i=0; i<size; i++){
		musics[i]->IncreaseVolume(dec);
	}
}

void Musics::SetFade(std::string file, FadeTypes fade){
	int size = musics.size();
		for (int i=0; i<size; i++){
			if (musics[i]->Is(file)){
				musics[i]->SetFade(fade);
		}
	}
}

void Musics::SetFadeAll(FadeTypes fade){
	int size = musics.size();
		for (int i=0; i<size; i++){
			musics[i]->SetFade(fade);
		}
	}

void Musics::FadeMusicTo(int index,int time,  int volume){
	musics[index]->FadeTo(time, volume);
}


void Musics::FadeMusicTo(std::string file,int time,  int volume){
	int size = musics.size();
	for (int i=0; i<size; i++){
		if (musics[i]->Is(file)){
			musics[i]->FadeTo(time, volume);
		}
	}
}

void Musics::FadeMusicToAll(int time,  int volume){
	int size = musics.size();
	for (int i=0; i<size; i++){
		musics[i]->FadeTo(time, volume);
	}
}
void Musics::Update(float dt){
	int size = musics.size();
	for (int i=0; i<size; i++){
		musics[i]->Update(dt);
	}
}

void Musics::ClearMusics(){
	int size = musics.size();
	for (int i=0; i<size; i++){
		musics[i]->~Sound();
	}
}

bool Musics::GetPlayStatus(int index){
	return musics[index]->IsPlaying();
}

// Mudar caso se mudem as musicas. Padrão - 0 é sem agua, 1 é com
void Musics::NotOnWater(){
	if (musics.size()<1) return;
	musics[0]->SetVolume(music_constants::MAXVOLUME);
}

void Musics::ApplyWaterDepth(float d){
	if (musics.size()<2) return;
	if (d>music_constants::MAXDEPTH) d = music_constants::MAXDEPTH;
	//musics[1]->SetVolume(music_constants::MAXVOLUME);
	//musics[0]->DistanceFade(d, music_constants::MAXDEPTH, false);
	musics[0]->DistanceFade(d, music_constants::MAXDEPTH, false);
	musics[1]->DistanceFade(d, music_constants::MAXDEPTH, true);
}

