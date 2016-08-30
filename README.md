# Wolfie Game Engine
A game engine written using openGL using Xcode.
The programming language is C++11.

Prequisites:
- GLFW
- GLEW
- GLM

How to setup :

glfw, and glew dynlib are built using cmake and make .
(Recommended for folks who like building it themselves)

Easier alternative is using HomeBrew(An amazing package installer for Mac)
Once Homebrew installed, type:

brew install glfw3

After add search path to /usr/local/include (or whereever you have the respective headers)
Also point the Library Path in Build Settings

A good video which explains the setups of GLFW and GLEW can be found here (Thanks to Sonar Systems):
https://youtu.be/Tz0dq2krCW8


For GLM support, user also needs to manually download glm headers and add them to the search path.

Inspired by Sparky Engine playlist on youtube: 
https://www.youtube.com/playlist?list=PLlrATfBNZ98fqE45g3jZA_hLGUrD4bo6_

Other OpenGL learning resources include:
http://learnopengl.com/#!Introduction
