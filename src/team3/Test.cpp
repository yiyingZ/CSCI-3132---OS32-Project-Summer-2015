class Test{

  namespace std;

public:

  UI ui = new UI();
  Login login = new Login();

  Test::Test(){}
  Test::~Test(){}

  void Test::printlnTest(){
    ui->println("Testing UI println");
  }

  void Test::printTest(){
    ui->print("Testing UI print");
  }

  bool Test::testParse(){
    cout<<"Beginning parse test: Sending 'Test' comparing to 'Test'";    
if(strcmp (ui->parseCommand("Test"), "Test"== 0){
	return true;
      }
      else{
	return false;
      }
      }
      

void Test::testLoginName(){
	login->notlog == false;
	cout<<"Testing login attempt while logged in, expecting invalid login attempt";
	login->login();
	login->notlog == true;
	cout<<"Testing login attempt while not logged in, expecting normal function";
	login->login();
  }
  }
