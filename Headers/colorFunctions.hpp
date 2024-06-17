#define RESET   "\033[0m"
#define RED     "\033[31m"      
#define GREEN   "\033[32m"      
#define YELLOW  "\033[33m"      
#define BLUE    "\033[34m"      
#define MAGENTA "\033[35m"      
#define CYAN    "\033[36m"      

void print(string text, string color){
    if(color=="RED")
        cout<<RED<<text<<RESET;
    else if(color=="GREEN")
        cout<<GREEN<<text<<RESET;
    else if(color=="YELLOW")
        cout<<YELLOW<<text<<RESET;
    else if(color=="BLUE")
        cout<<BLUE<<text<<RESET;
    else if(color=="MAGENTA")
        cout<<MAGENTA<<text<<RESET;
    else if(color=="CYAN")
        cout<<CYAN<<text<<RESET;
    else
        cerr<<"Invalid color"<<endl;
}

void print(char text, string color){
    if(color=="RED")
        cout<<RED<<text<<RESET;
    else if(color=="GREEN")
        cout<<GREEN<<text<<RESET;
    else if(color=="YELLOW")
        cout<<YELLOW<<text<<RESET;
    else if(color=="BLUE")
        cout<<BLUE<<text<<RESET;
    else if(color=="MAGENTA")
        cout<<MAGENTA<<text<<RESET;
    else if(color=="CYAN")
        cout<<CYAN<<text<<RESET;
    else
        cerr<<"Invalid color"<<endl;
}