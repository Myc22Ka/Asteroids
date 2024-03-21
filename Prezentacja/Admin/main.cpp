#include "Formularz.h";
#include "Users.h";

int main(){
	Form form;
	
	form.getName();
	form.getPassword();
	form.getEmail();
	
	form.sentByPOSTMethod();

	Users users;

	users.getPhoneNumber();
	users.countMales();
	users.getFemaleURL();

	return 0;
}