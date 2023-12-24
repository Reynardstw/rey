#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


char dataMenu(){ // function untuk memunculkan menu login yang akan mengreturn berupa pilihan yang dipilih
	system("cls");
	printf(" = = = = = = = = = = = = = = = = = = = = = = = = =\n");
	printf("    A	  R R	 C C C     A      N    N    E E E\n");
	printf("   A A	  R   R	 C        A A     N N  N    E\n");
	printf("  A   A	  R   R	 C       A   A    N  N N    E E E\n");
	printf(" A A A A  R R	 C      A A A A   N   NN    E\n");
	printf("A	A R   R	 C C C A       A  N    N    E E E\n");
	printf(" = = = = = = = = = = = = = = = = = = = = = = = = =\n");
	printf("		New Game(1)				\n");
	printf("		Load Game(2)				\n");
	printf("		Exit Game(3) 			\n");
	printf(" = = = = = = = = = = = = = = = = = = = = = = = = =");
	
	return getch();
}


char mainMenu(int gold,char name[]){//function yang memunculkan main menu dimana gold dan nama player menjadi parameter agar dapat dimunculkan di main menu
	 system("cls");
	printf(" = = = = = = = = = = = = = = = = = = = = = = = = =\n");
	printf("    A	  R R	 C C C     A      N    N    E E E\n");
	printf("   A A	  R   R	 C        A A     N N  N    E\n");
	printf("  A   A	  R   R	 C       A   A    N  N N    E E E\n");
	printf(" A A A A  R R	 C      A A A A   N   NN    E\n");
	printf("A	A R   R	 C C C A       A  N    N    E E E\n");
	printf(" = = = = = = = = = = = = = = = = = = = = = = = = =\n");
	printf("		 Welcome to Arcane                \n");
	printf("                      %s\n",name);
	printf("                      Gold : %d\n\n",gold);
	printf("		! Start Game(1)				\n");
	printf("		$ Shop(2)				\n");
	printf("		- Log Out(3)				\n");
	printf("		x Exit Game(4) 			\n");
	printf(" = = = = = = = = = = = = = = = = = = = = = = = = =");
	
	return getch();

}

void attack (int player, int* playerhealth1, int* playerhealth2,int playerattack1) { //Function ini berfungsi untuk menimbulkan efek serangan tipe attack pada lawan
	if (player == 1){
		*playerhealth2 -= playerattack1;
	}
	if (player == 2){
		*playerhealth1 -= 15;
	}
}
int skill (int player, int* playerhealth1, int* playerhealth2, int playerattack1) {//function ini berfungsi untuk menimbulkkan efek serangan tipe skill pada lawan
	if(player == 1){
		*playerhealth2 -= playerattack1;
		*playerhealth1 += 5;
	}
	if(player == 2){
		*playerhealth1 -= 15;
		*playerhealth2 += 5;
	}
	return 3;
}

int ultimate (int player, int* playerhealth1, int* playerhealth2,int playerattack1) { // funciton ini berfungsi untuk menimbulkan efek serangan tipe ultimate pada lawan
	if(player == 1){
		*playerhealth2 -= playerattack1*2;
	}
	if(player == 2){
		*playerhealth1 -= 30;
	}
	return 4;
}

void cd (int player,int* cooldown){//function ini berfungsi untuk mengurangi cooldown dari skill atau ultimate player yang dipanggil tiap turn player dimulai, saat kondisi cooldown tidak sama dengan 0
	
	if (player == 1){
		*cooldown -= 1;
	}
	if (player == 2){
		*cooldown -= 1;
	}
}

void swap(int *a, int *b) {//Function ini berungsi untuk menukar 2 angka yang digunakan pada sorting item berdasarkan gold atau nama
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swapStrings(char a[], char b[]) {//Function ini berfungsi untuk menukar 2 nama item yang digunakkan pada sorting item berdasarkan gold atau nama
    char temp[100];
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}


void sortByGold(char item[][100], int itemcode[], int price[], int size) {//function ini berguna untuk mengsort item berdasarkan gold dari murah ke mahal
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (price[j] > price[j + 1]) {

                swap(&price[j], &price[j + 1]);

                swap(&itemcode[j], &itemcode[j + 1]);

                swapStrings(item[j], item[j + 1]);
            }
        }
    }
}

void sortByName(char item[][100], int itemcode[], int price[], int size) {//function ini berguna untuk mengsort item berdasarkan abjad dari a ke z
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) { // sort yang digunakan adalah bubble sort karena tidak memuat banyak data
            if (strcmp(item[j], item[j + 1]) > 0) {
            	
                swap(&price[j], &price[j + 1]);

                swap(&itemcode[j], &itemcode[j + 1]);

                swapStrings(item[j], item[j + 1]);
            }
        }
    }
}

