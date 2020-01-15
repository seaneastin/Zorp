#pragma once




const char* const ESC = "\x1b";  //put what this does sometime
const char* const CSI = "\x1b["; //– this acronym stands for Control Sequence Introducer. 
//This character sequence is at the start of every command we’ll pass to the console. 
//It’s defined here for situations where we can’t use a pre-defined command. 
const char* const TITLE = "\x1b[5;20H"; // this command moves our cursor to the x,y coordinate (20, 5)
const char* const INDENT = "\x1b[5C"; //moves the cursor right by 5 characters
//colors 
const char* const YELLOW = "\x1b[93m"; //sets the text color to yellow.
const char* const MAGENTA = "\x1b[95m"; //sets the text color to magenta.
const char* const RESET_COLOR = "\x1b[0m"; //resets the text colour to the default color.
const char* const RED = "\x1b[91m"; //sets the text color to Red
const char* const BLUE = "\x1b[94m"; //sets the text color to blue
const char* const WHITE = "\x1b[97m"; //sets the text color to white
const char* const GREEN = "\x1b[92m"; //sets the text color to Green
const char* const CYAN = "\x1b[96m"; //sets the text color to cyan
const char* const EXTRA_OUTPUT_POS = "\x1b[21;6H";
const char* const INVENTORY_OUTPUT_POS = "\x1b[24;6H";


const int EMPTY = 0;


const int ENTRANCE = EMPTY+1;
const int EXIT = ENTRANCE+1;

const int MAZE_WIDTH = 10;
const int MAZE_HEIGHT = 6;



const int INDENT_X = 5; //how many spaces to use to indent all text. This can also be used as a tab.
const int ROOM_DESC_Y = 8; //the line to use for our room descriptions. Each type of room will have a description. 
//For example, for the empty room the description
//will be “You are in an empty meadow. There is nothing of interest here.”
const int MOVEMENT_DESC_Y = 9;

const int MAP_Y = 12; //the first line where the map is drawn.



const int PLAYER_INPUT_X = 30; //the character column where the player will type their input. 
const int PLAYER_INPUT_Y = 19; // the line where the player will type their input.


//input commands
const int WEST = 4; //
const int EAST = 6; //
const int NORTH = 8; //
const int SOUTH = 2; //
const int LOOK = 9; //
const int FIGHT = 10; //
const int PICKUP = 11; //
const int QUIT = 12;



static const char itemNames[15][30] =
{

	 "indifference", "invisibility", "invulnerability", "incontinence",
	"improbability", "impatience", "indecision", "inspiration",
	"independence", "incurability", "integration", "invocation",
	"inferno", "indigestion", "inoculation"

};



