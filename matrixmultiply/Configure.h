#pragma once


//----------------------------Ustawienia menu
#pragma region MENU

//----------------------------Inne ustawienia
#pragma region OTHER
#define STARTED_OPTION 1																					//Pocz¹tkowo wybrana opcja
#define SPACES_BEEREN_TITLE_OPTIONS 1																		//Przerwa "pod" tytu³em menu
#define BREAK_AFTER_NUBMER 20																				//Przerwa za numerem opcji.
#pragma endregion

//----------------------------Ustawienia poszczególnych opcji
#pragma region SINGLEOPTIONS
#define OPTIONS_POSITION_X 0																				//Pozycja na osi x
#define OPTIONS_POSITION_Y(CURRENT_POSITION) SPACES_BEEREN_TITLE_OPTIONS + CURRENT_POSITION					//Pozycja na osi y
#pragma endregion

//----------------------------USTAWIENIA NAPISU Z ZAZNACZZENIEM
#pragma region SELECTEDSTRING
#define SELECTED_STRING_POSITION_X 0																		//Pozycja na osi x 
#define SELECTED_STRING_POSITION_Y(AMOUNT_OF_OPTIONS) 1 + SPACES_BEEREN_TITLE_OPTIONS + AMOUNT_OF_OPTIONS	//Pozycja na osi y
#pragma endregion

//----------------------------USTAWIENIA napisu z tytulem
#pragma region TITLE
#define TITLE_OPTIONS_POS_X BREAK_AFTER_NUBMER + 1															// Pozycja tytu³u menu na osi x
#define TITLE_OPTIONS_POS_Y 0																				// Pozycja tytu³u menu na osi y
#pragma endregion
#pragma endregion

//----------------------------kolory
#pragma region COLORS 
#define NORMAL_COLOR 7																						//jasny szary	- normalny kolor konsoli
#define NO_SELECTED_COLOR 8																					//ciemno szary	- szary kolor nie wybranej opcji
#define SELECTED_OPTION_COLOR 29																			//bialy			- kolor wybranej opcji
#pragma endregion

//----------------------------klawisze
#pragma region KEYS
#define KEY_DOWN 80																							//Strza³ka w góre
#define KEY_UP 72																							//Strza³ka w dó³
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_RETURN 13																						//enter
#define KEY_0 48																							//0
#pragma endregion