#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <ctime>
#include <string>
#include <cctype>
#include <stdlib.h>

using namespace std;


class Node {	//κλάση για κάθε κόμβο της λίστας
public:
	int index;		//θέση κόμβου
	int x, y, sec;		//τροχία
	Node* next;	//το επόμενο στοιχείο της λίστας
	Node() {		//default κατασκευαστής
		index = 0;
		sec = 0;
		x = 0;
		y = 0;
		next = NULL;
	}
	Node(int i, int s, int x0, int y0) { //κατασκευαστής με παραμέτρους
		index = i;
		sec = s;
		x = x0;
		y = y0;
	}
};
class Chain {		//κλάση αλυσίδας
public:
	Node* head;		//πρώτο στοιχείο
	Node* day[14] = {};	//πρώτοσ κόμβος μετά από την αλλαγή της ημέρας
	Chain() {		//default κατασκευαστής
		head = NULL;
	}
	Chain(Node* n) {	//κατασκευστής με παραμέτρους
		head = n;	
	}
	void newDay(Node* n, int d) {	//προσθήκη στοιχείου της αρχής μιας ημέρας
		day[d] = n;
	}
	Node* NodeExists(int k) {	//έλεγχος για να μην έχουμε 2 κόμβους στην ίδια θέση
		Node* tmp = NULL;		//προσωρινή μεταβλητή 
		Node* pointer = head;	//αρχή της λίστας
		while (pointer != NULL) {	//προσπέλαση αλυσίδας
			if (pointer->index == k) {	//αν βρεθεί ίδιος δείκτης
				tmp = pointer;	//η μεταβλητή tmp γίνεται ίση με τη διεύθυνση του κόμβου που τον έχει
			}
			pointer = pointer->next;	//πάμε στον επόμενο κόμβο
		}
		return tmp;		//επιστρέφει ,αν υπάρχει, την διεύθυνση με θέση κ 
	}
	void appendNode(Node* n) {	//προσθήκη κόμβου στο τέλος της αλυσίδας
		if (NodeExists(n->index) != NULL) {	//αν υπάρχει ήδη κόμβος σε αυτή το δείκτη,δεν προσθέτεται
			cout << "There is already a node with key ->" << n->index << "time " << n->sec << endl;
		}
		else {
			if (head == NULL) {	//αν η λίστα είναι κενή
				head = n;	//η αρχή της γίνεται ο κόμβος που μόλις προσθέσαμε
			}
			else {	//αλλίώς θα προσπελάσουμε τη λίστα(άρχή ως τέλος)
				Node* ptr = head;	//θέτουμε μια μεταβλητή ίση με το δείκτη της αρχής της λίστας
				while (ptr->next != NULL) {	//ψάχνουμε το τέλος της λίστας
					ptr = ptr->next;
				}
				ptr->next = n;	//ο κόμβος δείχνει στον επόμενο
			}
		}
	}
	void insertNode(int k, Node* n) { //προσθήκη κόμβου μετά από κόμβο με δείκτη Κ
		Node* ptr = NodeExists(k);		//βρίσκουμε τη διεύθυνση του κόμβου με δείκτη Κ
		if (ptr != NULL) {		//αν υπάρχει τέτοιος κόμβος
			if (NodeExists(n->index) == NULL) {	//και δν υπάρχει κόμβος με δείκτη ίδιο με αυτόν που είναι να προσθεθεί
				n->next = ptr->next;	//ο νέος δείχνει τον επόμενο κόμβο του παλαιού
				ptr->next = n;	//ο παλιός τον νέο κόμβο
			}
		}
	}
	void deleteNode(int position) {	//διαγραφή κόμβου με θέση(pos) από τη λίστα 
		Node* temp = NULL;		//αρχικοποίση προσωρινής μεταβλητής
		Node* previousNode = head;	//ο προηγούμενος κόμβος είναι αρχικά ο πρώτος
		Node* currentPos = head->next;	//τρέχουσα θέση, είναι ο 2ος κόμβος
		while (currentPos != NULL) {	// προσπέλαση λίστας
			if (currentPos->index == position) {	//ο κόμβος βρέθηκε
				temp = currentPos;		//η διεύθυνση αποθηκεύεται στην προσωρινή μεταβλητή temp
				currentPos = NULL;		// η προσπέλαση θα σταματήσει
			}
			else {	
				previousNode = previousNode->next;	// η νέα προηγούμενη θέση είναι η επόμενη της παλιάς
				currentPos = currentPos->next;	//πάμε στον επόμενο κόμβο
			}
		}
		if (temp != NULL) {			//έχει βρεθεί ο κόμβος που ψάχνουμε
			previousNode->next = temp->next;	// αποσυνδέεται από τη λίστα
			delete temp;	//διαγραφή κόμβου
		}
	}
	void  REPAIR(int i) {	//επισκευή λίστας, με όρισμα την ημέρα στην οποία γίνεται η επισκευή
		Node* ptr = day[i];	//δείκτης που δείχνει στην αρχή της ημέρας
		while (ptr->next != NULL) {	//προσπέλαση λίστας(αρχή της ημέρας ως τέλος)
			if (ptr->next->sec - ptr->sec > 30) {	//ώσπου να βρω 2 κόμβους με διαφορά μεγαλύτερη ίση των 30 δευτ.
				int numOfNodesToAdd = floor((ptr->next->sec - ptr->sec) / 30);	//αριθμός κόμβων που θα προσθεθεί
				int currentKey = ptr->index;	//τρέχουσα θέση κόμβου που είμαστε
				for (int i = 1; i <= numOfNodesToAdd; i++) {		//επανάληψη προσθήκης κόμβων που χρειάζεται 
					Node* n0 = new Node();	//δημιουργία αντικειμένου τύπου Node*
					n0->index = currentKey + 1;	//ο νέος κόμβος θα έχει νέο κλειδί μεγαλύτερο κατά ένα
					n0->x = (ptr->next->x - ptr->x) * i / numOfNodesToAdd + ptr->x;		//υπολογισμός του x
					n0->y = (ptr->next->y - ptr->y) * i / numOfNodesToAdd + ptr->y;		//υπολογισμός του y
					n0->sec = ptr->sec + 30 * i;	//υπολογισμός sec
					insertNode(currentKey, n0);		//προσθήκη στην αλυσίδα
					currentKey = n0->index;	//ο νέος δείκτης δείχνει τον κόμβο που μόλις προσθέσαμε
				}
			}
			ptr = ptr->next;	//πηγαίνουμε στον επόμενο κόμβο
		}
	}
	void SUMMARIZE_TRAJECTORY(int d, int dBefore) {	//περίληψη
		if (d - dBefore >= 0) {	//αν έχει περάσει ένα ορισμένο χρονικό διάστημα
			Node* start = day[d - dBefore];	//η αρχή της ημέρας
			Node* end = day[d - dBefore + 1];	//η αρχή της επόμενης ,και άρα το τέλος αυτής
			int Radius = 6000;		//η ακτίνα που θα ελέγχεται
			Node* PointOfView = start;	//το στίγμα
			while (start!= end)		//μέχρι να φτάσουμε στην αρχή της επόμενης μέρας
			{
				if (start->next != end) {	//αν ο επόμενος κόμβος δεν είναι ο τελευταίος
					if (sqrt(pow(start->next->x - PointOfView->x, 2)+ pow(start->next->y - PointOfView->y,2)) < Radius) {	//αν αυτό το στίγμα απέχει λιγότερο από R,από το αρχικό
						deleteNode(PointOfView->next->index);		//διαγράφη στίγματος
					}
					else {
						PointOfView = start->next;			//γίνεται το νέο στίγμα αναφοράς
					}
				}
				start = start->next;	//πηγαίνουμε στον επόμενο κόμβο
			}
				
		}
	}


};

