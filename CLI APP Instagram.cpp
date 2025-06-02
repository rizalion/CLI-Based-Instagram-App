#include<iostream> // Input Output
#include<fstream> // File Handling
#include<conio.h> // Console Input Output 
#include <iomanip> //Manipulators
#include<string>

using namespace std;
const int maxaccount = 100;
struct Account{
	string name;
	string username;
	int age;
	string dob;
	string gender;
	string email;
	string password;
	string rating;
	int follower = 0;
	int following = 0;
	void showpost();
	
	 struct Post {
        string tweet;
        Post* next = NULL;        
        // Constructor to initialize a post with a tweet
        Post(const string& t) : tweet(t), next(NULL) {}
    } * head = NULL; // Each account has its own post list
};

Account account[maxaccount];

class insta{
public:
void createaccount();
void login();
void follow();
void createpost();
void deletepost(); 
void message(); 
void viewprofile();
void deleteaccount(); 
void rateapp();
void logout();
};      
static int count = 0;
static int loggedInIndex = -1;
static int ctpost = 0;  //count for posts
//create account
void insta::createaccount(){
    Account newacc;
    cout<<"Enter your name: ";
    cin>>newacc.name;
    int i=1;
    while (i==1)
    {
    cout<<"Enter your age: ";
    cin>>newacc.age;
    if(newacc.age<16){
        cout<<"You are not eligible to create account"<<endl;
    }
    else{
        i=0;
    }
}
    cout<<"Create username: ";
    cin>>newacc.username;
    cout<<"Enter date of birth(dd/mm/yyyy): ";
    cin>>newacc.dob;
    
        int j=1;
    while (j==1)
    {
    cout<<"Gender(male/female): ";
    cin>>newacc.gender;
    if(newacc.gender == "male"|| newacc.gender == "female" ){
    j=0;
    }
    else{
        cout<<"Enter valid gender"<<endl;
    }
}
	cout<<"Enter email: ";
	cin>>newacc.email;
	cout<<"Password: ";
	cin>>newacc.password;
	
	account[count] = newacc;
	count++;
	cout << "Account created successfully!\n";
}

//login
void insta::login() {
    if (count == 0) {
        cout << "No accounts available. Please create an account first.\n";
        return;
    }
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    loggedInIndex = -1;
    for (int i = 0; i < count; i++) {
        if (account[i].username == username && account[i].password == password) {
            loggedInIndex = i;
            break;
        }
    }

    if (loggedInIndex == -1) {
        cout << "Invalid username or password.\n";
        return;
    }

    cout << "Login successful! Welcome, " << account[loggedInIndex].name << "!\n";
    // Logged-in user menu
    int choice;
    do {
        cout << "\n--- Logged-in Menu ---\n";
        cout << "1. Follow\n";
        cout << "2. Post\n";
        cout << "3. Delete Post\n";
        cout << "4. View Profile\n";
        cout << "5. Message\n";
        cout << "6. Delete Account\n";
        cout << "7. Rate App\n";
        cout << "8. Logout\n";
        cout << "9. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: 
                follow();
                break;
            case 2: 
                createpost();
                break;
            case 3: 
                deletepost();
                break;
            case 4: 
                viewprofile();
				break;
            case 5: 
                message();
                break; 
            case 6: 
                deleteaccount();
                return; // Exit login after account deletion
            case 7: 
            rateapp();
            	break;
            case 8:
                logout();
                return;
            case 9:
            	cout<<"\n--- Exiting Logged-in Menu ---\n";
            	return;
            default: 
                cout << "Invalid choice. Try again.\n";
                break;
        }
    } while (choice!=9);
}

//follow
void insta::follow() {
    if (loggedInIndex == -1) {
        cout << "Please log in to follow users.\n";
        return;
    }

    string Username;
    cout << "Enter the username to follow: ";
    cin >> Username;
    //check does that username exist
    for(int i=0; i<count;i++){
    if(Username == account[i].username){
    	account[i].follower++;
    	account[loggedInIndex].following++;
    cout << "You are now following " << Username << ".\n";
    return;
}
}
	cout<<"This username does not exist"<<endl;
}

