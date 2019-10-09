/**
* \author Claire Dong
* Responsible for sending email notifications to gmail accounts
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>

using namespace std;

/**
* \name EmailNotification
* constructor for testing
* \param email - patient's email
* \param password - patient's email
* \param recipientEmail - emergency contact's email
*/
class EmailNotification{
      
    private:
      string senderEmail;
      string senderPassword;

    public: 
      EmailNotification(){
        senderEmail = "claire.dong5@gmail.com";
        senderPassword = "341395705";
      }

      /**
      * \name SendEmail
      * sends an email from the sender's address to the recipient's address, assumes the sender has a gmail account
      */
      void sendEmail(string recipientEmails, string emailTemplate){
        // curl needs a direct path to point to the email template
        emailTemplate = "~/Documents/TPR/autoEmail/templates/" + emailTemplate;
        
        // Command for email
        string command = 
          "curl --url \'smtps://smtp.gmail.com:465\' --ssl-reqd --mail-from \'" 
          + senderEmail
          + recipientEmails 
          + "\' --upload-file " + emailTemplate
          + " --user \'" + senderEmail + ":" + senderPassword + "\'";
        
        // system() expects a const char[]*
        const char* commandToChar = command.c_str();
        system(commandToChar);
        
        // Confirmation
        cout << "---------------------------------------" << endl;
        cout << "       -> Emails sent to";
      }
};

class getRecipients{
    private:
      stringstream allRecipients;

    public:
      // Concatenates recipient list
      getRecipients(string recipientFile){

        // Open file
        string file = "contacts/" + recipientFile;
        ifstream infile(file);
        string line;
        
        // Discard header of file
        getline(infile, line);
        getline(infile, line);
        
        // Concatenate all email recipients
        while (getline(infile, line)){
            allRecipients << "\' --mail-rcpt \'" << line;
        }
      }

      // Returns recipient list
      string returnRecipients(){
        return allRecipients.str();

      }
};

// Gets time in format of month/date 
string getTime(){
  
  time_t t = std::time(0);   
  tm* now = std::localtime(&t);
  return to_string(now->tm_mon + 1) + '/' + to_string(now->tm_mday);
}

int main(){

  // Get current date and prepare email object
  string currentTime = getTime();
  EmailNotification notify;

  // Grab all recipient classes
  getRecipients class1("413207.txt");
  getRecipients class2("413211.txt");
  getRecipients class3("435596.txt");
  getRecipients class4("413218.txt");
  getRecipients class5("435675.txt");
  getRecipients class6("416927.txt");
  getRecipients class7("417385.txt");
  getRecipients class8("417821.txt");

  // Parse schedule
  string line;
  string token;
  int i = 0; 

  // Open file and discard header
  ifstream infile("schedule.txt");
  getline(infile, line);
  getline(infile, line);

  // Read schedule line by line
  while (getline(infile, line)){

    // Find current day
    stringstream ss(line, stringstream::in);
    ss >> token;
    if (currentTime == token){
    
      // Send relevant email to each class
      while (ss >> token){
        i++;

        // Make sure there is an email to send
        if (token != "NULL"){
        
          // Find class and send email
          switch (i){
            case 1:
              notify.sendEmail(class1.returnRecipients(), token);
              cout << " 413207 (Erindale 9-12pm) containing: " << token << endl;
              cout << "---------------------------------------" << endl;
              break;
            
            case 2:
              notify.sendEmail(class2.returnRecipients(), token);
              cout << " 413211 (Alberta 11-2pm) containing: " << token << endl;
              cout << "---------------------------------------" << endl;
              break;
            
            case 3:
              notify.sendEmail(class3.returnRecipients(), token);
              cout << " 435596 (Online 2-5pm/6-9pm) containing: " << token << endl;
              cout << "---------------------------------------" << endl;
              break;

            case 4:
              notify.sendEmail(class4.returnRecipients(), token);
              cout << " 413218 (Erindale 9-12pm) containing: " << token << endl;
              cout << "---------------------------------------" << endl;
              break;

            case 5:
              notify.sendEmail(class5.returnRecipients(), token);
              cout << " 435675 (Online 7pm-10pm) containing: " << token << endl;
              cout << "---------------------------------------" << endl;
              break;

            case 6:
              notify.sendEmail(class6.returnRecipients(), token);
              cout << " 416927 containing: " << token << endl;
              cout << "---------------------------------------" << endl;
              break;

            case 7:
              notify.sendEmail(class7.returnRecipients(), token);
              cout << " 417385 containing: " << token << endl;
              cout << "---------------------------------------" << endl;
              break;

            case 8:
              notify.sendEmail(class8.returnRecipients(), token);
              cout << " 417821 (St. Louis 11-2pm) containing: " << token << endl;
              cout << "---------------------------------------" << endl;
              break;
          }
        }
      }
    }
} 

//Test Case
/*
stringstream ss;
ss << "\' --mail-rcpt \'" << "jdong56@uwo.ca";
notify.sendEmail( ss.str(), "FlashCards.txt");
*/

return 0;
}