int FIND_CROWDED_PLACES(int timeToLookFor, int Until, int x1, int y1, int x2, int y2, int Minimum_Stay, Node** locations) {
	int TotalPeople = 0;	// ο αριθμός των ατόμων που βρέθηκαν εκεί
	int duration = 0;		//διάρκεια
	for (int i = 0; i < 100; i++) {		
		while (locations[i] != NULL) {		// προσπέλαση λίστας κάθε χρήστη
			if (locations[i]->sec >= timeToLookFor && locations[i]->sec <= Until) {	// αν η προσπέλαση είναι εντός επιθυμητών χρονικών ορίων 
				if (locations[i]->x >= x1 && locations[i]->x <= x2 && locations[i]->y <= y2 && locations[i]->y >= y1) {	//αν πληρή της προυποθέσεις που θα βάλει ο χρήστης
					duration+=30;	//η διάρεκια αυξάνεται (κάθε κόμβος μετρά για 30 δευτ.)
					if (duration >= Minimum_Stay) {	//αν η διάρκεια ξεπερνά το ελάχιστο χρονικό διάστημα που έθεσε ο χρήστης
						TotalPeople++;	// το άτομο προσθέται 
						break;	//πάμε στο επόμενο
					}
				}
				else {	
					duration = 0;	// η διάρκεια μηδενίζεται
				}
			}
			locations[i] = locations[i]->next;		//πάμε στον επόμενο χρήστη
		}

	}
	return TotalPeople;		//επιστρέφει το σύνολο των χρηστών που αναζητήσαμε
}
	