// Create Post
void insta::createpost() {
    if (loggedInIndex == -1) {
        cout << "Please log in to create a post.\n";
        return;
    }
	
    cout << "Share Your Thoughts: ";
    cin.ignore();
    string tweet;
    getline(cin, tweet);

    Account::Post* newpost = new Account::Post{tweet};
    Account::Post*& head = account[loggedInIndex].head;

    if (head == NULL) {
        head = newpost;
    } else {
        Account::Post* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newpost;
    }
    ctpost++;
    cout << "Post created successfully!\n";
}
void Account::showpost() {
    Post* temp = head; // Access the head of this account
    int ct=1;
    while (temp != NULL) {
        cout <<ct<<". "<< temp->tweet << endl; // Print the tweet
        temp = temp->next;          // Move to the next post
    	ct++;
	}
}

//Delete post
void insta::deletepost(){
	Account::Post*& head = account[loggedInIndex].head;
	if(head==NULL){
		cout<<"No post to delete"<<endl;
		return;
	}
	cout<<"Your Posts: "<<endl;
	account[loggedInIndex].showpost();
	int postnum;
	cout<<"Enter a post number to delete: ";
	cin>>postnum;
	
	Account::Post* temp = head;
    if (postnum == 1) {
        // Delete the first post
        head = head->next;
        delete temp;
        ctpost--; // Decrease the post count
        cout << "Post deleted successfully.\n";
        return;
    }

    // Traverse to the post before the one to delete
    Account::Post* prev = NULL;
    for (int i = 1; i < postnum; i++) {
        prev = temp;
        temp = temp->next;

        if (temp == NULL) { // If post number exceeds available posts
            cout << "Invalid post number.\n";
            return;
        }
    }

    // Delete the selected post
    prev->next = temp->next;
    delete temp;
    ctpost--; // Decrease the post count
    cout << "Post deleted successfully.\n";
}

//message
void insta::message(){
	if (loggedInIndex == -1) {
        cout << "Please log in to send messages.\n";
        return;
    }

    string Username, msg;
    cout << "Enter the username to message: ";
    cin >> Username;
    //check does that username exist
    for(int i=0; i<count;i++){
    if(Username == account[i].username){
    break;
	}else{
	//cout<<"Username does not exist"<<endl;
    return;
}
}
    cout << "Enter your message: ";
    cin.ignore();
    getline(cin, msg);

    ofstream file("messages.txt", ios::app);
    if (file.is_open()) {
        file << "From: " << account[loggedInIndex].username << " To: " << Username << "\nMessage: " << msg << "\n\n";
        file.close();
        cout << "Message sent successfully!\n";
    } else {
        cout << "Error sending message.\n";
    }
}

//view profile
void insta::viewprofile(){
	int choice;
	cout<<"\n1.My Profile";
	cout<<"\n2.Someone else Profile";
	cout<<"\nEnter your choice: ";
	cin>>choice;
	if(choice == 1){
		cout<<"\t\tMy Profile: "<<endl;
		cout<<"Name: "<<account[loggedInIndex].name <<endl;
		cout<<"Age: "<<account[loggedInIndex].age <<endl;
		cout<<"Date of birth: "<<account[loggedInIndex].dob <<endl;
		cout<<"Gender: "<<account[loggedInIndex].gender <<endl;
		cout<<"Following: "<<account[loggedInIndex].following <<endl;
		cout<<"Follower: "<<account[loggedInIndex].follower <<endl;
		cout<<"Rating: "<<account[loggedInIndex].rating <<endl;
		cout<<"\t\tPosts: "<<endl;
		account[loggedInIndex].showpost();
		return;
	}
	else if(choice == 2){
		string Username;
		cout<<"Enter username: ";
		cin>>Username;
	for(int i=0; i<count;i++){
    if(Username == account[i].username){
    	cout<<"\t\t"<<Username<< "Profile: "<<endl;
		cout<<"Name: "<<account[i].name <<endl;
		cout<<"Age: "<<account[i].age <<endl;
		cout<<"Date of birth: "<<account[i].dob <<endl;
		cout<<"Gender: "<<account[i].gender <<endl;
		cout<<"Following: "<<account[i].following <<endl;
		cout<<"Follower: "<<account[i].follower <<endl;
		cout<<"Rating: "<<account[i].rating <<endl;
		cout<<"\t\tPosts: "<<endl;
		account[i].showpost();
    return;
}
}
}
	else{
		cout<<"Not valid choice";
		return;
	}
}

