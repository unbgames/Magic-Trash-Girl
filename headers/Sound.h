#ifndef SOUND_CLASS
#define SOUND_CLASS
#include "SDL2/SDL_mixer.h"
#include <iostream>
#include "globals.h"


class Sound{
	public:
		Sound();
		Sound(std::string file);
		Sound(std::string file, int volume);
		Sound(std::string file, unsigned int channel);
		Sound(std::string file, int volume, FadeTypes fade);
		~Sound();

		void Play (int times=1);
		void Play (float timeout);
		void Pause();
		void Stop();
		void Open(std::string file);
		bool IsOpen();
		bool Is(std::string file);
		bool IsPlaying();

		void Reset(int volume);
		void Restart(int volume);

		void Update(float dt);


		void FadeTo(int time, int volume);
		void SetFade(FadeTypes fade);
		void DistanceFade(float dist); 							// Segue fadeType
		void DistanceFade(float dist, float maxDist, bool up); 	// Segue fadeType

		void IncreaseVolume(int inc);
		void DecreaseVolume(int dec);
		void SetVolume(float volume);
		void SetVolumeVariable (float volume);

		float GetVolume();
		int GetChannel();
	private:
		FadeTypes fade;
		float time, currTime;	// tempo de FadeIn/FadeOut

		double a, b, c;			// constantes para fade

		float volume;			// Volume atual
		Mix_Chunk* chunk;
		int channel;
		std::string file;
};


#endif
