# Thermo-Leap

//main picture


## What is it?
Thermo-Leap allows someone to control the Nest thermostat using the Leap Motion. The left hand is used to decrease the temperature and right hand is used to increase the temperature. Finger represent how many degrees you would like to increase/decrease the temperature. Lastly, there are  gestures to signal home and away to the Nest thermostat. 

## Getting Started
You need to open thermo_leap.cpp and edit these 4 strings variables: 
* read_temp
* set_temp
* set_home
* set_away
When you see %Structure_id%, %Device_id%, or %Access_key% in the string names you need to replace it with your structure id, device id and access key. You can acquire these through the REST walkthrough [here](https://developers.nest.com/documentation/cloud/rest-quick-guide/)

A makefile is provided to compile all the code (currently only works on Mac and Linux).

## Demo
 
 Link: https://www.youtube.com/watch?v=3FCLV_fYFHs&list=UUrBGJDqVpaFRZlndfzClaKw 

## Author

**Ardlan Khalili**

## Questions?

Email me at ardlankhalili@gmail.com