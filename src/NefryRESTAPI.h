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

public:

	void begin();

};
extern nefryrestapi NefryRESTAPI;
#endif
