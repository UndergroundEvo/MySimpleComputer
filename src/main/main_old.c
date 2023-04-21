#include <include.h>

short currMemCell = 0;

/* волшебный пингвин 🐧 */
int ui_moveCurrMemPointer(enum keys key) {
	printf("%d", key);
	switch (key) {
	case KEY_UP:    (currMemCell <= 9) ? (currMemCell = 90 + currMemCell) : (currMemCell -= 10); return 0;
	case KEY_RIGHT: (!((currMemCell + 1) % 10)) ? (currMemCell -= 9) : (currMemCell += 1); return 0;
	case KEY_DOWN:  (currMemCell >= 90) ? (currMemCell = currMemCell - 90) : (currMemCell += 10); return 0;
	case KEY_LEFT:  (!(currMemCell % 10)) ? (currMemCell += 9) : (currMemCell -= 1); return 0;
	}
	return -1;
}
void setValue(){
	mt_gotoXY(1, 24);
	char buffer[10];
	printf("Set the value of the cell under the number \033[38;5;%dm%d\033[0m\n", YELLOW, currMemCell);
	printf("Enter value in \033[38;5;%dmHEX\033[0m format > ", YELLOW);
	fgets(buffer, 10, stdin);
	long int number;
	char* tmp;
	if (buffer[0] == '+') {
		number = strtol(&buffer[1], &tmp, 16);
		if (number > 0x3FFF) {
			print_norm((char*)"The command value must not exceed 14 bits (0x3FFF)", YELLOW);
			return -1;
		}
		sc_memorySet(currMemCell, (short int)number);
	}
	else {
		number = strtol(buffer, &tmp, 16);
		if (number > 0x3FFF) {
			print_norm((char*)"The value must not exceed 14 bits (0x3FFF)", YELLOW);
			return -1;
		}
		number = (1 << 14) | number;
		sc_memorySet(currMemCell, (short int)number);
	}
	return 0;
}
void printTerminal()
{
	int rows = 0, cols = 0;
	mt_clrscreen();
	mt_getscreensize(&rows, &cols);
	bc_box(1, 1, 61, 12);   // память
	bc_box(62, 1, 22, 3);   // аккамулятор
	bc_box(62, 4, 22, 3);   // счетчик инструкций
	bc_box(62, 7, 22, 3);   // операторы
	bc_box(62, 10, 22, 3);  // флаги
	bc_box(1, 13, 52, 10);  // буквы
	bc_box(53, 13, 31, 10); // кнопки
	mt_gotoXY(30, 1);
	printf(" Memory ");
	mt_gotoXY(66, 1);
	printf(" accumulator ");
	mt_gotoXY(63, 4);
	printf(" instructionCounter ");
	mt_gotoXY(68, 7);
	printf(" Operation ");
	mt_gotoXY(68, 10);
	printf(" Flags ");
	mt_gotoXY(55, 13);
	printf(" Keys: ");
	char* hotK[] = { (char*)"l  - load",
					 (char*)"s  - save",
					 (char*)"r  - run",
					 (char*)"t  - step",
					 (char*)"i  - reset",
					 (char*)"F5 - accumulator",
					 (char*)"F6 - instructionCounter" };

	for (int i = 0; i < sizeof(hotK) / sizeof(*hotK); ++i)
	{
		mt_gotoXY(55, i + 14);
		printf("%s", hotK[i]);
	}
}
void printMEM(){
	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10; ++j){
			mt_gotoXY(2 + (5 * j + j), 2 + i);
			int tmp = memory[i * 10 + j];
			if ((i * 10 + j) == currMemCell)
				mt_setbgcolor(GREEN);
			if ((tmp >> 14) & 1)
				printf(" %04X", tmp & (~(1 << 14)));
			else
				printf("+%04X", tmp);
		}
}
int printflag()
{
	char tmp[] = { 'O', 'Z', 'M', 'P', 'C' };
	// wchar_t tmp[] = { '💀', '🧨', '🗿', '💅', '🛑' };
	for (int i = 0; i < REG_SIZE; i++)
	{
		int value;
		if (sc_regGet(i, &value))
			return -1;
		if (value)
		{
			mt_gotoXY(69 + (i * 2), 11);
			printf("%c", tmp[i]);
		}
	}
	return 0;
}
int drawingBigChars()
{
	int tmp;
	sc_memoryGet(1, &tmp);
	if (!((tmp >> 14) & 1))
		bc_printbigchar(bc[16], 2, 14, GREEN, BLACK);
	tmp = tmp & 0x3FFF;
	for (int i = 0; i < 4; ++i)
	{
		int ch = (tmp & (0xF << (4 * (3 - i)))) >> (4 * (3 - i));

		bc_printbigchar(bc[ch], 2 + 8 * (i + 1) + 2 * (i + 1), 14, GREEN,
			BLACK);
	}
	return 0;
}
void InputControl(short flag) {
	enum keys key = 0;
	char buffer[64] = { 0 };
	mt_gotoXY(1, 24);
	rk_readKey(&key);
	switch (key)
	{
	case KEY_UP:
		ui_moveCurrMemPointer(KEY_UP); break;
		break;
	case KEY_RIGHT:
		ui_moveCurrMemPointer(KEY_RIGHT); break;
		break;
	case KEY_DOWN:
		ui_moveCurrMemPointer(KEY_DOWN); break;
		break;
	case KEY_LEFT:
		ui_moveCurrMemPointer(KEY_LEFT); break;
		break;
	case KEY_L: // l  - load
		//sc_memoryLoad(buffer);
		rk_myTermRestore();
		printf("Loaded!");
		getchar();
		break;
	case KEY_S: // s  - save
		//sc_memorySave(buffer);
		rk_myTermSave();
		printf("Saved!");
		getchar();
		break;
	case KEY_R: //not implemented // r  - run
		break;
	case KEY_T: //not implemented // t  - step
		break;
	case KEY_I: // i  - reset
		sc_memoryInit();
		break;
	case KEY_F5: //not implemented // F5 - accumulator
		//setAccum();
		break;
	case KEY_F6: //not implemented // F6 - instructionCounter
		//setIP();
		break;
	case KEY_ENTER:
		setValue();
		break;
	case KEY_ESC:
		flag = 0;
		break;
	}

}
void UpdateUI() {
	printTerminal();
	printMEM();
	drawingBigChars();
	printflag();
}
int main()
{
	short flag = 1;
	sc_memoryInit();
	sc_regInit();
	sc_memorySet(0, 5);
	sc_memorySet(1, 1);
	sc_memorySet(2, 3);
	sc_memorySet(3, 1);
	sc_memorySet(4, 1);
	/*sc_regSet(REG_SIZE, 5);
	sc_regSet(OVERFLOW, 1);
	sc_regSet(DIVISION_BY_ZERO, 1);
	sc_regSet(OUT_OF_MEMORY, 1);
	sc_regSet(IGNORING_CLOCK_PULSES, 1);
	sc_regSet(INCORRECT_COMMAND, 1);*/
	
	do
	{
		UpdateUI();
		InputControl(flag);
		mt_gotoXY(1, 24);
	} while (flag!=0);
	return 0;
}