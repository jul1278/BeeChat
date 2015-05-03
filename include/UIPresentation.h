// UIPresentation.h
#ifndef _UI_PRESENTATION_H
#define _UI_PRESNETATION_H

// UIPresentation
class UIPresentation
{
private:

public:
	
	UIPresentation();
	~UIPresentation(); 

	void PresentMessage( std::string chatMessage );
	void PresentMessage( Message* chatMessage ); 
};

#endif