void saveGameData(const char *filename, const char *name, int gold,int itemcode[]) { // function ini bergunsi untuk mengsave data baru
    FILE *file = fopen(filename, "a"); // berguna untuk mengset file pointe bernama file yang membuka file dengan nama yang ada di variabel filename dengan a yang berarti untuk append atau menambahkan data baru.

    if (file != NULL) {
        fprintf(file, "%s#%d#%d#%d#%d\n", name, gold,itemcode[0],itemcode[1],itemcode[2]);  
        fclose(file);
        printf("Game data saved successfully.\n");
    } 
}


void displayGameData(const char *filename) { // function ini berfungsi untuk memunculkan data apa saja yang sudah terdaftar saat ingin melanjutkan progress game
	system("cls");
    FILE *file = fopen(filename, "r"); // Set file pointer file dengan nama file sesuai yang ada di variabel filename dengan menggunakan "r" yang berarti digunakan untuk membaca isi file

    if (file != NULL) {
        printf("Available Game Data:\n");
        char name[50];
        int gold;
        int count = 1;
		int itemcode[3]; // variabel2 yang di declare digunakan untuk menyimpan data yang di baca didalam file save data
        while (fscanf(file, "%[^#]#%d#%d#%d#%d\n", name, &gold,&itemcode[0],&itemcode[1],&itemcode[2]) == 5) { //Looping digunakan untuk mengscan setiap baris jika memiliki 5 input maka terus jalan 
            printf("%d. Name: %s, Gold: %d\n", count, name, gold); //ketika sudah membaca ke 5 input, ke 5 input di print ke layar terminal dan akan diulang terus
            count++;//count digunakan untuk menunjukkan baris ke berapa data disimpan
        }

        fclose(file);
    } 
}

