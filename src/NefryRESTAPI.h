/**
Nefry lib

Copyright (c) 2016 wami

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/


#ifndef __NEFRYAPI_H__
#define __NEFRYAPI_H__

#include <Nefry.h>

class nefryrestapi {

private:
	int pinString(String s);
	int stateString(String s);
	void gpioInput(); 
	void gpioOutput();
	void serialCotrol();
	void nefryControl();
	void apiControl();
	String key;
	bool passcheck(String keyset);

public:

	void begin(bool nefry=1,bool input=1,bool output=1,bool serial=1);
	void setPassword(String password);

};
extern nefryrestapi NefryRESTAPI;
#endif
