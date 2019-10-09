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

int main(){

  // Prepare email object
  EmailNotification notify;

  // Send Missing Emails
  getRecipients class1("416927.txt");
  notify.sendEmail(class1.returnRecipients(), "TOTD.txt");
  notify.sendEmail(class1.returnRecipients(), "IdealPlan.txt");
  notify.sendEmail(class1.returnRecipients(), "Regurgitate.txt");
  notify.sendEmail(class1.returnRecipients(), "Timing.txt");
  notify.sendEmail(class1.returnRecipients(), "Glycolysis.txt");
  notify.sendEmail(class1.returnRecipients(), "ICCTechniques.txt");
  notify.sendEmail(class1.returnRecipients(), "HowToMakeProtein.txt");
  notify.sendEmail(class1.returnRecipients(), "Location.txt");
  notify.sendEmail(class1.returnRecipients(), "TextResources.txt");


//Test Case
/*
stringstream ss;
ss << "\' --mail-rcpt \'" << "jdong56@uwo.ca";
notify.sendEmail( ss.str(), "FlashCards.txt");
*/

return 0;
}
