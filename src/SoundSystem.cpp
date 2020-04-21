#include <SDL.h>

#include "SoundSystem.h"
#include "FileSystemUtils.h"

MusicTrack::MusicTrack(const char* fileName)
{
	/*
	m_music = Mix_LoadMUS(fileName);
	m_isValid = true;
	if(m_music == NULL)
	{
		fprintf(stderr, "Unable to load Ogg Music file: %s\n", Mix_GetError());;
		m_isValid = false;
	}
	*/
	m_isValid = false;
}

MusicTrack::MusicTrack(SDL_RWops *rw)
{
	/*
	m_music = Mix_LoadMUS_RW(rw, 0);
	m_music = NULL;
	m_isValid = true;
	if(m_music == NULL)
	{
		fprintf(stderr, "Unable to load Magic Binary Music file: %s\n", Mix_GetError());
		m_isValid = false;
	}
	*/
	m_isValid = false;
}

SoundTrack::SoundTrack(const char* fileName)
{
	/*
	sound = NULL;

	unsigned char *mem;
	size_t length = 0;
	FILESYSTEM_loadFileToMemory(fileName, &mem, &length);
	SDL_RWops *fileIn = SDL_RWFromMem(mem, length);
	sound = Mix_LoadWAV_RW(fileIn, 1);
	if (length)
	{
		FILESYSTEM_freeMemory(&mem);
	}

	if (sound == NULL)
	{
		fprintf(stderr, "Unable to load WAV file: %s\n", Mix_GetError());
	}
	*/
}

SoundSystem::SoundSystem()
{
	int audio_rate = 44100;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 1024;

	/*
	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0)
	{
		fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
		SDL_assert(0 && "Unable to initialize audio!");
	}
	*/
}

void SoundSystem::playMusic(MusicTrack* music)
{
	/*
	if(!music->m_isValid)
	{
		fprintf(stderr, "Invalid mix specified: %s\n", Mix_GetError());
	}
	
	if(Mix_PlayMusic(music->m_music, 0) == -1)
	{
		fprintf(stderr, "Unable to play Ogg file: %s\n", Mix_GetError());
	}
	*/
}

//Help from http://www.xbdev.net/tuts/subpages/prt9/index.php
IDirectMusicLoader8*          CSound::m_pLoader       = NULL;
IDirectMusicPerformance8*     CSound::m_pPerformance  = NULL;

 void CSound::Create(char* filename)
{
      if( (m_pLoader == NULL) && (m_pPerformance == NULL)) SetupSound();
      LoadSound(filename);
}

 void CSound::LoadSound(char* filename)
{    
    m_pLoader->LoadObjectFromFile( CLSID_DirectMusicSegment, IID_IDirectMusicSegment8,
	filename, (VOID**)&m_pSoundSegment);
}

 void CSound::playsound()
{
	m_pPerformance->PlaySegmentEx( m_pSoundSegment, NULL, NULL, DMUS_SEGF_SECONDARY, 0, NULL, NULL, NULL);
}

 void CSound::SetupSound()

{
    // Initialize DMusic
    IDirectMusicHeap* pNormalHeap;
    DirectMusicCreateDefaultHeap( &pNormalHeap );
    IDirectMusicHeap* pPhysicalHeap;
    DirectMusicCreateDefaultPhysicalHeap( &pPhysicalHeap );
    DirectMusicInitializeEx( pNormalHeap, pPhysicalHeap, &DirectMusicDefaultFactory );
	pNormalHeap->Release();
	pPhysicalHeap->Release();

    // Create loader object
    DirectMusicCreateInstance( CLSID_DirectMusicLoader, NULL, IID_IDirectMusicLoader8, (VOID**)&m_pLoader );

    // Create performance object
    DirectMusicCreateInstance( CLSID_DirectMusicPerformance, NULL, IID_IDirectMusicPerformance8, (VOID**)&m_pPerformance );
	m_pPerformance->InitAudioX( DMUS_INITAUDIO_NOTHREADS, 64, 128, 0 );
}

 void CSound::Release()
{
	m_pSoundSegment->Release();
}