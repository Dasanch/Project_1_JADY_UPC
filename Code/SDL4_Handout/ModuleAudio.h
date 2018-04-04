#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"

class ModuleAudio : public Module {
public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	bool CleanUp();

private:

};


#endif // __ModuleAudio_H__