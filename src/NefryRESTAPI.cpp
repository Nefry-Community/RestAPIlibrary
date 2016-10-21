/**
Nefry lib

Copyright (c) 2016 wami

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#include "NefryRESTAPI.h"

#define VERSION "beta"

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

void nefryrestapi::gpioInput()
{
	//GPIO‚Ì“ü—Í‚ð‚Ü‚Æ‚ß‚½ŠÖ”

	//digitalRead
	Nefry.getWebServer()->on(("/api/"+VERSION+"/digitalRead").c_str(), [&]() {
		if (!passcheck(Nefry.getWebServer()->arg("pass"))) {
			Nefry.getWebServer()->send(403, "text/html", "password err");
		}
		else {
			String ps = Nefry.getWebServer()->arg("pin");
			pinMode(pinString(ps), INPUT);
			String content = F("{\"mode\":\"digitalRead\",\"pin\":\"");
			content += ps;
			content += F("\",\"value\":");
			content += digitalRead(pinString(ps));
			content += F("}");
			Nefry.getWebServer()->send(200, "application/json", content);
		}
	});

	//digitalReadpullup
	Nefry.getWebServer()->on(("/api/" + VERSION + "/digitalReadpullup").c_str(), [&]() {
		if (!passcheck(Nefry.getWebServer()->arg("pass"))) {
			Nefry.getWebServer()->send(403, "text/html", "password err");
		}
		else {
			String ps = Nefry.getWebServer()->arg("pin");
			pinMode(pinString(ps), INPUT_PULLUP);
			String content = F("{\"mode\":\"digitalRead\",\"pin\":\"");
			content += ps;
			content += F("\",\"value\":");
			content += digitalRead(pinString(ps));
			content += F("}");
			Nefry.getWebServer()->send(200, "application/json", content);
		}
	});

	//analogRead
	Nefry.getWebServer()->on(("/api/" + VERSION + "/analogRead").c_str(), [&]() {
		if (!passcheck(Nefry.getWebServer()->arg("pass"))) {
			Nefry.getWebServer()->send(403, "text/html", "password err");
		}
		else {
			String content = F("{\"mode\":\"analogRead\",\"value\":");
			content += analogRead(A0);
			content += F("}");
			Nefry.getWebServer()->send(200, "application/json", content);
		}
	});
}

void nefryrestapi::gpioOutput()
{
	//GPIO‚Ìo—Í‚ð‚Ü‚Æ‚ß‚½ŠÖ”

	//digitalWeite
	Nefry.getWebServer()->on(("/api/" + VERSION + "/digitalWrite").c_str(), [&]() {
		if (!passcheck(Nefry.getWebServer()->arg("pass"))) {
			Nefry.getWebServer()->send(403, "text/html", "password err");
		}
		else {
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
		}
	});

	//analogWrite
	Nefry.getWebServer()->on(("/api/" + VERSION + "/analogWrite").c_str(), [&]() {
		if (!passcheck(Nefry.getWebServer()->arg("pass"))) {
			Nefry.getWebServer()->send(403, "text/html", "password err");
		}
		else {
			String ps = Nefry.getWebServer()->arg("pin");
			String st = Nefry.getWebServer()->arg("state");
			int sti = st.toInt();
			if (sti < 0)sti = 0;
			if (sti > 1023)sti = 1023;
			String content = F("{\"mode\":\"analogWrite\",\"pin\":\"");
			content += ps;
			content += F("\",\"value\":");
			content += st.toInt();
			analogWrite(pinString(ps), st.toInt());
			content += F("}");
			Nefry.getWebServer()->send(200, "application/json", content);
		}
	});
}

void nefryrestapi::serialCotrol()
{
	//Serialbegin
	Nefry.getWebServer()->on(("/api/" + VERSION + "/Serialbegin").c_str(), [&]() {
		if (!passcheck(Nefry.getWebServer()->arg("pass"))) {
			Nefry.getWebServer()->send(403, "text/html", "password err");
		}
		else {
			String ba = Nefry.getWebServer()->arg("band");
			String content = F("{\"mode\":\"Serialbegin\",\"band\":");
			content += ba.toInt();
			content += F("}");
			Serial.begin(ba.toInt());
			Nefry.getWebServer()->send(200, "application/json", content);
		}
	});

	//Serialprint
	Nefry.getWebServer()->on(("/api/" + VERSION + "/Serialprint").c_str(), [&]() {
		if (!passcheck(Nefry.getWebServer()->arg("pass"))) {
			Nefry.getWebServer()->send(403, "text/html", "password err");
		}
		else {
			String ba = Nefry.getWebServer()->arg("message");
			String content = F("{\"mode\":\"Serialprint\",\"message\":\"");
			content += ba;
			content += F("\"}");
			Serial.print(ba);
			Nefry.getWebServer()->send(200, "application/json", content);
		}
	});

	//Serialprintln
	Nefry.getWebServer()->on(("/api/" + VERSION + "/Serialprintln").c_str(), [&](){
		if (!passcheck(Nefry.getWebServer()->arg("pass"))) {
			Nefry.getWebServer()->send(403, "text/html", "password err");
		}
		else {
			String ba = Nefry.getWebServer()->arg("message");
			String content = F("{\"mode\":\"Serialprintln\",\"message\":\"");
			content += ba;
			content += F("\"}");
			Serial.println(ba);
			Nefry.getWebServer()->send(200, "application/json", content);
		}
	});



	//Serialread
	Nefry.getWebServer()->on(("/api/" + VERSION + "/Serialread").c_str(), [&]() {
		if (!passcheck(Nefry.getWebServer()->arg("pass"))) {
			Nefry.getWebServer()->send(403, "text/html", "password err");
		}
		else {
			char read_char[128], i = 0, w = 0;
			while (Serial.available() <= 0 || w++ != 10) {
				while (Serial.available() > 0) {
					read_char[i++] = Serial.read();
					if (i > 127 || read_char[i] == '\n' || read_char[i] == '\r') {
						read_char[i - 1] = '\0';
						break;
					}
				}
				if (i != 0)break;
				delay(100);
			}
			String content = F("{\"mode\":\"Serialread\",\"message\":\"");
			content += read_char;
			content += F("\"}");
			Nefry.getWebServer()->send(200, "application/json", content);
		}
	});
}

void nefryrestapi::nefryControl()
{
	//Nefryprint
	Nefry.getWebServer()->on(("/api/" + VERSION + "/Nefryprint").c_str(), [&]() {
		if (!passcheck(Nefry.getWebServer()->arg("pass"))) {
			Nefry.getWebServer()->send(403, "text/html", "password err");
		}
		else {
			String ba = Nefry.getWebServer()->arg("message");
			String content = F("{\"mode\":\"Nefryprint\",\"message\":\"");
			content += ba;
			content += F("\"}");
			Nefry.print(ba);
			Nefry.getWebServer()->send(200, "application/json", content);
		}
	});

	//Nefryprintln
	Nefry.getWebServer()->on(("/api/" + VERSION + "/Nefryprintln").c_str(), [&]() {
		if (!passcheck(Nefry.getWebServer()->arg("pass"))) {
			Nefry.getWebServer()->send(403, "text/html", "password err");
		}
		else {
			String ba = Nefry.getWebServer()->arg("message");
			String content = F("{\"mode\":\"Nefryprintln\",\"message\":\"");
			content += ba;
			content += F("\"}");
			Nefry.println(ba);
			Nefry.getWebServer()->send(200, "application/json", content);
		}
	});

	//Nefryread
	Nefry.getWebServer()->on(("/api/" + VERSION + "/Nefryread").c_str(), [&]() {
		if (!passcheck(Nefry.getWebServer()->arg("pass"))) {
			Nefry.getWebServer()->send(403, "text/html", "password err");
		}
		else {
			String content = F("{\"mode\":\"Nefryread\",\"message\":\"");
			content += Nefry.read();
			content += F("\"}");
			Nefry.getWebServer()->send(200, "application/json", content);
		}
	});

	//NefrysetLed
	Nefry.getWebServer()->on(("/api/" + VERSION + "/NefrysetLed").c_str(), [&]() {
		if (!passcheck(Nefry.getWebServer()->arg("pass"))) {
			Nefry.getWebServer()->send(403, "text/html", "password err");
		}
		else {
			String rs = Nefry.getWebServer()->arg("r");
			String gs = Nefry.getWebServer()->arg("g");
			String bs = Nefry.getWebServer()->arg("b");
			String content = F("{\"mode\":\"NefrysetLed\",\"r\":");
			content += rs;
			content += F(",\"g\":");
			content += gs;
			content += F(",\"b\":");
			content += bs;
			content += F("}");
			Nefry.setLed(rs.toInt(), gs.toInt(), bs.toInt());
			Nefry.getWebServer()->send(200, "application/json", content);
		}
	});

}
void nefryrestapi::apiControl() {
	//NefryapiVersion
	Nefry.getWebServer()->on("/api/version", [&]() {
		String content = F("{\"mode\":\"version\",\"version\":");
		content += VERSION;
		content += F("}");
		Nefry.setLed(rs.toInt(), gs.toInt(), bs.toInt());
		Nefry.getWebServer()->send(200, "application/json", content);

	});
}

bool nefryrestapi::passcheck(String keyset)
{
	if (key.length() == 0)return true;
	if (key.equals(keyset))return true;
	return false;
}

void nefryrestapi::begin(bool nefry,bool input, bool output, bool serial) {
	apiControl();
	if (nefry)nefryControl();
	if (input)gpioInput();
	if (input)gpioOutput();
	if (serial)serialCotrol();

}
void nefryrestapi::setPassword(String password)
{
	key = password;
}
nefryrestapi NefryRESTAPI;