int POSSIBLE_COVID_19_INFECTION(Node* inHealth, Node* inCovid_19, int user, int leftFromYesterday) {
	int counter = 1;	//τρέχον κόμβος στην αλυσίδα του υγιή χρήστη
	bool flag = false;	//υποψία για κορονοιό
	double duration = leftFromYesterday;	//διάρκεια παραμονής κοντά σε άρρωστο ,ίση με χθεσινή
	while (inHealth->next != NULL) {	//προσπέλαση αλυσίδας υγιούς ατόμου
		Node* tmp = inCovid_19;			//προσωρινή μεταβλητή ίση με την αρχή της αλυσίδας του αρρώστου
		int counter2 = 1;		//τρέχον κόμβος στην αλυσίδα του ασθενούς
		while (counter2 <= counter && tmp->next != NULL) {	//συγκρίνουμε όλους τους κόμβους του ασθενή με τους υγιή που βρίσκονται σε μικρότερη θέση
			if (counter - counter2 <= 600) {	//αν η χρονική διαφορά ειναι μικρότερη-ίση από 5 ώρες 300 λεπτά επί 2 30λεπτα σε κάθε ένα => 300*2 = 600
				double distanceBetween = sqrt(pow(tmp->x - inHealth->x, 2) + pow(tmp->y - inHealth->y, 2));	//υπολογισμός απόστασης
				if (distanceBetween < 1000) {	//αν είναι μικρότερη από 400 μ.
					duration+=30;	//η διάρκεια παραμονής κοντά στον ασθενή αυξάνεται
					if (duration >= 90) {	//αν η συνολική διάρκεια είναι μεγαλύτερη από 1,5 λεπτό
						flag = true;		//ο χρήστης ίσως κόλλησε Covid-19
					}
				}
				else {
					duration = 0; //αν η απόσταση είναι μικρότερη από 400
				}
				leftFromYesterday = duration;		//αν είμαστε στο τέλος της μέρας προσθέτεται στην επόμενη
			}
			counter2++;	//αύξηση μετρητή της αλυσίδας του ασθενούς
			tmp = tmp->next;	//πάμε στον επόμενο κόμβο
		}
		counter++;		//αύξηση του μετρητή του υγιούς
		inHealth = inHealth->next;	//πάμε στον επόμενο κόμβο του υγιούς χρήστη
		if (flag == true) {	//αν έχει μολυνθεί 
			cout << user<<" ";
			break;	// ο έλεγχος σταματάει
		}
	}
	return leftFromYesterday;	//επιστρέφει διάρκεια που έμεινε ,ώστε να προσθεθεί στην επόμενη μέρα
}

void randomMovement(int& x11, int& y11) {	//pass by reference ώστε να αλλάζουν οι τιμές και στη main
	int extraDistance = 27 + rand()%21; //κίνηση 27μ - 48μ αν΄α 30 δευτ
	int situation = rand() % 5;	//επιλογή τυχαίας κατάστασης(κίνηση ή όχι)
	switch (situation) {
	case 1:
		//κίνηση
		x11 += extraDistance;
		break;
	case 2:
		//κίνηση
		x11 -= extraDistance;
		break;
	case 3:
		//κίνηση
		y11 -= extraDistance;
		break;
	case 4:
		//κίνηση
		y11 += extraDistance;
		break;
	default:
		//καμία κίνηση
		break;
	}
	//έλεγχος για κίνηση εντός ορίων
	if (x11 <= 0) {	//το χ ξεπέρασε το όριο 
		x11 += extraDistance;
	}
	if (x11 >= 12000) {	//το χ ξεπέρασε το όριο 	
		x11 -= extraDistance;
	}
	if (y11 <= 0) {	//το y ξεπέρασε το όριο 
		y11 += extraDistance;
	}
	if (y11 >= 12000) {	//το y ξεπέρασε το όριο 
		y11 -= extraDistance;
	}
}

