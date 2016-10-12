/**
Nefry lib

Copyright (c) 2016 wami

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#include "NefryRESTAPI.h"


int nefryrestapi::pinString(String s)
{
	s.toLowerCase();
	if (s.equals("d0"))return D0;
	else if (s.equals("d1"))return D1;
	else if (s.equals("d2"))return D2;
	else if (s.equals("d3"))return D3;
	else if (s.equals("d4"))return D4;
	else if (s.equals("d5"))return D5;
	return -1;
}

int nefryrestapi::stateString(String s)
{	
	s.toLowerCase();
	if (s.equals("high"))return 1;
	else if (s.equals("low"))return 0;
	else if (s.equals("0"))return 0;
	else if (s.equals("1"))return 1;
	return 0;
}

void nefryrestapi::begin() {
	//digitalRead
	Nefry.getWebServer()->on("/api/beta/digitalRead", [&]() {
		String ps = Nefry.getWebServer()->arg("pin");
		pinMode(pinString(ps), INPUT);
		String content = F("{\"mode\":\"digitalRead\",\"pin\":\"");
		content += ps;
		content += F("\",\"value\":");
		content += digitalRead(pinString(ps));
		content += F("}");
		Nefry.getWebServer()->send(200, "application/json", content);
	});
	//digitalWeite
	Nefry.getWebServer()->on("/api/beta/digitalWrite", [&]() {
		String ps = Nefry.getWebServer()->arg("pin");
		String st = Nefry.getWebServer()->arg("state");
		pinMode(pinString(ps), OUTPUT);
		String content = F("{\"mode\":\"digitalWrite\",\"pin\":\"");
		content += ps;
		content += F("\",\"value\":");
		content += stateString(st);
		digitalWrite(pinString(ps), stateString(st));
		content += F("}");
		Nefry.getWebServer()->send(200, "application/json", content);
	});
	//analogRead
	Nefry.getWebServer()->on("/api/beta/analogRead", [&]() {
		String content = F("{\"mode\":\"analogRead\",\"value\":");
		content += analogRead(A0);
		content += F("}");
		Nefry.getWebServer()->send(200, "application/json", content);
	});
	//analogWrite
	Nefry.getWebServer()->on("/api/beta/digitalWrite", [&]() {
		String ps = Nefry.getWebServer()->arg("pin");
		String st = Nefry.getWebServer()->arg("state");
		String content = F("{\"mode\":\"digitalWrite\",\"pin\":\"");
		content += ps;
		content += F("\",\"value\":");
		content += st.toInt();
		analogWrite(pinString(ps), st.toInt());
		content += F("}");
		Nefry.getWebServer()->send(200, "application/json", content);
	});
}
nefryrestapi NefryRESTAPI;
