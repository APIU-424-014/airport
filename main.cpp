#include <iostream>
#include <cstdlib>		//system()

using namespace std;

struct plane{
	bool fly;
	int id;
};

struct runway{
	bool occupied=false;
	int occupiedBy=NULL;
	int id;
};

void initialAirport(plane*, runway*);
void overview(plane*, runway*);
void starting(plane*, runway*);
void landing(plane*, runway*);
void clearScreen();

int main(){
	short all=5;
	short uChoice;
	plane pl[all];
	runway rw[all];
	
	initialAirport(&pl[0], &rw[0]);

	clearScreen();
	while(uChoice!=-1){
		
		cout<<"\n############################\n"
			"###\t### MENU ###\t###\n############################\n"
			"\n### 1\t Starting\n### 2\t Langing\n### 3\t Airport Overview\n"
			"### -1\t Exit Game!\n"
			"\n############################\n";
		//USER INPUT AND ERROR HANDLING
		while(!(cin>>uChoice && uChoice!=0 && uChoice>-2 && uChoice<4)){
			cout<<"error: falsche Eingabe! Try again:\t";
		}
		
		clearScreen();
		switch(uChoice){
			case 1:
				starting(&pl[0], &rw[0]);
				break;
			case 2:
				landing(&pl[0], &rw[0]);
				break;
			case 3:
				overview(&pl[0], &rw[0]);
			default:
				break;
		}
	}
}

void initialAirport(plane *p, runway *r){
	for(short i=0;i<5; i++){
		p[i].id=i+222;
		if(i%2){
			p[i].fly=true;
		}else{
			p[i].fly=false;
		}
	}
	for(short i=0; i<5; i++){
		if(p[i].fly){
			r[i].id=i+1;
			r[i].occupied=false;
		}else{
			r[i].id=i+1;
			r[i].occupied=true;
			r[i].occupiedBy=p[i].id;
		}
	}
}

void overview(plane *p, runway *r){
	cout<<"\nUebersicht Flughafen\n############################\n";
	for(short i=0; i<5; i++){
		cout<<"\nRunway ~"<<r[i].id<<"~ ist";
		if(r[i].occupied){
			cout<<" belegt! von Flugzeug: -="<<r[i].occupiedBy<<"=-";
		}else{
			cout<<" frei!"; 
		}
	}
	cout<<endl;
	for(short i=0; i<5; i++){
		if(p[i].fly){
			cout<<"\nFlugzeug -="<<p[i].id<<"=- ist in der Luft!";
		}
	}
	cout<<endl<<endl;
}

void starting(plane *p, runway *r){
	short fn, rn;
	cout<<"\nFlugzeug starten lassen\n############################\n";
	cout<<"\nGib die Runway Nummer und Flugzeug Nummer an\n";
	cout<<"Runway:\t\t";
	//USER INPUT & ERROR HANDLING
	while(!(cin>>rn && rn<6 && rn>0)){
		cout<<"error: Runway existiert nicht! Try again:\t";
	}
	rn=rn-1;
	cout<<"Flugzeug:\t";
	
	while(!(cin>>fn && fn<227 && fn>221)){
		cout<<"error: FLugzeug existiert nicht! Try again:\t";
	}
	cout<<endl;
	
	if(!(r[rn].occupied)){
		cout<<"Runway ~"<<rn+1<<"~ ist nicht belegt!";
	}else if(r[rn].occupiedBy==fn){
		cout<<"Flugzeug -="<<fn<<"=- ist gestartet!";
		r[rn].occupied=false;
		r[rn].occupiedBy=NULL;
		p[fn-222].fly=true;
	}else{
		cout<<"Flugzeug -="<<fn<<"=- steht nicht auf dem Runway!";
	}
	cout<<endl<<endl;
}

void landing(plane *p, runway *r){
	short fn, rn;
	cout<<"\nFlugzeug landen lassen\n############################\n";
	cout<<"\nGib die Flugzeug Nummer und die Runway Nummer an\n";
	cout<<"Flugzeug:\t";
	//USER INPUT & ERROR HANDLING
	while(!(cin>>fn && fn<227 && fn>221)){
		cout<<"error: Flugzeug existiert nicht! Try again:\t";
	}
	cout<<"Runway:\t\t";
	//cin>>rn;
	while(!(cin>>rn && rn<6 && rn>0)){
		cout<<"error: Runway existiert nicht! Try again:\t";
	}
	rn=rn-1;
	cout<<endl;
	
	if(!(p[fn-222].fly)){
		cout<<"Flugzeug -="<<fn<<"=- ist nicht in der Luft!";
	}else if(r[rn].occupied){
		cout<<"Runway ~"<<rn+1<<"~ ist belegt!";
	}else{
		cout<<"Flugzeug -="<<fn<<"=- ist sicher auf Runway ~"<<rn+1<<"~ gelandet!";
		p[fn-222].fly=false;
		r[rn].occupied=true;
		r[rn].occupiedBy=fn;
	}
	cout<<endl<<endl;
}

void clearScreen(){
#ifdef WINDOWS
		system("cls");
#else
		system("clear");
#endif
}
