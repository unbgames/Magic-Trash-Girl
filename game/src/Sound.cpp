#include "Sound.h"
#include "SDL2/SDL_mixer.h"
#include <cmath>
#include "Fader.h"

Sound::Sound(){
	chunk=nullptr;
	channel=-1;
	file=nullptr;
	volume=128;
	time=0;
	a=0;
	b=0;
	c=0;
	currTime=0;
	fade = music_constants::STDFADE;
}

Sound::Sound(std::string file){
	chunk=nullptr;
	channel=-1;
	Open(file);
	this->file = file;
	volume=128;
	this->SetVolume(volume);
	time=0;
	a=0;
	b=0;
	c=0;
	currTime=0;
	fade = music_constants::STDFADE;
}

Sound::Sound(std::string file, unsigned int channel){
	chunk=nullptr;
	this->channel = channel;
	Open(file);
	this->file = file;
	volume=128;
	this->SetVolume(volume);
	time=0;
	a=0;
	b=0;
	c=0;
	currTime=0;
	fade = music_constants::STDFADE;
}

Sound::Sound(std::string file, int volume): Sound(file){
	this->volume=volume;
	Mix_VolumeChunk(chunk, volume);
}
Sound::Sound(std::string file, int volume, FadeTypes fade) : Sound(file, volume){
	this->fade = fade;
	// Como inverse square vai ser usado para inimigos, primariamente, já faz a inicialização com os valores relevantes. Se não for, vai trocar no FadeTo mesmo...
	if (fade == FadeTypes::INVERSESQUARE) Fader::CalculateParam(fade, a, b, c, music_constants::MAXVOLUME, music_constants::MINVOLUME, enemy_constants::SOUNDMAXDIST);
}

void Sound::Play(int times){
	if (Mix_Paused(channel))
		Mix_Resume(channel);
	else
		channel = Mix_PlayChannel (channel, chunk, times-1);
}

void Sound::Play(float timeout){
	channel = Mix_PlayChannelTimed (channel, chunk,1,(int) timeout);

}

void Sound::Stop(){
	Mix_HaltChannel (channel);
}

void Sound::Open(std::string file){
	chunk =  Mix_LoadWAV(file.c_str());
}

void Sound::Update(float dt){
	currTime+=dt;
	if (time>currTime){
		volume = Fader::Eval(fade, a, b, c, currTime);
		SetVolume(volume);
	}
	else{
		currTime=0;
		time=0;
	}

}

void Sound::FadeTo(int time, int volume){
//	printf ("Volume: %f\n", this->volume);
	Fader::CalculateParam(fade, a, b, c, this->volume, volume, time);
	this->time = time;
	currTime=0;
//	printf ("fade: %d, a: %f, b: %f, c: %f\n", fade, a, b,c);
//	printf ("Parabola em 0: %f, parabola em %d: %f\n", c, time, a*time*time + b*time * c);
}

void Sound::DistanceFade(float dist){
	if (dist> enemy_constants::SOUNDMAXDIST) dist = enemy_constants::SOUNDMAXDIST;
	volume = Fader::Eval(fade, a, b, c, dist);
	SetVolume(volume);

}

void Sound::DistanceFade(float dist, float maxDist, bool up){
	if (dist> maxDist) dist = maxDist;
	if (up) Fader::CalculateParam(fade, a, b, c, music_constants::MINVOLUME, music_constants::MAXVOLUME, maxDist);
	else Fader::CalculateParam(fade, a, b, c, music_constants::MAXVOLUME, music_constants::MINVOLUME, maxDist);
	volume = Fader::Eval(fade, a, b, c, dist);
	SetVolume(volume);

}

void Sound::SetFade(FadeTypes fade){
	this->fade = fade;
}

void Sound::IncreaseVolume(int inc){
	volume+=inc;
	SetVolume(volume);
}
void Sound::DecreaseVolume(int dec){
	volume-=dec;
	SetVolume(volume);
}

void Sound::SetVolume(float volume){
	if (volume>128) this->volume=128;
	else if (volume<0){
		this->volume=0;
		volume=0;
	}
	else this->volume=volume;
	Mix_VolumeChunk(chunk, volume);
	//Mix_Volume(channel, volume);
}

void Sound::SetVolumeVariable (float volume){
	this->volume = volume;
}


bool Sound::Is(std::string file){
	return this->file==file;
}

void Sound::Pause(){
	Mix_Pause(channel);
}

void Sound::Reset(int volume){
	Stop();
	Play(0);
	SetVolume(volume);
	Pause();
}

void Sound::Restart(int volume){
	Stop();
	Play(0);
	SetVolume(volume);
}

float Sound::GetVolume(){
	return volume;
}

int Sound::GetChannel(){
	return channel;
}


Sound::~Sound(){
	if (chunk!=nullptr) Mix_HaltChannel (channel);
	chunk=nullptr;
}

bool Sound::IsPlaying(){
	return Mix_Playing(channel);
}
