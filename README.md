# Oric App Template
===================

Template that provides a simple start point to develop an app/game
It provides the following:

- Intro
- Main menu
- Options screen (to sel volume only at this point)
- Load/Save features

It is designed to allow a game/app state to be saved and loaded using the lores1 screen as a buffer.

It tracks the state of the current game/app andthe menu options change depending on that state.
The quick demo added to the template shows a simple set of array variables that can be stored on tape and retrived.
When running a 'new' or 'loading' a state you will see a table of information stored in a typedef array.

That array is a simple struct that contains the following values:

	unsigned char x, y;	   
	unsigned char active;
	int hp;

These are from another game development but can be anytthing of courtse.
In the example if you press the space bar the state changes with the x/y/hp values being incremeneted one. It is not very exciting but can be used to illustrate the point of the template code.

When running in a emulator it is really easy to start a new game/app, press space a few times as if the user has done some work or played the game. Next you can save it to tape and continue or close the game state and start again. Then you can load your saves state from before by providing the file name. The Oriucutron will ausomatially load the tape file with that name so it becomes suprisingly simple to load and save as if you had a modern Oric!

Of course on a real Oric it would require some manual tape messing about but it should work fine.

Currently the addresses for the buffer are hard coded to: Start 47104 End 47999 whcih is the lores 0 screen area. That is 895 bytes of data. Therefore you can only store and retrive that much informatiuon so there is a hard limit here.
The addresses can be change if you wish but you will need to look into the code at the void SaveBufferToTape() method to find out.

The display and IO functions here are meant as placehgolders for your own code as the formatting is very crude. That was not the intention of this template.

For example there are simple DialogBox and DialogText functions that either prompt the user or ask them for a line of text input.
Currently the DialogText is limited to 8 chars as that if the largest tape file name.

SAVING
======
To save data you need to modify method void SetSaveBuffer() with your own game/app variables. The most important thing is the accumplying method void GetLoadBuffer() must specify the varraiblers in the game order.

Each time you with to store a value in the buffer call one of the following methods, depending on the type:

StoreCharInBuffer()

StoreIntInBuffer()

The mmethod SaveBufferToTape() is then called which saves the buffer to tape using the name gathered from the DialogText call.


LOADING
=======
To load the data back from tape call the method LoadBufferFromTape() whcih will load a file with the name specificed in DialogText.

Next call GetLoadBuffer() which will scan the buffer and set your game/app varaibles.

The most importnat thing is to ensure that the SAVE and LOAD methods process the data in the same order and that the total size is not gigger than 895

Limitations
The current template does not dynamically scale the size of the buffer when saving. It will always store 895 bytes. A nice update would be to calcualate the size of the buffer that needs to be saved each time.

As with other LOAD operations on the Oric if something goes wrong or the file name is incorrect there is no way to get your machine back without a reset.

The template uses the amazing libbasic library from raxxis:
 
 https://github.com/iss000/oricOpenLibrary

It is my intention to actually remove this as I only need it to patch into the BASIC LOAD and SAVE commands.