//delete account
void insta::deleteaccount() {
    if (count == 0) {
        cout << "No accounts available to delete.\n";
        return;
    }
    string Username, Password;
    cout << "Enter username: ";
    cin >> Username;
    cout << "Enter Password: ";
    cin >> Password;
    for (int i = 0; i < count; i++) {
        if (Username == account[loggedInIndex].username && Password == account[loggedInIndex].password) {
            string confirmation;
            cout << "Are you sure you want to delete your account (yes or no): ";
            cin >> confirmation;
            if (confirmation == "no") {
                cout << "Account not deleted.\n";
                return;
            } 
			else if (confirmation == "yes") {
                // Shift accounts to remove the deleted one
                for (int j = i; j < count - 1; j++) {
                    account[j] = account[j + 1];
                }
                count--; // Decrease account count
                loggedInIndex = -1;
                cout << "Your account has been deleted successfully.\n";
                return;
            }
        }
    }
    cout << "Account not found.\n";
}

//Rate App
void insta::rateapp() {
    if (count == 0) {
        cout << "No accounts available to rate the app.\n";
        return;
    }
    string stars;
    cout << "Please give 5 stars(*) if you like this App: ";
    cin >> stars;
    if(loggedInIndex !=-1){
    if (stars == "*" || stars == "**" || stars == "***" || stars == "****" || stars == "*****") {
        account[loggedInIndex].rating = stars; // Use loggedInIndex to store rating
        cout << "Thanks for your feedback!\n";
        cout << "You gave: " << stars << endl;
    } else {
        cout << "Invalid rating. Please give a valid rating.\n";
    }
}
	else
	cout<<"phly login to kr shapper"<<endl;
}

//Log out
void insta::logout() {
    loggedInIndex = -1; // Reset the logged-in user index
    cout << "You have been logged out successfully.\n";
}

void introduction()
{
	
		cout<<"\n\t\t*******************************************";
		cout<<"\n\t\t*                                         *";
		cout<<"\n\t\t*        CLI BASED INSTAGRAM APP          *";
		cout<<"\n\t\t*                                         *";
		cout<<"\n\t\t*******************************************";
		cout<<"\n\t\t*******************************************";
		cout<<"\n\t\t *****************************************";
		cout<<"\n\t\t  ***************************************";
		cout<<"\n\n\t\t  Roll No.:                      23-CS-007";
		cout<<"\n\t\t  Student:                     Muhammad Huzaifa";
		cout<<"\n\n\t\t  Roll No.:                      23-CS-019";
		cout<<"\n\t\t  Student:                     Muhammad Ibrahim";
		cout<<"\n\n\t\t  Roll No.:                      23-CS-055";
		cout<<"\n\t\t  Student:                     Muhammad Awais";
		cout<<"\n\n\t\t  Roll No.:                      23-CS-035";
		cout<<"\n\t\t  Student:                     Matti-ur-rehman";
		cout<<"\n\n\t\t  Project:     Cli Based Instagram App    ";
		cout<<"\n\n\t\t          HITEC UNIVERSITY TAIXLA";
		cout<<"\n\n\t\t  ***************************************";
		cout<<"\n\t\t *****************************************";
		cout<<"\n\t\t*******************************************";
		cout<<"\nPress any key to see menu";
		getch();
	}
	
int main() {
    insta obj;
    introduction();
    system("cls");
    int choice;
    do {
        cout << "\n--- Instagram CLI Menu ---\n";
        cout << "1. Create Account\n";
        cout << "2. Login\n";
        cout << "3. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                obj.createaccount();
                break;
            case 2:
                obj.login();
                break;
            case 3:
                cout << "Exiting the app. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.";
                break;
        }
    }while(choice!=3);
}
