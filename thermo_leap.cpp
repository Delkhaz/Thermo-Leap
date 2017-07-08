/*
Ardlan Khalili
10/22/16

This program uses the Leap Motion API to grab movements from the user's hand and 
sends it to the NEST through the NEST's developer system calls. Gestures include increase
temp, decrease temp, change status to home, and change status to away. using a certain hand
(left/right) and the amount of fingers you put up. 
*/

#include <iostream>
#include <unistd.h>
#include "Leap.h"
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <pthread.h>

using namespace Leap;

class SampleListener : public Listener {
	public:
		virtual void onInit(const Controller&);
		virtual void onConnect(const Controller&);
		virtual void onDisconnect(const Controller&);
		virtual void onExit(const Controller&);
		virtual void onFrame(const Controller&);
		virtual void onFocusGained(const Controller&);
		virtual void onFocusLost(const Controller&);
		virtual void onDeviceChange(const Controller&);
		virtual void onServiceConnect(const Controller&);
		virtual void onServiceDisconnect(const Controller&);

	private:
};

int do_sleep;


void SampleListener::onInit(const Controller& controller) {
	std::cout << "Initialized" << std::endl;
}

void SampleListener::onConnect(const Controller& controller) {
	std::cout << "Connected" << std::endl;
}

void SampleListener::onDisconnect(const Controller& controller) {
	// Note: not dispatched when running in a debugger.
	std::cout << "Disconnected" << std::endl;
}

void SampleListener::onExit(const Controller& controller) {
	std::cout << "Exited" << std::endl;
}

void SampleListener::onFrame(const Controller& controller) {
	// Get the most recent frame and report some basic information
	if(do_sleep){
		sleep(2);
		do_sleep = 0;
	}
	else{
		do_sleep = 1;
		const Frame frame = controller.frame();
		int incre_decre;
		char char_temp[2];
		int cur_temp;
		FILE *fp;
		std::string tmp_set;
		
		//NEST system calls
		std::string read_temp = "curl -L --silent https://developer-api.nest.com/devices/thermostats/%Device_id%/target_temperature_f\?auth\=%Access_key%";
		
		std::string set_temp = "curl -L -X PUT \"https://developer-api.nest.com/devices/thermostats/%Device_id%/target_temperature_f?auth=%Access_key\" -H \"Content-Type: application/json\" -d \"";
		
		std::string set_home = "curl -L -X PUT \"https://developer-api.nest.com/structures/%Structure_id%/away?auth=%Access_key%\" -H \"Content-Type: application/json\" -d '\"home\"'";
		
		std::string set_away = "curl -L -X PUT \"https://developer-api.nest.com/structures/%Structure_id%/away?auth=%Access_key%\" -H \"Content-Type: application/json\" -d '\"away\"'";

		std::cout << "Frame id: " << frame.id()
			<< ", timestamp: " << frame.timestamp()
			<< ", hands: " << frame.hands().count()
			<< ", extended fingers: " << frame.fingers().extended().count()
			<< ", tools: " << frame.tools().count()
			<< ", gestures: " << frame.gestures().count() << std::endl;

		HandList hands = frame.hands();
		for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
			const Hand hand = *hl;		
			std::string handType = hand.isLeft() ? "Left hand" : "Right hand";
			if(frame.hands().count() == 2 && frame.fingers().extended().count() > 6){
				printf("%s\n", set_away.c_str());
				system(set_away.c_str());			
			}

			else if(frame.hands().count() == 2 && frame.fingers().extended().count() < 6){
				printf("%s\n", set_home.c_str());
                                system(set_home.c_str());
			}

			else{
				fp = popen(read_temp.c_str(), "r");
			
				while(fgets(char_temp, 4, fp) != NULL){

				}

				pclose(fp);
				cur_temp = atoi(char_temp);
				printf("%d\n", cur_temp);

				if(handType == "Left hand" && frame.hands().count() != 2){
					switch(frame.fingers().extended().count()){
						case 0:
							incre_decre = 0;
							break;
						case 1:
							incre_decre = 1;
							break;
						case 2:
							incre_decre = 2;
							break;
						case 3:
							incre_decre = 3;
							break;
						case 4:
							incre_decre = 4;
							break;
						case 5:	
							incre_decre = 5;
							break;
						default:
							;
					}
				}

				else if(handType == "Right hand" && frame.hands().count() != 2){
					switch(frame.fingers().extended().count()){
						case 0:
							incre_decre = 0;
							break;
						case 1:
							incre_decre = 1;
							break;
						case 2:
							incre_decre = 2;
							break;
						case 3:
							incre_decre = 3;
							break;
						case 4:
							incre_decre = 4;
							break;
						case 5:
							incre_decre = 5;
							break;
						default:
							;
					}
				}
				if(handType == "Left hand" && frame.hands().count() != 2){
					cur_temp -= incre_decre;
					tmp_set = set_temp + std::to_string(cur_temp);
					tmp_set = tmp_set + "\"";
					printf("left hand:\n");
					printf("%s\n", tmp_set.c_str());
					system(tmp_set.c_str());
					std::cout << std::endl;
				}

				if(handType == "Right hand" && frame.hands().count() != 2){
					cur_temp += incre_decre;
					tmp_set = set_temp + std::to_string(cur_temp);
					tmp_set = tmp_set + "\"";
					printf("right hand:\n");
					printf("%s\n", tmp_set.c_str());
					system(tmp_set.c_str());
					std::cout << std::endl;
				}
			}

		}
	}
}

void SampleListener::onFocusGained(const Controller& controller) {
	std::cout << "Focus Gained" << std::endl;
}

void SampleListener::onFocusLost(const Controller& controller) {
	std::cout << "Focus Lost" << std::endl;
}

void SampleListener::onDeviceChange(const Controller& controller) {
	std::cout << "Device Changed" << std::endl;
	const DeviceList devices = controller.devices();

	for (int i = 0; i < devices.count(); ++i) {
		std::cout << "id: " << devices[i].toString() << std::endl;
		std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
	}
}

void SampleListener::onServiceConnect(const Controller& controller) {
	std::cout << "Service Connected" << std::endl;
}

void SampleListener::onServiceDisconnect(const Controller& controller) {
	std::cout << "Service Disconnected" << std::endl;
}

int main(int argc, char** argv) {
	// Create a sample listener and controller
	SampleListener listener;
	Controller controller;
	do_sleep = 1;

	// Have the sample listener receive events from the controller
	controller.addListener(listener);

	if (argc > 1 && strcmp(argv[1], "--bg") == 0)
		controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);

	// Keep this process running until Enter is pressed
	std::cout << "Press Enter to quit..." << std::endl;
	std::cin.get();

	// Remove the sample listener when done
	controller.removeListener(listener);

	return 0;
}