int loadGameData(const char *filename, char *name, int *gold, int num,int itemcode[]) {//function digunakan untuk mengambil data yang tersimpan pada baris yang dipilih sehingga data di load dan digunakan saat game dimulai untuk melanjutkan progress
    FILE *file = fopen(filename, "r");

    if (file != NULL) {
        int count = 1;
        while (fscanf(file, "%[^#]#%d#%d#%d#%d\n", name, gold,&itemcode[0],&itemcode[1],&itemcode[2]) == 5) {//sama seperti sebelumnya, loop terus berjalan ketika di 1 baris ada 5 input yang ada, terus hingga count bertemu dengan tujuan/input baris yang ingin di load
            if (count == num) {
                fclose(file);
                return 1;  
            }
            count++;
        }

        fclose(file);
        return 0;  
    } 
}


	int getRandomMove() { // function ini digunakan untuk mengrandom input yang digunakan oleh player2 yang disini kami anggap sebagai bot musuh
    return rand() % 3 + 1;
}
void itembuff(int *playerattack1,int *playerhealth1,int itemcode[],char item[][100]){ // function ini digunakan untuk menambahkan status pada karakter ketika item tertentu dimiliki
	int i;
	for(i=0;i<3;i++){
		if(itemcode [i] == 1 && strcmp(item[i],"Sword") == 0){ // saat kondisi itemcode = 1/true, maka sword dimiliki dan akan menambahkan attack player sebesar 5
			*playerattack1 += 5;
		}
		if(itemcode [i] == 1 && strcmp(item[i],"Armor")==0){// saat kondisi itemcode = 1/true, maka armor dimiliki dan akan menambahkan health player sebesar 30
			*playerhealth1 += 30;
		}
		if(itemcode [i] == 1 && strcmp(item[i],"Dagger")==0){// saat kondisi itemcode = 1/true, maka dagger dimiliki dan akan menambahkan attack player sebesar 3
			*playerattack1 += 3;
		}
	}
}

	void replaceLine(const char *filename, int lineToReplace, char *name,int newgold,int itemcode[]) {//function ini digunakan untuk menimpa data yang sudah ada dengan data yang baru, terutama saat kita melanjutkan progress game, maka akan diperbaharuii dengan function ini
    FILE *originalFile, *tempFile; // buat file pointer original file dan temp file
    char buffer[1000]; // buffer digunakan untuk menyimpan baris yang akan dipindah dari original file ke temp file
    int currentLine = 0; // menandakan baris start dari baris ke-0

    originalFile = fopen(filename, "r"); // membuka file dengan nama dari variabel filename sebagai originalfile yang digunakan untuk membaca
    tempFile = fopen("tempfile.txt", "w"); // membuka file dengan nama tempfile.txt sebagai tempfile yang digunakan untuk menulis



    while (fgets(buffer, sizeof(buffer), originalFile) != NULL) {// ketika baris yang dibaca tidak kosong, loop terus berjalan
        currentLine++; // increment pada current line yang digunakan untuk menandakan sedang membaca baris ke-berapa

        if (currentLine == lineToReplace) {//ketika baris ke-sekian sudah sama dengan baris tujuan, string pada baris original file tidak dipindah ke temp file namun digantikan dengan string baru yang berisikan data-data player yang baru
            fprintf(tempFile, "%s#%d#%d#%d#%d\n", name,newgold,itemcode[0],itemcode[1],itemcode[2]); // print data yang baru
        } else {
            fprintf(tempFile, "%s", buffer); // print data yang sudah ada dari sebelumnya tanpa diganti
        }
    }

    fclose(originalFile);
    fclose(tempFile);

    remove(filename); // file awal yang belum diubah dihapus

    rename("tempfile.txt", filename); // tempfile yang sudah diperbaharui diganti namanya menjadi nama filename, untuk menggantikan original file itu sendiri

}
	
	
int main(){
	
	char filename[] = "saveData.txt";
	char datachoose;
	int k;
	char menuchoose;
	int i,move,menu,info;
	char shop;
	int j;
	char item[3][100] = {"Armor", "Dagger","Sword"};
	int itemcode [3] = {0,0,0};
	int price[3] = {2000,1100,1500};
	char name[50];
	int gold = 0;
	int accountnum;
	int dataChoose;
	
	srand(time(NULL)); // mengambil nilai acak berdasarkan waktu saat itu juga
	
	login:// sebagai titik jump bernama login
	datachoose = dataMenu(); //mengambil input pengguna yang didapat dari getch pada function dataMenu
	
	if(datachoose == '3'){ // jika pengguna memilih 3, maka keluar dari game
		exit(0);
	}
	else if(datachoose == '1'){// jika pengguna memilih 1 maka membuat progres game baru
	do{
		 system("cls");
        printf("Insert Name (Can't contain #): ");
        scanf("%s", name);
        if (strchr(name, '#') != NULL) { // digunakan untuk membandingkan apakah ada # pada nama , jika ada tolak.
            printf("Name cannot contain '#'. Please enter a valid name.\n");
            getch();
        }
    } while (strchr(name, '#') != NULL); // ulang terus kondisi do ketika ada # pada nama

		accountnum = -1; // jika tidak ada # maka set nomorakun ke-1
		gold = 0; //dan juga set gold menjadi 0 karena akun baru
	}
	else if(datachoose == '2'){ // jika memilih 2 , maka pengguna akan memilih akun mana yang akan dipilih
		displayGameData("saveData.txt"); // function yang dipanggil berfungsi untuk memunculkan data pengguna
		printf("Which account you want to load : "); 
		scanf("%d",&accountnum);
		dataChoose = loadGameData(filename,name,&gold,accountnum,itemcode); // function loadgamedata akan mengreturn angka1 jika ditemukan baris data yang diingingkan
		if(dataChoose == 0){ // jika return = 0 maka tidak ditemukan baris yang ingin di load datanya maka akan dilempar kembali ke menu
			system("cls");
			printf("Invalid Input");
			getch();
			goto login;
		}
	}
	else{
		goto login;//jika memilih tombol selain 1/2/3 maka dikembalikan ke login atau tidak terjadi apa2
	}
	
		int newgold = gold; // newgold digunakan sebagai tempat menyimpan gold dari hasil load game data
	
	
	menu: // titik jump bernama menu
	
	menuchoose = mainMenu(newgold,name); //memanggil function mainMenu yang akan mengreturn pilih pengguna apa yang akan dilakukan dan juga memunculkan main menu
	sortByName(item, itemcode, price, 3);// digunakan untuk mengsort item sesuai nama agar ketika di save data urutan item yang tersave sesuai urutan
	int dead=0;
	int playerhealth1 = 100;
	int playerhealth2 = 100;
	int playerattack1 = 15;
	int playerattack2 = 15;
	int cdskill1=0;
	int cdskill2=0;
	int cdult1=0;
	int cdult2=0;

	if(menuchoose == '1'){ //Ketika dipilih 1, maka game akan dimulai
		itembuff(&playerattack1,&playerhealth1,itemcode,item);  // menambah attribut karakter pengguna jika dimiliki item2 tertentu
	for(i=0;dead == 0;i++){//looping game terus menerus selama belum ada yang mati / dead = 0
		p1:

		system("cls");
		printf("Menu (4)\n");
		printf("Information (5)\n");
		printf("\n");
		
	if(move == 0){ // ini digunakan untuk menunjukkan bot melakukan gerakan apa
		}
		else if(move == 1){
			printf("Player 2 chose: Attack\n\n");
		}
		else if(move == 2){
			printf("Player 2 chose: Skill\n\n");
		}
		else if(move == 3){
			printf("Player 2 chose: Ultimate\n\n");
		}
		
		printf("Player 1 health : %d\n",playerhealth1); // menunjukkan nyawa pengguna
		printf("Player 2 health : %d\n\n",playerhealth2); //menunjukkan nyawa musuh
			if (i%2 == 0){ // ketika iterasi = ganjil, maka giliran pengguna , ketika genap, maka giliran musuh
				
				
				if(cdskill1 > 0){ // jika ada cooldown skill pada saat turn dimulai, dipanggil function yang mengurangi cooldown
					cd (1,&cdskill1);
				}
				if(cdult1 > 0){// jika ada cooldown ultimate pada saat turn dimulai, dipanggil function yang mengurangi cooldown
					cd (1,&cdult1);
				}
				
				printf("Player 1 turn \n");
				printf("Select your move : \n");
				printf("Basic attack (1)\n");
				printf("Skill (2)"); if(cdskill1 > 0)printf(" (Cooldown : %d turn)",cdskill1);printf("\n");
				printf("Ultimate (3)"); if(cdult1 > 0)printf(" (Cooldown : %d turn)",cdult1);printf("\n");
				invalid1:
				int move = getch(); // mengambil input pengguna sebagai move
				if(move == '1'){ // jika input 1 gunakan attack
					attack(1, &playerhealth1, &playerhealth2,playerattack1); 

				}
				else if ((move == '2') && (cdskill1 == 0)){//jika input 2 gunakan skill
					cdskill1 = skill(1, &playerhealth1, &playerhealth2,playerattack1);
					
				}
				else if ((move == '3') && (cdult1 == 0)){//jika input 3 gunakan ultimate
					cdult1 = ultimate(1, &playerhealth1, &playerhealth2,playerattack1);
				}
				else if (move == '4'){//jika input 4 membuka menu
					system ("cls");
					printf("Return (1)\n");
					printf("Exit (2)");
					menu1:
					menu = getch();
					if (menu == '1'){
						goto p1;
					}
					else if(menu == '2'){
						goto menu;
					}
					else{
						goto menu1;
					}
				}
				else if (move == '5'){//jika input 5 maka buka informasi tentang attack.
					system ("cls");
					printf("Attack inflict 10 damage\n");
					printf("Skill inflict 15 damage and recover 5 HP\n");
					printf("Ultimate inflict 30 damage\n\n");
					printf("Return (1)\n");
					info1:
					info = getch();
					if (info == '1'){
						goto p1;
					}
					else{
						goto info1;
					}
				}
				else{
				goto invalid1;
				}
			}
			if (i%2 == 1){ // jika ganjil maka giliran musuh
				
				
					if(cdskill2 > 0){
					cd (2,&cdskill2);
				}
				if(cdult2 > 0){
					cd (2,&cdult2);
				}
				
				printf("Player 2 turn \n");
				printf("Select your move : \n");
				printf("Basic attack (1)\n");
				printf("Skill (2)"); if(cdskill2 > 0)printf(" (Cooldown : %d turn)",cdskill2);printf("\n");
				printf("Ultimate (3)"); if(cdult2 > 0)printf(" (Cooldown : %d turn)",cdult2);printf("\n");
			retry:
            move = getRandomMove(); // digunakan seed random untuk mendapatkan move bagi musuh
            if((move == 2) && (cdskill2 != 0) || (move == 3) && (cdult2 != 0)){
            	goto retry;
			}

            if (move == 1) {
                attack(2, &playerhealth1, &playerhealth2,playerattack1);
            } else if ((move == 2) && (cdskill2 == 0)) {
                cdskill2 = skill(2, &playerhealth1, &playerhealth2,playerattack1);
            } else if ((move == 3) && (cdult2 == 0)) {
                cdult2 = ultimate(2, &playerhealth1, &playerhealth2,playerattack1);
            }
			}
			if(playerhealth1 <= 0){
				dead = 1;
			}
			if(playerhealth2 <= 0){
				dead = 2;
			}
	}
	
	if(dead == 1){//ketika pengguna mati, maka dead = 1 dan akan dimunculkan bahwa kita mati
		system ("cls");
		printf("You Died\n");
		getch();
		goto menu;
	}
	if(dead == 2){ // jika kita membunuh musuh, maka dead = 2 dan akan dimunculkan player 1 win, serta mendapatkan gold sebanyak 300
		system ("cls");
		printf("Player 1 win\n");
		printf("You earned 300 gold");
		newgold += 300;
		getch();
		goto menu;
	}
}

	else if(menuchoose == '2'){ // jika pengguna input 2 maka masuk ke menu shop
		

	for(j=0;;j++){ // endless loop agar keluar saat ditekan 4 dan kembali ke main menu
		system("cls");
		
		if(shop == '1'){ 
		printf("Item sorted based on gold\n");
	}
		else if(shop == '2'){
		printf("Item sorted based on Name\n");
	}
	
	for(i=0;i<3;i++){
	printf("%s (%d)",item[i],price[i]);
	if(itemcode[i] == 1){
		printf(" (Owned)");
	}
	printf("\n");
	
}
printf("Gold : %d\n",newgold);
printf("Sort item based on gold[1]\n");
printf("Sort item based on name[2]\n");
printf("Buy item[3]\n");
printf("Exit Shop[4]\n");	
	shop = getch();
	if(shop == '1'){ // jika input = 1 maka item di shop di sort berdasarkan gold
		sortByGold(item, itemcode, price, 3);
	}
	else if(shop == '2'){ // jika input = 2 maka item di sort berdasarkan abjad
		sortByName(item, itemcode, price, 3);
	}
	else if(shop == '3'){ // jika input = 3 maka akan muncul pilihan untuk membeli barang
		buyitem:
		for(k=0;;k++){
			system("cls");
			for(i=0;i<3;i++){
				printf("%d ",i+1);
	printf("%s (%d)",item[i],price[i]);
	if(itemcode[i] == 1){ 
		printf(" (Owned)");
	}
	printf("\n");
	}	
	printf("Gold : %d\n",newgold);
	printf("Quit (x)\n");
	printf("\nBuy item (1,2,3) : ");	
	char buyitem;
	scanf("%c",&buyitem);
		if (buyitem == '1'){ // input 1 , 2 , 3 digunakan untuk membeli barang, yang melewati pengecekan apakah item dimiliki, dan apakah gold cukup, jika kedua tes dilewati , ubah itemcode = 1/owned.
			if(itemcode[0] == 1){
				system("cls");
				printf("item owned");
				getch();
				goto buyitem;
			}
			if(newgold < price[0]){
				system("cls");
				printf("Not enough gold");
				getch();
				goto buyitem;
			}
			else{
			itemcode[0] = 1;
			newgold -= price[0];
			system("cls");
			printf("Item Bought");
			getch();
			goto buyitem;
		}
		}
		if (buyitem == '2'){
			if(itemcode[1] == 1){
				system("cls");
				printf("item owned");
				getch();
				goto buyitem;
			}
			if(newgold < price[1]){
				system("cls");
				printf("Not enough gold");
				getch();
				goto buyitem;
			}
			else{
			itemcode[1] = 1;
			newgold -= price[1];
			system("cls");
			printf("Item Bought");
			getch();
			goto buyitem;
		}
		}
		if (buyitem == '3'){
			if(itemcode[2] == 1){
				system("cls");
				printf("item owned");
				getch();
				goto buyitem;
			}
			if(newgold < price[2]){
				system("cls");
				printf("Not enough gold");
				getch();
				goto buyitem;
			}
			else{
			itemcode[2] = 1;
			newgold -= price[2];
			system("cls");
			printf("Item Bought");
			getch();
			goto buyitem;
		}
		}
		if (buyitem == 'x' || buyitem == 'X'){//jika input x, maka keluar dari buy menu
			goto menu;
		}
		}
	}
	else if(shop == '4'){ // jika pilihan 4 , maka kembali ke main menu
		goto menu;
	}
	else{
	}
}
	}
	
	else if(menuchoose == '3'){ // jika pilihan =3 maka akan logout dimana data akan di save jika belum ada dengan nomor akun -1 di baris baru, jika sudah ada maka akan ditumpuk pada nomor akun yang menandakan di baris mana progress tersimpan
		if(accountnum == -1){
			saveGameData(filename,name,newgold,itemcode);
		}
		else{
		replaceLine(filename,accountnum,name,newgold,itemcode);}
		goto login;
	}
	else if(menuchoose == '4'){ // pilihan 4 sama dengan pilihan 3 , tapi langsung keluar dari game
		if(accountnum == -1){
			saveGameData(filename,name,newgold,itemcode);
		}
		else{
		replaceLine(filename,accountnum,name,newgold,itemcode);}
		exit(0);
	}
	else{ // jika tombol lain ditekan , tidak berpengaruh apa2
		goto menu;
	}
return 0;
}
//Inget \n

