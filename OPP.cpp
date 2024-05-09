// Operator Precedence Parser


// Grammar is :

    //S -> id = E
    //E -> E+E | E-E | E*E | E/E | E^E | (E) | id | intlit | fllit



#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<stack>
using namespace std;

void takeInput(vector<string>&input){
    cout<<"pls enter the size of the input string: "<<endl;
    int n;
    cin>>n;
    cout<<"Pls enter the input string: "<<endl;
    for(int i=0;i<n;i++){
        string temp;
        cin>>temp;
        input.push_back(temp);
    }
    return;
}

void printstack(stack<string> temp){

    stack<string> temp1;
    while(!temp.empty()){
        temp1.push(temp.top());
        temp.pop();
    }

    while(!temp1.empty()){
        cout<<temp1.top();
        temp.push(temp1.top());
        temp1.pop();
    }

    cout<<"\t\t\t";
    return;
}

bool OPP(vector<string>input){
    //Grammer
    //S -> id = E
    //E -> E+E | E-E | E*E | E/E | E^E | (E) | id | intlit | fllit

    //Adding $ to the end of the input string
    input.push_back("$");

    //creating the operator precedence table

    //{stack_top,incomming} -> precedence
    map<vector<string>,string>OPP_table;

    OPP_table[{"+","+"}]=">";
    OPP_table[{"+","-"}]=">";
    OPP_table[{"+","*"}]="<";
    OPP_table[{"+","/"}]="<";
    OPP_table[{"+","^"}]="<";
    OPP_table[{"+","id"}]="<";
    OPP_table[{"+","intlit"}]="<";
    OPP_table[{"+","fllit"}]="<";
    OPP_table[{"+","("}]="<";
    OPP_table[{"+",")"}]=">";
    OPP_table[{"+","$"}]=">";
    OPP_table[{"+","="}]=">";

    OPP_table[{"-","+"}]=">";
    OPP_table[{"-","-"}]=">";
    OPP_table[{"-","*"}]="<";
    OPP_table[{"-","/"}]="<";
    OPP_table[{"-","^"}]="<";
    OPP_table[{"-","id"}]="<";
    OPP_table[{"-","intlit"}]="<";
    OPP_table[{"-","fllit"}]="<";
    OPP_table[{"-","("}]="<";
    OPP_table[{"-",")"}]=">";
    OPP_table[{"-","$"}]=">";
    OPP_table[{"-","="}]=">";

    OPP_table[{"*","+"}]=">";
    OPP_table[{"*","-"}]=">";
    OPP_table[{"*","*"}]=">";
    OPP_table[{"*","/"}]=">";
    OPP_table[{"*","^"}]="<";
    OPP_table[{"*","id"}]="<";
    OPP_table[{"*","intlit"}]="<";
    OPP_table[{"*","fllit"}]="<";
    OPP_table[{"*","("}]="<";
    OPP_table[{"*",")"}]=">";
    OPP_table[{"*","$"}]=">";
    OPP_table[{"*","="}]=">";

    OPP_table[{"/","+"}]=">";
    OPP_table[{"/","-"}]=">";
    OPP_table[{"/","*"}]=">";
    OPP_table[{"/","/"}]=">";
    OPP_table[{"/","^"}]="<";
    OPP_table[{"/","id"}]="<";
    OPP_table[{"/","intlit"}]="<";
    OPP_table[{"/","fllit"}]="<";
    OPP_table[{"/","("}]="<";
    OPP_table[{"/",")"}]=">";
    OPP_table[{"/","$"}]=">";
    OPP_table[{"/","="}]=">";

    OPP_table[{"^","+"}]=">";
    OPP_table[{"^","-"}]=">";
    OPP_table[{"^","*"}]=">";
    OPP_table[{"^","/"}]=">";
    OPP_table[{"^","^"}]="<";
    OPP_table[{"^","id"}]="<";
    OPP_table[{"^","intlit"}]="<";
    OPP_table[{"^","fllit"}]="<";
    OPP_table[{"^","("}]="<";
    OPP_table[{"^",")"}]=">";
    OPP_table[{"^","$"}]=">";
    OPP_table[{"^","="}]=">";

    OPP_table[{"id","+"}]=">";
    OPP_table[{"id","-"}]=">";
    OPP_table[{"id","*"}]=">";
    OPP_table[{"id","/"}]=">";
    OPP_table[{"id","^"}]=">";
    OPP_table[{"id","id"}]=">";
    OPP_table[{"id","intlit"}]=">";
    OPP_table[{"id","fllit"}]=">";
    OPP_table[{"id","("}]=">";
    OPP_table[{"id",")"}]=">";
    OPP_table[{"id","$"}]=">";
    OPP_table[{"id","="}]=">";

    OPP_table[{"intlit","+"}]=">";
    OPP_table[{"intlit","-"}]=">";
    OPP_table[{"intlit","*"}]=">";
    OPP_table[{"intlit","/"}]=">";
    OPP_table[{"intlit","^"}]=">";
    OPP_table[{"intlit","id"}]=">";
    OPP_table[{"intlit","intlit"}]=">";
    OPP_table[{"intlit","fllit"}]=">";
    OPP_table[{"intlit","("}]=">";
    OPP_table[{"intlit",")"}]=">";
    OPP_table[{"intlit","$"}]=">";
    OPP_table[{"intlit","="}]=">";

    OPP_table[{"fllit","+"}]=">";
    OPP_table[{"fllit","-"}]=">";
    OPP_table[{"fllit","*"}]=">";
    OPP_table[{"fllit","/"}]=">";
    OPP_table[{"fllit","^"}]=">";
    OPP_table[{"fllit","id"}]=">";
    OPP_table[{"fllit","intlit"}]=">";
    OPP_table[{"fllit","fllit"}]=">";
    OPP_table[{"fllit","("}]=">";
    OPP_table[{"fllit",")"}]=">";
    OPP_table[{"fllit","$"}]=">";
    OPP_table[{"fllit","="}]=">";

    OPP_table[{"(","+"}]="<";
    OPP_table[{"(","-"}]="<";
    OPP_table[{"(","*"}]="<";
    OPP_table[{"(","/"}]="<";
    OPP_table[{"(","^"}]="<";
    OPP_table[{"(","id"}]="<";
    OPP_table[{"(","intlit"}]="<";
    OPP_table[{"(","fllit"}]="<";
    OPP_table[{"(","("}]="<";
    OPP_table[{"(",")"}]="=";
    OPP_table[{"(","$"}]=">";
    OPP_table[{"(","="}]="<";

    OPP_table[{")","+"}]=">";
    OPP_table[{")","-"}]=">";
    OPP_table[{")","*"}]=">";
    OPP_table[{")","/"}]=">";
    OPP_table[{")","^"}]=">";
    OPP_table[{")","id"}]=">";
    OPP_table[{")","intlit"}]=">";
    OPP_table[{")","fllit"}]=">";
    OPP_table[{")","("}]=">";
    OPP_table[{")",")"}]=">";
    OPP_table[{")","$"}]=">";
    OPP_table[{")","="}]=">";
    
    OPP_table[{"$","+"}]="<";
    OPP_table[{"$","-"}]="<";
    OPP_table[{"$","*"}]="<";
    OPP_table[{"$","/"}]="<";
    OPP_table[{"$","^"}]="<";
    OPP_table[{"$","id"}]="<";
    OPP_table[{"$","intlit"}]="<";
    OPP_table[{"$","fllit"}]="<";
    OPP_table[{"$","("}]="<";
    OPP_table[{"$",")"}]=">";
    OPP_table[{"$","$"}]="=";
    OPP_table[{"$","="}]="<";
    
    OPP_table[{"=","+"}]=">";
    OPP_table[{"=","-"}]=">";
    OPP_table[{"=","*"}]=">";
    OPP_table[{"=","/"}]=">";
    OPP_table[{"=","^"}]=">";
    OPP_table[{"=","id"}]="<";
    OPP_table[{"=","intlit"}]="<";
    OPP_table[{"=","fllit"}]="<";
    OPP_table[{"=","("}]="<";
    OPP_table[{"=",")"}]=">";
    OPP_table[{"=","$"}]=">";
    OPP_table[{"=","="}]=">";

    //creating the stack
    stack<string> stack;
    stack.push("$");
    //string pointer
    int pointer=0;
    //lets parse the input string

    while(true){
        string stack_top=stack.top();
        string incoming_symbol=input[pointer];

        cout<<"stack_top: "<<stack_top<<"\t"<<"incoming_symbol: "<<incoming_symbol<<endl;

        cout<<"Stack\t\t\tInput"<<endl;
        printstack(stack);
       
        for(int i=pointer;i<input.size();i++){
            cout<<input[i];
        }
        cout<<endl;
       

        if(OPP_table.find({stack_top,incoming_symbol})==OPP_table.end()){
            return false;
        }

        //the case for accepting the string
        if(stack_top=="$" && incoming_symbol=="$"){
            return true;
        }

        string precedence=OPP_table[{stack_top,incoming_symbol}];

        if(precedence=="<"){
            stack.push(precedence);
            stack.push(incoming_symbol);
           
            pointer++;
        }else if(precedence==">"){
            string popped_symbol;
            while(true){
                popped_symbol=stack.top();
                stack.pop();
                if(popped_symbol=="<"){
                    break;
                }
            }
        }else if(precedence=="="){
            //this will never happen but stil masti
            stack.push(precedence);
            stack.push(incoming_symbol);
          
            pointer++;
        }
    }

    return false;
}

int main(){

    vector<string>input;
    takeInput(input);

    bool parsed= OPP(input);

    if(parsed){
        cout<<"The input string is parsed by the given grammar"<<endl;
    }else{
        cout<<"The input string is not parsed by the given grammar"<<endl;
    }

    return 0;   
}