int main() {
	system("COLOR f3"); // αλλαγή χρώματος
	//μεταβλητές
	int seconds_from_user, seconds_from_user2, x1_u, y1_u, x2_u, y2_u, Minimum_Stay_Duration; // για την συνάρτηση FIND_CROWDED_PLACES
	bool stop = false;	//για να σταματήσει η δυνατότητα του χρήστη να χρησιμοποιεί την FIND_CROWDED_PLACES
	string answer;	// αν θέλει ο χρήστης να χρησιμοποιήσει την FIND_CROWDED_PLACES
	int totalUsers = 100;	//σύνολο χρηστών
	int totalDays = 14;	//σύνολο ημερών
	srand(time(0));
	int x11[totalUsers],y11[totalUsers];	//συντεταγμένες για κάθε χρήστη
	int leftovers[totalUsers] = { 0 };		//ότι έμεινε από την προηγούμενη μέρα από την POSSIBLE_COVID_19_INFECTION
	Node* sick[totalDays];		// πίνακας για τη τοποθεσία του ασθενούς στην αρχή κάθε μέρας
	Node* whereWasUser[totalUsers] = {}; //πίνακας για την τοποθεσία των χρηστών στην αρχή κάθε ημέρας
	Chain obj[totalUsers];	// πίνακας με τις αλυσίδες των χρηστών 
	for (int days = 0; days < totalDays; days++) {
		cout<<endl<<"-_-_-_-_-_-_-_-_-_-_-_-_--_-_-_-_-_-_-_-_-_-_-_-_--_-_-_-_-_-_-_-_-_-_-_-_-"<<endl;	
		cout << endl << "~DAY " << days + 1 <<"~"<< endl;											 	//	για εμφάνιση
		cout << "CHAINS REPAIRED SUCCESFULLY" << endl;												 
		cout<<"USERS WITH POSSIBLE INFECTION : ";													 
		for (int users = 0; users < totalUsers; users++) {
			int seconds = 0;
			if(days == 0 ){
				x11[users] = rand() % 12000;	//ο χρήστης αρχίζει από μια τυχαία θέση 
				y11[users] = rand() % 12000;	//ο χρήστης αρχίζει από μια τυχαία θέση 
			}
			while (seconds < 2880) {
				Node* n1 = new Node();	//νέο αντικείμενο τύπου Node*
				int random = rand() % 10 + 1; // αν random == 10 το σήμα χάνεται
				if (random < 9 || seconds == 0 || seconds == 2850) {	//το σήμα GPS είναι καλό
					randomMovement(x11[users], y11[users]);	//τυχαία κίνηση 3-6χλμ/ώρα
					//εισαγωγή δεδομένων στον κόμβο
					n1->sec = seconds;
					n1->x = x11[users];
					n1->y = y11[users];
					n1->index = floor(seconds / 30) + days * 2880; //εισαγωγή και υπολογισμός χρονικής στιγμής
					obj[users].appendNode(n1);	//προσθήκη στην αλυσίδα
					if (seconds == 0) {
						whereWasUser[users] = n1;	// κόμβος που δείχνει στην αρχή της ημέρας
						if (users == 0) {
							sick[days] = n1;	//κόμβος που δείχνει στην αρχή της ημέρας για τον ασθενή
						}
					}
				}
				if (seconds == 0) {
					obj[users].newDay(n1, days);	//αν είναι η αρχή κάποιας ημέρας αποθηκεύεται μόνιμα(σε αντίθεση με το wherewasuser που αλλάζει κάθε μέρα)
				}
				seconds += 30;
			}
			obj[users].REPAIR(days);
			if (users != 0) { //αν ο χρήστης δεν είναι ο άρρωστος
				leftovers[users] = POSSIBLE_COVID_19_INFECTION(whereWasUser[users], sick[days], users, leftovers[users]); // το υπόλοιπο της δίαρκειας αποθηκεύεται
			}
			obj[users].SUMMARIZE_TRAJECTORY(days,10);	//κλήση της συνάρτησης SUMMARIZE_TRAJECTORY
		}
		if (stop == false) {
			cout <<endl<< "Do you want to find crowded places?( ans : yes(-yes-)/don't ask again(-STOP-)/no(anything else...))" << endl;//εισαγωγή δεδομένων από το χρήστη
			cin >> answer;
			if (answer == "yes") {
				system("COLOR f9");
				cout << "From...to... (in seconds(0-86400))" << endl;
				cin >> seconds_from_user >> seconds_from_user2;
				cout << "What is your region of interest ?(x1,y1,x2,y1(0-12000))" << endl;
				cin >> x1_u >> y1_u >> x2_u >> y2_u;
				cout << "Minimum stay duration?(in seconds(0-86400))" << endl;
				cin >> Minimum_Stay_Duration;
				if (x1_u > x2_u) swap(x1_u, x2_u);	
				if (y1_u > y2_u) swap(y1_u, y2_u);
				cout << FIND_CROWDED_PLACES(seconds_from_user, seconds_from_user2, x1_u, y1_u, x2_u, y2_u, Minimum_Stay_Duration, whereWasUser) <<" PEOPLE WHERE THERE"<< endl;
			}
			else if (answer == "STOP") {	//δυνατότητα να μην του ξαναγίνει ερώτηση
				stop = true;
				system("COLOR cf");
			}else{
				system("COLOR 84");		//άκυρη απάντηση
			}
		}
		if (days - 10 >= 0) {
			cout <<endl<< "SUM OF DAY " << days - 10 + 1 << " SUCCESFULLY DONE" << endl;
		}	
	}
	return 0;
}
