/*
 _______  _______  _______  _______           _        _______    _______  _______  _        ______   _______  _______ 
(  ____ \(  ___  )(  ____ )(       )|\     /|( \      (  ___  )  (  ____ )(  ___  )( (    /|(  __  \ (  ___  )(       )
| (    \/| (   ) || (    )|| () () || )   ( || (      | (   ) |  | (    )|| (   ) ||  \  ( || (  \  )| (   ) || () () |
| (__    | |   | || (____)|| || || || |   | || |      | (___) |  | (____)|| (___) ||   \ | || |   ) || |   | || || || |
|  __)   | |   | ||     __)| |(_)| || |   | || |      |  ___  |  |     __)|  ___  || (\ \) || |   | || |   | || |(_)| |
| (      | |   | || (\ (   | |   | || |   | || |      | (   ) |  | (\ (   | (   ) || | \   || |   ) || |   | || |   | |
| )      | (___) || ) \ \__| )   ( || (___) || (____/\| )   ( |  | ) \ \__| )   ( || )  \  || (__/  )| (___) || )   ( |
|/       (_______)|/   \__/|/     \|(_______)(_______/|/     \|  |/   \__/|/     \||/    )_)(______/ (_______)|/     \|
                                                                                                                       
                                                                                                                       

the M looks like it has a penis lol
                                                                                                                       
THIS APPLICATION RANDOMLY GENERATES AN (unrealistic) FORMULA ONE� RACE! This creates a text file with the starting conditions of
the race, and a CSV file with every single event that happens in the race.

LEGAL MUMBO JUMBO: Formula One� is a trademark owned by Liberty Media Corporation. The creator of this application does not promote
hate towards anyone involved in the Formula One, including but not limited to drivers, teams, stewards and organizers. Every comment
and bias towards any driver is a joke and should not be taken seriously. Every event generated by this application is fictional.

DWTFYWCIABNN LICENSE:

Do whatever the fuck you want. Credit is appreciated but not needed.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define ARRAYLENGTH 3
#define LINEUPLENGTH 20
#define LAPSLENGTH 24
#define RAINCHANCE 10
#define MAXINCIDENTS 5

//This function will write a new line in the output CSV file.
void writeLine(FILE *file, int a[]){
	int i;
	for(i=0;i<ARRAYLENGTH-1;i++){
		fprintf(file, "%d,", a[i]);
	}
	fprintf(file, "%d\n", a[ARRAYLENGTH - 1]);
}

//This function will return a pseudorandom integer between 0 and the specified value.
int randInt(int maxvalue){
	int output = rand() % (maxvalue + 1);
	return output;
}

//This function will look for the specified value in the specified array. Returns the index of the value if found, otherwise returns -1.
int arrayLookup(int a[], int x){
	int i;
	for(i=0;i<LINEUPLENGTH;i++){
		if(a[i] == x){
			return i;
		}
	}
	return -1;
}

//This function will swap two values in an array, given the array and the indexes of the desired values.
void arraySwap(int a[], int ind1, int ind2){
	int temp = a[ind1];
	a[ind1] = a[ind2];
	a[ind2] = temp;
}

//This function will swap two values in the same row of a two-dimensional array, given the array, the target row index and the indexes of the desired columns.
void columnSwap(int a[][4], int row, int col1, int col2){
	int temp = a[row][col1];
	a[row][col1] = a[row][col2];
	a[row][col2] = temp;
}

//This function will print an array, with every element separated by a comma.
void printArray(int a[], int length){
	int i;
	for(i=0;i<length;i++){
		printf("%d, ", a[i]);
	}
}

int main(){
	//This line of code seems to improve pseudorandom number generator idk how it works lol
	srand(time(NULL));
	
	//Declare driver lookup table
	int lineup[LINEUPLENGTH] = {1, 16, 4, 55, 11, 81, 63, 44, 14, 22, 18, 3, 27, 10, 23, 31, 20, 24, 77, 2};
	/*LINEUP, IN ORDER:
	- 1 Max Verstappen (of course he's first)
	- 16 Charles Leclerc
	- 4 Lando Norris
	- 55 Carlos Sainz
	- 11 Sergio Perez
	- 81 Oscar Piastri
	- 63 George Russell
	- 44 Lewis Hamilton
	- 14 Fernando Alonso (the GOAT)
	- 22 Yuki Tsunoda
	- 18 Lance Stroll
	- 3 Daniel Ricciardo
	- 27 Nico Hulkenberg
	- 10 Pierre Gasly
	- 23 Alexander Albon
	- 31 Esteban Ocon (fuck you)
	- 20 Kevin Magnussen
	- 24 Zhou Guanyu
	- 77 Valtteri Bottas
	- 2 Logan Sargeant
	(Drivers are sorted by position as of June 17th, 2024. This is just for reference, they'll be randomized anyways.
	For simplification, backup drivers are not used in this application. I'm sorry, Oliver Bearman. Your great performance will not be forgotten.)
	*/
	
	//Declare laps on each track
	int lapspertrack[LAPSLENGTH] = {57, 50, 58, 53, 56, 57, 63, 78, 70, 66, 71, 52, 70, 44, 72, 53, 51, 62, 56, 71, 71, 50, 57, 58};
	/*LIST OF TRACKS, IN ORDER:
	- Bahrain, 57
	- Jeddah, 50
	- Albert Park, 58
	- Suzuka, 53
	- Shanghai, 56
	- Miami, 57
	- Imola, 63
	- Monaco, 78
	- Montreal, 70
	- Barcelona, 66
	- Red Bull Ring, 71
	- Silverstone, 52
	- Hungaroring, 70
	- Spa, 44
	- Zandvoort, 72
	- Monza, 53
	- Baku, 51
	- Singapore, 62
	- COTA, 56
	- Mexico, 71
	- Brazil, 71
	- Las Vegas, 50
	- Qatar, 57
	- Yas Marina, 58
	(Tracks are sorted by chronological order in the 2024 F1 Championship. Number of laps taken from Wikipedia as of June 17th, 2024.)
	*/
	
	//Generate starting grid
	int sgrid[LINEUPLENGTH];
	int i, j, k ,flag, randDriver;
	int verstappen = 0;
	for(i=0;i<LINEUPLENGTH;i++){
		flag = 0;
		do{
			randDriver = randInt(LINEUPLENGTH - 1);
			if(arrayLookup(sgrid, lineup[randDriver]) == -1){
				sgrid[i] = lineup[randDriver];
				flag = 1;
			}
		}while(flag == 0);
	}
	//Verstappen is unbeatable if he gets the pole position
	if(sgrid[0] == 1){
		verstappen = 1;
	}
	
	//Choose track and number of laps
	int track = randInt(LAPSLENGTH);
	int laps = lapspertrack[track];
	
	//Choose weather (default: 10% chance of rain)
	int rain;
	if(randInt(9) == 0){
		rain = 1;
	}else{
		rain = 0;
	}
	
	//Print starting grid, track, number of laps and weather
	printf("The starting grid is: ");
	for(i=0;i<LINEUPLENGTH;i++){
		printf("%d, ", sgrid[i]);
	}
	printf("\nTrack ID: %d\n", track);
	printf("Laps: %d\n", laps);
	printf("Is raining: %d\n", rain);
	printf("Is Verstappen unbeatable: %d\n", verstappen);
	
	/*LIST OF EVENT IDS AND PARAMETERS:
	0: Overtake, OvertakingDriver, OvertakenDriver
	1: Mistake, Driver, PositionsLost
	2: Incident, CausingDriver, VictimDriver
	3: Crash, Driver
	4: Pitstop, Driver, PositionsLost
	5: Penalty, CausingDriver, PenaltyType
	6: NextLap
	7: TsunodaSpecialDNF
	(Every event requires two parameters, but the ones that use less than two will ignore any unused parameters)
	Penalty types: 
	0: Nothing
	1: Penalty
	2: DSQ
	*/
	
	/*Define pitstop array. Follows the same order as the driver lineup. The array contains the laps in which the driver will do a pitstop.
	Only one pitstop should be done in a single lap, and pitstops are not allowed in the first and last laps. If any violation is found, the value is changed.
	Values in every row are sorted, but unused values are ignored. In theory this should work just fine, if anything is wrong, blame RNGesus :\   */
	int pitstops[LINEUPLENGTH][2];
	for(i=0;i<LINEUPLENGTH;i++){
		for(j=0;j<2;j++){
			pitstops[i][j] = randInt(laps - 2) + 1;
			if(j == 1){
				if(pitstops[i][0] == pitstops[i][1]){
					pitstops[i][1]++;
				}else if(pitstops[i][0] > pitstops[i][1]){
					arraySwap(pitstops[i], 0, 1);
				}
			}
		}
		printf("\nDriver %d\'s pitstops: ", lineup[i]);
		for(j=0;j<2;j++){
			printf("%d, ", pitstops[i][j]);
		}
	}
	
	//Small chance of Tsunoda being unable to start the race because he can't reach the pedals (default: 1 in 4000)
	int activeDrivers = LINEUPLENGTH;
	if(randInt(4000) == 0){
		printf("\nTsunoda can't start the race because he can\'t reach the pedals!");
		int tsunodaPos = arrayLookup(sgrid, 22);
		for(i=0;i<activeDrivers - 1 - tsunodaPos; i++){
			arraySwap(sgrid, tsunodaPos + i, tsunodaPos + i + 1);
		}
		activeDrivers--;
	}
	
	//Initialize crashed drivers array
	int crashedDrivers[LINEUPLENGTH];
	for(i=0;i<LINEUPLENGTH;i++){
		crashedDrivers[i] = 0;
	}
	
	//Main loop
	int overtakes, temp, temp2;
	int incidents = 0;
	int eventArray[ARRAYLENGTH];
	int currentLapPitstops[LINEUPLENGTH];
	int incidentArray[MAXINCIDENTS][2];
	for(i=0;i<laps;i++){
		//Beggining of the current lap
		printf("\n\n---LAP %d---", i+1);
		
		//OVERTAKES
		//Choose amount of overtakes. Follows a binomial distribution with n=3, p=0.4.
		overtakes = 0;
		for(j=0;j<3;j++){
			if(randInt(10) < 4){
				overtakes++;
			}	
		}
		
		//Choose random driver to overtake, perform the overtake in the grid array, and write that to the output CSV file.
		for(j=0;j<overtakes;j++){
			//If it rains, the overtaking driver has a 1 in 4 chance to be Alonso
			if(rain == 1 && arrayLookup(sgrid, 14) != 0 && randInt(3) == 0){
				randDriver = arrayLookup(sgrid, 14);
			}else{
				randDriver = randInt(activeDrivers - 2) + 1;
			}
			//If Stroll tries to overtake Alonso, there is a 50% chance for the overtake to be skipped
			if(arrayLookup(sgrid, randDriver) != 18 || randInt(1) != 0){
				if(verstappen == 0 || randDriver != 1){
					eventArray[0] = 0;
					eventArray[1] = sgrid[randDriver];
					eventArray[2] = sgrid[randDriver - 1];
					arraySwap(sgrid, randDriver, randDriver - 1);
					printf("\nDriver %d overtakes %d!\nLeaderboard: ", sgrid[randDriver - 1], sgrid[randDriver]);
					printArray(sgrid, LINEUPLENGTH);
				}
			}
		}
			
		
		//MISTAKES
		/*Choose a random driver to make a mistake and lose positions. Positions lost follow a binomial distribution with n=6, p=0.3.
		Drivers who would end up in a position lower than 20th exist are excluded from the driver selection algorithm. (Default chance of mistake per lap: 4%)*/
		if(randInt(100) < 4){
			eventArray[0] = 1;
			eventArray[2] = 0;
			for(j=0;j<6;j++){
				if(randInt(10) < 3){
					eventArray[2]++;
				}
			}
			randDriver = randInt(activeDrivers - eventArray[2] - 1);
			eventArray[1] = lineup[randDriver];
			for(j=0;j<eventArray[2];j++){
				arraySwap(sgrid, randDriver + j, randDriver + j + 1);
			}
			printf("\nDriver %d makes a mistake and loses %d position(s)!\nLeaderboard: ", sgrid[randDriver + eventArray[2]], eventArray[2]);
			printArray(sgrid, LINEUPLENGTH);
		}
		
		//INCIDENTS
		/*Choose a random driver to cause an incident and get a penalty, giving them a chance to lose a position when the race ends. A maximum of 5 incidents can happen
		in a race (let's say the stewards don't have time for that) (Default chance of incident per lap: 2%)*/
		if(randInt(100) < 2 && incidents < MAXINCIDENTS){
			switch(randInt(10)){
				case 0:
					randDriver = arrayLookup(sgrid, 20);
					break;
				case 1:
					randDriver = arrayLookup(sgrid, 31);
					break;
				case 2:
					randDriver = arrayLookup(sgrid, 63);
					break;
				default:
					randDriver = randInt(activeDrivers - 1);
					break;
			}
			eventArray[0] = 2;
			eventArray[1] = sgrid[randDriver];
			switch(randDriver){
				case 0:
					eventArray[2] = sgrid[randDriver + 1];
					break;
				case 19:
					eventArray[2] = sgrid[randDriver - 1];
					break;
				default:
					if(randInt(1) == 0){
						eventArray[2] = sgrid[randDriver - 1];
					}else{
						eventArray[2] = sgrid[randDriver + 1];
					}
					break;
			}
			incidentArray[incidents][0] = eventArray[1];
			incidentArray[incidents][1] = eventArray[2];
			printf("\nDriver %d has caused an incident against %d!", eventArray[1], eventArray[2]);
			incidents++;
		}
		
		//CRASHES
		//Choose a random driver to crash. The driver will fall to the last active place. (Default chance: 2%, Default rain bonus: 0.5%)
		if(randInt(1000) < 20 + 5 * rain){
			//1 in 4 chance of forcing the crashing driver to be Sargeant
			//If Leclerc is 15th or worse, there is a 1 in 6 chance of forcing the crashing driver to be him
			if(randInt(3) == 0){
				randDriver = 2;
			}else if(arrayLookup(sgrid, 16) > 14 && randInt(5) == 0){
				randDriver = 16;
			}else{
				randDriver = randInt(activeDrivers - 1);
			}
			eventArray[0] = 3;
			eventArray[1] = sgrid[randDriver];
			eventArray[2] = 0;
			if(crashedDrivers[arrayLookup(lineup, eventArray[1])] == 0){
				crashedDrivers[arrayLookup(lineup, eventArray[1])] = 1;
				for(j=0;j < activeDrivers - 1 - randDriver; j++){
					arraySwap(sgrid, randDriver + j, randDriver + j + 1);
				}
				printf("\nDriver %d has crashed!\nLeaderboard: ", eventArray[1]);
				printArray(sgrid, LINEUPLENGTH);
				activeDrivers--;
			}
		}
		
		//PITSTOPS
		//Look for the current lap in the pitstop array. The array will be ignored in the first lap. Positions lost on pitstop follow same distribution as mistakes. Crashed drivers can't pitstop.
		if(i > 0 && i < laps - 1){
			printf("\nThe following drivers are performing a pitstop: ");
			for(j=0;j<LINEUPLENGTH;j++){
				temp = 0;
				if(pitstops[j][0] == i || pitstops[j][1] == i){
					eventArray[0] = 4;
					eventArray[1] = lineup[j];
					eventArray[2] = 0;
					printf("%d ", eventArray[1]); 
					temp = arrayLookup(sgrid, eventArray[1]);
					//Zhou and Bottas have a 1 in 3 chance of falling to last place after a pitstop
					if(eventArray[1] == 24 || eventArray[1] == 77){
						if(randInt(2) == 0){
							eventArray[2] = activeDrivers - temp - 1;
						}else{
							for(k=0;k<6;k++){
								if(randInt(10) < 3 && temp + k < activeDrivers - 1){
									eventArray[2]++;
								}else{
									break;
								}
							}
						}
					}else{
						for(k=0;k<6;k++){
							if(randInt(10) < 3 && temp + k < activeDrivers - 1){
								eventArray[2]++;
							}else{
								break;
							}
						}
					}
					printf("(%d positions lost), ", eventArray[2]);
					for(k=0;k<eventArray[2];k++){
						arraySwap(sgrid, temp + k, temp + k + 1);
					}
				}
			}
			printf("\nLeaderboard: ");
			printArray(sgrid, LINEUPLENGTH);
		}
	}
	printf("\n\n---END OF RACE---");
	
	//Apply penalties. (Default weights: 60% penalty, 5% DSQ, 35% nothing)
	for(i=0;i<incidents;i++){
		eventArray[0] = 5;
		eventArray[1] = incidentArray[i][0];
		temp = randInt(99);
		temp2 = 0;
		//Hamilton will never get a penalty (the FIA is biased towards him)
		if(temp < 34 || eventArray[1] == 44){
			eventArray[2] = 0;
			printf("\nDriver %d got away with his incident!", eventArray[1]);
		}else if(temp < 39){
			eventArray[2] = 2;
			temp2 = arrayLookup(sgrid, eventArray[1]);
			printf("\nDriver %d has been disqualified from the race!", eventArray[1]);
			for(j=0; j < LINEUPLENGTH - 1 - temp2; j++){
				arraySwap(sgrid, temp2 + j, temp2 + j + 1);
			}
		}else{
			eventArray[2] = 1;
			temp2 = arrayLookup(sgrid, eventArray[1]);
			printf("\nDriver %d has received a penalty and lost a position!", eventArray[1]);
			if(temp2 < LINEUPLENGTH - 1){
				arraySwap(sgrid, temp2, temp2 + 1);
			}
		}
	}
	
	printf("\nThe following drivers have crashed: ");
	for(i=0;i<LINEUPLENGTH;i++){
		if(crashedDrivers[i] == 1){
			printf("%d, ", lineup[i]);
		}
	}
	
	printf("\n\nFINAL LEADERBOARD: ");
	printArray(sgrid, LINEUPLENGTH);
	
	printf("\nPress any key to exit...");
	getchar();
}

//This piece of crap of an app was made by EinjelFrei and commissioned by an anonymous user.
